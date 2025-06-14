#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "timest.h"

int main(int argc, char const *argv[]){
    if(argc != 3){
        printf("Entrata invalidas, muito argumento");
        return -1;
    }
    FILE* file;
    data_t generic = {0};
    data_t data[DATA_SIZE] = {0};
    int index = 0;
    char text[LINE];
    char filename[20];

    inputVerify(&generic, argv[1], argv[2]);
    strncpy(filename, generic.ID, sizeof(filename));
    strncat(filename, ".txt", sizeof(filename)-strlen(filename)-1);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return 1;
    }

    fgets(text, LINE, file);
    while(fgets(text, LINE, file) != NULL){
        char* parser = strtok(text, " ");
        if(parser == NULL){continue;}
        data[index].tmstamp = atoll(parser);

        parser = strtok(NULL, " ");
        if(parser == NULL){continue;}
        strncpy(data[index].ID, parser, sizeof(data[index].ID));

        parser = strtok(NULL, "\r\n");
        if(parser == NULL){continue;}
        strncpy(data[index].valor, parser, sizeof(data[index].valor));
        index++;
    }
    fclose(file);
    
    int indexBS = binarySearch(data, &index, &generic.tmstamp);
    if(indexBS < 0 || indexBS >= index){
        printf("Nao foi encontrado nenhum registro");
        return -1;
    }
    printf("O registro mais perto do pedido encontrado eh de: TIMESTAMP: %lld || ID: %s || VALOR: %s", data[indexBS].tmstamp, data[indexBS].ID, data[indexBS].valor);
    return 0;
}