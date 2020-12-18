struct window_t
{
	char* name;
	int startX;
	int startY;
	int endX;
	int endY;
	char* attribute;
};

struct window_t* window_create(char*name,int startx,int starty,
int endx,int endy, char attrib);
void window_open(struct window_t* w);
void window_close(struct window_t*);
void window_delete(struct window_t*);