#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LINE 2000
#define ITENS 1000

void buffree(){
    while(getchar() != '\n');
}

void inputVerify(time_t* timestamp, char* input, char** id, int index){
    int year, mon, flag = 0;
    struct tm data;

    while (1){
        printf("Digite uma data (DD MM AAAA HH MM SS): ");
        if(scanf("%d %d %d %d %d %d", &data.tm_mday, &mon, &year, &data.tm_hour, &data.tm_min, &data.tm_sec) != 6){
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

        data.tm_mon = mon - 1;
        data.tm_year = year - 1900;
        data.tm_isdst = -1;

        *timestamp = mktime(&data);

        for(int i = 0; i < index; i++){
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

int binarySearch(long timestamp[], int size, long timeSet){
    int start = 0;
    int end = size - 1;
    int mid;
    int near = 0;

    while(start <= end){
        mid = (start + end) / 2;

        if (abs(timestamp[mid] - timeSet) < abs(timestamp[near] - timeSet)) {
            near = mid;
        }

        if(timeSet == timestamp[mid]){
            return mid;
        }else if(timeSet > timestamp[mid]){
            start = mid + 1;
        }else{
            end = mid - 1;
        }
    }

    return near;
}

int main(int argc, char const *argv[]){
    FILE* file;
    time_t t;
    int index = 0;
    long timestampFile[ITENS];
    float valor[ITENS];
    char* id[ITENS];
    char* idTypes[5] = {"TEMP", "PRES", "UMID", "VIBR", "FLUX"};
    char input[10], text[LINE];

    inputVerify(&t, input, idTypes, 5);

    strncat(input, ".txt", sizeof(input) - strlen(input) - 1);

    file = fopen(input, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", input);
        return 1;
    }

        while(fgets(text, LINE, file) != NULL){
            char* parser = strtok(text, " ");
            timestampFile[index] = atol(parser);

            parser = strtok(NULL, " ");
            id[index] = strdup(parser);

            parser = strtok(NULL, "\r\n");
            valor[index] = atof(parser);

            //printf("Timestamp: %ld, ID: %s, Valor: %.2f\n", timestampFile[index], id[index], valor[index]);

            index++;
        }
    fclose(file);

    int indexBS = binarySearch(timestampFile, index, t);

    if(indexBS >= 0 && indexBS < index){
        printf("O registro mais perto do pedido encontrado e de: TIMESTAMP: %ld | ID: %s | VALOR: %.2f", timestampFile[indexBS], id[indexBS], valor[indexBS]);
    }else{
        printf("Nao foi encontrado nenhum registro");
    }
    
    return 0;
}
