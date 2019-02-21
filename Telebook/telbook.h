#pragma once
#include <stdio.h>

typedef struct record record;
typedef struct TelBook TelBook;

int telbook();

void add_contact(TelBook *ex);
void print_contacts(TelBook *ex);
void find_name(TelBook *ex, char *name_find, char *surname_find);
void find_number(TelBook *ex, char *number_find);
void save(FILE *finput, TelBook *ex);

int memory_controller(TelBook *ex);

void hint();

void create_telbook(TelBook *ex);
void file_reader(FILE *finput, TelBook *ex);