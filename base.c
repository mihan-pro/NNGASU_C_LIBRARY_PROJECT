#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

#define MAX_ROW 25
#define MAX_COLUMN 80

#define VIDEO_MEMORY 0xb8000000L
#define BUFFER_SIZE MAX_ROW *MAX_COLUMN * 2 * sizeof(char)

#define DOUBLE_HORIZONTAL_BORDER 0xCD
#define DOUBLE_VERTICAL_BORDER 0xBA
#define DOUBLE_LEFT_TOP_CORNER 0xC9
#define DOUBLE_RIGHT_TOP_CORNER 0xBB
#define DOUBLE_LEFT_DOWN_CORNER 0xC8
#define DOUBLE_RIGHT_DOWN_CORNER 0xBC

#define SOLID_HORIZONTAL_BORDER 0xC4
#define SOLID_VERTICAL_BORDER 0xB3
#define SOLID_LEFT_TOP_CORNER 0xDA
#define SOLID_RIGHT_TOP_CORNER 0xBF
#define SOLID_LEFT_DOWN_CORNER 0xC0
#define SOLID_RIGHT_DOWN_CORNER 0xD9


void createBorder(int startX, int startY, int endX, int endY, int typeOfBorder, char attr)
{
	char border;
	int row = startY;
	int col = startX;
	for (; row <= endY; row++)
	{
		for (; col <= endX; col++)
		{
			if (row == startX && col == startY)
			{
				border = typeOfBorder ? DOUBLE_LEFT_TOP_CORNER : SOLID_LEFT_TOP_CORNER;
				write_char(row, col, border, attr);
				continue;
			}
			else if (row == startY && col == endX)
			{
				border = typeOfBorder ? DOUBLE_RIGHT_TOP_CORNER : SOLID_RIGHT_TOP_CORNER;
				write_char(row, col, border, attr);
				continue;
			}
			else if (row == endY && col == startX)
			{
				border = typeOfBorder ? DOUBLE_LEFT_DOWN_CORNER : SOLID_LEFT_DOWN_CORNER;
				write_char(row, col, border, attr);
				continue;
			}
			else if (row == endY && col == endX)
			{
				border = typeOfBorder ? DOUBLE_RIGHT_DOWN_CORNER : SOLID_RIGHT_DOWN_CORNER;
				write_char(row, col, border, attr);
				continue;
			}
			else if (row == startY || row == endY)
			{
				border = typeOfBorder ? DOUBLE_HORIZONTAL_BORDER : SOLID_HORIZONTAL_BORDER;
				write_char(row, col, border, attr);
				continue;
			}
			else if (col == startX || col == endX)
			{
				border = typeOfBorder ? DOUBLE_VERTICAL_BORDER : SOLID_VERTICAL_BORDER;
				write_char(row, col, border, attr);
				continue;
			}
		}
		col = startX;
	}
};

void fullDescktop(char *windowName, int typeOfBorder, char attr)
{
	int row = 0;
	int col = 0;
	char border;
	fullClear(attr);
	createBorder(row, col, 79, 24, typeOfBorder, attr);
	name(windowName, 0, MAX_ROW, 0, attr);
}

void particularDescktop(int startX, int startY, int endX, int endY, char attr, char *windowName, int typeOfBorder)
{
	particularClear(startX, startY, endX, endY, attr);
	createBorder(startX, startY, endX, endY, typeOfBorder, attr);
	name(windowName, startX, endX, startY, attr);
}

void name(char *window_name, int startX, int endX, int startY, char attr)
{
	int sizeOfName = strlen(window_name);
	int position = startX + (endX - sizeOfName) / 2;
	write_string(startY, position, window_name, attr);
};

void write_char(int row, int column, char symbol, char attr)
{
	char *v = (char *)VIDEO_MEMORY;
	v += row * 160 + column * 2;
	*v = symbol;
	v++;
	*v = attr;
};

void write_string(int row, int column, char *string, char attr)
{
	int i = 0;
	while (string[i])
	{
		write_char(row, column++, string[i++], attr);
	}
}

void fullClear(char attr)
{
	int row = 0;
	int col = 0;
	for (; row < MAX_ROW; row++)
	{
		for (; col < MAX_COLUMN; col++)
		{
			write_char(row, col, ' ', attr);
		}
		col = 0;
	}
}

void particularClear(int startX, int startY, int endX, int endY, char attr)
{
	int row = startY;
	int col = startX;
	for (; row <= endY; row++)
	{
		for (; col <= endX; col++)
		{
			write_char(row, col, ' ', attr);
		}
		col = startX;
	}
}

char *createBuffer()
{
	char *buffer;
	int size = BUFFER_SIZE;
	char *tmpString;
	char *sizeStr = itoa(size, tmpString, 10);
	buffer = malloc(size);
	if (!buffer)
	{
		perror("error in creating buffer \n");
		exit(1);
	}
	return buffer;
}

void takeVideoMemory(char *buffer)
{
	char *pointer = (char *)VIDEO_MEMORY;
	char *buffer_pointer = buffer;
	int i = 0;
	while (i < BUFFER_SIZE)
	{
		*buffer_pointer = *pointer;
		buffer_pointer += 1;
		pointer += 1;
		*buffer_pointer = *pointer;
		buffer_pointer += 1;
		pointer += 1;
		i += 1;
	}
};

void putVideoMemory(char *buffer)
{
	char *pointer = (char *)VIDEO_MEMORY;
	char *buffer_pointer = buffer;
	int i = 0;
	while (i < BUFFER_SIZE)
	{
		*pointer = *buffer_pointer;
		buffer_pointer += 1;
		pointer += 1;
		*pointer = *buffer_pointer;
		buffer_pointer += 1;
		pointer += 1;
		i += 1;
	}
};
