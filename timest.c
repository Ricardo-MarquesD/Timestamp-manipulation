#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "timest.h"

void buffree(){
    while(getchar() != '\n');
}

void orderData(data_t *data[], int size){
    int flag = 1;
    while(flag) {
        flag = 0;
        for (int i = 0; i < size - 1; i++) {
            if (data[i]->tmstamp > data[i+1]->tmstamp) {
                data_t *temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;

                flag = 1;
            }
        }
    }
}

time_t generateTimestamp(struct tm data){
    time_t start_timestamp, final_timestamp;
    
    data.tm_mon = data.tm_mon - 1;
    data.tm_year = data.tm_year - 1900;
    data.tm_isdst = -1;
    start_timestamp = mktime(&data);
    if(start_timestamp == -1){
        printf("Data invalido no timestamp\n");
        return -1;
    }

    data.tm_mday += 3;
    data.tm_hour += 23;
    data.tm_min += 59;
    data.tm_sec += 59;
    final_timestamp = mktime(&data);
    if(final_timestamp == -1){
        printf("Data invalido no timestamp\n");
        return -1;
    }

    time_t result_timestamp = start_timestamp + rand() % (final_timestamp - start_timestamp + 1);
    return result_timestamp;
}

time_t getTime(){
    int year, mon;
    struct tm data;

    while (1){
        printf("Digite uma data (DD MM AAAA HH MM SS): ");
        if(scanf("%d %d %d %d %d %d", &data.tm_mday, &mon, &year, &data.tm_hour, &data.tm_min, &data.tm_sec) != 6){
            buffree();
            printf("Entrada de data invalida.\n");
            continue;
        }
        data.tm_mon = mon - 1;
        data.tm_year = year - 1900;
        data.tm_isdst = -1;
        time_t timestamp = mktime(&data);
        if(timestamp == -1){
            printf("Valor do timestamp invalido.\n");
        }else{
            return timestamp;
        }
    } 
}

char randomID(){
    char *id[4] = {"TEMP", "PRESS", "UMID", "FLUX"};
    int i = rand() % 4;
    return *id[i];
}

int randomInt(){
    return rand()%10;
}

bool randomBool(){
    return (bool)rand()%2;
}

double randomDouble(){
    return (double)rand()/RAND_MAX;
}

char randomChar(){
    char letter[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    static char random[CHAR_S];
    for(int i = 0; i < CHAR_S-1; i++){
        random[i] = letter[rand()%26];
    }
    random[CHAR_S-1] = '\0';
    return random;
}