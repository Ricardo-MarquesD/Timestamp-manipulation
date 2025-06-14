# Projeto de Manipulação de Arquivo usando timestamp's:

Este projeto em linguagem C simula a geração, ordenação, armazenamento e consulta de dados de sensores com diferentes tipos de valor (`int`, `bool`, `double`, `String`), utilizando arquivos como forma de persistência.

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- `programm1.c`: Lê o `test.txt`, separa e ordena os dados por ID em arquivos distintos.
- `programm2.c`: Consulta registros em arquivos separados com base em um timestamp e ID fornecidos.
- `programm3.c`: Gera dados de sensores aleatórios e os salva em um arquivo `test.txt`.
- `timest.h`: Arquivo de cabeçalho que define estruturas e declara as funções auxiliares.
- `timest.c`: Implementa funções auxiliares para manipulação e ordenação de dados, além de geração aleatória.

---

## Estrutura do `typedef struct data_t`
```c
    typedef struct data_t{
    time_t tmstamp;
    char ID[ID_S];
    char valro[CHAR_S]
    }data_t;
```

---

## Formato do arquivo.txt:

- Estrutura dos arquivos em .txt:
```
    TIMESTAMP ID VALOR(cabeçalho)
    <timestamp> <ID> <valor>(como está escrito)
```

- Exemplo:
```
    TIMESTAMP ID VALOR
    1749852106 sensor1 true
```

---

## Programm 01

- Compilação: ```gcc programm1.c timest.c -o play1```
- Execução: ```.\play1.exe```

### Funções usadas nesse programa:

- orderData(): Ordena dados por timestamp.
- countID(): Conta IDs únicos e identifica seus tipos no test.txt.

---

## Programm 02

- Compilação: ```gcc programm2.c timest.c -o play1```
- Execução: ```.\play2.exe <data> <nome_sensor>```
- Formatação das datas: ```"DD/MM/YYYY HH/MM/SS"```;
- Exemplo: ```.\play2.exe "14/06/2025 16:01:00" sensor2```

### Funções usadas nesse programa:

- inputVerify(): Faz a conversão dos argumentos em um dado_t generico.
- binarySearch(): Busca binária por timestamp mais próximo.

---

## Programm 03

- Compilação: ```gcc programm3.c timest.c -o play1```
- Execução: ```.\play3.exe <data_inicial> <data_final> <nome_sensor> <tipo_de_dado>```
- Formatação das datas: ```"DD/MM/YYYY HH/MM/SS"```;
- Exemplo: ```.\play3.exe "13/06/2025 15:58:12" "15/06/2025 15:58:12" sensor1 sensor2 bool String```

### Funções usadas nesse programa:

- getTime(): Converte e valida entradas de data e transforma em timestamp.
- randomInt(), randomDouble(), randomBool(), randomString(): Geradores aleatórios de valores, de acordo com o tipo de valor.