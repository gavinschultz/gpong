
#ifndef  GRAPHICS_INC
#define  GRAPHICS_INC

#include	"sdl.h"

#define RANDOM_PIXEL_FORMAT     get_pixel_format(((rand() % 255) << 16) | ((rand() % 255) << 8) | rand() % 255)

SDL_Rect get_rect(int x, int y, int w, int h);
void apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest, SDL_Rect *clip);
long get_pixel_format(long rgbHex);
int init_gl(int hRes, int vRes);
void draw_rect_gl(int x, int y, int w, int h);

#endif
