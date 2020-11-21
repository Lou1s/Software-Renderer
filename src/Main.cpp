#include <iostream>
#include "../include/Engine.h"
#include<SDL.h>
#undef main

int main()
{
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    engine->init();

    while (engine->isRunning())
    {
        engine->processInput();
        engine->update();
        engine->render();

    }
    engine->shutdown();
    return 0;

}
