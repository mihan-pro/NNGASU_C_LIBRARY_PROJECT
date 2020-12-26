#include "window.h"
#include "base.h"

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define CYAN 3
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define BGBLACK 0
#define BGBLUE 16
#define BGGREEN 32
#define BGCYAN 48
#define BGRED 64
#define BGMAGENTA 80
#define BGBROWN 96
#define BGLIGHTGRAY 112

#define BLINK 128



int main()
{
	struct window_t* window = window_create("window", 2, 2, 60, 20, WHITE|BGBLUE, 1);
	struct window_t* frame = window_create("frame", 5, 5, 70, 10, WHITE|BGBLUE, 0);
	window_open(frame);
	window_open(window);
	window_close(window);
	window_delete(window);
	return 0;
}