#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

#ifdef _WIN32
#include <windows.h>
#include <d3d9.h>
#endif

class CRenderer
{
private:
    SDL_Window* window;

    SDL_GLContext glContext;

    #ifdef _WIN32
    HWND windowHandle;

    IDirect3D9* d3d9;
    IDirect3DDevice9* device;
    #endif
public:
    CRenderer() { };
    CRenderer(SDL_Window* w);
    ~CRenderer();

    void Clear();
    void Present();
};


#endif