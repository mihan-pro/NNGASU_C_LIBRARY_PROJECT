#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void write_char(int row, int column, char symbol, char attr);
void write_string(int row, int column, char *string, char attr);
void clear();
char *createBuffer();
void takeVideoMemory(char *buffer);
void putVideoMemory(char *buffer);
void descktop(char *windowName, int typeOfBorder);
void name(char *name);
void printBuffer(char *buffer);
void printBufferToFile(char *bufer, char *fileName);

char *buffer;

int main()
{
	buffer = createBuffer();
	write_string(5, 5, "content", GREEN | BGMAGENTA);
	takeVideoMemory(buffer);
	printBufferToFile("my dear friend i wanna fuck you", "MyLog.txt");
	putVideoMemory(buffer);
	free(buffer);
	return 0;
}

void descktop(char *windowName, int typeOfBorder)
{
	int row = 0;
	int col = 0;
	char border;
	for (; row < MAX_ROW; row++)
	{
		for (; col <= MAX_COLUMN; col++)
		{
			if (row == 0 && col == 0)
			{
				border = typeOfBorder ? DOUBLE_LEFT_TOP_CORNER : SOLID_LEFT_TOP_CORNER;
				write_char(row, col, border, WHITE | BGBLUE);
				continue;
			}
			else if (row == 0 && col == 79)
			{
				border = typeOfBorder ? DOUBLE_RIGHT_TOP_CORNER : SOLID_RIGHT_TOP_CORNER;
				write_char(row, col, border, WHITE | BGBLUE);
				continue;
			}
			else if (row == 24 && col == 0)
			{
				border = typeOfBorder ? DOUBLE_LEFT_DOWN_CORNER : SOLID_LEFT_DOWN_CORNER;
				write_char(row, col, border, WHITE | BGBLUE);
				continue;
			}
			else if (row == 24 && col == 79)
			{
				border = typeOfBorder ? DOUBLE_RIGHT_DOWN_CORNER : SOLID_RIGHT_DOWN_CORNER;
				write_char(row, col, border, WHITE | BGBLUE);
				continue;
			}
			else if (row == 0 || row == 24)
			{
				border = typeOfBorder ? DOUBLE_HORIZONTAL_BORDER : SOLID_HORIZONTAL_BORDER;
				write_char(row, col, border, WHITE | BGBLUE);
				continue;
			}
			else if (col == 0 || col == 79)
			{
				border = typeOfBorder ? DOUBLE_VERTICAL_BORDER : SOLID_VERTICAL_BORDER;
				write_char(row, col, border, WHITE | BGBLUE);
				continue;
			}
			write_char(row, col, ' ', WHITE | BGBLUE);
		}
		col = 0;
	}
	name(windowName);
}

void name(char *name)
{
	int sizeOfName = strlen(name);
	int position = 0 + (MAX_COLUMN - sizeOfName) / 2;
	write_string(0, position, name, WHITE | BGBLUE);
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

void clear()
{
	int row = 0;
	int col = 0;
	for (; row < MAX_ROW; row++)
	{
		for (; col < MAX_COLUMN; col++)
		{
			write_char(row, col, ' ', BLUE | BGBLUE);
		}
		col = 0;
	}
}

char *createBuffer()
{
	char *buffer;
	int size = BUFFER_SIZE;
	buffer = malloc(size);
	if (!buffer)
	{
		printf("error in creating buffer \n");
		exit(1);
	}
	return buffer;
}

void printBufferToFile(char *bufer, char *fileName)
{
	FILE *file = fopen(fileName, "a");
	if (file == NULL)
	{
		perror("problem with creating file");
	};
	fputs(buffer, file);
	fclose(file);
}

void takeVideoMemory(char *buffer)
{
	char *pointer = (char *)VIDEO_MEMORY;
	char *buffer_pointer = buffer;
	int row = 0;
	int col = 0;
	for (; row < MAX_ROW; row++)
	{
		for (; col < MAX_COLUMN; col++)
		{
			*buffer_pointer = '0';
			*buffer_pointer += 1;
			*pointer += 1;
			*buffer_pointer = GREEN | BGRED;
			*buffer_pointer += 1;
			*pointer += 1;
		}
		col = 0;
	}
};

void putVideoMemory(char *buffer)
{
	char *pointer = (char *)VIDEO_MEMORY;
	char *buffer_pointer = buffer;
	int row = 0;
	int col = 0;
	for (; row < MAX_ROW; row++)
	{
		for (; col < MAX_COLUMN; col++)
		{
			*pointer = *buffer_pointer;
			*buffer_pointer += 1;
			*pointer += 1;
			*pointer = *buffer_pointer;
			*buffer_pointer += 1;
			*pointer += 1;
		}
		col = 0;
	}
};

void printBuffer(char *buffer)
{
	int i = 0;
	while (i < BUFFER_SIZE)
	{
		printf(*buffer++);
		i++;
	}
}