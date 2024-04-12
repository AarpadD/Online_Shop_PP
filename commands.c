#include "data_structures.h"


void login(char *name, char *surname) {
    int i;
    for (i = 0; i < numPersons; i++) {
        if (strcmp(persons[i].name, name) == 0 && strcmp(persons[i].surname, surname) == 0) {
            printf("\tLogin successful!\n");
            return;
        }
    }
    //add if not found//
    strcpy(persons[numPersons].name, name);
    strcpy(persons[numPersons].surname, surname);
    persons[numPersons].numOrders = 0;
    numPersons++;
    printf("\tNew user registered!\n");
}


void placeOrder(char *personName, char *personSurname) {
    int i;
    for (i = 0; i < numPersons; i++) {
        if (strcmp(persons[i].name, personName) == 0 && strcmp(persons[i].surname, personSurname) == 0) {
            printf("\n\tAvailable Products:\n");
            for (int k = 0; k < numProducts; k++) {
                printf("\t%d. %s (Price: %.2f) - Available Quantity: %d\n", k + 1, storeInventory[k].name, storeInventory[k].price, storeInventory[k].quantity);
            }

            int orderCode = rand() % 1000 + 1; //random order 1 < code < 1000//

            Order newOrder;
            newOrder.code = orderCode;
            strcpy(newOrder.personName, personName);
            strcpy(newOrder.personSurname, personSurname);

            printf("\tEnter the number of products you want to order: ");
            int numProductsToOrder;
            scanf("%d", &numProductsToOrder);

            //validate input//
            if (numProductsToOrder < 1 || numProductsToOrder > MAX_PRODUCTS) {
                printf("\tInvalid number of products. Please try again.\n");
                return;
            }

            newOrder.numProducts = numProductsToOrder;
            for (int j = 0; j < numProductsToOrder; j++) {
                printf("\tEnter the product number for product %d: ", j + 1);
                int productNumber;
                scanf("%d", &productNumber);

                if (productNumber < 1 || productNumber > numProducts) {
                    printf("\tInvalid product number. Please try again.\n");
                    return;
                }

                int requestedQuantity;
                printf("\tEnter the quantity for product %d: ", j + 1);
                scanf("%d", &requestedQuantity);

                if (requestedQuantity <= 0 || requestedQuantity > storeInventory[productNumber - 1].quantity) {
                    printf("\tInvalid quantity. Please enter a quantity between 1 and %d.\n", storeInventory[productNumber - 1].quantity);
                    return;
                }

                strcpy(newOrder.products[j].name, storeInventory[productNumber - 1].name);
                newOrder.products[j].quantity = requestedQuantity;
                newOrder.products[j].price = storeInventory[productNumber - 1].price;

                storeInventory[productNumber - 1].quantity -= requestedQuantity;
            }

            float totalAmount = 0;
            for (int j = 0; j < numProductsToOrder; j++) {
                totalAmount += newOrder.products[j].price * newOrder.products[j].quantity;
            }
            newOrder.amountPaid = totalAmount;

            persons[i].orders[persons[i].numOrders] = newOrder;
            persons[i].numOrders++;

            orders[numOrders] = newOrder;
            numOrders++;

            printf("\tOrder placed successfully! Total amount paid: %.2f\n", totalAmount);
            return;
        }
    }
}


void sellProduct() {
    char productName[50];
    int quantity;
    float price;

    printf("\n\tEnter the product details\n");
    printf("\tProduct name: ");
    getchar(); //clear the input buffer//
    fgets(productName, sizeof(productName), stdin);
    productName[strcspn(productName, "\n")] = '\0';

    for (int i = 0; i < numProducts; i++) {
        if (strcmp(storeInventory[i].name, productName) == 0) {
            printf("\tProduct with the same name already exists. Please choose a different name.\n");
            return;
        }
    }

    printf("\tQuantity: ");
    scanf("%d", &quantity);
    printf("\tPrice: ");
    scanf("%f", &price);

    strcpy(storeInventory[numProducts].name, productName);
    storeInventory[numProducts].quantity = quantity;
    storeInventory[numProducts].price = price;
    numProducts++;

    printf("\tProduct '%s' added to store's inventory.\n", productName);
}


void viewPlacedOrders(char *personName, char *personSurname) {
    int i;
    for (i = 0; i < numPersons; i++) {
        if (strcmp(persons[i].name, personName) == 0 && strcmp(persons[i].surname, personSurname) == 0) {
            printf("\n\tPlaced orders for %s %s:\n", personName, personSurname);
            for (int j = 0; j < persons[i].numOrders; j++) {
                printf("\tOrder Code: %d\n", persons[i].orders[j].code);
                printf("\tAmount Paid: %.2f\n", persons[i].orders[j].amountPaid);
                printf("\tProducts:\n");
                for (int k = 0; k < persons[i].orders[j].numProducts; k++) {
                    printf("\tProduct Name: %s, Quantity: %d, Price: %.2f\n",
                           persons[i].orders[j].products[k].name,
                           persons[i].orders[j].products[k].quantity,
                           persons[i].orders[j].products[k].price);
                }
                printf("\n");
            }
            return;
        }
    }
}


void searchProducts() {
    char keyword[50];
    float minPrice, maxPrice;
    int option;

    printf("\n\tSearch products by:\n");
    printf("\t1. Name\n");
    printf("\t2. Price (min-max)\n");
    printf("\t3. Name and Price\n");
    printf("\tEnter your choice: ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            printf("\tEnter product name: ");
            scanf("%s", keyword);
            printf("\n\tMatching products:\n");
            for (int i = 0; i < numProducts; i++) {
                if (strstr(storeInventory[i].name, keyword) != NULL) {
                    printf("\tProduct: %s, Quantity: %d, Price: %.2f\n",
                           storeInventory[i].name,
                           storeInventory[i].quantity,
                           storeInventory[i].price);
                }
            }
            break;
        case 2:
            printf("\tEnter min price: ");
            scanf("%f", &minPrice);
            printf("\tEnter max price: ");
            scanf("%f", &maxPrice);
            printf("\n\tMatching products:\n");
            for (int i = 0; i < numProducts; i++) {
                if (storeInventory[i].price >= minPrice && storeInventory[i].price <= maxPrice) {
                    printf("\tProduct: %s, Quantity: %d, Price: %.2f\n",
                           storeInventory[i].name,
                           storeInventory[i].quantity,
                           storeInventory[i].price);
                }
            }
            break;
        case 3:
            printf("\tEnter product name: ");
            scanf("%s", keyword);
            printf("\tEnter min price: ");
            scanf("%f", &minPrice);
            printf("\tEnter max price: ");
            scanf("%f", &maxPrice);
            printf("\n\tMatching products:\n");
            for (int i = 0; i < numProducts; i++) {
                if (strstr(storeInventory[i].name, keyword) != NULL &&
                    storeInventory[i].price >= minPrice && storeInventory[i].price <= maxPrice) {
                    printf("\tProduct: %s, Quantity: %d, Price: %.2f\n",
                           storeInventory[i].name,
                           storeInventory[i].quantity,
                           storeInventory[i].price);
                }
            }
            break;
        default:
            printf("\tInvalid option. Please try again.\n");
    }
}
