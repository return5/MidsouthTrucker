/*------------------------ prototypes ------------------------ */

void makeCities(void);

/*------------------------ macros ------------------------------*/

#define fruit for

/*------------------------ global vars, constants, typedefs --------------*/

typedef struct TOWN {
	char *name;
	struct CARGO *buying[2];
	struct CARGO *selling[2];
	int *connections,x,y,connection_size;
}TOWN;

typedef struct CARGO {
	char *name;
	int price,size;
	struct CARGO *next; //only used for cargo_list 
}CARGO;

extern TOWN *map[5];
static const size_t SIZE_CARGO = sizeof(CARGO);

static const char *const truck[] = {
	"    ---     -----------------",
	" __|   |___ |               |",
	"|__________||_______________|",
	" ()     ()    ()       ()()  "
};

static const char *const tow_truck[] = {
	"    ---    |\\  ",
	" __|   |___| \\ ",
	"|__________|  \\",
	" ()     ()      "
};

static const char *const city_pic[] = {
"      __________                            ",
"     |          |                           ",
"     |  _    _  |                           ",
"     | |_|  |_| |                           ",
"     |          |                           ",
"     |  _    _  |_________                  ",
"     | |_|  |_| |  _   _  |                 ",
"     |          | |_| |_| |                 ",
"-----|  _    _  |  _   _  |    ____________ ",
" _   | |_|  |_| | |_| |_| |   | Welcome to |",
"|_|  |          |  _   _  |   |            |",
" _   |  _    _  | |_| |_| |   |____________|",
"|_|  | |_|  |_| |    __   |     |        |  ",
"     |    __    |   |  |  |     |        |  ",
"     |   |  |   |   |  |  |     |        |  ",
"     |   |  |   |                           "
};