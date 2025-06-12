#ifndef TIMEST_H
#define TIMEST_H

#include <stdbool.h>
#include <time.h>

#define LINE 2000
#define ITENS 1000
#define DATA_SIZE 2000
#define ID_S 4
#define CHAR_S 16

typedef struct data_t{
    time_t tmstamp;
    char ID[ID_S];
    union valor{
        int intType;
        bool boolType;
        double doubleType;
        char stringType[CHAR_S];
    }valor_u;
}data_t;

void buffree();
void orderData(data_t *data[], int size);
void inputVerify(time_t *timestamp, char *input, char **id);
int binarySearch(data_t data[], int size, long long timeSet);
time_t getTime(const char *charTime);
time_t generateTimestamp(time_t *start_timestamp, time_t *final_timestamp);
int randomInt();
bool randomBool();
double randomDouble();
char *randomString();

#endif