/*------------------------ headers ------------------------------*/
#include <stdlib.h>
#include <unistd.h>  
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>  //isalpha
#include "gamepieces.h"

/*------------------------ prototypes ---------------------------*/
static void gameLoop(void);
static void initWindows(void);
static void initScreen(void);
static void takeInputMainPrompt(void);
static void buySellPrompt(void);
static void buyFuelMenu(void);
static void buyFoodPrompt(void);
static void buySleepPrompt(void);
static void viewConnections(void);
static void buySellPromptInput(void);
static void buyGoodsPrompt(void);
static void sellGoodsPrompt(void);
static void initVars(void);
static void buySellGoodsInput(void(*func)(const int choice));
static void buyGoodsCheck(const int choice);
static void buyGood(const int choice);
static void sellGood(const int choice);
static void dontHaveGood(const int choice);
static void printTruck(const int start);
static void moveTruckForward(const int limit);
static void printTowTruck(const int start);
static void moveTowTruckBackwards(void);
static void moveTowTruckForward(void);
static void payTowTruck(void);
static int giveUpCargo(void);
static int getTowInput(void);
static int getTowCargoInput(void);
static int giveUpCargo(void);
static void promptPrint(const char *const str);
static void travelToCity(const int choice);
static void getTravelInput(void);
static void buyFuelPrompt(void);
static void buyFuel(void);
static void getFuel(const int choice);
static void printCafeMenu(void);
static void visitCafe(void);
static void printHungerPrompt(void);
static void sleepInTrcuk(void);
static void visitMotel(void);
static void printSleepPrompt(void);
static void endGame();
static int giveUpCargoCrash(void);
static void getCrashCargoInput(void);
static void getCrashInput(void);
static void crashTruck(void);
static void printCity(void);
static void delCity(void);
static void readNewsPaper(void);
static void turnOffCurs(void);
static void turnOnCurs(void);

void makeCities(void);  //cities.c

/*------------------------ macros ------------------------------*/
#define CITY map[player_i]
#define SELL(x) CITY->selling[x] 
#define BUY(x) CITY->buying[x] 
#define MAX_FUEL 50
#define MAX_HUNGER 25
#define MAX_SLEEP 25
#define START_MONEY 50
#define MAX_CARGO 50

