#ifndef TIMEST_H
#define TIMEST_H

#include <stdbool.h>
#include <time.h>

#define LINE 2000
#define DATA_SIZE 8000
#define ID_S 10
#define ID_Q 4
#define CHAR_S 16

typedef struct data_t{
    time_t tmstamp;
    char ID[ID_S];
    char valor[CHAR_S];
}data_t;

void buffree();
bool atob(const char *_Str);
void orderData(data_t data[], int *quantity);
int inputVerify(data_t *_generic, const char *charTime, const char *inputID);
int binarySearch(data_t *data, int *size, time_t *timeSet);
int countID(int *count, char *data_id[], int size);
time_t getTime(const char *charTime);
time_t generateTimestamp(time_t *start_timestamp, time_t *final_timestamp);
int randomInt();
bool randomBool();
double randomDouble();
char *randomString();

#endif