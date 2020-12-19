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

char *buffer;

int main()
{
    struct window_t* window = window_create(window, 2 ,2, 60, 23, WHITE|BGBLUE);
	buffer = createBuffer();
    window_open(window);
	free(buffer);
	return 0;
}