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
		format value by min and max edge
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

int checkMinMaxValueWithPrev(int value, int min, int max, int startValue) 
{
	/*
		format value by min and max edge and make it equal start value if it's less than it
	*/
	value = checkMinMaxValue(value, min, max);
	if(value < startValue) 
	{
		value = startValue;
	}
	return value;
}

/*
	int startX - min value: 0, max value: 79
	int startY - min value: 0, max value: 24
	int endX - min value: 0, max value: 79 && endX > startX
	int endY - min value: 0, max value: 24 && endY > startY
	int typeOfBorder - 0 || 1
	char attr - any
*/
void createBorder(int startX, int startY, int endX, int endY, int typeOfBorder, char attr)
{
	char border;
	int row = checkMinMaxValue(startY, 0, 24);
	int col = checkMinMaxValue(startX, 0, 79);
	typeOfBorder = (typeOfBorder == 1)? 1 : 0;
	endX = checkMinMaxValueWithPrev(endX, 0, 79, col);
	endY = checkMinMaxValueWithPrev(endY, 0, 24, row);
	for (; row <= endY; row++)
	{
		for (; col <= endX; col++)
		{
			if (row == startY && col == startX)
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
	int startX - min value: 0, max value: 79
	int startY - min value: 0, max value: 24
	int endX - min value: 0, max value: 79 && endX > startX
	int endY - min value: 0, max value: 24 && endY > startY
	int typeOfBorder - 0 || 1
	char attr - any
	char *windowName - любая строка размером не более endX - startX
*/
void particularDescktop(int startX, int startY, int endX, int endY, char attr, char *windowName, int typeOfBorder)
{
	typeOfBorder = (typeOfBorder == 1)? 1 : 0;
	startX = checkMinMaxValue(startX, 0, 79);
	startY = checkMinMaxValue(startY, 0, 24);
	endX = checkMinMaxValueWithPrev(endX, 0, 79, startX);
	endY = checkMinMaxValueWithPrev(endY, 0, 24, startY);
	particularClear(startX, startY, endX, endY, attr);
	createBorder(startX, startY, endX, endY, typeOfBorder, attr);
	name(windowName, startX, endX, startY, attr);
}

/*
	int startX - min value: 0, max value: 79
	int startY - min value: 0, max value: 24
	int endX - min value: 0, max value: 79 && endX > startX
	char attr - any
	char *windowName - любая строка размером не более endX - startX
*/
void name(char *window_name, int startX, int endX, int startY, char attr)
{
	int position;
	char * correctedString = window_name;
	int maxNameLength = endX - startX;
	int nameLength = strlen(window_name);
	int sizeOfName = strlen(window_name);
	startX = checkMinMaxValue(startY, 0, 79);
	startY = checkMinMaxValue(startX, 0, 24);
	endX = checkMinMaxValueWithPrev(endX, 0, 79, startX);
	if( maxNameLength < nameLength)
	{
		window_name = strncpy(correctedString, window_name, maxNameLength);
	}
	position = startX + (endX - sizeOfName) / 2;
	write_string(startY, position, correctedString, attr);
};

/*
	int row -  min value: 0, max value: 24
	int column - min value: 0, max value: 79
	char symbol - any symbol
	char attr - any attribute symbol
*/
void write_char(int row, int column, char symbol, char attr)
{
	char *videoPointer = (char *)VIDEO_MEMORY;
	column = checkMinMaxValue(column, 0, 79);
	row = checkMinMaxValue(row, 0, 24);
	videoPointer += row * 160 + column * 2;
	*videoPointer = symbol;
	videoPointer += 1;
	*videoPointer = attr;
};

/*
	int row -  min value: 0, max value: 24
	int column - min value: 0, max value: 79
	char *string - любая строка длинной не более 80 - column
	char attr - any attribute symbol
*/
void write_string(int row, int column, char *string, char attr)
{
	int i = 0;
	row = checkMinMaxValue(row, 0, 24);
	column = checkMinMaxValue(column, 0, 79);
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
	int startX - min value: 0, max value: 79
	int startY - min value: 0, max value: 24
	int endX - min value: 0, max value: 79 && endX > startX
	int endY - min value: 0, max value: 24 && endY > startY
	char attr - any
*/
void particularClear(int startX, int startY, int endX, int endY, char attr)
{
	int row = checkMinMaxValue(startY, 0, 24);
	int col = checkMinMaxValue(startX, 0 , 79);
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
