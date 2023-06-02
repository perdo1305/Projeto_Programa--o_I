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
▪ Listagem de todos os dados de todos os Leitores.3
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

#define MAX_NUM_LIVROS 20 
#define MAX_NUM_LEITORES 20

//char Confirm_Exit(void);

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
    int estado;
} Livro_t;

typedef struct {
    int codigo_leitor;
    char nome[50];
    char data_nascimento[11];
    char localidade[50];
    int contato_telefonico;
} Leitor_t;

char Menu_Pincipal(void);
char Registar_Livro(Livro_t livro[], int livro_count);
char Registar_Leitor(Leitor_t leitor[], int leitor_count);
char Requisitar_Livro(void);
char Devolver_Livro(void);
char Listagens(void);
char keyboard_Read_dec();

void main(){

    char menu1, menu2;

    Livro_t livro[MAX_NUM_LIVROS];
    Leitor_t leitor[MAX_NUM_LEITORES];

    load_data(livro, leitor, &livro_count, &leitor_count);

    

    do{
        menu1 = Menu_Pincipal();
        switch (menu1){
        case '1':
            do{
                menu2 = Registar_Livro(livro, livro_count);

            } while (menu2 != '0');
            break;
        case '2':
            do{
                menu2 = Registar_Leitor(leitor, leitor_count);

            } while (menu2 != '0');
            break;
        case '3':
            do{
                menu2 = Requisitar_Livro();
                
            } while (menu2 != '0');
            break;
        case '4':
            do{
                menu2 = Devolver_Livro();
                
            } while (menu2 != '0');
            break;

        case '5':
            do{
                menu2 = Listagens();

            } while (menu2 != '0');
            break;

        case '0':
            system("cls");
            // menu1 = Confirm_Exit();
            break;
        }
    } while (menu1 != 'S' && menu1 != 's' );
    printf("FIM");
    return 0;
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
    printf("%c\tTotal de Livros:%d \t\t\tTotal de Leitores:%d \t\t\t    %c\n", 186, Total_Livros, Total_Leitores, 186);
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
    printf("\t%c 0-Sair\n\n", 175);
    printf("\t\tOP%c%cO: ", 128, 199);
    // ################################

    menu = keyboard_Read_dec();
    return menu;
}

char Registar_Livro(Livro_t livro[], int livro_count){

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
    int numero_livro;
    numero_livro++;
    
    printf("\n\n\t%c ISBN: ",175);
    fgets(livro[numero_livro].ISBN, sizeof(livro->ISBN), stdin);

    printf("\t%c Titulo do Livro: ",175);
    fgets(livro[numero_livro].titulo, sizeof(livro->titulo), stdin);

    printf("\t%c Autor do Livro: ",175);
    fgets(livro[numero_livro].autor, sizeof(livro->autor), stdin);

    printf("\t%c Editora do Livro: ",175);
    fgets(livro[numero_livro].editora, sizeof(livro->editora), stdin);

    printf("\t%c Estado do Livro: DISPONIVEL\n\n",175);
    //livro->estado = AVAILABLE;

    printf("\tDeseja confirmar registo%? [S/N]\n");
    switch (S_or_N()){
    case 'S':
        printf("\n\tLivro Registado com Sucesso!\n\n");

        break;
    case 'N':
        for(int i=0;i<100;i++){
            livro[numero_livro].ISBN[i] = 0;
            livro[numero_livro].titulo[i] = 0;
            livro[numero_livro].autor[i] = 0;
            livro[numero_livro].editora[i] = 0;
            livro[numero_livro].estado = 0;
        }
        numero_livro--;
        printf("\n\tLivro N%co Registado!\n\n",198);
        break;
    }

    printf("\tDeseja Continuar%? [S/N] ");
    switch (S_or_N()){
    case 'S':
        menu = 1;
        return menu;
        break;
    case 'N':
        menu = 0;
        return menu;
        break;
    }

    menu = keyboard_Read_dec();
    return menu;
}

char Registar_Leitor(Leitor_t leitor[],int leitor_count){
    char menu;

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

    printf("\n\n\t%c Codigo do Leitor \n",175);
    printf("\t%c Nome: \n",175);
    printf("\t%c Data nascimento: \n",175);
    printf("\t%c Localidade: \n",175);
    printf("\t%c Numero Telemovel: \n",175);
    printf("\t%c Email: **\n\n",175);
    printf("\tDeseja confirmar registo%? [Y/N]\n");
    printf("\tDeseja Continuar%? [Y/N] ");

    menu = keyboard_Read_dec();
    return menu;
}

char Requisitar_Livro(){
    char menu;
    system("cls");
    printf("\n\t\t\t-- Requisitar livro --\n\n");

    printf("\tCodigo do Leitor **\n");
    printf("\tIntroduzir codigo existente%! [Y/N]\n");
    printf("\tDeseja Registar novo Leitor%? [Y/N]\n");
    printf("\tNome: **\n");
    printf("\tData da requisicao: **\n\n");
    printf("\tDeseja confirmar requisicao%? [Y/N]\n");
    printf("\tDeseja Continuar%? [Y/N] ");

    menu = keyboard_Read_dec();
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

    menu = keyboard_Read_dec();
    return menu;
}

char Listagens(){
    char menu;
    system("cls");
    printf("\n\t\t\t-- Listagens --\n\n");

    printf("\t1-Lista dos Livros\n");
    printf("\t2-Lista de Leitores\n");
    printf("\t3-Lista de Livros\n");
    printf("\t4-Ultimas Requisicoes\n\n");
    printf("\t0-Voltar");

    menu = keyboard_Read_dec();
    return menu;
}

char keyboard_Read_dec(){
    char data_dec[10];

    fflush(stdin);
    do{
        gotoxy(23,16);
        printf("\33[2K\r");
        //data_dec = _getch();
        printf("\t\tOP%c%cO: ",128,199);
        gets(data_dec);
    }while(!(isdigit(data_dec[0]) && data_dec[0] != '\0'));

    return data_dec[0];
}

char keyboard_Read_str(){
    char data_srt;

    fflush(stdin);
    do{
        data_srt = _getch();
    }while(!(isalpha(data_srt)));
    return data_srt;
}

void load_data(Livro_t *livros, int num_livros, Leitor_t *leitores, int num_leitores) {
    FILE *fileptr = fopen("data.dat", "rb");
    if (fileptr == NULL) {
        printf("Erro a abrir o ficheiro!\n");
        return;
    }
    fread(livros, sizeof(Livro_t), num_livros, fileptr);
    fread(leitores, sizeof(Leitor_t), num_leitores, fileptr);
    fclose(fileptr);
}

void save_data(Livro_t *livros, int num_livros, Leitor_t *leitores, int num_leitores) {
    FILE *fileptr = fopen("data.dat", "wb");
    if (fileptr == NULL) {
        printf("Erro a guardar o ficheiro!\n");
        return;
    }
    fwrite(livros, sizeof(Livro_t), num_livros, fileptr);
    fwrite(leitores, sizeof(Leitor_t), num_leitores, fileptr);
    fclose(fileptr);
}

void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char S_or_N(void){
    char c;
    do{
        fflush(stdin);
        scanf("%c",&c);
        toupper(c);
    }while(!(c == 'S' || c == 'N'));
    return c;
}