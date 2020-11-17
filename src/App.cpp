#include "../include/App.h"
#include "../include/Display.h"
#include "../include/Rasteriser.h"
#include <math.h>
#include <SDL_stdinc.h>

#define SCREEN_TEST 0
App::App() :
    _rasteriser(nullptr),
    _display(nullptr),
    _quit(false)
{

}

App::~App()
{
    //shutdown();
}

void App::init() {
    _display = std::make_shared<Display>(1600, 1200, "Software Renderer");
    _rasteriser = std::make_unique<Rasteriser>(_display);

}

void App::update() {
#if SCREEN_TEST
    int x = std::rand() % _display->getWidth();
    int y = std::rand() % _display->getHeight();
    int r = std::rand() % 255;
    int g = std::rand() % 255;
    int b = std::rand() % 255;
    _display->drawPixel(x, y, r, g, b, 254);
#endif
    
}

void App::draw() {
    _display->update();
}

void App::shutdown() {
    //delete _display;
    //delete _raytracer;
}

