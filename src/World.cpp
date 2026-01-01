#include "Main.h"
#include <Renderer.h>
#include <SDL3/SDl.h>
#include <iostream>
#include <memory>

extern SDL_Window* window;

std::unique_ptr<CRenderer> renderer;

void InitWorld()
{
    renderer = std::make_unique<CRenderer>(window);
}

void RenderWorld(float deltaTime)
{
    renderer->Clear();
    renderer->Present();
}

void FreeWorld()
{

}