#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "timest.h"

int main(int argc, char const *argv[]){
    if(argc < 5 || argc > 11){
        printf("Error: quantidade invalidade de argumento.\n");
        return -1;
    }
    srand(time(NULL));
    FILE *file;
    int size = (argc - 3)/2;
    time_t start_timestamp = getTime(argv[1]);
    time_t final_timestamp = getTime(argv[2]);

    file = fopen("test.txt", "w");
    if(file == NULL){
        printf("Falha ao abri o arquivo.\n");
        return -1;
    }
    fputs("TIMESTAMP ID VALOR\n", file);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < 2000; j++){
            int index = size+3;
            time_t tmstamp = generateTimestamp(&start_timestamp, &final_timestamp);

            if(!strcmp(argv[index+i], "bool")){
                fprintf(file, "%ld %s bool: %s\n", tmstamp, argv[3+i], randomBool() ? "true" : "false");
            }else if(!strcmp(argv[index+i], "String")){
                fprintf(file, "%ld %s str: %s\n", tmstamp, argv[3+i], randomString());
            }else if(!strcmp(argv[index+i], "double")){
                fprintf(file, "%ld %s double: %.2lf\n", tmstamp, argv[3+i], randomDouble());
            }else if(!strcmp(argv[index+i], "int")){
                fprintf(file, "%ld %s int: %d\n", tmstamp, argv[3+i], randomInt());
            }else {printf("Tipo de sensor invalido!\n"); return -1;}
        }
    }
    fclose(file);

    return 0;
}
