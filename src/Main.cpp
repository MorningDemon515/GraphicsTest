#include <iostream>
#include <SDL3/SDL.h>
#include "Window.h"
#include "glad.h"
#include "Message.h"

#ifdef _WIN32
#include <windows.h>
#include <d3d9.h>
#endif

SDL_Window* window;
SDL_Event event;

int s_renderer = 0;

#ifdef _WIN32
HWND windowHandle;

IDirect3D9* d3d9;
IDirect3DDevice9* device;
#endif

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

/*
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
    #endif
*/
    window = SDL_CreateWindow(
        "GraphicsTest",
        w, h,
        SDL_WINDOW_OPENGL
    );

    SDL_PropertiesID props;
    props = SDL_GetWindowProperties(window);
    windowHandle = static_cast<HWND>(SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL));

    SDL_GLContext glContext;
    glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    #ifdef _WIN32
    
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    d3dpp.BackBufferWidth = GetWindowWidth();
    d3dpp.BackBufferHeight = GetWindowHeight();
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 
    d3dpp.hDeviceWindow = windowHandle;
    d3dpp.EnableAutoDepthStencil = true; 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL,   
		windowHandle,    
		D3DCREATE_HARDWARE_VERTEXPROCESSING,      
	    &d3dpp,   
	    &device);       

    #endif

    while (1)
    {
        SDL_PollEvent(&event);

        if(event.type == SDL_EVENT_QUIT)
            break;

        if(s_renderer == 1)
        {
            #ifdef _WIN32
            device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255,0), 1.0f, 0);

            device->Present(0, 0, 0, 0);

            #endif
        }
        else
        {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            SDL_GL_SwapWindow(window);
        }
    }
    
    #ifdef _WIN32
    d3d9->Release();
    device->Release();
    #endif
    SDL_DestroyProperties(props);
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}