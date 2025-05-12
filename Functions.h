#include <SDL.h>
#include <iostream>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template<class ReturnType, class... Ts>
ReturnType callFunction(void *function, const Ts&... args)
{	
	return reinterpret_cast<ReturnType(*)(Ts...)>(function)(args...);
}

void Print_Thing(std::string thing)
{
    std::cout << thing << std::endl;
}

bool PointCollide(Object a, Vector2_int point)
{
    if(point.x > a.Position.x && point.x < a.Position.x + a.Scale.x && point.y > a.Position.y && point.y < a.Position.y + a.Scale.y)
    {
        return true;
    }
    return false;
}


void Render_Object(SDL_Renderer *renderer, Object a)
{
    SDL_Rect temp;
    temp.w = a.Scale.x;
    temp.h = a.Scale.y;
    temp.x = a.Position.x;
    temp.y = a.Position.y;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, a.Color.r, a.Color.g, a.Color.b, a.Color.a);
    SDL_RenderFillRect(renderer, &temp);
}

Image Create_Image(SDL_Renderer *renderer, char* file)
{
    Image out;
    out.image_file = file;
    out.Init(renderer);
    return out;
}

void Render_Image(SDL_Renderer *renderer, Image image, Vector2 pos, Vector2 scale)
{
    SDL_Rect Dest;
    Dest.x = pos.x;
    Dest.y = pos.y;
    Dest.w = scale.x;
    Dest.h = scale.y;
    SDL_RenderCopy(renderer, image.Get_Texture(), nullptr, &Dest);
}

Button Create_Button(Object obj, Image img)
{
    Button out;
    out.object = obj;
    out.image = img;
    return out;
}

void Render_Button(SDL_Renderer *renderer, Button button)
{
   Render_Object(renderer, button.object);
}

NameTag Create_Nametag(Object obj, char* file, SDL_Color color, int size, char* Name)
{
    NameTag out;
    out.object = obj;
    out.font_file = file;
    out.font_color = color;
    out.size = size;
    out.Name = Name;
    return out;
}

void Render_Nametag(SDL_Renderer *renderer, NameTag a)
{
    SDL_Rect Dest = a.Get_Textbox();
    // Render_Object(renderer, a.object);
    SDL_RenderCopy(renderer, a.Text_Texture, nullptr, &Dest);
}

Textbox Create_Textbox(Button box, char* file, SDL_Color color, int size, std::string text, NameTag Speaker)
{
    Textbox out;
    out.box = box;
    out.font_file = file;
    out.font_color = color;
    out.size = size;
    out.text = text;
    out.Speaker = Speaker;

    return out;
}

void Render_Textbox(SDL_Renderer *renderer, Textbox textbox)
{
    SDL_Rect Dest = textbox.Get_Textbox();
    textbox.Speaker.object.Position = textbox.box.object.Position;
    textbox.Speaker.object.Position.y -= textbox.Speaker.object.Scale.y;
    
    // Render_Button(renderer, textbox.box);
    // SDL_RenderCopy(renderer, textbox.Text_Texture, nullptr, &Dest);
    Render_Nametag(renderer, textbox.Speaker);
}

void Next_Textbox(SDL_Renderer *renderer, Textbox *textbox)
{
    (*textbox).Next_Textbox(renderer);
}

#endif