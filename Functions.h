#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>

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

NameTag Create_Nametag(Object obj, char* file, SDL_Color color, int size, std::string text)
{
    NameTag out;
    out.object = obj;
    out.font_file = file;
    out.font_color = color;
    out.size = size;
    out.Text = text;

    return out;
}

void Render_NameTag(SDL_Renderer *renderer, NameTag *Name)
{
    TTF_Font *tempFont = TTF_OpenFont(Name->font_file, Name->size);
    TTF_SetFontStyle(tempFont, TTF_STYLE_BOLD);
    Name->Text_Surface = TTF_RenderText_Solid(tempFont, Name->Text.c_str(), Name->font_color);
    Name->Text_Texture = SDL_CreateTextureFromSurface(renderer, Name->Text_Surface);

    SDL_Rect Dest = {Name->object.Position.x + 10, Name->object.Position.y + 5, Name->Text_Surface->w, Name->Text_Surface->h};

    SDL_RenderCopy(renderer, Name->Text_Texture, nullptr, &Dest);
    SDL_FreeSurface(Name->Text_Surface);
    SDL_DestroyTexture(Name->Text_Texture);
    TTF_CloseFont(tempFont);

    Render_Object(renderer, Name->object);
}

Textbox Create_Textbox(Button box, NameTag Speaker, char* file, SDL_Color color, int size, std::string text)
{
    Textbox out;
    out.box = box;
    out.font_file = file;
    out.font_color = color;
    out.size = size;
    out.text = text;
    Speaker.object.Position = box.object.Position;
    Speaker.object.Position.y -= Speaker.object.Scale.y;
    out.Speaker = Speaker;

    return out;
}

void Render_Textbox(SDL_Renderer *renderer, Textbox *textbox)
{
    TTF_Font *tempFont = TTF_OpenFont(textbox->font_file, textbox->size);
    TTF_SetFontStyle(tempFont, textbox->style);
    textbox->Text_Surface = TTF_RenderText_Solid_Wrapped(tempFont, textbox->display_text.c_str(), textbox->font_color, textbox->box.object.Scale.x - 20);
    textbox->Text_Texture = SDL_CreateTextureFromSurface(renderer, textbox->Text_Surface);
    SDL_Rect Dest = {textbox->box.object.Position.x + 20, textbox->box.object.Position.y + 20, textbox->Text_Surface->w, textbox->Text_Surface->h};

    SDL_RenderCopy(renderer, textbox->Text_Texture, nullptr, &Dest);
    SDL_FreeSurface(textbox->Text_Surface);
    SDL_DestroyTexture(textbox->Text_Texture);
    TTF_CloseFont(tempFont);
    Render_Button(renderer, textbox->box);

    Render_NameTag(renderer, &textbox->Speaker);
}

void Set_Textbox(std::fstream *File, Textbox *Textbox)
{
    std::string Name, Style, Text;
    std::getline(*File, Name);
    std::getline(*File, Style);
    std::getline(*File, Text);
    Textbox->Speaker.Text = Name;
    Textbox->text = Text;
    Textbox->style = (int)(Style[0]) - 48;
}

void Reset_Textbox(SDL_Renderer *renderer, Textbox *textbox)
{
    (*textbox).Reset_Textbox(renderer);
}

#endif