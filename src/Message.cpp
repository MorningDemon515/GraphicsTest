#include "Message.h"
#include <SDL3/SDL.h>

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