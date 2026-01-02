#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// globals
SDL_Window *window;
SDL_Surface *cat;

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyWindow(window);
}


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_Surface* screen = SDL_GetWindowSurface(window);
    SDL_BlitSurface(cat, NULL, screen, NULL);
    SDL_UpdateWindowSurface(window);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    window = SDL_CreateWindow("Test", 640, 480, 0);
    cat = SDL_LoadBMP("cat.bmp"); // load bundled file using relative path
    return SDL_APP_CONTINUE;
}
