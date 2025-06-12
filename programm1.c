#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 2000
#define ITENS 1000

void orderTime(long *timestamp, char **id, float *valor, int size){
    int flag = 1;
    while(flag) {
        flag = 0;
        for (int i = 0; i < size - 1; i++) {
            if (timestamp[i] > timestamp[i+1]) {
                long tempTimestamp = timestamp[i];
                timestamp[i] = timestamp[i + 1];
                timestamp[i + 1] = tempTimestamp;

                char* tempId = id[i];
                id[i] = id[i + 1];
                id[i + 1] = tempId;

                float tempValor = valor[i];
                valor[i] = valor[i + 1];
                valor[i + 1] = tempValor;

                flag = 1;
            }
        }
    }
}

int main(int argc, char const *argv[]){
    FILE *file;
    char text[LINE];
    char* idTypes[5] = {"TEMP", "PRESS", "UMID", "VIBR", "FLUX"};
    long timestampF[ITENS]; char* idF[ITENS]; float valorF[ITENS];
    long timestamp[ITENS]; char* id[ITENS]; float valor[ITENS];
    int times = 0, point = 0;

    while(times < 5){
        char filename[100];
        sprintf(filename, "%s.txt", idTypes[times]);

        file = fopen("test.txt", "r");  
        if(file == NULL){
            printf("Erro ao abrir o arquivo.");
            return 1;
        }

        fgets(text, LINE, file);
        point = 0;
        
        while (fgets(text, LINE, file) != NULL) {
            char *parser = strtok(text, " ");
            timestampF[point] = atol(parser);
    
            parser = strtok(NULL, " ");
            idF[point] = strdup(parser);

            parser = strtok(NULL, "\r\n");
            valorF[point] = atof(parser);

            #ifdef DEBUG
                printf("Timestamp: %ld, ID: %s, Valor: %.2f\n", timestampF[point], idF[point], valorF[point]);
            #endif

            point++;
        }
        fclose(file);

        for (int i = 0; i < ITENS; i++) {
            timestamp[i] = 0;
            id[i] = NULL;
            valor[i] = 0.0;
        }

        int index = 0;
        for(int i = 0; i < point; i++) {
            if (strcmp(idF[i], idTypes[times]) == 0) { 
                timestamp[index] = timestampF[i];
                id[index] = idF[i];
                valor[index] = valorF[i];
                index++;
            }
        }

        for(int i = 0; i < ITENS; i++){
            free(idF[i]);
        }

        orderTime(timestamp, id, valor, index);

        file = fopen(filename, "w");
        if(file == NULL){
            printf("Erro ao abrir o arquivo.");
            return 1;
        }

        fputs("TIMESTAMP ID VALOR\n", file);

        for(int i = 0; i < index; i++){
            fprintf(file, "%ld %s %.2f\n", timestamp[i], id[i], valor[i]);
        }

        fclose(file);

        times++;
    }
    return 0;
}