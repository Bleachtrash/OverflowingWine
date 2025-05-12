#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Structs.h"
#include "Functions.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("Buttons", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 800, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Event event;

    // Button Test_Button = Create_Button(Object{{300, 550}, {1000, 200}}, Create_Image(renderer, "./Media/Button.png"));
    // Test_Button.On_Press = reinterpret_cast<void*>(&Print_Thing);

    NameTag Speaker = Create_Nametag(Object{{0, 0}, {100, 25}, {255, 255, 255, 10}}, "./Media/Fonts/Vividly-Regular.ttf", SDL_Color{255, 255, 255}, 20, "YOU");
    Speaker.Update(renderer);
    Textbox Test_Texbox = Create_Textbox(Create_Button(Object{{300, 550}, {1000, 200}, {255, 255, 255, 10}}, Create_Image(renderer, "./Media/Images/Button.png")), "./Media/Fonts/Vividly-Regular.ttf", SDL_Color{255, 255, 255}, 50, "THIS IS SO COOL!!", Speaker);
    Test_Texbox.box.On_Press = reinterpret_cast<void*>(&Next_Textbox);
    Test_Texbox.Next_Textbox(renderer);
    int Text_Render_Speed = 100;
    Vector2_int MousePos;
    bool mouse_click = false;

    bool quit = false;

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
            Test_Texbox.Update_Textbox(renderer);
            Last_Text_Render = NOW;
        }

        Render_Textbox(renderer, Test_Texbox);

        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_click = !mouse_click;
                if(PointCollide(Test_Texbox.box.object, MousePos) && mouse_click)
                {
                    if(Test_Texbox.display_text != Test_Texbox.text)
                    {
                        Text_Render_Speed = 0;
                    }
                    else
                    {
                        Text_Render_Speed = 100;
                        Test_Texbox.text = "LOOK AT ME!!! I'M DIFFERENT NOW!";
                        callFunction<void>(Test_Texbox.box.On_Press, renderer, &Test_Texbox);
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