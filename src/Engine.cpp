#include "../include/Engine.h"
#include "../include/Display.h"
#include "../include/Rasteriser.h"
#include <math.h>
#include <SDL_stdinc.h>

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
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    _display = std::make_shared<Display>(display_mode.w, display_mode.h, "Software Renderer");
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
    //_rasteriser->drawGrid();
    //_rasteriser->drawRectangle(600, 200, 400, 150, 0xFF7FFFD4);
    _rasteriser->projectionTest();
}

void Engine::render() {
    _display->update();
}

void Engine::shutdown() {
    //delete _display;
    //delete _raytracer;
}

