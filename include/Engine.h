#pragma once

#include <memory>

class Display;
class Rasteriser;

class Engine
{
private:
    std::unique_ptr<Rasteriser> _rasteriser;
    std::shared_ptr<Display> _display;
    bool _is_running;
public:
    Engine();
    ~Engine();
    void init();
    bool isRunning();
    void processInput();
    void update();
    void render();
    void shutdown();
};
