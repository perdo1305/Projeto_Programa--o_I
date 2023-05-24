#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <windows.h>
#include <conio.h>

#define MAX_NUM_LIVROS 20


char Menu_Pincipal(void);
char Registar_Livro(int);
char Registar_Leitor(void);
char Requisitar_Livro(void);
char Devolver_Livro(void);
char Listagens(void);
char keyboard_Read_dec();

//char Confirm_Exit(void);

int livro_count=0;

//ESTRUTURAS DE DADOS

typedef struct {
    char ISBN[14];
    char titlo[100];
    char autor[100];
    char editora[100];
    char estado[20];
} Livro_t;

typedef struct {
    int codigo_leitor;
    char nome[50];
    char data_nascimento[11];
    char localidade[50];
    int contato_telefonico;
} Leitor_t;

void main(){

    char menu1, menu2;

    do{
        menu1 = Menu_Pincipal();
        switch (menu1)
        {
        case '1':
            do{
                int k = livro_count;

                Livro_t livro[MAX_NUM_LIVROS];
                //enviar so k
                menu2 = Registar_Livro(k);
                livro_count++;

            } while (menu2 != '0');
            break;
        case '2':
            do{
                menu2 = Registar_Leitor();
                switch (menu2)
                {
                case '1':
                    printf("opcao 1");
                    break;
                case '2':
                    printf("opcao 2");
                    break;
                case '3':
                    printf("opcao 3");
                    break;
                }
            } while (menu2 != '0');
            break;
        case '3':
            do
            {
                menu2 = Requisitar_Livro();
                switch (menu2)
                {
                case '1':
                    printf("opcao 1");
                    break;

                case '2':
                    printf("opcao 2");
                    break;

                case '3':
                    printf("opcao 3");
                    break;
                }
            } while (menu2 != '0');
            break;
        case '4':
            do
            {
                menu2 = Devolver_Livro();
                switch (menu2)
                {
                case '1':
                    printf("opcao 1");
                    break;
                case '2':
                    printf("opcao 2");
                    break;
                case '3':
                    printf("opcao 3");
                    break;
                }
            } while (menu2 != '0');
            break;
        case '5':
            do
            {
                menu2 = Listagens();
                switch (menu2)
                {
                case '1':
                    printf("opcao 1");
                    break;
                case '2':
                    printf("opcao 2");
                    break;
                case '3':
                    printf("opcao 3");
                    break;
                }
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

char Menu_Pincipal()
{
    char menu;
    uint8_t i;

    system("cls");
    system("color 70");
    printf("%c",201);
    for (i = 1; i < 92; i++) {
             printf("%c",205);
            }
    printf("%c",187);
    printf("\n%c",186);
    for (i = 1; i < 12; i++) {
             printf("\t");
            }
    printf("    %c",186);

    printf("\n%c\t\t\t-- Gest%co de Requisi%c%ces de uma Biblioteca --\t\t\t    %c",186,198,135,228,186);
    printf("\n%c",186);
    for (i = 1; i < 12; i++) {
             printf("\t");
            }
    printf("    %c\n",186);
    printf( "%c\tTotal de Livros \t\t\tTotal de Leitores: \t\t\t    %c\n",186,186 );
    printf( "%c\tTotal de Requisi%c%ces ativas: **\t",186,135,228);
    for (i = 1; i < 7; i++) {
             printf("\t");
            }
    printf("    %c\n",186);
    printf("%c",186);
    for (i = 1; i < 12; i++) {
             printf("\t");
            }
    printf("    %c",186);
    printf("\n%c",200);
        for (i = 1; i < 92; i++) {
             printf("%c",205);
            }
    printf("%c",188);
    printf("\n\n\t%c 1-Registar Livro\n",175);
    printf("\t%c 2-Registar Leitor\n",175);
    printf("\t%c 3-Requisitar Livro\n",175);
    printf("\t%c 4-Devolver Livro\n",175);
    printf("\t%c 5-Listagens\n",175);
    printf("\t%c 0-Sair\n\n",175);
    printf("\t\tOP%c%cO: ",128,199);

    menu = keyboard_Read_dec();
    return menu;
}

char Registar_Livro(k){
    char menu;
    uint8_t i;

    system("cls");
    printf("%c",201);
    for (i = 1; i < 66; i++) {
             printf("%c",205);
            }
    printf("%c\n",187);
    printf("%c",186);
    for (i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("  %c\n",186);

    printf("%c\t\t\t-- Registar Livro --\t\t\t  %c\n",186,186);
    printf("%c",186);
    for (i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("  %c",186);
    printf("\n%c",200);
        for (i = 1; i < 66; i++) {
             printf("%c",205);
            }
    printf("%c",188);
    printf("\n\n\t%c ISBN: \n",175);
    printf("\t%c Titulo do Livro: \n",175);
    printf("\t%c Autor do Livro: \n",175);
    printf("\t%c Editor do Livro: \n",175);
    printf("\t%c Estado do Livro: \n\n",175);
    printf("\tDeseja confirmar registo%? [Y/N]\n");
    printf("\tDeseja Continuar%? [Y/N] ");

    menu = keyboard_Read_dec();
    return menu;
}

char Registar_Leitor(){
    char menu;
    uint8_t i;
    system("cls");
    printf("%c",201);
    for (i = 1; i < 67; i++) {
             printf("%c",205);
            }
    printf("%c\n",187);
    printf("%c",186);
    for (i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("   %c\n",186);

    printf("%c\t\t\t-- Registar Leitor --\t\t\t   %c\n",186,186);
    printf("%c",186);
    for (i = 1; i < 9; i++) {
             printf("\t");
            }
    printf("   %c",186);
    printf("\n%c",200);
        for (i = 1; i < 67; i++) {
             printf("%c",205);
            }
    printf("%c",188);

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
    printf("\tDeseja confirmar devolucao%? [Y/N]\n");
    printf("\tDeseja Continuar%? [Y/N] ");

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
    }while(!(isdigit(data_dec[0])));
    
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