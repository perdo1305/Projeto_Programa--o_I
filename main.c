#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

typedef struct {
    char ISBN[14];
    char titlo[100];
    char autor[100];
    char editora[100];
    char estado[20];
} Livro_t;

void dividir_numero_telemovel(int *g1, int *g2)
{
    *g1 = 10;
    *g2 = 20;S
}

void main()
{
    int grupo1, grupo2;
    dividir_numero_telemovel(&grupo1, &grupo2);
    char menu1, menu2;
    do
    {
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
            do
            {
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

char Menu_Pincipal(){
        char menu;
        system("cls");
        printf("\033[0;33m"); // yellow
        printf("\n\t\t\t-- Gestao de requisiçoes de uma Biblioteca --\n\n");
        printf("\033[0m"); // default
        printf("\n\tTotal de Livros \t\t\tTotal de Leitores: *\n");
        printf("\tTotal de Requisicpes ativas: **\n");
        printf("\n\t1-Registar Livro_t\n");
        printf("\t2-Registar Leitor\n");
        printf("\t3-Requisitar Livro_t\n");
        printf("\t4-Devolver Livro_t\n");
        printf("\t5-Listagens\n");
        printf("\t0-Sair\n\n");
        printf("\t\tOPCAO: ");
        menu = keyboard_Read_dec();
    return menu;
}

char Registar_Livro(k){
    char menu;
    system("cls");
    printf("\033[0;33m"); // yellow
    printf("\n\t\t\t-- Registar Livro_t --\n\n" );
    printf("\033[0m"); // default

    printf("\tISBN: \n");
    scanf("%s", livro->ISBN);
    printf("\tTitulo do Livro_t: **\n");
    scanf(" %[^\n]s", livro->titlo);
    printf("\tAutor do Livro_t: **\n");
    scanf(" %[^\n]s", livro->autor);
    printf("\tEditor do Livro_t: **\n");
    scanf(" %[^\n]s", livro->editora);
    printf("\tEstado do Livro_t: **\n\n");
    strcpy(livro->estado, "disponível");
    printf("\tDeseja confirmar registo ? [Y/N]\n");
    printf("\tDeseja Continuar ? [Y/N] ");

    menu = keyboard_Read_dec();
    return menu;
}


char Registar_Leitor(){
    char menu;
    system("cls");
    printf("\033[0;33m"); // yellow
    printf("\n\t\t\t-- Registar Leitor --\n\n");
    printf("\033[0m"); // default
    menu = keyboard_Read_dec();
    return menu;
}

char Requisitar_Livro(){
    char menu;
    system("cls");
    printf("\033[0;33m"); // yellow
    printf("\n\t\t\t-- Requisitar livro --\n\n");
    printf("\033[0m"); // default
    menu = keyboard_Read_dec();
    return menu;
}

char Devolver_Livro(){
    char menu;
    system("cls");
    printf("\033[0;33m"); // yellow
    printf("\n\t\t\t-- Devolver Livro_t --\n\n");
    printf("\033[0m"); // default
    menu = keyboard_Read_dec();
    return menu;
}

char Listagens(){
    char menu;
    system("cls");
    printf("\033[0;33m"); // yellow
    printf("\n\t\t\t-- Listagens --\n\n");
    printf("\033[0m"); // default
    menu = keyboard_Read_dec();
    return menu;
}

char keyboard_Read_dec(){
    char data_dec;
    fflush(stdin);
    do{
        data_dec = _getch();
    }while(!(isdigit(data_dec)));
    return data_dec;
}

char keyboard_Read_str(){
    char data_srt;
    fflush(stdin);
    do{
        data_srt = _getch();
    }while(!(isalpha(data_srt)));
    return data_srt;
}

