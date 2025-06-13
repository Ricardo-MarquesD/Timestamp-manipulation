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
    char *type = {0};
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
        if(parser == NULL){return -1;}
        data[index].tmstamp = atoll(parser);

        parser = strtok(NULL, " ");
        strncpy(data[index].ID, parser, sizeof(data[index].ID));

        parser = strtok(NULL, " ");
        type = strdup(parser);
        if(type == NULL){return -1;}

        parser = strtok(NULL, "\r\n");
        if (strcmp(type, "bool:") == 0) {
            data[index].valor_u.boolType = atob(parser);
        } else if (strcmp(type, "str:") == 0) {
            strcpy(data[index].valor_u.stringType, parser);
        } else if (strcmp(type, "double:") == 0) {
            data[index].valor_u.doubleType = atof(parser);
        } else if (strcmp(type, "int:") == 0) {
            data[index].valor_u.intType = atoi(parser);
        } else {
            printf("Tipo inválido!\n");
            free(type);
            return -1;
        }
        index++;
    }
    fclose(file);
    
    int indexBS = binarySearch(data, &index, &generic.tmstamp);
    if(indexBS < 0 || indexBS >= index){
        printf("Nao foi encontrado nenhum registro");
        return -1;
    }
    printf("O registro mais perto do pedido encontrado eh de: TIMESTAMP: %lld || ID: %s || ", data[indexBS].tmstamp, data[indexBS].ID);
    if(strcmp(type, "bool:") == 0){
        printf("VALOR: %s", data[indexBS].valor_u.boolType);
    }else if(strcmp(type, "str:") == 0){
        printf("VALOR: %s", data[indexBS].valor_u.stringType);
    }else if(strcmp(type, "double:") == 0){
        printf("VALOR: %.2lf", data[indexBS].valor_u.doubleType);
    }else if(strcmp(type, "int:") == 0){
        printf("VALOR: %d", data[indexBS].valor_u.intType);
    }else{
        printf("Tipo inválido!\n");
        return -1;
    }
    
    free(type);
    return 0;
}