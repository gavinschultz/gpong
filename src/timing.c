
#include	"timing.h"
#include    "debug.h"

#define DEFAULT_FPS     60      /* default frames per second */
#define MAX_FPS         200     /* maximum frames per second */

static long _start_ticks = 0;
static int _fps = DEFAULT_FPS;

void start_timer()
{
    _start_ticks = SDL_GetTicks();
}

void set_fps(int fps)
{
    if (fps < 1)
        _fps = DEFAULT_FPS;
    else if (fps > MAX_FPS)
        _fps = MAX_FPS;
    else
        _fps = fps;
}

void delay()
{
    long end_ticks = 0;
    end_ticks = SDL_GetTicks() - _start_ticks;
    if (end_ticks < (1000 / _fps))
    {
        SDL_Delay((1000 / _fps) - end_ticks); 
    }
}
