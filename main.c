#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data_structures.h"

Person persons[MAX_PERSONS];
int numPersons = 0;

Order orders[MAX_ORDERS];
int numOrders = 0;

Product storeInventory[MAX_PRODUCTS];
int numProducts = 0;

int main() {
    srand(time(NULL));
    char choice;
    char personName[50];
    char personSurname[50];

    printf("\n\tWelcome to my small garden!\n\n");

    load_people();
    load_orders();
    load_products();

    printf("\tEnter your name: ");
    scanf("%s", personName);
    printf("\tEnter your surname: ");
    scanf("%s", personSurname);
    login(personName, personSurname);

    do {
        printf("\n\tMenu:\n");
        printf("\t1. Place Order\n");
        printf("\t2. Sell Products to Store\n");
        printf("\t3. View Placed Orders\n");
        printf("\t4. Search Products\n");
        printf("\t5. Exit\n");

        printf("\tEnter your choice: ");
        scanf(" %c", &choice);

        switch(choice) {
            case '1':
                placeOrder(personName, personSurname);
                break;
            case '2':
                sellProduct();
                break;
            case '3':
                viewPlacedOrders(personName, personSurname);
                break;
            case '4':
                searchProducts();
                break;
            case '5':
                printf("\tExiting...\n");
                save_people();
                save_orders();
                save_products();
                break;
            default:
                printf("\tInvalid choice. Please try again.\n");
        }
    } while(choice != '5');

    return 0;
}


