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

int checkMinMaxValue(int value, int min, int max) 
{
	/*
		Приводит значение в рамки крайних значиний в случае выхода за пределы
	*/
	if(value < min) 
	{
		value = 0;
	}
	else if(value > max) 
	{
		value = max;
	}
	return value;
}

/*
	int startX - min value: 0, max value: 80
	int startY - min value: 0, max value: 25
	int endX - min value: 0, max value: 80 && endX > startX
	int endY - min value: 0, max value: 25 && endY > startY
	int typeOfBorder - 0 || 1
	char attr - any
*/
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

/*
	int startX - min value: 0, max value: 80
	int startY - min value: 0, max value: 25
	int endX - min value: 0, max value: 80 && endX > startX
	int endY - min value: 0, max value: 25 && endY > startY
	int typeOfBorder - 0 || 1
	char attr - any
	char *windowName - любая строка размером не более endX - startX
*/
void particularDescktop(int startX, int startY, int endX, int endY, char attr, char *windowName, int typeOfBorder)
{
	particularClear(startX, startY, endX, endY, attr);
	createBorder(startX, startY, endX, endY, typeOfBorder, attr);
	name(windowName, startX, endX, startY, attr);
}

/*
	int startX - min value: 0, max value: 80
	int startY - min value: 0, max value: 25
	int endX - min value: 0, max value: 80 && endX > startX
	char attr - any
	char *windowName - любая строка размером не более endX - startX
*/
void name(char *window_name, int startX, int endX, int startY, char attr)
{
	int sizeOfName = strlen(window_name);
	int position = startX + (endX - sizeOfName) / 2;
	write_string(startY, position, window_name, attr);
};

/*
	int row -  min value: 0, max value: 25
	int column - min value: 0, max value: 80
	char symbol - any symbol
	char attr - any attribute symbol
*/
void write_char(int row, int column, char symbol, char attr)
{
	char *videoPointer = (char *)VIDEO_MEMORY;
	videoPointer += row * 160 + column * 2;
	*videoPointer = symbol;
	videoPointer += 1;
	*videoPointer = attr;
};

/*
	int row -  min value: 0, max value: 25
	int column - min value: 0, max value: 80
	char *string - любая строка длинной не более 80 - column
	char attr - any attribute symbol
*/
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

/*	
	int startX - min value: 0, max value: 80
	int startY - min value: 0, max value: 25
	int endX - min value: 0, max value: 80 && endX > startX
	int endY - min value: 0, max value: 25 && endY > startY
	char attr - any
*/
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
	buffer = malloc(size);
	if (!buffer)
	{
		perror("error in creating buffer \n");
		exit(1);
	}
	return buffer;
}

/*
	char *buffer указатель на область памяти не менее 4000 байт
*/
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

/*
	char *buffer указатель на область памяти не менее 4000 байт
*/
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
