/*
Pretende-se elaborar um programa em linguagem C que apoie na gestão de requisições
de livros de uma biblioteca por parte dos seus leitores. O programa deverá incluir a
informação referente aos livros e aos leitores e garantir que, no máximo, existirão NLIVROS
livros e NLEITORES leitores. Para cada leitor deverão também ser guardados as últimas 10
requisições efetuadas. O programa deverá permitir a realização das seguintes operações:

1. Registar Livro
Opção que permite, se possível, registar a seguinte informação referente a um livro
(dados introduzidos através do teclado com exceção do estado):
▪ ISBN (International Standard Book Number), será um número único
▪ Título;
▪ Autor;
▪ Editora;
▪ Estado, que poderá ser: disponível, requisitado ou inutilizado. No entanto, no acto
do registo, o estado do livro deverá ser automaticamente “disponível”

2. Registar Leitor
Opção que permite, se possível, registar um leitor. Para tal deverão ser solicitados os
seguintes dados (introduzidos através do teclado):
▪ Código de leitor (único)
▪ Nome;
▪ Data de Nascimento;
▪ Localidade
▪ Contacto telefónico

3. Requisitar Livro
Opção que permite um leitor já registado requisitar um livro disponível. Nesta opção, além
das identificações do livro e do leitor, deverá ser solicitada a data de requisição.

4. Devolver Livro
Opção que permite registar a devolução de um livro requisitado bem como o número de
dias que esteve requisitado. Nesta opção deverá ser tido em conta se o livro regressa
inutilizado

5. Listagens
Esta opção deverá apresentar um submenu com as seguintes opções:
▪ Listagem de todos os dados de todos os Livros.
▪ Listagem de todos os dados de todos os Leitores.
▪ Listagem dos livros já requisitados e no final a quantidade total desses livros.
▪ Listagem das 10 últimas requisições efetuadas por um determinado leitor.

0. Sair
Opção que permite ao utilizador sair do programa e guardar para um ficheiro binário
todos os dados do programa

Notas Importantes
▪ Ao iniciar o programa todos os dados armazenados no ficheiro binário deverão ser
carregados para o programa.
▪ Se achar pertinente poderá acrescentar outros campos nas estruturas criadas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

#define MAX_NUM_LIVROS 20
#define MAX_NUM_LEITORES 20

uint8_t Total_Livros;
uint8_t Total_Leitores;
uint8_t Total_Requisicoes;

int livro_count=0;
int leitor_count=0;

//ESTRUTURAS DE DADOS
typedef struct {
    char ISBN[14];
    char titulo[100];
    char autor[100];
    char editora[100];
    char estado[1]; //D-disponivel, R-requisitado, I-inutilizado
} Livro_t;

typedef struct {
    char codigo_leitor[20];
    char nome[50];
    char data_nascimento[11];
    char localidade[50];
    char contato_telefonico[9];
} Leitor_t;

char Menu_Pincipal(void);
char Registar_Livro(Livro_t livro[]);
char Registar_Leitor(Leitor_t leitor[]);
char Requisitar_Livro(Leitor_t leitor[], Livro_t livro[]);
char Devolver_Livro(void);
char Listagens(void);
void Listagem_livros(Livro_t livro[]);
void Listagem_leitores(Leitor_t leitor[]);
void Listagem_livros_requisitados(Livro_t livro[]);
void Listagem_ultimas_requisicoes(Leitor_t leitor[]);
char keyboard_Read();
char S_or_N(void);

void main(){

    char menu1, menu2;

    Livro_t livro[MAX_NUM_LIVROS];
    Leitor_t leitor[MAX_NUM_LEITORES];

    //Copies the character 0 to the first n characters of the string pointed to, by the argument str.
    memset(&livro, 0, sizeof(livro));   //Coloca todos os bytes da estrutura a 0
    memset(&leitor, 0, sizeof(leitor)); //Coloca todos os bytes da estrutura a 0

    load_data(&livro,&leitor);//load the data from the file

    //Check the struck and count the number of books and readers
    for (int i = 0; i < MAX_NUM_LIVROS; i++){
        if (livro[i].ISBN[0] != 0){
            livro_count++;
        }
    }

    for (int i = 0; i < MAX_NUM_LEITORES; i++){
        if (leitor[i].codigo_leitor[0] != 0){
            leitor_count++;
        }
    }

    do{
        menu1 = Menu_Pincipal();
        switch (menu1){
        case '1':
            do{
                menu2 = Registar_Livro(livro);

            }while (menu2 != 0);
            break;
        case '2':
            do{
                menu2 = Registar_Leitor(leitor);

            } while (menu2 != 0);
            break;
        case '3':
            do{
                menu2 = Requisitar_Livro(leitor, livro);

            } while (menu2 != 0);
            break;
        case '4':
            do{
                menu2 = Devolver_Livro();


            } while (menu2 != 0);
            break;

        case '5':
            do{
                menu2 = Listagens();

                switch (menu2){
                case '1':
                    Listagem_livros(livro);
                    break;
                case '2':
                    Listagem_leitores(leitor);
                    break;
                case '3':
                    Listagem_livros_requisitados(livro);
                    break;
                case '4':
                    Listagem_ultimas_requisicoes(leitor);
                    break;
                }

            } while (menu2 != 0);
            break;

        case '0':
            system("cls");
            // menu1 = Confirm_Exit();
            break;
        }
    } while (menu1 != 'S' && menu1 != 's' );

    system("cls");

    save_data(&livro,&leitor);


    printf("\n\n\n\t\t-----FIM-----\n\n\n");
}

char Menu_Pincipal(){
    char menu;

    // ############## UI ##############
    system("cls");
    system("color 70");
    printf("%c", 201); // canto superior esquerdo
    for (uint8_t i = 1; i < 92; i++){
        printf("%c", 205); // linha horizontal
    }
    printf("%c", 187);   // canto superior direito
    printf("\n%c", 186); // linha vertical
    for (uint8_t i = 1; i < 12; i++){
        printf("\t");
    }
    printf("    %c", 186); // linha vertical
    printf("\n%c\t\t\t-- Gest%co de Requisi%c%ces de uma Biblioteca --\t\t\t    %c", 186, 198, 135, 228, 186);
    printf("\n%c", 186); // linha vertical
    for (uint8_t i = 1; i < 12; i++){
        printf("\t");
    }
    printf("    %c\n", 186); // linha vertical
    printf("%c\tTotal de Livros:%d \t\t\tTotal de Leitores:%d \t\t\t    %c\n", 186, livro_count, leitor_count, 186);
    printf("%c\tTotal de Requisi%c%ces ativas:%d\t", 186, 135, 228, Total_Requisicoes);
    for (uint8_t i = 1; i < 7; i++){
        printf("\t");
    }
    printf("    %c\n", 186); // linha vertical
    printf("%c", 186);       // linha vertical
    for (uint8_t i = 1; i < 12; i++){
        printf("\t");
    }
    printf("    %c", 186); // linha vertical
    printf("\n%c", 200);   // canto inferior esquerdo
    for (uint8_t i = 1; i < 92; i++){
        printf("%c", 205); // linha horizontal
    }
    printf("%c", 188); // canto inferior direito

    printf("\n\n\t%c 1-Registar Livro\n", 175);
    printf("\t%c 2-Registar Leitor\n", 175);
    printf("\t%c 3-Requisitar Livro\n", 175);
    printf("\t%c 4-Devolver Livro\n", 175);
    printf("\t%c 5-Listagens\n", 175);
    printf("\t%c S-Sair\n\n", 175);
    printf("\t\tOP%c%cO: ", 128, 199);
    // ################################

    menu = keyboard_Read();
    return menu;
}

char Registar_Livro(Livro_t livro[]){

    //############## UI ##############
    system("cls");
    printf("%c",201);
    for (uint8_t i = 1; i < 66; i++) {
             printf("%c",205);
            }
    printf("%c\n",187);
    printf("%c",186);
    for (uint8_t i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("  %c\n",186);

    printf("%c\t\t\t-- Registar Livro --\t\t\t  %c\n",186,186);
    printf("%c",186);
    for (uint8_t i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("  %c",186);
    printf("\n%c",200);
        for (uint8_t i = 1; i < 66; i++) {
             printf("%c",205);
            }
    printf("%c",188);
    //################################

    char menu;
    livro_count++;

    printf("\n\n\t%c ISBN: ",175);
    fgets(livro[livro_count].ISBN, sizeof(livro->ISBN), stdin);

    printf("\t%c Titulo do Livro: ",175);
    fgets(livro[livro_count].titulo, sizeof(livro->titulo), stdin);

    printf("\t%c Autor do Livro: ",175);
    fgets(livro[livro_count].autor, sizeof(livro->autor), stdin);

    printf("\t%c Editora do Livro: ",175);
    fgets(livro[livro_count].editora, sizeof(livro->editora), stdin);

    printf("\t%c Estado do Livro: DISPONIVEL\n\n",175);
    livro[livro_count].estado[0] = 'D';

    printf("\tDeseja confirmar registo%? [S/N]");

    char sim_nao= S_or_N();
    switch (sim_nao){
    case 'S':
        printf("\n\tLivro Registado com Sucesso!\n\n");
        usleep(500000); //delay de 500ms

        break;
    case 'N':
        for(int i=0;i<100;i++){
            livro[livro_count].ISBN[i] = 0;
            livro[livro_count].titulo[i] = 0;
            livro[livro_count].autor[i] = 0;
            livro[livro_count].editora[i] = 0;
            livro[livro_count].estado[i] = 0;
        }
        livro_count--;
        printf("\n\tLivro N%co Registado!\n\n",198);
        usleep(500000); //delay de 500ms
        break;
    }

    printf("\tDeseja Continuar%? [S/N] ");

    char sim_nao2 = S_or_N();

    if(sim_nao2 == 'S'){
        menu = 1;
        return menu;
    }
    else if(sim_nao2 == 'N'){
        menu = 0;
        return menu;
    }
}

char Registar_Leitor(Leitor_t leitor[]){

    //############## UI ##############
    system("cls");
    printf("%c",201);
    for (uint8_t i = 1; i < 67; i++) {
             printf("%c",205);
            }
    printf("%c\n",187);
    printf("%c",186);
    for (uint8_t i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("   %c\n",186);

    printf("%c\t\t\t-- Registar Leitor --\t\t\t   %c\n",186,186);
    printf("%c",186);
    for (uint8_t i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("   %c",186);
    printf("\n%c",200);
        for (uint8_t i = 1; i < 67; i++) {
             printf("%c",205);
            }
    printf("%c",188);
    //################################

    char menu;
    leitor_count++;

    printf("\n\n\t%c Codigo de Leitor: ",175);
    fgets(leitor[leitor_count].codigo_leitor, sizeof(leitor->codigo_leitor), stdin);

    printf("\t%c Nome: ",175);
    fgets(leitor[leitor_count].nome, sizeof(leitor->nome), stdin);

    printf("\t%c Data nascimento: ",175);
    fgets(leitor[leitor_count].data_nascimento, sizeof(leitor->data_nascimento), stdin);

    printf("\t%c Localidade: ",175);
    fgets(leitor[leitor_count].localidade, sizeof(leitor->localidade), stdin);

    printf("\t%c Numero de Telefone: ",175);
    fgets(leitor[leitor_count].contato_telefonico, sizeof(leitor->contato_telefonico), stdin);

    //printf("\t%c Email: **\n\n",175);

    printf("\tDeseja confirmar registo%? [S/N]");
    char sim_nao= S_or_N();
    switch (sim_nao){
    case 'S':
        printf("\n\tLeitor Registado com Sucesso!\n\n");
        usleep(500000); //delay de 500ms

        break;
    case 'N':
        for(int i=0;i<100;i++){
            leitor[leitor_count].codigo_leitor[i] = 0;
            leitor[leitor_count].nome[i] = 0;
            leitor[leitor_count].data_nascimento[i] = 0;
            leitor[leitor_count].localidade[i] = 0;
            leitor[leitor_count].contato_telefonico[i]= 0;
        }
        leitor_count--;
        printf("\n\tLeitor N%co Registado!\n\n",198);
        usleep(500000); //delay de 500ms
        break;
    }

    printf("\tDeseja Continuar%? [S/N] ");

    char sim_nao2 = S_or_N();

    if(sim_nao2 == 'S'){
        menu = 1;
        return menu;
    }
    else if(sim_nao2 == 'N'){
        menu = 0;
        return menu;
    }
}

char Requisitar_Livro(Leitor_t leitor[], Livro_t livro[]){

    //############## UI ##############
    system("cls");
    printf("%c",201);
    for (uint8_t i = 1; i < 67; i++) {
             printf("%c",205);
            }
    printf("%c\n",187);
    printf("%c",186);
    for (uint8_t i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("   %c\n",186);

    printf("%c\t\t\t-- Requisitar livro --\t\t\t   %c\n",186,186);
    printf("%c",186);
    for (uint8_t i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("   %c",186);
    printf("\n%c",200);
        for (uint8_t i = 1; i < 67; i++) {
             printf("%c",205);
            }
    printf("%c\n",188);
    //################################

    char menu;
    //Opção que permite um leitor já registado requisitar um livro disponível. Nesta opção, além das identificações do livro e do leitor, deverá ser solicitada a data de requisição.

    printf("\tInserir Codigo do Leitor:");
    //percorrer o array de leitores e verificar se o codigo existe
    char codigo_leitor_compare[100];
    fgets(codigo_leitor_compare, sizeof(codigo_leitor_compare), stdin);
    for(int i=0;i<leitor_count;i++){
        if(strcmp(codigo_leitor_compare,leitor[i].codigo_leitor)==0){
            printf("\tIntroduzir codigo existente%!\n");
            //mostrar codigos existentes
            for(int i=0;i<leitor_count;i++){
                    printf("Codigos disponiveis:\n")
                    printf("\tCodigo: %s\n",leitor[i].codigo_leitor);
            }
            if(leitor_count==0){
                printf("\tNao existem codigos disponiveis!\n");
                printf("\tA voltar ao menu principal...")
                sleep(1);
                menu = 0;
                return menu;
            }
            break;
        }
        else{
            printf("\tDeseja Registar novo Leitor%? [Y/N]\n");
            char sim_nao2 = S_or_N();

            if (sim_nao2 == 'S'){
                menu = 1;
                return menu;
            }
            else if (sim_nao2 == 'N'){
                menu = 0;
                return menu;
            }
            break;
        }
    }

    printf("\tIntroduzir codigo existente%! [Y/N]\n");
    printf("\tDeseja Registar novo Leitor%? [Y/N]\n");
    printf("\tNome: **\n");
    printf("\tData da requisicao: **\n\n");
    printf("\tDeseja confirmar requisicao%? [Y/N]\n");
    printf("\tDeseja Continuar%? [Y/N] ");

    menu = keyboard_Read();
    return menu;
}

char Devolver_Livro(){
    char menu;
    system("cls");
    printf("\n\t\t\t-- Devolver Livro_t --\n\n");

    printf("\tISBN: **\n");
    printf("\tData da entrega: **\n");
    printf("\tDias de utilizacao: **\n");
    printf("\tEstado do Livro: [1-inutilizavel/2-utilizavel]\n\n");
    printf("\tDeseja confirmar devolucao%? [S/N]\n");
    printf("\tDeseja Continuar%? [S/N] ");

    menu = keyboard_Read();
    return menu;
}

char Listagens(void){

    //############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Listagens --\t\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n",188);
    //################################

    //menu para apresentar as listas

    char menu;
    printf("\t1 - Lista de Livros\n");
    printf("\t2 - Lista de Leitores\n");
    printf("\t3 - Lista de Requisicoes\n");
    printf("\t4 - Lista de ultimas Requisicoes\n\n");
    printf("\tOpcao: ");

    menu = keyboard_Read();
    return menu;
}

void Listagem_livros(Livro_t livro[]){

    //############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Livros --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);

    }
    printf("%c\n",188);
    //################################

    //apresentar todos dos livros existentes na estrutura de dados
    for(uint8_t i=0;i<livro_count;i++){
        printf("ISBN: %s\n",livro[i].ISBN);
        printf("Titulo: %s\n",livro[i].titulo);
        printf("Autor: %s\n",livro[i].autor);
        printf("Editora: %s\n",livro[i].editora);
        printf("Estado: %s\n",livro[i].estado);
        printf("-----------------------------\n");
    }
    if (livro_count == 0){
        printf("\n\tNao existem livros registados!\n\n");
    }

    printf("\n\n\tPressione qualquer tecla para voltar ao menu das listagens...");

    char menu;
    scanf("%c",&menu);

    return menu;
}

void Listagem_leitores(Leitor_t leitor[]){
    //############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Leitores --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
    //################################

    //apresentar todos dos leitores existentes na estrutura de dados
    for(uint8_t i=0;i<leitor_count;i++){
        printf("Numero de leitor: %s\n",leitor[i].codigo_leitor);
        printf("Nome: %s\n",leitor[i].nome);
        printf("Data de nascimento: %s\n",leitor[i].data_nascimento);
        printf("Morada: %s\n",leitor[i].localidade);
        printf("Telefone: %s\n",leitor[i].contato_telefonico);
        printf("-----------------------------\n");
    }
    if (leitor_count == 0){
        printf("Nao existem leitores registados!\n");
    }

    printf("\n\n\tPressione qualquer tecla para voltar ao menu das listagens...");

    char menu;
    scanf("%c",&menu);

    return menu;

}

void Listagem_livros_requisitados(Livro_t livro[]){
    //############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Livros Requisitados --\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
    printf("\t1: ");
    printf("\n\n\n\n\t2: ");
    //################################

    char menu;
}

void Listagem_ultimas_requisicoes(Leitor_t leitor[]){
    //############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Ultimas Requisicoes --\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
    printf("\t1: ");
    printf("\n\n\n\n\t2: ");
    //################################

    //lista de ultimas requisicoes


    char menu;
}

void Listagem_requisicoes(Leitor_t leitor[]){
    //############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Requisicoes --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++){
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++){
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
    printf("\t1: ");
    printf("\n\n\n\n\t2: ");
    //################################

    //lista de livros que estao requisitados


    char menu;

}

char keyboard_Read(){

    char data_dec[10];

    fflush(stdin);
    do{
        //gotoxy(23,16);
        //printf("\33[2K\r");
        //data_dec = _getch();
        //printf("\t\tOP%c%cO: ",128,199);
        fgets(data_dec, sizeof(data_dec), stdin);
        //gets(data_dec);
    }while (!(isdigit(data_dec[0]) || toupper(data_dec[0]) == 'S') || data_dec[1] != '\n');

    return toupper(data_dec[0]);
}

char keyboard_Read_str(){
    char data_srt;

    fflush(stdin);
    do{
        data_srt = _getch();
    }while(!(isalpha(data_srt)));
    return data_srt;
}

void load_data(Livro_t *livros, Leitor_t *leitores) {
    //ler ficheiro binario e se nao existir criar um novo
    FILE *fileptr = fopen("data.dat", "rb");
    if (fileptr == NULL) {
        fileptr = fopen("data.dat", "wb");
        printf("Erro a abrir o ficheiro!\n");
        fclose(fileptr);
        return;
    }
    fread(livros, sizeof(Livro_t), MAX_NUM_LIVROS, fileptr);
    fread(leitores, sizeof(Leitor_t), MAX_NUM_LEITORES, fileptr);
    fclose(fileptr);
}

void save_data(Livro_t *livros, Leitor_t *leitores) {
    //guardar ficheiro binario
    FILE *fileptr = fopen("data.dat", "wb");
    if (fileptr == NULL) {
        printf("Erro a guardar o ficheiro!\n");
        return;
    }
    fwrite(livros, sizeof(Livro_t), MAX_NUM_LIVROS, fileptr);
    fwrite(leitores, sizeof(Leitor_t), MAX_NUM_LEITORES, fileptr);
    fclose(fileptr);
    printf("\n\tDados guardados com sucesso!\n");
}

void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char S_or_N(void){
    //recebe S ou N e retorna S ou N
    char c[10];
    do{
        fgets(c, sizeof(c), stdin);
    }while(!(c[0] == 'S' || c[0] == 'N' || c[0] == 's' || c[0] == 'n' || c[0] == '0' || c[1]=='\n'));

    return toupper(c[0]);
}
