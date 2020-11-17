#include <iostream>
#include "../include/App.h"
#include<SDL.h>
#undef main

int main()
{
    bool quit = false;
    SDL_Event event;
    auto app = std::make_unique<App>();
    app->init();



    while (!quit)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
        app->update();
        app->draw();

    }
    app->shutdown();
    return 0;

}
