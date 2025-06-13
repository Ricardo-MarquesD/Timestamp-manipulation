#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timest.h"

int main(int argc, char const *argv[]) {
    FILE *file;
    data_t temp[DATA_SIZE] = {0};
    data_t data[DATA_SIZE] = {0};
    char text[LINE] = {0};
    char *idTypes[ID_Q] = {0};
    char *keyType[ID_Q] = {0};
    int times = 0, point = 0, count = 0;

    if (countID(&count, idTypes, ID_Q, keyType) != 0) {
        printf("Erro ao contar IDs.\n");
        return -1;
    }

    while (times < count) {
        char filename[100];
        sprintf(filename, "%s.txt", idTypes[times]);

        file = fopen("test.txt", "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return -1;
        }

        fgets(text, LINE, file);
        point = 0;

        while (fgets(text, LINE, file) != NULL) {
            char *parser = strtok(text, " ");
            temp[point].tmstamp = atoll(parser);

            parser = strtok(NULL, " ");
            strcpy(temp[point].ID, parser);

            parser = strtok(NULL, " ");
            char *type = strdup(parser);

            parser = strtok(NULL, "\r\n");
            if (strcmp(type, "bool:") == 0) {
                temp[point].valor_u.boolType = atob(parser);
            } else if (strcmp(type, "str:") == 0) {
                strcpy(temp[point].valor_u.stringType, parser);
            } else if (strcmp(type, "double:") == 0) {
                temp[point].valor_u.doubleType = atof(parser);
            } else if (strcmp(type, "int:") == 0) {
                temp[point].valor_u.intType = atoi(parser);
            } else {
                printf("Tipo inválido!\n");
                free(type);
                return -1;
            }
            free(type);
            point++;
        }
        fclose(file);

        int index = 0;
        for (int i = 0; i < point; i++) {
            if (strcmp(temp[i].ID, idTypes[times]) == 0) {
                data[index++] = temp[i];
            }
        }
        orderData(data, &index);

        file = fopen(filename, "w");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return -1;
        }
        fputs("TIMESTAMP ID VALOR\n", file);
        for (int i = 0; i < index; i++) {
            fprintf(file, "%ld %s ", data[i].tmstamp, data[i].ID);

            if (strcmp(keyType[times], "bool:") == 0) {
                fprintf(file, "bool: %s\n", data[i].valor_u.boolType ? "true" : "false");
            } else if (strcmp(keyType[times], "str:") == 0) {
                fprintf(file, "str: %s\n", data[i].valor_u.stringType);
            } else if (strcmp(keyType[times], "double:") == 0) {
                fprintf(file, "double: %.2lf\n", data[i].valor_u.doubleType);
            } else if (strcmp(keyType[times], "int:") == 0) {
                fprintf(file, "int: %d\n", data[i].valor_u.intType);
            } else {
                printf("Tipo inválido!\n");
                return -1;
            }
        }
        fclose(file);
        times++;
    }
    for (int i = 0; i < count; i++) {
        free(idTypes[i]);
        free(keyType[i]);
    }
    return 0;
}