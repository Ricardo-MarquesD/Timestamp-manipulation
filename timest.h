#ifndef TIMEST_H
#define TIMEST_H

#include <stdbool.h>
#include <time.h>

#define LINE 2000
#define ITENS 1000
#define DATA_SIZE 2000
#define CHAR_S 16

typedef struct type_t{
    int intType;
    bool boolType;
    double doubleType;
    char stringType[CHAR_S];
}type_t;
typedef struct data_t{
    time_t tmstamp;
    char id[5];
    type_t type;
}data_t;

void buffree();
void orderData(data_t *data[], int size);
time_t generateTimestamp(int day, int mon, int year, int hour, int min, int sec);
time_t getTime();
char randomID();
int randomInt();
bool randomBool();
double randomDouble();
char randomChar();

#endif