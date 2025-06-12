#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void buffree(){
    while(getchar() != '\n');
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

time_t generateTimestamp(int day, int mon, int year, int hour, int min, int sec){
    struct tm data;
    time_t start_timestamp, final_timestamp;
    
    data.tm_mday = day;
    data.tm_mon = mon - 1;
    data.tm_year = year - 1900;
    data.tm_isdst = -1;
    data.tm_hour = hour;
    data.tm_min = min;
    data.tm_sec = sec;

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

    #ifdef DEBUGGT
        printf("Timstamp incial: %ld . Timestamp final: %ld\n", start_timestamp, final_timestamp);
    #endif

    return result_timestamp;
}

char *randomID(){
    char *id[4] = {"TEMP", "PRESS", "UMID", "FLUX"};
    int i = rand() % 5;
    return id[i];
}

double randomValor(){
    return (double)rand()/100;
}

int main(int argc, char const *argv[]){
    FILE *file;
    struct tm *pointData;
    time_t timeT;
    
    srand(time(NULL));

    file = fopen("test.txt", "w");
    if(file == NULL){
        printf("Falha ao abri o arquivo.\n");
    }

    timeT = getTime();
    pointData = localtime(&timeT);

    fputs("TIMESTAMP ID VALOR\n", file);

    for(int i = 0; i < 1000; i++){
        time_t randTimestamp = generateTimestamp(pointData->tm_mday, pointData->tm_mon + 1, pointData->tm_year + 1900, pointData->tm_hour, pointData->tm_min, pointData->tm_sec);
        fprintf(file, "%ld %s %.2f\n", randTimestamp, randomID(), randomValor());
    }
    fclose(file);

    return 0;
}
