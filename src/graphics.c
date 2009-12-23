
#include	"graphics.h"

extern SDL_Surface *screen;

SDL_Rect get_rect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *dest, SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, dest, &offset); 
}

long get_pixel_format(long rgbHex)
{
    long red = ((rgbHex & 0xFF0000) >> 16);
    long green = ((rgbHex & 0xFF00) >> 8);
    long blue = ((rgbHex & 0xFF));

    return SDL_MapRGB(screen->format, red, green, blue);
}

