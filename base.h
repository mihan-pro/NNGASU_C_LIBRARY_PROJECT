void write_char(int row, int column, char symbol, char attr);
void write_string(int row, int column, char *string, char attr);

char *createBuffer();
void fullClear(char attr);
void particularClear(int startX, int startY, int endX, int endY, char attr);

void particularDescktop(int startX, int startY, int endX, int endY, char attr, char *windowName, int typeOfBorder);

void takeVideoMemory(char *buffer);
void putVideoMemory(char *buffer);
void name(char *name, int startX, int endX, int startY, char attr);