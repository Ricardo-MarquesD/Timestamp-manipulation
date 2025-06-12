#ifndef TIMEST_H
#define TIMEST_H

#include <stdbool.h>
#include <time.h>

#define LINE 2000
#define ITENS 1000
#define DATA_SIZE 2000
#define ID_S 5
#define CHAR_S 16

typedef enum type_t{
    SENS_01,
    SENS_02,
    SENS_03,
    SENS_04,
}type_t;
typedef struct data_t{
    time_t tmstamp;
    type_t ID;
    union valor{
        int intType;
        bool boolType;
        double doubleType;
        char stringType[CHAR_S];
    };
    
}data_t;

void buffree();
void orderData(data_t *data[], int size);
void inputVerify(time_t *timestamp, char *input, char **id);
int binarySearch(data_t data[], int size, long long timeSet);
time_t getTime();
time_t generateTimestamp(struct tm data);
char randomID();
int randomInt();
bool randomBool();
double randomDouble();
char randomChar();

#endif