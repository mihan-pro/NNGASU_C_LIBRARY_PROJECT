#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "base.h"

struct window_t *window_create(char *window_name, int startX, int startY, int endX, int endY, char attribute, int typeOfBorder)
{
    struct window_t *window = malloc(sizeof(struct window_t) + 4000);
    window->name = window_name;
    window->startX = startX;
    window->startY = startY;
    window->endX = endX;
    window->endY = endY;
    window->attribute = attribute;
    window->typeOfBorder = typeOfBorder;
    window->buffer = createBuffer();
    return window;
}

void window_open(struct window_t *window)
{
    takeVideoMemory(window->buffer);
    particularDescktop(window->startX, window->startY, window->endX, window->endY, window->attribute, window->name, window->typeOfBorder);
}
void window_close(struct window_t *window)
{
    putVideoMemory(window->buffer);
}
void window_delete(struct window_t *window)
{
    free(window->buffer);
    free(window);
}