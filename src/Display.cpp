#include "../include/Display.h"



Display::Display(long long width, long long height, std::string title):
    _pixel_buffer(nullptr),
    _width(width),
    _height(height),
    _title(title),
    _SDL_renderer(nullptr, &SDL_DestroyRenderer),
    _frame_texture(nullptr, &SDL_DestroyTexture),
    _window(nullptr, &SDL_DestroyWindow)
{
    _window.reset(SDL_CreateWindow(
                _title.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                _width,
                _height,
                SDL_WINDOW_OPENGL
                ));
    _SDL_renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));
    _frame_texture.reset(SDL_CreateTexture(_SDL_renderer.get(), SDL_PIXELFORMAT_ARGB8888,
                                       SDL_TEXTUREACCESS_STREAMING, _width, _height));

    SDL_SetRenderDrawBlendMode(_SDL_renderer.get(), SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(_frame_texture.get(), SDL_BLENDMODE_BLEND);


    _pixel_buffer.reset(new Uint32[_width * _height]);
    memset(_pixel_buffer.get(), 0x00000000, _width * _height * sizeof(Uint32));

}

void Display::drawPixel(int x, int y, Uint32 colour) {
    if (x >= _width || y >= _height) {
        return;
    }
    if (x < 0 || y < 0) {
        return;
    }

    _pixel_buffer.get()[y * _width + x] = colour;
}

void Display::drawPixel(int x, int y, int r, int g, int b, int a) {
    Uint32 colour = (Uint8) a;
    colour <<= 8;
    colour |= (Uint8) r;
    colour <<= 8;
    colour |= (Uint8) g;
    colour <<= 8;
    colour |= (Uint8) b;
    drawPixel(x, y, colour);
}

void Display::update() {
    SDL_UpdateTexture(_frame_texture.get(), NULL, _pixel_buffer.get(),
                      _width * sizeof(Uint32));

    SDL_RenderCopy(_SDL_renderer.get(), _frame_texture.get(), NULL, NULL);
    SDL_RenderPresent(_SDL_renderer.get());
    memset(_pixel_buffer.get(), 0x00000000, _width * _height * sizeof(Uint32));
}

int Display::getWidth() {
    return _width;
}

int Display::getHeight() {
    return _height;
}
Display::~Display() {
    //std::cout << "Display - Shutdown" << std::endl;
    //SDL_DestroyTexture(_frame_texture);
   // delete[] _pixel_buffer;
    //SDL_DestroyRenderer(_SDL_renderer);
    //SDL_DestroyWindow(_window);
}