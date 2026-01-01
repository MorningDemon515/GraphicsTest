#include "Main.h"
#include <iostream>
#include <SDL3/SDL.h>

SDL_Window* window;
SDL_Event event;

int s_renderer = 0;

void InitWorld();
void RenderWorld(float deltaTime);
void FreeWorld();

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    int w = 800, h = 600;
/*
    std::cout << "Enter Window Width And Height" << std::endl;
    std::cout << "Width: ";
    std::cin >> w;
    std::cout << "Height: ";
    std::cin >> h;
*/    


    #ifdef _WIN32
    std::cout << "Enter Renderer: "; //0 : OpenGL; 1 : Direct3D 9
    std::cin >> s_renderer;
    if(s_renderer != 0 && s_renderer != 1)
    {
        ErrorMsg("Unkonw Renderer!");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    std::cout << "Current Renderer: ";
    if(s_renderer == 1)
    {
        std::cout << "Direct3D 9" << std::endl;
    }
    else
    {
        std::cout << "OpenGL" << std::endl;
    }
    #endif
    
    window = SDL_CreateWindow(
        "GraphicsTest",
        w, h,
        SDL_WINDOW_OPENGL
    );

    InitWorld();
    
    static float lastTime = (float)SDL_GetTicks(); 
    while (1)
    {
        SDL_PollEvent(&event);

        if(event.type == SDL_EVENT_QUIT)
            break;

        float currTime  = (float)SDL_GetTicks();
		float timeDelta = (currTime - lastTime)*0.001f;

        RenderWorld(timeDelta);

        lastTime = currTime;
    }

    FreeWorld();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

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

void ErrorMsg(const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Engine Error!", message, NULL);
}

void Message(const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Engine Message", message, NULL);
}

void WarnMsg(const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Engine Warning!", message, NULL);
}