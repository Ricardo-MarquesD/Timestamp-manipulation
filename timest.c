#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "timest.h"

void buffree(){
    while(getchar() != '\n');
}

bool atob(const char *_Str){
    if(_Str == NULL){
        printf("Valor de str_file invalido.\n");
    }
    return strcmp(_Str, "true") == 0 ? 1 : 0;
}

void orderData(data_t data[], int *quantity){
    int flag = 1;
    while(flag) {
        flag = 0;
        for (int i = 0; i < *quantity - 1; i++) {
            if (data[i].tmstamp > data[i+1].tmstamp) {
                data_t temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;

                flag = 1;
            }
        }
    }
}

int inputVerify(data_t *_generic, const char *charTime, const char *inputID){
    if(charTime == NULL || inputID == NULL){
        printf("Parametro NULL informado.\n");
        return -1;
    }
    int flag = 0;
    struct tm data = {0};

    if(sscanf(charTime, "%d/%d/%d %d:%d:%d", &data.tm_mday, &data.tm_mon, &data.tm_year, &data.tm_hour, &data.tm_min, &data.tm_sec) != 6){
        printf("Falha de transformação.\n");
        return -1;
    }
    data.tm_mon = data.tm_mon - 1;
    data.tm_year = data.tm_year - 1900;
    data.tm_isdst = -1;
    strcpy(_generic->ID, inputID);
    if(_generic->ID[0] == '\0'){
        printf("ID invalido ou nao encontrado.\n");
        return -1;
    }
    _generic->tmstamp = mktime(&data);
    if (inputID == NULL) {
        printf("Timestamp invalido.\n");
        return -1;
    }
    return 0;
}

int binarySearch(data_t *data, int *size,  time_t *timeSet){
    if (*size <= 0) {
        return -1;
    }
    int start = 0;
    int end = *size - 1;
    int mid;
    int near = 0;

    while(start <= end){
        mid = (start + end) / 2;
        if (llabs(data[mid].tmstamp - *timeSet) < llabs(data[near].tmstamp - *timeSet)) {
            near = mid;
        }
        if(*timeSet == data[mid].tmstamp){
            return mid;
        }else if(*timeSet > data[mid].tmstamp){
            start = mid + 1;
        }else{
            end = mid - 1;
        }
    }
    
    return near;
}

int countID(int *count, char *data_id[], int size){
    if(count == NULL){return -1;}
    
    FILE *file;
    char buffer[LINE];
    char *id = NULL;
    *count = 0;
    int nLinha = 1;

    file = fopen("test.txt", "r");
    if(file == NULL){return -1;}
    fgets(buffer, LINE, file);
    while(fgets(buffer, LINE, file)){
        nLinha++;
        char *parser = strtok(buffer, " ");
        if(parser == NULL) {
            printf("Linha %d invalida, em text.txt. Portanto, linha pulada.\n", nLinha);
            continue;
        }

        parser = strtok(NULL, " "); 
        if(parser == NULL) {
            printf("Linha %d invalida, em text.txt. Portanto, linha pulada.\n", nLinha);
            continue;
        }
        char *copy = strdup(parser);
        if(copy == NULL){
            fclose(file);
            free(id);
            return -1;
        }
        parser = strtok(NULL, " ");
        if(parser == NULL) {
            printf("Linha %d invalida, em text.txt. Portanto, linha pulada.\n", nLinha);
            continue;
        }
        if(id == NULL || strcmp(copy, id) != 0){
            if(*count < size){
                data_id[*count] = copy;
                (*count)++;
                free(id);
                id = strdup(copy);
            } else {
                free(copy);
                break;
            }
        } else {
            free(copy);
        }
    }
    fclose(file);
    free(id);
    return 0;
}


time_t getTime(const char *charTime){
    struct tm data;
    int mday, mon, year, hour, min, sec;
    if(sscanf(charTime, "%d/%d/%d %d:%d:%d", &mday, &mon, &year, &hour, &min, &sec) != 6){
        printf("Falha de transformação.\n");
        return -1;
    }
    if(mday > 31 || mon > 12 || hour > 24 || min > 60 || sec > 60){
        printf("Argumento(s) de data invalida: Valores de data, muito acima do esperado\n");
        return -1;
    }else if(mday < 1 || mon < 1 || hour < 0 || min < 0 || sec < 0){
        printf("Argumento(s) de data invalida: Valores de data, muito abaixo do esperado\n");
        return -1;
    }

    data.tm_mday = mday;
    data.tm_mon = mon - 1;
    data.tm_year = year - 1900;
    data.tm_hour = hour;
    data.tm_min = min;
    data.tm_sec = sec;
    data.tm_isdst = -1;

    time_t timestamp = mktime(&data);
    if(timestamp == -1){
        printf("Valor do timestamp invalido.\n");
    }else{
        return timestamp;
    }
}

time_t generateTimestamp(time_t *start_timestamp, time_t *final_timestamp){ 
    time_t result_timestamp = *start_timestamp + rand() % (*final_timestamp - *start_timestamp + 1);
    return result_timestamp;
}

int randomInt(){
    return rand()%10;
}

bool randomBool(){
    return rand()%2;
}

double randomDouble(){
    return (double)rand()/RAND_MAX;
}

char *randomString(){
    char letter[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    static char random[CHAR_S];
    for(int i = 0; i < CHAR_S-1; i++){
        random[i] = letter[rand()%26];
    }
    random[CHAR_S-1] = '\0';
    return random;
}