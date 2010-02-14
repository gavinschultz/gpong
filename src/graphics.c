
#include	"graphics.h"
#include    "SDL.h"
#include    "SDL_opengl.h"

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

long get_pixel_format(long rgbHex)
{
    long red = ((rgbHex & 0xFF0000) >> 16);
    long green = ((rgbHex & 0xFF00) >> 8);
    long blue = ((rgbHex & 0xFF));

    return SDL_MapRGB(screen->format, red, green, blue);
}

int init_gl(int hRes, int vRes)
{
    GLenum response;

    glClearColor( 0, 0, 0, 0 );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, hRes, vRes, 0, -1, 1);
    glEnable(GL_LINE_STIPPLE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    response = glGetError();
    if (response != GL_NO_ERROR)
    {
        trace("OpenGL error detected: %d", response);
        return 0;
    }
    return 1;
}

void draw_rect_gl(int x, int y, int w, int h)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    glRectf(0.0f,0.0f,w,h);

    glLoadIdentity();
    glPopMatrix();
}
