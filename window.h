struct window_t
{
	char* name;
	int startX;
	int startY;
	int endX;
	int endY;
	char attribute;
    int typeOfBorder;
	char* buffer;
};

struct window_t *window_create(char *window_name, int startX, int startY, int endX, int endY, char attribute, int typeOfBorder);

void window_open(struct window_t *window);
void window_close(struct window_t *window);
void window_delete(struct window_t*);