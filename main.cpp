#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Structs.h"
#include "Functions.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("Overflowing Wine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 800, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Event event;

    SDL_Surface *Icon = IMG_Load("./Media/Images/Icon.jpg");
    SDL_SetWindowIcon(window, Icon);

    // Button Test_Button = Create_Button(Object{{300, 550}, {1000, 200}}, Create_Image(renderer, "./Media/Button.png"));
    // Test_Button.On_Press = reinterpret_cast<void*>(&Print_Thing);

    NameTag speaker = Create_Nametag(Object{{0, 0}, {300, 25}, {120, 120, 120, 200}}, "./Media/Fonts/TypeWheel/TypeWheel.ttf", SDL_Color{255, 255, 255}, 20, "YOU");

    Textbox Texbox = Create_Textbox(Create_Button(Object{{300, 550}, {1000, 200}, {120, 120, 120, 200}}), speaker, "./Media/Fonts/TypeWheel/TypeWheel.ttf", SDL_Color{255, 255, 255}, 25, "THIS IS SO COOL!!");
    Texbox.box.On_Press = reinterpret_cast<void*>(&Reset_Textbox);

    Texbox.Reset_Textbox(renderer);
    
    int Text_Render_Speed = 20;
    Vector2_int MousePos;
    bool mouse_click = false;

    bool quit = false;

    Image Background;
    std::vector<ButtonImage> Characters;
    std::fstream Script;
    Change_Script(&Script, "./Media/Scripts/Script1.txt");

    Set_Scene(renderer, &Script, &Texbox, &Background, &Characters);

    Uint32 NOW = SDL_GetTicks();
    Uint32 LAST = 0;
    float deltatime = 0;
    Uint32 Last_Text_Render = 0;
    while(!quit)
    {
        LAST = NOW;
        NOW = SDL_GetTicks();
        deltatime = (float)(NOW - LAST) / 1000;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_GetMouseState(&MousePos.x, &MousePos.y);

        if(NOW - Last_Text_Render >= Text_Render_Speed)
        {
            Texbox.Update_Textbox(renderer);
            Last_Text_Render = NOW;
        }

        Render_Image(renderer, Background, {0, 0}, {2600, 800});

        for(int i = 0; i < Characters.size(); i++)
        {
            Render_ButtonImage(renderer, Characters[i]);
        }
        Render_Textbox(renderer, &Texbox);

        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_click = !mouse_click;
                if(PointCollide(Texbox.box.object, MousePos) && mouse_click)
                {
                    if(Texbox.display_text != Texbox.text)
                    {
                        Texbox.display_text = Texbox.text;
                    }
                    else
                    {
                        Set_Scene(renderer, &Script, &Texbox, &Background, &Characters);
                        Text_Render_Speed = 20;
                        callFunction<void>(Texbox.box.On_Press, renderer, &Texbox);
                    }
                    Last_Text_Render = NOW;
                }
                else{
                    for(int i = 0; i < Characters.size(); i++)
                    {
                        if(PointCollide(Characters[i].button.object, MousePos) && mouse_click && Characters[i].Script_Path != " ")
                        {
                            // callFunction<void>(Characters.at(i).button.On_Press, &Script, Characters[i].Script_Path);
                            // std::cout << Characters.at(i).Script_Path << std::endl;
                            Change_Script(&Script, Characters[i].Script_Path);
                            Set_Scene(renderer, &Script, &Texbox, &Background, &Characters);
                        }
                    }
                }
            }
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
                {
                    if(Texbox.display_text != Texbox.text)
                    {
                        Texbox.display_text = Texbox.text;
                    }
                    else
                    {
                        Set_Scene(renderer, &Script, &Texbox, &Background, &Characters);
                        Text_Render_Speed = 20;
                        callFunction<void>(Texbox.box.On_Press, renderer, &Texbox);
                    }
                    Last_Text_Render = NOW;
                }
            }
        }
        
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}