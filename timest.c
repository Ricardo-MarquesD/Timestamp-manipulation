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

void inputVerify(time_t *timestamp, char *input, char **id){
    int flag = 0;
    struct tm data;

    while (1){
        printf("Digite uma data (DD MM AAAA HH MM SS): ");
        if(scanf("%d %d %d %d %d %d", &data.tm_mday, &data.tm_mon, &data.tm_year, &data.tm_hour, &data.tm_min, &data.tm_sec) != 6){
            buffree();
            printf("Entrada de data invalida.\n");
            continue;
        }
        buffree();
        printf("Digite o id do sensor desejado: ");
        if(fgets(input,sizeof(input), stdin) == NULL){
            printf("Entrada de id invalido.\n");
            continue;
        }
        input[strcspn(input, "\n")] = 0;

        data.tm_mon = data.tm_mon - 1;
        data.tm_year = data.tm_year - 1900;
        data.tm_isdst = -1;
        *timestamp = mktime(&data);

        for(int i = 0; i < ID_S-1; i++){
            if(strcmp(input, id[i]) == 0){
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            printf("ID invalido.\n");
        } else if (*timestamp == -1) {
            printf("Timestamp invalido.\n");
        } else {
            return;
        }
    }
}

int binarySearch(data_t data[], int size, long long timeSet){
    int start = 0;
    int end = size - 1;
    int mid;
    int near = 0;

    while(start <= end){
        mid = (start + end) / 2;
        if (abs(data[mid].tmstamp - timeSet) < abs(data[near].tmstamp - timeSet)) {
            near = mid;
        }
        if(timeSet == data[mid].tmstamp){
            return mid;
        }else if(timeSet > data[mid].tmstamp){
            start = mid + 1;
        }else{
            end = mid - 1;
        }
    }
    
    return near;
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