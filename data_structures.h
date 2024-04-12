#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#define MAX_PRODUCTS 100
#define MAX_ORDERS 100
#define MAX_PERSONS 100


//Structures//
typedef struct {
    char name[50];
    int quantity;
    float price;
} Product;

typedef struct {
    int code;
    char personName[50];
    char personSurname[50];
    int numProducts;
    Product products[MAX_PRODUCTS];
    float amountPaid;
} Order;

typedef struct {
    char name[50];
    char surname[50];
    int numOrders;
    Order orders[MAX_ORDERS];
} Person;


//global variables//
extern Person persons[MAX_PERSONS];
extern int numPersons;

extern Order orders[MAX_ORDERS];
extern int numOrders;

extern Product storeInventory[MAX_PRODUCTS];
extern int numProducts;


// Function prototypes//
void login(char *name, char *surname);
void placeOrder(char *personName, char *personSurname);
void sellProduct();
void viewPlacedOrders(char *personName, char *personSurname);
void searchProducts();

void save_people();
void load_people();
void load_orders();
void save_products();
void save_orders();
void load_products();


#endif
