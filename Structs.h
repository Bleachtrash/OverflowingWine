#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#ifndef STRUCTS_H
#define STRUCTS_H
struct Vector2
{
    float x;
    float y;
};

struct Vector2_int
{
    int x;
    int y;
};


struct Object
{
    Vector2 Position;
    Vector2 Scale;
    SDL_Color Color;
};

struct Image
{
    private:
        SDL_Surface *Image_Surface;
        SDL_Texture *Image_Texture;
    public:
        char* image_file;
        SDL_Surface *Get_Surface()
        {
            return Image_Surface;
        }
        SDL_Texture *Get_Texture()
        {
            return Image_Texture;
        }
        void Init(SDL_Renderer *renderer)
        {
            Image_Surface = IMG_Load(image_file);
            Image_Texture = SDL_CreateTextureFromSurface(renderer, Image_Surface);
            SDL_FreeSurface(Image_Surface);
        }
};

struct Button
{
    Object object; // Button Object
    Image image; // Button Image
    void *On_Press; //Function that triggers on press
};

struct NameTag
{
    
    private:
        TTF_Font *font;

    public:
        Object object;
        char* Name;
        int size;
        SDL_Surface *Text_Surface;
        SDL_Texture *Text_Texture;
        char* font_file;
        SDL_Color font_color;

        void Update(SDL_Renderer *renderer)
        {
            font = TTF_OpenFont(font_file, size);
            Text_Surface = TTF_RenderText_Solid(font, Name, font_color);
            Text_Texture = SDL_CreateTextureFromSurface(renderer, Text_Surface);
            SDL_FreeSurface(Text_Surface);
        }
        SDL_Rect Get_Textbox()
        {
            return {object.Position.x + 100, object.Position.y + 50, Text_Surface->w, Text_Surface->h};
        }

};

struct Textbox
{
    public:
        Button box;
        char* font_file;
        SDL_Color font_color;
        int size;
        std::string text;
        NameTag Speaker;
        SDL_Surface *Text_Surface;
        SDL_Texture *Text_Texture;
        std::string display_text = " ";
        TTF_Font *font;

        void Next_Textbox(SDL_Renderer *renderer)
        {
            font = TTF_OpenFont(font_file, size);
            display_text = "";
            display_text += text[0];
            Text_Surface = TTF_RenderText_Solid(font, display_text.c_str(), font_color);
            Text_Texture = SDL_CreateTextureFromSurface(renderer, Text_Surface);
            SDL_FreeSurface(Text_Surface);
        }
        void Update_Textbox(SDL_Renderer *renderer)
        {
            if(display_text == text)
            {
                return;
            }

            display_text = text.substr(0, display_text.size()+1);
            Text_Surface = TTF_RenderText_Solid(font, display_text.c_str(), font_color);
            Text_Texture = SDL_CreateTextureFromSurface(renderer, Text_Surface);
            SDL_FreeSurface(Text_Surface);
        }
        SDL_Rect Get_Textbox()
        {
            return {box.object.Position.x + 100, box.object.Position.y + 50, Text_Surface->w, Text_Surface->h};
        }
};
#endif