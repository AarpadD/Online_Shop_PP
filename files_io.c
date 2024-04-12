#include "data_structures.h"


FILE* openFile(const char* filename, const char* mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return NULL;
    }
    return file;
}

void save_orders() {
    FILE *file = openFile("orders_pp.txt", "w");
    if (!file) return;
    for (int i = 0; i < numOrders; i++) {
        fprintf(file, "%d,%s,%s,%d,%.2f\n", orders[i].code, orders[i].personName, orders[i].personSurname, orders[i].numProducts, orders[i].amountPaid);
        for (int j = 0; j < orders[i].numProducts; j++) {
            fprintf(file, "%s,%d,%.2f\n", orders[i].products[j].name, orders[i].products[j].quantity, orders[i].products[j].price);
        }
    }
    fclose(file);
}
void load_orders() {
    FILE *file = openFile("orders_pp.txt", "r");
    if (!file) return;
    while (!feof(file) && fscanf(file, "%d,%s,%s,%d,%f\n", &orders[numOrders].code, orders[numOrders].personName, orders[numOrders].personSurname, &orders[numOrders].numProducts, &orders[numOrders].amountPaid) == 5) {
        for (int j = 0; j < orders[numOrders].numProducts; j++) {
            fscanf(file, "%s,%d,%f\n", orders[numOrders].products[j].name, &orders[numOrders].products[j].quantity, &orders[numOrders].products[j].price);
        }
        numOrders++;
    }
    fclose(file);
}

void save_products() {
    FILE *file = openFile("products_pp.txt", "w");
    if (!file) return;
    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s,%d,%.2f\n", storeInventory[i].name, storeInventory[i].quantity, storeInventory[i].price);
    }
    fclose(file);
}
void load_products() {
    FILE *file = openFile("products_pp.txt", "r");
    if (!file) return;
    while (!feof(file) && fscanf(file, "%[^,],%d,%f\n", storeInventory[numProducts].name, &storeInventory[numProducts].quantity, &storeInventory[numProducts].price) == 3) {
        numProducts++;
    }
    fclose(file);
}

void load_people() {
    FILE* file = openFile("people_pp.txt", "r");
    if (!file) return;
    while (numPersons < MAX_PERSONS && fscanf(file, "%s %s\n", persons[numPersons].name, persons[numPersons].surname) == 2) {
        numPersons++;
    }
    fclose(file);
}
void save_people() {
    FILE* file = openFile("people_pp.txt", "w");
    if (!file) return;
    for (int i = 0; i < numPersons; i++) {
        fprintf(file, "%s %s\n", persons[i].name, persons[i].surname);
    }
    fclose(file);
}