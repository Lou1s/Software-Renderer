#pragma once

#include <memory>

class Display;
class Rasteriser;

class App
{
private:
    std::unique_ptr<Rasteriser> _rasteriser;
    std::shared_ptr<Display> _display;
    bool _quit;
public:
    App();
    ~App();
    void init();
    void update();
    void draw();
    void shutdown();
};
