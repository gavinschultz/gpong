#define FPS         60          /* Frames per second */
#define	HRES        640			/* Horizontal resolution */
#define	VRES        480			/* Vertical resolution */
#define COLOR_DEPTH 32          /* Colour depth */
#define FULLSCREEN  0

#define	PADDLE_SPEED    8		/* Maximum velocity for the paddle (per frame) */

#define BGCOLOR     0x000000    /* starting background color */
#define P1COLOR     0xFFFFFF    /* starting color of player 1 paddle */
#define P2COLOR     0xFFFFFF    /* starting color of player 2 paddle */
#define BALLCOLOR   0xFFFFFF    /* starting color of ball */
#define	MIDLINECOLOR 0xDDDDDD	/* starting color of the middle line */

#define PADDLE_W    5           /* default width of the paddle */
#define PADDLE_H    80          /* default height of the paddle */
#define SCORE_W     75          /* default width of the score box */
#define SCORE_H     75          /* default height of the score box */
#define MIDLINE_W   4           /* default width of the useless middle line */
#define MIDLINE_H   10          /* default height of each "perforation" in the middle line */
#define	BALLSIZE    11			/* starting width/height of the ball in pixels */
#define	BALLSPEED   8 		/* starting ball speed (per frame) */
#define	GOAL_INSET  40          /* distance of the goal from the edge of the screen, also determines the paddle X position */

#define	GOAL1       1			/* goal 1 (on left) */
#define GOAL2       0           /* goal 2 (on right) */
#define	MAX_ANGLE   60			/* maximum angle of reflection from paddle */

#define	MAX_SCORE   ((sizeof(scorebits) / sizeof(char)) / 25) - 1		/* the maximum score, as determined by the scorebit array */

struct Paddle { 
    int yVel;
    int x, y, w, h;
    uint32_t color;
};

struct Ball {
    double xVel, yVel;
    int x, y, w, h;
    uint32_t color;
};

// Simple struct for mapping score onto screen; each bit is an (enormous) "pixel"
struct ScoreBits {
    char bits[25];
};

void init(void);
void shutdown(void);
void init_game(void);
void pause(void);
void launch_ball(void);
void accel_paddle(struct Paddle *, int);   // 1 = up, -1 = down, 0 = stop
void move_paddle(struct Paddle *);
void move_ball(struct Ball *);
void move_objects(void);
void draw_objects(void);
void collide(struct Paddle *, struct Ball *);
void goal(int);
void win(void);
void set_score(int, int);

// Special functions
void resize_ball(int);
void resize_paddle(struct Paddle *, int);
void randomize_colors();
void reset_colors();
