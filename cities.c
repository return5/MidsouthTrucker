/*------------------------ headers ------------------------------*/

#include <stdlib.h>
#include <string.h> 
#include "gamepieces.h"

/*------------------------ prototypes ---------------------------*/

void initTown(const int index,const int x, const int y,const char *const name);
void makeConnections(const int index,const int size,const int *const connect);
void makeBuyingCargo(const int index,const int cargo_index,const char *const name,const int size, const int price);
void makeSellingCargo(const int index,const int cargo_index,const char *const name,const int size, const int price);

/*------------------------ macros ------------------------------*/

/*------------------------ global vars, constants --------------*/

static const size_t SIZE_TOWN = sizeof(TOWN);

/*------------------------ code ------------------------------*/
void makeSellingCargo(const int index,const int cargo_index,const char *const name,const int size, const int price) {
	map[index]->selling[cargo_index] = malloc(SIZE_CARGO);
	map[index]->selling[cargo_index]->name = malloc(15);
	strcpy(map[index]->selling[cargo_index]->name,name);
	map[index]->selling[cargo_index]->price = price;
	map[index]->selling[cargo_index]->size = size;
	map[index]->selling[cargo_index]->next = NULL;
}

void makeBuyingCargo(const int index,const int cargo_index,const char *const name,const int size, const int price) {
	map[index]->buying[cargo_index] = malloc(SIZE_CARGO);
	map[index]->buying[cargo_index]->name = malloc(15);
	strcpy(map[index]->buying[cargo_index]->name,name);
	map[index]->buying[cargo_index]->price = price;
	map[index]->buying[cargo_index]->size = size;
	map[index]->buying[cargo_index]->next = NULL;
}

void makeConnections(const int index,const int size,const int *const connect) {
	map[index]->connections = malloc(SIZE_CARGO * size);
	map[index]->connection_size = size;
	fruit(int i = 0; i < size; i++) {
		map[index]->connections[i] = connect[i];
	}
}

void initTown(const int index,const int x, const int y,const char *const name) {
	map[index] = malloc(SIZE_TOWN);
	map[index]->x = x;
	map[index]->y = y;
	map[index]->name = malloc(15);
	strcpy(map[index]->name,name);
}

void makeCities(void){
	initTown(0,0,0,"Oxford");
	initTown(1,-10,-10,"Memphis");
	initTown(2,20,-20,"Nashville");
	initTown(3,20,5,"Birmingham");
	initTown(4,40,4,"Atlanta");

	const int oxfordar[2] = {1,3};
	makeConnections(0,2,oxfordar);
	const int memphisar[3] = {0,2,3};
	makeConnections(1,3,memphisar);
	const int nashvillear[3] = {1,3,4};
	makeConnections(2,3,nashvillear);
	const int birminghamar[4] ={0,1,2,4};
	makeConnections(3,4,birminghamar);
	const int atlantaar[2] = {2,3};
	makeConnections(4,2,atlantaar);

	//Oxford
	makeBuyingCargo(0,0,"Beer",10,15);
	makeBuyingCargo(0,1,"Cartoons",5,20);
	makeSellingCargo(0,0,"Art",10,10);
	makeSellingCargo(0,1,"Interns",20,20);
	//Memphis
	makeBuyingCargo(1,0,"Pencils",2,7);
	makeBuyingCargo(1,1,"Car Parts",10,30);
	makeSellingCargo(1,0,"Beer",10,5);
	makeSellingCargo(1,1,"Food",10,10);
	//Nashville
	makeBuyingCargo(2,0,"Art",10,25);
	makeBuyingCargo(2,1,"Instruments",15,50);
	makeSellingCargo(2,0,"Music",5,10);
	makeSellingCargo(2,1,"Jewelry",5,20);
	//Birmingham
	makeBuyingCargo(3,0,"Food",10,20);
	makeBuyingCargo(3,1,"Jewelry",5,40);
	makeSellingCargo(3,0,"Pencils",2,2);
	makeSellingCargo(3,1,"Instruments",15,30);
	//Atlanta
	makeBuyingCargo(4,0,"Music",5,22);
	makeBuyingCargo(4,1,"Interns",20,60);
	makeSellingCargo(4,0,"Cartoons",5,10);
	makeSellingCargo(4,1,"Car Parts",10,15);
}
