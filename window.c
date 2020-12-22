#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "base.h"

struct window_t *window_create(char *name, int startX, int startY, int endX, int endY, char attribute, int typeOfBorder)
{
    struct window_t window = {name, startX, startY, endX, endY, attribute, typeOfBorder};
    return &window;
}

void window_open(struct window_t *window, char* buffer)
{
    takeVideoMemory(buffer);
    particularDescktop(window->startX, window->startY, window->endX, window->endY, window->attribute, window->name, window->typeOfBorder);
}
void window_close(char* buffer)
{
    putVideoMemory(buffer);
}
void window_delete(struct window_t *window)
{
    free(window);
}