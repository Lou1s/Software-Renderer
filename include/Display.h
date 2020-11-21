#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>

#include "SDL.h"
#undef main

class Display
{
public:
    Display(long long width, long long height, std::string title); //used long long to get rid of MVS "overflow warning" that occurs when they are ints...bug?
    ~Display();
    void update();
    void drawPixel(int x, int y, Uint32 colour);
    void drawPixel(int x, int y, int r, int g, int b, int a);
    int getHeight();
    int getWidth();
private:
    std::unique_ptr<Uint32> _pixel_buffer;
    long long _width;
    long long _height;
    std::string _title;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _SDL_renderer;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _frame_texture;

};

#endif // DISPLAY_H