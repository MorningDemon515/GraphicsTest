#include "Renderer.h"
#include "../glad.h"
#include "../Main.h"

extern int s_renderer;

CRenderer::CRenderer(SDL_Window* w) : window(w)
{
    glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    #ifdef _WIN32

    SDL_PropertiesID props;
    props = SDL_GetWindowProperties(window);
    windowHandle = static_cast<HWND>(SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL));
    SDL_DestroyProperties(props);
    
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
    d3dpp.Windowed = true;
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
}

CRenderer::~CRenderer()
{
    SDL_GL_DestroyContext(glContext);

    #ifdef _WIN32
    d3d9->Release();
    device->Release();
    #endif
}

void CRenderer::Present()
{
    
    if (s_renderer == 1)
    {
    #ifdef _WIN32
        device->Present(0, 0 ,0 ,0);
    #endif
    }
    else
    {
        SDL_GL_SwapWindow(window);
    }
    
}

void CRenderer::Clear()
{
    if(s_renderer == 1)
    {
        device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 0), 1.0f, 0);
    }
    else
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}