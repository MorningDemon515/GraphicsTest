#include "Window.h"
#include <SDL3/SDL.h>

extern SDL_Window* window;

int GetWindowWidth()
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return w;
}

int GetWindowHeight()
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return h;
}