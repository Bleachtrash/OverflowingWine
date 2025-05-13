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
    void *On_Press; //Function that triggers on press
};

struct ButtonImage
{
    Button button;
    Image image;
    std::string Script_Path;
};

struct NameTag
{
    Object object;
    char* font_file;
    SDL_Color font_color;
    int size;
    std::string Text;
    SDL_Surface *Text_Surface;
    SDL_Texture *Text_Texture;
};

struct Textbox
{
    Button box;
    int style;
    NameTag Speaker;
    char* font_file;
    SDL_Color font_color;
    int size;
    std::string text;
    SDL_Surface *Text_Surface;
    SDL_Texture *Text_Texture;
    std::string display_text = " ";

    void Reset_Textbox(SDL_Renderer *renderer)
    {
        display_text = "";
        display_text += text[0];
    }
    void Update_Textbox(SDL_Renderer *renderer)
    {
        if(display_text == text)
        {
            return;
        }
        display_text = text.substr(0, display_text.size()+1);
    }
};
#endif