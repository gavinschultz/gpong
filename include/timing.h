
#include	"SDL.h"

#define TIMETRACE   0       /* Enabled / disable time tracing */

void set_fps(int);
void start_timer();
void end_frame();
void timetrace(char *,...);
float get_frame_rate();
