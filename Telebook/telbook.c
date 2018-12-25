#define N 100
#define NAME_LENGTH 20
#define NUMBER_LENGTH 20

static const int tresshold = 10;
static const char file_name[20] = "TelBook.txt";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "telbook.h"

typedef struct record
{
    char FirstName[NAME_LENGTH];
    char LastName[NAME_LENGTH];
    char Number[NUMBER_LENGTH];
} record;

typedef struct TelBook{
    
    record *records;
    size_t quantity;
    size_t max_quantity;
}TelBook;

void file_reader(FILE *finput, TelBook *ex, int index) {
    char string[100];
    while (fscanf(finput, "%s", string) != EOF) {
        while (fscanf(finput, "%s %s %s", ex->records[index].FirstName, ex->records[index].LastName,
                      ex->records[index].Number) != EOF) {
            index++;
        }
    }
}

    void add_contact(TelBook *ex) {
        size_t i = ex->quantity;
        printf("New contact first name:");
        scanf("%s", ex->records[i].FirstName);

        printf("New contact last name:");
        scanf("%s", ex->records[i].LastName);

        printf("New contact phone number :");
        scanf("%s", ex->records[i].Number);
        ex->quantity++;
    }
    void print_contacts(TelBook *ex){
        for (int i = 0; i < ex->quantity; i++) {
            printf("%s %s %s", ex->records[i].FirstName, ex->records[i].LastName, ex->records[i].Number);
            break;
        }
}

    void find_name(TelBook *ex, char *name_find, char *surname_find) {
        for (int i = 0; i <= ex->quantity; i++) {
            if (!strncmp(name_find, ex->records[i].FirstName, N) &&
                !strncmp(surname_find, ex->records[i].LastName, N)) {
                printf("%s %s %s\n", ex->records[i].FirstName, ex->records[i].LastName, ex->records[i].Number);
            }
        }
    }

    void find_number(TelBook *ex, char *number_find) {
        for (int i = 0; i <= ex->quantity; i++) {
            if (!strncmp(number_find, ex->records[i].Number, N)) {
                printf("%s %s %s", ex->records[i].FirstName, ex->records[i].LastName, ex->records[i].Number);
            }
        }
    }
    void save_exit(FILE *finput, TelBook *ex) {
        for (int i = 0; i < N; i++) {
            fprintf(finput, "%s ", ex->records[i].FirstName);
            fprintf(finput, "%s ", ex->records[i].LastName);
            fprintf(finput, "%s\n", ex->records[i].Number);
            break;
        }
    }

    int memory_controller(TelBook *ex) {
        if (ex->quantity == ex->max_quantity) {
            ex->max_quantity += tresshold;
            if (!(ex->records = realloc(ex->records, ex->max_quantity * sizeof(record)))) {
                return 1;
            }
        }

        if (ex->max_quantity - ex->quantity > 2 * tresshold) {
            ex->max_quantity -= tresshold;
            ex->records = realloc(ex->records, ex->max_quantity * sizeof(record));
        }

        return 0;
    }

    void create_telbook(TelBook *ex) {
        ex->max_quantity = tresshold;
        ex->records = malloc(ex->max_quantity * sizeof(record));
    }

    void hint() {
        printf("0 - exit\n"
               "1 - add new contact\n"
               "2 - print all contacts\n"
               "3 - find number by name\n"
               "4 - find contact by number\n"
               "5 - save and exit\n");
    }

    int telbook() {
        TelBook ex;
        create_telbook(&ex);
        memory(&ex);
        ex.quantity = 0;
        int index = 0;
        FILE *finput = fopen(file_name, "r+");
        file_reader(finput, &ex, index);
        hint();
        while (1) {
            int a;
            scanf("%d", &a);
            switch (a) {
                case 0: {
                    free(ex.records);
                    fclose(finput);
                    break;
                }
                case 1: {
                    memory_controller(&ex);
                    add_contact(&ex);
                    break;
                }
                case 2: {
                    print_contacts(&ex);
                }
                case 3: {
                    printf("Contact Name:");
                    char name_find[N];
                    scanf("%s", name_find);
                    printf("Contact Surname:");
                    char surname_find[N];
                    scanf("%s", surname_find);
                    find_name(&ex, name_find, surname_find);
                    break;
                }
                case 4: {
                    printf("Contact number: ");
                    char number_find[N];
                    scanf("%s", number_find);
                    find_number(&ex, number_find);
                    break;
                }
                case 5: {
                    save_exit(finput, &ex);
                    exit(0);
                    break;
                }


                default: {
                    printf("Incorrect input");
                    hint();
                    break;
                }
            }
        }


        return 0;
    }

