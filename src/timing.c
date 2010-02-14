
#include	"timing.h"
#include    "debug.h"

#define DEFAULT_FPS     60      /* default frames per second */
#define MAX_FPS         200     /* maximum frames per second */

static long _start_ticks = 0;
static int _fps = DEFAULT_FPS;
static int frame = 0;
static float frame_rate = 0.0;

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

void end_frame()
{
    long end_ticks = 0;
    end_ticks = SDL_GetTicks() - _start_ticks;
    if (end_ticks < (1000 / _fps))
    {
        SDL_Delay((1000 / _fps) - end_ticks); 
    }
    frame++;
    frame_rate = 1000 / (SDL_GetTicks() - _start_ticks);
}

float get_frame_rate()
{
    return frame_rate;
}

void timetrace(char *str, ...)
{
#if TIMETRACE 
    va_list ap;
    long ticks = 0;
    ticks = SDL_GetTicks() - _start_ticks;

    va_start(ap, str);
    printf("Trace time: %d   ", ticks);
    vprintf(str, ap);
    putchar('\n');
    va_end(ap);
#endif
}
