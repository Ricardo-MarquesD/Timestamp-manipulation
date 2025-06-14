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
    int times = 0, point = 0, count = 0;

    if (countID(&count, idTypes, ID_Q) != 0) {
        printf("Erro ao contar e capturar IDs.\n");
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
            if(parser == NULL){continue;}
            temp[point].tmstamp = atoll(parser);

            parser = strtok(NULL, " ");
            if(parser == NULL){continue;}
            strncpy(temp[point].ID, parser, sizeof(temp[point].valor));

            parser = strtok(NULL, "\r\n");
            if(parser == NULL){continue;}
            strncpy(temp[point].valor, parser, sizeof(temp[point].valor));
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
            fprintf(file, "%ld %s %s\n", data[i].tmstamp, data[i].ID, data[i].valor);
        }
        fclose(file);
        times++;
    }
    for (int i = 0; i < count; i++) {
        free(idTypes[i]);
    }
    return 0;
}