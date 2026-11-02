// Shows the game on the GamePad as well as on the TV, without modifying upstream.
// Hooked in with -Wl,--wrap=SDL_CreateWindow (see cmake/wiiu.cmake).
//
// The Wii U SDL3 fork (dborth/SDL, branch wut-port) can route a window to "tv", "gamepad" or "both" (hint
// SDL_WIIU_WINDOW_TARGET). Upstream creates one window and one renderer, on the TV, and never says where it should
// go, so the fork's default (the TV only) applies. Set the hint to "both" just before the window is created: the
// renderer then mirrors every frame to the GamePad, and the system scales it.
//
// SDL_HINT_DEFAULT priority: a value set by the application or the environment still wins.
#include <SDL3/SDL.h>

extern "C" SDL_Window* __real_SDL_CreateWindow(const char* title, int w, int h, SDL_WindowFlags flags);
extern "C" SDL_Window* __wrap_SDL_CreateWindow(const char* title, int w, int h, SDL_WindowFlags flags)
{
    SDL_SetHintWithPriority("SDL_WIIU_WINDOW_TARGET", "both", SDL_HINT_DEFAULT);
    return __real_SDL_CreateWindow(title, w, h, flags);
}
