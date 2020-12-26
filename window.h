struct window_t
{
	char* name;
	int startX;
	int startY;
	int endX;
	int endY;
	char* attribute;
    int typeOfBorder;
};

struct window_t* window_create(char*name, int startX, int startY,int endX, int endY, char attribute);

void window_open(struct window_t *window, char* buffer);
void window_close(char* buffer);
void window_delete(struct window_t*);