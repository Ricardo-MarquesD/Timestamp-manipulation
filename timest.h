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
    union valor{
        int intType;
        bool boolType;
        double doubleType;
        char stringType[CHAR_S];
    }valor_u;
}data_t;

void buffree(); // Pronto
bool atob(const char *_Str); // Pronta
void orderData(data_t data[], int *quantity); // Pronta
int inputVerify(data_t *_generic, const char *charTime, const char *inputID); // Em testes
int binarySearch(data_t *data, int *size, time_t *timeSet); // Em testes
int countID(int *count, char *data_id[], int size, char *getType[]); // Pronta
time_t getTime(const char *charTime); // Pronto
time_t generateTimestamp(time_t *start_timestamp, time_t *final_timestamp); // Pronto
int randomInt(); // Pronto
bool randomBool(); // Pronto
double randomDouble(); // Pronto
char *randomString(); // Pronto

#endif