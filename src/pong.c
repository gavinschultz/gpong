/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *         Author:  Gavin Schultz (), gavin.d.schultz@gmail.com
 *
 * =====================================================================================
 */
#include	"sdl.h"
#include    "SDL_mixer.h"
#include    "SDL_opengl.h"
#include	"pong.h"
#include    "debug.h"
#include    "util.h"
#include    "graphics.h"
#include    "timing.h"
#include	<math.h>
#include    <stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include    <windows.h>

SDL_Surface *screen = NULL;        /* entire screen surface */
SDL_Surface *p1_score_s = NULL;
SDL_Surface *p2_score_s = NULL;
SDL_Surface *diagnostics_s = NULL;
struct Paddle left_p;
struct Paddle right_p;
struct Ball ball;
int p1_score;
int p2_score;
Mix_Chunk *paddle_hit = NULL;
Mix_Chunk *wall_hit = NULL; 
uint32_t bg_color;
uint32_t score_color;
uint32_t midline_color;

float angle_mult = 1.0;
float paddle_angles[9] = {-15.0,-8.5,-5.0,-2.5,0.0,2.5,5.0,8.5,15.0};

struct ScoreBits scorebits[] = {
    { 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1 }, // 0
    { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }, // 1
    { 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1 }, // 2
    { 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 }, // 3
    { 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }, // 4
    { 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 }, // 5
    { 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1 }, // 6
    { 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }, // 7
    { 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1 }, // 8
    { 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0 ,0 ,1, 0, 0, 1, 1, 1 }, // 9
    { 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1 }, // 10
    { 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0 }, // 11
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
    SDL_Event event;
    uint8_t *keystate = NULL;
    int quit = 0;

    init();
    init_game();
    launch_ball();

    /* main loop */
    while(!quit)
    {
        start_timer();

        if (SDL_PollEvent(&event))
        {
            keystate = SDL_GetKeyState(NULL);
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_q:
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        case SDLK_p:
                            pause();
                            break;
                        case SDLK_a:
                            accel_paddle(&left_p, 1);
                            break;
                        case SDLK_z:
                            accel_paddle(&left_p, -1);
                            break;
                        case SDLK_QUOTE:
                            accel_paddle(&right_p, 1);
                            break;
                        case SDLK_SLASH:
                            accel_paddle(&right_p, -1);
                            break;
                        case SDLK_c:
                            randomize_colors();
                            break;
                        case SDLK_b:
                            reset_colors();
                            break;
                        case SDLK_F9:
                            resize_paddle(&left_p, 10);
                            resize_paddle(&right_p, 10);
                            break;
                        case SDLK_F10:
                            resize_paddle(&left_p, -10);
                            resize_paddle(&right_p, -10);
                            break;
                        case SDLK_F11:
                            resize_ball(5);
                            break;
                        case SDLK_F12:
                            resize_ball(-5);
                            break;
                        case SDLK_1:
                            angle_mult += 0.5;
                            break;
                        case SDLK_2:
                            angle_mult -= 0.5;
                            break;
                        case SDLK_r:
                            init_game();
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    // These key-up events are used to make directions still work properly in cases where
                    // both up & down keys were held and one is released; the direction still held down
                    // will activate instead.
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_a:
                            accel_paddle(&left_p, (keystate[SDLK_z] ? -1 : 0));
                            break;
                        case SDLK_z:
                            accel_paddle(&left_p, (keystate[SDLK_a] ? 1 : 0));
                            break;
                        case SDLK_QUOTE:
                            accel_paddle(&right_p, (keystate[SDLK_SLASH] ? -1 : 0));
                            break;
                        case SDLK_SLASH:
                            accel_paddle(&right_p, (keystate[SDLK_QUOTE] ? 1 : 0));
                            break;
                    }
            }
        }

        timetrace("start move_objects()");

        // Move objects based on their velocity
        move_objects();

        timetrace("end move_objects(), start draw_objects()");

        // Redraw the objects on the screen
        draw_objects();

        timetrace("end draw_objects, start delay()");

        end_frame();    // delay for frame rate

        timetrace("end delay()");
    }
    return 0;
}

void init()
{
    uint32_t video_flags = SDL_OPENGL;

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        trace("SDL initialization failed: %s.", SDL_GetError());
        exit(-1);
    }

    atexit(shutdown);

    SDL_WM_SetCaption("GPong",NULL);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

    if (FULLSCREEN)
        video_flags |= SDL_FULLSCREEN;

    screen = SDL_SetVideoMode(HRES, VRES, COLOR_DEPTH, video_flags);
    if (screen == NULL)
    {
        trace("SDl video mode setting failure: %s", SDL_GetError());
        exit(1);
    }

    if(!init_gl(HRES, VRES))
    {
        trace("Could not initialise OpenGL.");
        exit(1);
    }

    if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 ) {
        trace("Could not initialise sound mixer: %s", SDL_GetError());
        exit(1);
    } 

    paddle_hit = Mix_LoadWAV("blipG5.wav");
    wall_hit = Mix_LoadWAV("blipF4.wav");

    set_fps(FPS);
}

void init_game()
{
    left_p.w = PADDLE_W;    left_p.h = PADDLE_H;
    left_p.x = GOAL_INSET;  left_p.y = (VRES / 2) - (left_p.w / 2);
    left_p.color = get_pixel_format(P1COLOR);

    right_p.w = PADDLE_W;   right_p.h = PADDLE_H;
    right_p.y = left_p.y;   right_p.x = HRES - PADDLE_W - GOAL_INSET;  
    right_p.color = get_pixel_format(P2COLOR);

    ball.w = BALLSIZE;      ball.h = BALLSIZE;
    ball.color = get_pixel_format(BALLCOLOR);

    bg_color = get_pixel_format(BGCOLOR);
    midline_color = get_pixel_format(MIDLINECOLOR);
    score_color = get_pixel_format(BALLCOLOR);

    p1_score = 0;           p2_score = 0;
    set_score(GOAL1, 0);    set_score(GOAL2, 0);
}

void launch_ball()
{
    double speed, angle;
    ball.x = (HRES / 3) - (BALLSIZE / 2);
    ball.y = (VRES / 2) - (BALLSIZE / 2);
    srand(time(NULL));

    speed = BALLSPEED - 2;   // initial launch speed slower than typical game speed
    angle = (rand() % 2 == 1 ? 1 : -1) * ((double)(rand() % 40));     // initial angle between +/- 10 to 40 degrees
    trace("LAUNCH! Angle: %f", angle);
    ball.xVel = abs(speed * cos(deg_to_rad(angle)));        // abs() used to make it always start to the right
    ball.yVel = speed * sin(deg_to_rad(angle));
}

void shutdown()
{
    if (screen != NULL)
        SDL_FreeSurface(screen);
    if (diagnostics_s != NULL)
        SDL_FreeSurface(diagnostics_s);
    

    SDL_Quit();
}

// Accelerate the paddle in one direction or another
// In reality, velocity is currently fixed so there is no
// real acceleration.
void accel_paddle(struct Paddle *paddle, int direction)
{
    if (paddle == NULL)
    {
        trace("Paddle not correctly initialised!");
        exit(1);
    }

    if (direction)
    {
        paddle->yVel = (-1) * direction * PADDLE_SPEED;
    }
    else
    {
        paddle->yVel = 0;   // Stop the paddle!
    }
}

void move_objects()
{
    move_paddle(&left_p);
    move_paddle(&right_p);
    move_ball(&ball);
}

void draw_objects()
{
    int i;
    SDL_Rect left_r, right_r, ball_r;

    glClear( GL_COLOR_BUFFER_BIT );

    // Draw ball (OpenGL)
    draw_rect_gl(ball.x, ball.y, ball.w, ball.h);

    // Draw paddles
    draw_rect_gl(left_p.x, left_p.y, left_p.w, left_p.h);
    draw_rect_gl(right_p.x, right_p.y, right_p.w, right_p.h);

    // Draw scores
    set_score(GOAL1, p2_score);
    set_score(GOAL2, p1_score);

    if (glGetError() != GL_NO_ERROR)
    {
        trace("Open GL error detected during draw_objects()!");
    }

    // Draw middle line
    glLineWidth(4);
    glLineStipple(10, 0x5555);
    glBegin(GL_LINES);
    {
        glVertex2f((HRES/2) - 2, 0);
        glVertex2f((HRES/2) - 2, VRES);
    }
    glEnd();

    SDL_GL_SwapBuffers();
}

void set_score(int g, int score)
{
    int i;
    int x, y, w, h;

    if (score > MAX_SCORE)
    {
        trace("score out of range: %d", score);
        exit(1);
    }

    w = ceil(SCORE_W / 5);
    h = ceil(SCORE_H / 5);
    
    // draw scores
    for (i=0;i<25;i++)
    {
        if (scorebits[score].bits[i])
        {
            if (g == GOAL1)
            {
                x = (HRES / 2) + (HRES / 8) + (i % 5) * w;
            }
            else
            {
                x = (HRES / 2) - (HRES / 8) - (SCORE_W) + (i % 5) * w;
            }
            y = 30 + floor(i / 5) * h;
            glRectf(x, y, x + w, y + h);
        }
    }
}

void move_paddle(struct Paddle *paddle)
{
    if (paddle == NULL)
    {
        trace("Paddle not correctly initialised!");
        exit(1);
    }

    if (paddle->yVel)
    {
        if ((paddle->y > 0 && paddle->yVel < 0) 
                || (paddle->y + paddle->h < VRES && paddle->yVel > 0))
        {
            paddle->y += paddle->yVel;
        }
    }
}

void move_ball(struct Ball *b)
{
    if (b == NULL)
        return;

    if (b->yVel)
    {
        // Detect border collision
        if ((b->y <= 0 && b->yVel < 0) || b->y + b->h >= VRES && b->yVel > 0)
        {
            b->yVel *= -1;
            Mix_PlayChannel(-1, wall_hit, 0);
        }
    }

    if (b->xVel)
    {
        // Detect paddle collision
        if (b->xVel < 0 
                && b->x <= left_p.x + left_p.w 
                && b->y <= left_p.y + left_p.h 
                && b->y + b->h >= left_p.y)
        {
            trace("hit left paddle! At ball x: %d   y: %d   , paddle x: %d   y: %d", b->x, b->y, left_p.x + left_p.w, left_p.y);
            collide(&left_p, b);
        }

        if (b->xVel > 0 
                && b->x + b->w >= right_p.x 
                && b->y <= right_p.y + right_p.h 
                && b->y + b->h >= right_p.y)
        {
            trace("hit right paddle! At ball x: %d   y: %d   , paddle x: %d   y: %d", b->x + b->w, b->y, right_p.x, right_p.y);
            collide(&right_p, b);  
        }

        // Detect goal collision
        if (b->x <= GOAL_INSET && b->xVel < 0)
            goal(GOAL1);
        else if (b->x + b->w >= HRES - GOAL_INSET && b->xVel > 0)
            goal(GOAL2);
    }

    b->y += b->yVel;
    b->x += b->xVel;
}

// collide the ball with a paddle
void collide(struct Paddle *paddle, struct Ball *b)
{
    double ball_angle = 0;  // the angle of the ball to the horizontal
    double refl_angle = 0;  // the angle the ball is to be reflected
    double paddle_angle = 0;  // the angle of the paddle to the vertical
    int paddle_segment = 0;   // the segment of the paddle (between 0 and 8) in which the paddle was hit
    int paddle_hity = 0;    // the no of pixels down on the paddle where it was hit by the ball
    double speed = 0;   // the speed of the ball when it hits the paddle

    // depending on the angle / direction of the ball, need to multiply in different ways to get the right angle
    int y_mult;
    int x_mult;

    // Play hit sound
    Mix_PlayChannel(-1, paddle_hit, 0);

    srand(time(NULL));

    y_mult = (b->yVel < 0 ? 1 : -1);
    x_mult = (b->xVel < 0 ? 1 : -1);

    trace("\tball velocity x: %f   y: %f", b->xVel, b->yVel);

    // determine angle of ball coming in to the horizontal
    // subtract from 90/-90 to convert to relative vertical angle
    // Remember this! 
    // 90 - arctan(xVel/yVel) * (180/PI) 
    ball_angle = (y_mult * 90.0) - (atan(b->xVel/b->yVel) * (180/PI)) * x_mult;

    trace("\tball angle: %f", ball_angle);

    // calculate where the ball hit the paddle
    paddle_hity = (b->y + b->h/2) - paddle->y;

    // determine which segment of the paddle was hit
    paddle_segment = ceil((double)paddle_hity/(double)(paddle->h/9)) - 1;
    if (paddle_segment < 0) paddle_segment = 0;     // the ball can technically hit the paddle when it is above or below the paddle
    if (paddle_segment > 8) paddle_segment = 8;

    paddle_angle = paddle_angles[paddle_segment] * angle_mult;

    trace("\tpaddle angle: %f   mult:%f", paddle_angle, angle_mult);

    // Reflected angle depends on the segment it hit the paddle
    // Remember this too!
    // (paddle angle * 2) - ball angle
    refl_angle = (paddle_angle * 2) + ball_angle * (-1);

    // Reflected angles may be a bit too shallow or steep to be any fun; cheat physics accordingly
    if (refl_angle > MAX_ANGLE) refl_angle = MAX_ANGLE;
    else if (refl_angle < -MAX_ANGLE) refl_angle = -MAX_ANGLE;
    else if (refl_angle > 0 && refl_angle < 15.0 && fabs(ball_angle) < 15.0) refl_angle += (rand() % 15);
    else if (refl_angle < 0 && refl_angle > -15.0 && fabs(ball_angle) < 15.0) refl_angle -= (rand() % 15);

    trace("\treflection angle: %f", refl_angle);

    // determine new velocities
    speed = sqrt(square(b->xVel) + square(b->yVel));

    trace("\tspeed: %f", speed);

    // also increment speed to min speed, and faster with each hit
    speed = (speed < BALLSPEED ? BALLSPEED : speed) + 0.2f;

    b->xVel = speed * cos(deg_to_rad(refl_angle)) * x_mult;
    b->yVel = speed * sin(deg_to_rad(refl_angle));
}

void goal(int g)
{
    if (g == GOAL1) 
        set_score(g, ++p2_score);
    else
        set_score(g, ++p1_score);

    if (p1_score >= MAX_SCORE || p2_score >= MAX_SCORE)
        win();

    launch_ball();
}

void win()
{
    draw_objects();
    SDL_Delay(1000);
    init_game();
}

void pause()
{
    SDL_Event event;
    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            return;
    }
}

void resize_ball(int increment)
{
    if (ball.w + increment <= 0)
        ball.w = ball.h = 1;
    else
        ball.w = ball.h += increment;
}

void resize_paddle(struct Paddle *paddle, int increment)
{
    if (paddle->h + increment <= 10)
        paddle->h = 10;
    else
        paddle->h += increment;
}

void randomize_colors()
{
    srand(time(NULL) + (rand() % 100));
    bg_color = RANDOM_PIXEL_FORMAT;
    score_color = RANDOM_PIXEL_FORMAT;
    left_p.color = RANDOM_PIXEL_FORMAT;
    right_p.color = RANDOM_PIXEL_FORMAT;
    ball.color = RANDOM_PIXEL_FORMAT;
    set_score(GOAL1, p2_score);     set_score(GOAL2, p1_score);
}

void reset_colors()
{
    srand(time(NULL) + (rand() % 100));
    bg_color = get_pixel_format(BGCOLOR);
    score_color = get_pixel_format(BALLCOLOR);
    left_p.color = get_pixel_format(P1COLOR);
    right_p.color = get_pixel_format(P2COLOR);
    ball.color = get_pixel_format(BALLCOLOR);
    set_score(GOAL1, p2_score);     set_score(GOAL2, p1_score);
}
