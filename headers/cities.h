/*------------------------ headers ------------------------------*/
#include <stdlib.h>
#include <string.h> 
#include "gamepieces.h"

/*------------------------ prototypes ---------------------------*/

static void initTown(const int index,const int x, const int y,const char *const name);
static void makeConnections(const int index,const int size,const int *const connect);
static void makeBuyingCargo(const int index,const int cargo_index,const char *const name,const int size, const int price);
static void makeSellingCargo(const int index,const int cargo_index,const char *const name,const int size, const int price);

void makeCities(void);
/*------------------------ macros ------------------------------*/
