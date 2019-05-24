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
void gameLoop(void);
void initWindows(void);
void initScreen(void);
void takeInputMainPrompt(void);
void buySellPrompt(void);
void buyFuelMenu(void);
void buyFoodPrompt(void);
void buySleepPrompt(void);
void viewConnections(void);
void buySellPromptInput(void);
void buyGoodsPrompt(void);
void sellGoodsPrompt(void);
void initVars(void);
void buySellGoodsInput(void(*func)(const int choice));
void buyGoodsCheck(const int choice);
void buyGood(const int choice);
void sellGood(const int choice);
int checkIfPlayerHasGood(const int choice);
void dontHaveGood(const int choice);
void printTruck(const int start);
void moveTruckForward(const int limit);
void printTowTruck(const int start);
void moveTowTruckBackwards(void);
void moveTowTruckForward(void);
void printBreakDownPrompt(void);
void payTowTruck(void);
int giveUpCargo(void);
int getTowInput(void);
int getTowCargoInput(void);
int giveUpCargo(void);
void promptPrint(const char *const str);
void travelToCity(const int choice);
void getTravelInput(void);
void buyFuelPrompt(void);
void buyFuel(void);
void getFuel(const int choice);
void printCafeMenu(void);
void visitCafe(void);
void printHungerPrompt(void);
void sleepInTrcuk(void);
void visitMotel(void);
void printSleepPrompt(void);
void endGame();
int giveUpCargoCrash(void);
void getCrashCargoInput(void);
void getCrashInput(void);
void crashTruck(void);
void printCity(void);
void delCity(void);
void readNewsPaper(void);
void turnOffCurs(void);
void turnOnCurs(void);

/*------------------------ macros ------------------------------*/
#define CITY map[player_i]
#define SELL(x) CITY->selling[x] 
#define BUY(x) CITY->buying[x] 
#define MAX_FUEL 50
#define MAX_HUNGER 25
#define MAX_SLEEP 25
#define START_MONEY 50
#define MAX_CARGO 50


/*------------------------ global vars, constants --------------*/

static int continue_game = 1;
WINDOW *truck_win,*tow_win,*prompt_win,*city_win;
int player_i,player_money,player_sleep,player_hunger,player_fuel,player_money,cargo_space;
int break_down = 0;
int well_rested = 1;
int crash_Truck = 0;
TOWN *map[5];
CARGO *cargo_list;

/*------------------------ code ------------------------------*/

void printCity(void) {
	for(int i = 0; i < 16; i++) {
		mvwprintw(city_win,i,0,"%s",city_pic[i]);
	}
	mvwprintw(city_win,10,32,"%s",CITY->name);
	wrefresh(city_win);
}

void delCity(void) {
	wclear(city_win);
	wrefresh(city_win);
}

void moveTruckTowTogether(void) {
	fruit(int i = 15; i >= -45; i--) {
		wclear(truck_win);
		wrefresh(truck_win);		
		wclear(tow_win);
		wrefresh(tow_win);
		if(i >= -15) {
			(i >= 0) ? (mvwin(tow_win,5,i),printTowTruck(0)) : printTowTruck(i*-1);
			mvwin(truck_win,5,i+15);
			printTruck(0);
		} 
		else {
			printTruck((-1*i)-16);
		}
		usleep(72000);
	}
	getch();
	printCity();
}

void promptPrint(const char *const str) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"%s",str);
	wrefresh(prompt_win);
}

void payTowTruck(void) {
	promptPrint("you pay him $20 and he tows you into town.");
	player_money -= 20;
	player_fuel = MAX_FUEL;
}

int giveUpCargo(void) {
	if (cargo_list == NULL || cargo_list->next == NULL) {
		promptPrint("you dont have enough cargo to give up.");
		getch();
		promptPrint("the two truck drives away.");
		return 0;
	}
	else {
		cargo_space += cargo_list->size;
		cargo_space += cargo_list->next->size;
		cargo_list = cargo_list->next->next;
		promptPrint("you gave up two pieces of cargo.\nhe will now tow you into town.");
		player_fuel = MAX_FUEL;
		return 1;
	}
}

int getTowInput(void) {
	switch(getch()) {
		case 'y': 
		if(player_money >= 20) {
			payTowTruck();
		 	return 1;
		 }
		 else {
		 	promptPrint("you dont have enough money.\nwould you be willing to trade cargo instead?(y/n)");
		 	return getTowCargoInput();
		 }
		case 'n':
		 	promptPrint("you dont have enough money.\nwould you be willing to trade cargo instead?(y/n)");
		 	return getTowCargoInput();
		default: 
			promptPrint("wrong choice, please try again."); 
			return getTowInput();
			break;
	}
}

int getTowCargoInput(void) {
	switch(getch()) {
		case 'y': return giveUpCargo();
			break;
		case 'n':
			promptPrint("you decide not to get towed into town.");
			getch();
			promptPrint("the tow truck drives away.");
			return 0;
		default: 
			promptPrint("wrong choice, please try again."); 
			return getTowInput();
	}
}

void breakDown(void) {
	moveTruckForward(30);
	const char *const str = (player_fuel >= 0) ? "you broke down. luckily a tow truck is on its way." : "you ran out of gas,luckily a tow truck is on its way.";
	promptPrint(str);
	getch();
	moveTowTruckBackwards();
	promptPrint("you can get towed to town and your truck fixed for $20.(y/n)");
	(getTowInput() == 1) ? moveTruckTowTogether() : (moveTowTruckForward(),endGame());
}

void printTruck(const int start) {
	fruit(int i = 0; i < 4; i++) {
		mvwprintw(truck_win,i,0,"%s",&truck[i][start]);
	}
	wrefresh(truck_win);
}

void moveTruckForward(const int limit) {
	fruit(int i = 50; i >= limit; i--) {
		wclear(truck_win);
		wrefresh(truck_win);
		(i >= 0) ? (mvwin(truck_win,5,i) ,printTruck(0)) : printTruck(i*-1);
		usleep(72000);
	}
	if(limit < 0) {
		printCity();
	}
}

void printTowTruck(const int start) {
	fruit(int i = 0; i < 4; i++) {
		mvwprintw(tow_win,i,0,"%s",&tow_truck[i][start]);
	}
	wrefresh(tow_win);
}

void moveTowTruckBackwards(void) {
	fruit(int i = 0; i <= 15; i++) {
		wclear(tow_win);
		wrefresh(tow_win);
		mvwin(tow_win,5,i);
		printTowTruck(0);
		usleep(72000);
	}
}

void moveTowTruckForward(void) {
	fruit(int i = 14; i >= -15; i--) {
		wclear(tow_win);
		wrefresh(tow_win);
		(i >= 0) ? (mvwin(tow_win,5,i),printTowTruck(0)) : printTowTruck(i*-1);
		usleep(72000);
	}
	getch();
}

void dontHaveGood(const int choice) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"sorry, but you don't have any %s",BUY(choice)->name);
	wrefresh(prompt_win);
	getch();
}

void sellGood(const int choice) {
	CARGO *head = cargo_list;
	CARGO *prev = cargo_list;
	while (head != NULL) {	
		if(strcmp(BUY(choice)->name,head->name) == 0) {
			wclear(prompt_win);
			mvwprintw(prompt_win,0,0,"you sold %s for $%d",BUY(choice)->name,BUY(choice)->price);
			wrefresh(prompt_win);
			getch();
			cargo_space += BUY(choice)->size;
			player_money += BUY(choice)->price;
			(head == prev) ? (cargo_list = head->next) : (prev->next = head->next);
			return;
		}
		prev = head;
		head = head->next;
	}
	dontHaveGood(choice);
	return;
} 

void buyGood(const int choice) {
	CARGO *head = cargo_list;	
	if(head==NULL) {
		cargo_list = malloc(SIZE_CARGO);
		memcpy(cargo_list,SELL(choice),SIZE_CARGO);
	}
	else {
		while(head->next != NULL) {
			head = head->next;
		}
		head->next = malloc(SIZE_CARGO);
		memcpy(head->next,SELL(choice),SIZE_CARGO);
	}
	cargo_space -= SELL(choice)->size;
	player_money -= SELL(choice)->price;
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"you bought %s for $%d",SELL(choice)->name,SELL(choice)->price);
	wrefresh(prompt_win);
	getch();
}

void buyGoodsCheck(const int choice) {
	if(player_money < SELL(choice)->price)	{
		promptPrint("sorry, you cant afford that. stop being poor.");
		getch();
	}
	else if(cargo_space < SELL(choice)->size) {
		promptPrint("sorry, it's too big, it wont fit(that's what she said.)");
		getch();
	}
	else {
		buyGood(choice);
	}
}

void buySellGoodsInput(void(*func)(const int choice)) {
	const int choice = getch() -'0';
	switch(choice) {
		case 1: 
		case 2: func(choice-1);
			break;
		case 3: //do nothing, return to gameLoop
			break;
		default: 
			promptPrint("error, wrong choice. please try again.");
			buySellPrompt();
			break;
	}
}

void buyGoodsPrompt(void) {
	wclear(prompt_win);	
	mvwprintw(prompt_win,0,0,"you have $%d and %d cargo space",player_money,cargo_space);
	mvwprintw(prompt_win,1,0,"the city of %s is selling:",CITY->name);
	mvwprintw(prompt_win,2,5,"1)%s for %d dollars (takes %d cargo space)",SELL(0)->name,SELL(0)->price,SELL(0)->size);
	mvwprintw(prompt_win,3,5,"2)%s for %d dollars (takes %d cargo space)",SELL(1)->name,SELL(1)->price,SELL(1)->size);
	mvwprintw(prompt_win,4,5,"3)neither");
	wrefresh(prompt_win);
}

void sellGoodsPrompt(void) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"the city of %s is buying:",CITY->name);
	mvwprintw(prompt_win,1,5,"1)%s for %d dollars",BUY(0)->name,BUY(0)->price);
	mvwprintw(prompt_win,2,5,"2)%s for %d dollars",BUY(1)->name,BUY(1)->price);
	mvwprintw(prompt_win,3,5,"3)neither");
	wrefresh(prompt_win);
}

void buySellPromptInput(void) {
	switch(getch()) {
		case '1': 
			buyGoodsPrompt();
			buySellGoodsInput(buyGoodsCheck);
			break;
		case '2': 
			sellGoodsPrompt();
			buySellGoodsInput(sellGood);
			break;
		case '3': //do nothing, return to gameLoop
			break;
		default: 
			promptPrint("error, wrong choice. please try again.");
			buySellPrompt();
			break;
	}
}

void buySellPrompt(void) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"would you like to:");
	mvwprintw(prompt_win,1,5,"1)buy");
	mvwprintw(prompt_win,2,5,"2)sell");
	mvwprintw(prompt_win,3,5,"3)neither");
	wrefresh(prompt_win);
	buySellPromptInput();
}

void buyFuelPrompt(void) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"you have %d out of %d fuel.",player_fuel,MAX_FUEL);
	mvwprintw(prompt_win,1,0,"you have $%d.",player_money);
	mvwprintw(prompt_win,2,0,"would you like to buy fuel(y/n)?");
	wrefresh(prompt_win);
}

void getFuel(const int choice) {	
	if((2 * choice) <= (MAX_FUEL - player_fuel) && choice <= player_money) {
		wclear(prompt_win);
		mvwprintw(prompt_win,0,0,"you bought %d fuel for $%d",(2 * choice),choice);
		wrefresh(prompt_win);
		getch();
		player_money -= choice;
		player_fuel += 2 * choice;
	}
	else if((2 * choice) >= (MAX_FUEL - player_fuel)) {	
		wclear(prompt_win);
		promptPrint("sorry, that's too much fuel.");
		wrefresh(prompt_win);
		getch();
		buyFuel();
	}
	else {	
		wclear(prompt_win);
		promptPrint("sorry, you can't afford that much. try again.");
		wrefresh(prompt_win);
		getch();
		buyFuel();
	}
}

void buyFuel(void) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"$1 for 2 fuel. how much do you want to spend on fuel?");
	turnOnCurs();
	move(17,30);
	wrefresh(prompt_win);
	char *choice = malloc(5);
	getstr(choice);
	turnOffCurs();
	getFuel(atoi(choice));
}

void buyFuelInput(void) {
	const int choice = getch();
	if(choice == 'y' || choice == 'Y') {
		buyFuel();
	}
	else if(choice != 'n' && choice != 'N') {
		promptPrint("error, wrong choice, please try again.");
		getch();
		buyFuelMenu();
	}
}

void buyFuelMenu(void) {
	buyFuelPrompt();
	buyFuelInput();
}

void printCafeMenu(void) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"you visit a small cafe. you have $%d, what would you like to order:",player_money);
	mvwprintw(prompt_win,1,5,"1)large dinner for $10.");
	mvwprintw(prompt_win,2,5,"2)small dinner for $5.");
	mvwprintw(prompt_win,3,5,"3)nothing.");
	wrefresh(prompt_win);
}

void visitCafe(void) {
	printCafeMenu();
	int choice;
	while(!isdigit((choice = getch()))) {
		promptPrint("wrong choice. please try again.");
		getch();
		printCafeMenu();
	}
	if(choice == '1' && player_money >= 10) {
		promptPrint("you bought a large dinner. you fill stuffed.");
		player_hunger = MAX_HUNGER;
		player_money -= 10;
		getch();
	}
	else if(choice == '2' && player_money >= 5) {
		promptPrint("you bought a small dinner. that was pretty good.");
		player_hunger = (player_hunger < MAX_HUNGER - 11 ) ? player_hunger + 10 :  MAX_HUNGER;
		player_money -= 5;
		getch();
	}
	else if((choice == '1' && player_money < 10) || (choice == '2' && player_money < 5)) {
		promptPrint("sorry, you dont have enough money for that.");
		getch();
	}
	else if (choice != '3'){
		promptPrint("sorry, wrong choice. try again");
		getch();
		visitCafe();
	}
}
	

void printHungerPrompt(void) {
	switch(player_hunger) {
		case 0 ... 7: promptPrint("you are starving.");
			break;
		case 8 ... 15: promptPrint("you are feeling fairly hungry.");
			break;
		case 16 ... MAX_HUNGER: promptPrint("you arn't feeling very hungry right now.");
			break;
		default: //do nothing
			break;
	}
	getch();
}

void buyFoodPrompt(void) {
	printHungerPrompt();
	visitCafe();
}

void sleepInTrcuk(void) {
	promptPrint("would you like to sleep in your truck(y/n)?");
	int choice;
	while((choice = getch() )!= 'y' && choice != 'n') {
		promptPrint("wrong choice. please try again.");
		getch();
		promptPrint("would you like to sleep in your truck(y/n)?");
	}
	if(choice == 'y') {
		player_sleep = (player_sleep <= MAX_SLEEP - 11) ? player_sleep + 10 : MAX_SLEEP;
		promptPrint("you sleep in your truck. wasn't too bad.");
		player_hunger = (player_hunger < 5) ? 0: player_hunger - 5;
		getch();
	}
	else {
		promptPrint("you decide not to sleep tonight.");
		getch();
	}
}

void visitMotel(void) {
	promptPrint("you can sleep in the motel for $15. do you accept (y/n)?");
	int choice;
	while((choice = getch()) != 'y' && choice != 'n') {
		promptPrint("wrong choice. please try again.");
		getch();
		promptPrint("you can sleep in the motel for $15. do you accept (y/n)?");
	}
	switch(choice) {
		case 'y':
			if(player_money >= 15) {	
				well_rested = 1;
				promptPrint("you get a good night sleep in a moderately clean motel.");
				player_sleep = MAX_SLEEP;
				getch();
				break;
			}
			else{
				promptPrint("sorry, but you can't afford that.");
				getch();
			}
		default: sleepInTrcuk();
			break;
	}
}

void printSleepPrompt(void) {
	switch(player_sleep) {
		case 0 ... 7: promptPrint("you are about to pass out");
			break;
		case 8 ... 15: promptPrint("you are feeling pretty sleepy.");
			break;
		case 16 ... MAX_SLEEP: promptPrint("you aren't feeling very tired now.");
			break;
		default: //do nothing
			break;
	}
	getch();
}

void buySleepPrompt(void) {
	printSleepPrompt();
	visitMotel();

}

void checkDistance(const int choice) {
	const int distance = (int) sqrt(pow((CITY->x - map[choice]->x),2) + pow((CITY->y - map[choice]->y),2));
	const int modifier = (int)(100 - ((2.5 * player_hunger) + (2.5 * player_sleep)));
	const int dis = distance / 2;
	player_fuel -= distance;
	player_sleep = (player_sleep >= dis) ? player_sleep - dis : 0;
	player_hunger = (player_hunger >= dis) ? player_hunger - dis : 0; 
	break_down = (random() % 75 + (well_rested * 25) == 0) ? 1 : 0;
	crash_Truck = (player_sleep <= 0 && player_hunger <= 0 ) ? 1 : (random() % 102 - modifier == 0) ? 1 : 0;
}

int giveUpCargoCrash(void) {
	if(cargo_list == NULL || cargo_list->next == NULL || cargo_list->next->next == NULL) {
		return 0;
	}
	else {
		cargo_space += cargo_list->size;
		cargo_space += cargo_list->next->size;
		cargo_space += cargo_list->next->next->size;
		cargo_list = cargo_list->next->next->next;
		return 1;
	}
}

void getCrashCargoInput(void) {
	switch(getch()) {
		case 'y':
			if(giveUpCargoCrash() == 1) {
				promptPrint("you gave up cargo and now get towed into town.");
				getch();
				moveTruckTowTogether();
				break;
			}
			else{
				promptPrint("sorry, you don't have enough cargo to give up.tow truck drives away.");
				getch();
				moveTowTruckForward();
				endGame();
				break;
			}
				
		case 'n': 
			promptPrint("you decide to not give up cargo. tow truck drives away.");
			getch();
			moveTowTruckForward();
			endGame();
			break;
		default : 
			promptPrint("wrong choice, please try again.");
			getch();
			crashTruck();
			break;
	}
}

void getCrashInput(void) {
	switch(getch()) {
		case 'y':
			if(player_money >= 35) {
				promptPrint("you get towed to town.");
				getch();
				moveTruckTowTogether();
				break;
			}
			else {
				promptPrint("you don't have enough money.");
				getch();
			}
		case 'n':
			promptPrint("would you like to trade some cargo instead(y/n)?");
			getCrashCargoInput();
			break;
		default : 
			promptPrint("error, wrong choice. please try again.");
			getch();
			crashTruck();
			break;
	}
}

void crashTruck(void) {
	moveTruckForward(30);
	promptPrint("you crashed your truck. luckily a tow truck is on the way.");
	getch();
	moveTowTruckBackwards();
	promptPrint("it will cost $35 to tow you to town and fix your truck. do you accept(y/n)?");
	getCrashInput();
}

void travelToCity(const int choice) {
	checkDistance(choice);
	delCity();
	char str[150];
	sprintf(str,"you travel to %s",map[choice]->name);
	promptPrint(str);
	getch();
	player_i = choice;
	if (break_down == 1 || player_fuel < 0) {
		breakDown();
	}
	else if (crash_Truck == 1) {
		crashTruck();
	}
	else {
		moveTruckForward(-29);
	}
	well_rested = 0;
	getch();
}

void getTravelInput(void) {
	const int choice = getch();
	if(choice == 'n') {
		promptPrint("you decide to stay here.");
		getch();
	}
	else if(isalpha(choice) || (choice - '0') -1 >= CITY->connection_size) {
		promptPrint("wrong choice, please try again.");
		getch();
		viewConnections();
	}
	else {
		travelToCity(CITY->connections[(choice - '0') -1]);
	}
}

void viewConnections(void) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"the city of %s connects to:",CITY->name);
	int i;
	for(i = 0; i < CITY->connection_size; i++) {
		mvwprintw(prompt_win,i+1,5,"%d)%s",i+1,map[CITY->connections[i]]->name);
	}
	mvwprintw(prompt_win,i+2,0,"press number you'd like to travel to. press 'n' to stay here.");
	wrefresh(prompt_win);
	getTravelInput();
}

void readNewsPaper(void) {
	wclear(prompt_win);
	fruit(int i = 0; i < 5; i++) {
		mvwprintw(prompt_win,i,0,"the city of %s is buying %s and %s.",map[i]->name,map[i]->buying[0]->name,map[i]->buying[1]->name);
	}
	wrefresh(prompt_win);
	getch();
}

void takeInputMainPrompt(void) {
	switch(getch()) {
		case '1': buySellPrompt();
			break;
		case '2': buyFuelMenu();
			break;
		case '3': buyFoodPrompt();
			break;
		case '4': buySleepPrompt();
			break;
		case '5': viewConnections();
			break;
		case '6': readNewsPaper();
			break;
		case '7': 
			promptPrint("you decide to quit the trucker life for good.\nyou are now officially retired.");
			getch();
			continue_game = 0;
			break;	
		default: promptPrint("error, wrong choice. please try again.");
			break;	
	}
}

void displayMainPrompt(void) {
	wclear(prompt_win);
	mvwprintw(prompt_win,0,0,"would you like to:");
	mvwprintw(prompt_win,1,5,"1)buy/sell goods");
	mvwprintw(prompt_win,2,5,"2)buy fuel");
	mvwprintw(prompt_win,3,5,"3)buy food");
	mvwprintw(prompt_win,4,5,"4)sleep");
	mvwprintw(prompt_win,5,5,"5)travel to another city");
	mvwprintw(prompt_win,6,5,"6)read business section of newspaper.");
	mvwprintw(prompt_win,7,5,"7)retire");
	wrefresh(prompt_win);
}

void gameLoop(void) {
	while(continue_game == 1) {
		displayMainPrompt();
		takeInputMainPrompt();
	}
}

void initVars(void) {
	player_i = 0;
	player_fuel = MAX_FUEL;
	player_sleep = MAX_SLEEP;
	player_hunger = MAX_HUNGER;
	player_money = START_MONEY;
	cargo_space = MAX_CARGO;
	srandom(time(NULL));
}

void initWindows(void) {
	truck_win = newwin(5,29,5,30);
	tow_win = newwin(5,15,5,0);
	prompt_win = newwin(8,70,16,20);
	city_win = newwin(16,45,0,0);
}

void turnOffCurs(void) {
	noecho();	      //dont display key strokes
	cbreak();	     //disable line buffering
	curs_set(0);     //hide cursor
}

void turnOnCurs(void) {
	echo();	      
	nocbreak();	    
	curs_set(1);     
}

void initScreen(void) {
	initscr();
	turnOffCurs();
	refresh();
}

void endGame(void) {
	promptPrint("stuck on the side of the road with no way to get to town, your career is over.");
	continue_game = 0;
}

void retireGame(void) {
	char str [150];
	sprintf(str,"game over. you started with $%d and you end with $%d.",START_MONEY,player_money);
	promptPrint(str);
	getch();
	endwin(); 
}

int main(void) {
	initScreen();
	initWindows();
	initVars();
	makeCities(); //cities.c
	printCity();
	gameLoop();
	retireGame(); 

	return EXIT_SUCCESS;
}