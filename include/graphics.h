
#ifndef  GRAPHICS_INC
#define  GRAPHICS_INC

#include	"SDL/sdl.h"

SDL_Rect get_rect(int x, int y, int w, int h);
void apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest, SDL_Rect *clip);
long get_pixel_format(long rgbHex);

#endif
