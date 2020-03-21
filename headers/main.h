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
static void gameLoop(static void);
static void initWindows(static void);
static void initScreen(static void);
static void takeInputMainPrompt(static void);
static void buySellPrompt(static void);
static void buyFuelMenu(static void);
static void buyFoodPrompt(static void);
static void buySleepPrompt(static void);
static void viewConnections(static void);
static void buySellPromptInput(static void);
static void buyGoodsPrompt(static void);
static void sellGoodsPrompt(static void);
static void initVars(static void);
static void buySellGoodsInput(static void(*func)(const int choice));
static void buyGoodsCheck(const int choice);
static void buyGood(const int choice);
static void sellGood(const int choice);
static int checkIfPlayerHasGood(const int choice);
static void dontHaveGood(const int choice);
static void printTruck(const int start);
static void moveTruckForward(const int limit);
static void printTowTruck(const int start);
static void moveTowTruckBackwards(static void);
static void moveTowTruckForward(static void);
static void printBreakDownPrompt(static void);
static void payTowTruck(static void);
static int giveUpCargo(static void);
static int getTowInput(static void);
static int getTowCargoInput(static void);
static int giveUpCargo(static void);
static void promptPrint(const char *const str);
static void travelToCity(const int choice);
static void getTravelInput(static void);
static void buyFuelPrompt(static void);
static void buyFuel(static void);
static void getFuel(const int choice);
static void printCafeMenu(static void);
static void visitCafe(static void);
static void printHungerPrompt(static void);
static void sleepInTrcuk(static void);
static void visitMotel(static void);
static void printSleepPrompt(static void);
static void endGame();
static int giveUpCargoCrash(static void);
static void getCrashCargoInput(static void);
static void getCrashInput(static void);
static void crashTruck(static void);
static void printCity(static void);
static void delCity(static void);
static void readNewsPaper(static void);
static void turnOffCurs(static void);
static void turnOnCurs(static void);

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

