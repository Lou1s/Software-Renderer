#include "../include/Engine.h"
#include "../include/Display.h"
#include "../include/Rasteriser.h"
#include <math.h>
#include <SDL_stdinc.h>

#define SCREEN_TEST 0
Engine::Engine() :
    _rasteriser(nullptr),
    _display(nullptr),
    _is_running(false)
{

}

Engine::~Engine()
{
    //shutdown();
}

void Engine::init() {
    _display = std::make_shared<Display>(1600, 1200, "Software Renderer");
    _rasteriser = std::make_unique<Rasteriser>(_display);
    _is_running = true;
}

bool Engine::isRunning() {
    return _is_running;
}

void Engine::processInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch (event.type)
    {
    case SDL_QUIT:
        _is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            _is_running = false;
        }

    }
}

void Engine::update() {
#if SCREEN_TEST
    int x = std::rand() % _display->getWidth();
    int y = std::rand() % _display->getHeight();
    int r = std::rand() % 255;
    int g = std::rand() % 255;
    int b = std::rand() % 255;
    _display->drawPixel(x, y, r, g, b, 254);
#endif
    
}

void Engine::render() {
    _display->update();
}

void Engine::shutdown() {
    //delete _display;
    //delete _raytracer;
}

