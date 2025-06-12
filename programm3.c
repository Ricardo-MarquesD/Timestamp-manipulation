#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timest.h"

int main(int argc, char const *argv[]){
    FILE *file;
    struct tm *pointData;
    time_t timeT;
    
    srand(time(NULL));
    timeT = getTime();
    pointData = localtime(&timeT);

    file = fopen("test.txt", "w");
    if(file == NULL){
        printf("Falha ao abri o arquivo.\n");
        return -1;
    }
    fputs("TIMESTAMP ID VALOR\n", file);
    for(int i = 0; i < CHAR_S-1; i++){
        for(int j = 0; j < 1000; j++){
            time_t randTimestamp = generateTimestamp(*pointData);
            fprintf(file, "%ld %s %.2f\n", randTimestamp, randomID(), randomValor());
        }
    }
    fclose(file);

    return 0;
}
