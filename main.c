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

int livro_count = 0;
int leitor_count = 0;
int requisicao_count = 0;

// ESTRUTURAS DE DADOS
typedef struct
{
    char ISBN[14];
    char titulo[100];
    char autor[100];
    char editora[100];
    char estado[10]; // D-disponivel, R-requisitado, I-inutilizado
} Livro_t;
typedef struct
{
    char codigo_leitor[20];
    char nome[50];
    char data_nascimento[20];
    char localidade[50];
    char contato_telefonico[9];
} Leitor_t;

typedef struct
{
    char codigo_leitor[20];
    char ISBN[14];
    char data_requisicao[20];
    char data_devolucao[20];
    char estado_livro[10]; // D-disponivel, R-requisitado, I-inutilizado
    char index_livro[10];
} Requisicao_t;

// FUNCOES
char Menu_Pincipal(void);
char Registar_Livro(Livro_t livro[]);
char Registar_Leitor(Leitor_t leitor[]);
char Requisitar_Livro(Leitor_t leitor[], Livro_t livro[], Requisicao_t requisicao[]);
char Devolver_Livro(Leitor_t leitor[], Livro_t livro[], Requisicao_t requisicao[]);
char Listagens(void);
void Listagem_livros(Livro_t livro[]);
void Listagem_leitores(Leitor_t leitor[]);
void Listagem_livros_requisitados(Livro_t livro[], Requisicao_t requisicao[]);
void Listagem_ultimas_requisicoes(Leitor_t leitor[]);
char keyboard_Read();
char S_or_N(void);
void formatar_data(char *data);

void load_data(Livro_t *livros, Leitor_t *leitores, Requisicao_t *requisicoes);
void save_data(Livro_t *livros, Leitor_t *leitores, Requisicao_t *requisicoes);

void main()
{

    char menu1, menu2;

    Livro_t livro[MAX_NUM_LIVROS];
    Leitor_t leitor[MAX_NUM_LEITORES];
    Requisicao_t requisicao[MAX_NUM_LEITORES];

    // Copies the character 0 to the first n characters of the string pointed to, by the argument str.
    memset(&livro, 0, sizeof(livro));           // Coloca todos os bytes da estrutura a 0
    memset(&leitor, 0, sizeof(leitor));         // Coloca todos os bytes da estrutura a 0
    memset(&requisicao, 0, sizeof(requisicao)); // Coloca todos os bytes da estrutura a 0

    load_data(&livro, &leitor, &requisicao); // load the data from the file

    // Check the struck and count the number of books
    for (int i = 0; i < MAX_NUM_LIVROS; i++)
    {
        if (livro[i].ISBN[0] != 0)
        {
            livro_count++;
        }
    }
    // Check the struck and count the number of readers
    for (int i = 0; i < MAX_NUM_LEITORES; i++)
    {
        if (leitor[i].codigo_leitor[0] != 0)
        {
            leitor_count++;
        }
    }
    // Check the struck and count the number of requisitions
    for (int i = 0; i < MAX_NUM_LEITORES; i++)
    {
        if (requisicao[i].ISBN[0] != 0)
        {
            requisicao_count++;
        }
    }

    do
    {
        menu1 = Menu_Pincipal();
        switch (menu1)
        {
        case '1':
            do
            {
                menu2 = Registar_Livro(livro);

            } while (menu2 != 0 && menu2 != '0');
            break;
        case '2':
            do
            {
                menu2 = Registar_Leitor(leitor);

            } while (menu2 != 0 && menu2 != '0');
            break;
        case '3':
            do
            {
                menu2 = Requisitar_Livro(leitor, livro, requisicao);

            } while (menu2 != 0 && menu2 != '0');
            break;
        case '4':
            do
            {
                menu2 = Devolver_Livro(leitor, livro, requisicao);

            } while (menu2 != 0 && menu2 != '0');
            break;

        case '5':
            do
            {
                menu2 = Listagens();

                switch (menu2)
                {
                case '1':
                    Listagem_livros(livro);
                    break;
                case '2':
                    Listagem_leitores(leitor);
                    break;
                case '3':
                    Listagem_livros_requisitados(livro, requisicao);
                    break;
                case '4':
                    Listagem_ultimas_requisicoes(leitor);
                    break;
                }

            } while (menu2 != 0 && menu2 != '0');
            break;

        case '0':
            system("cls");
            // menu1 = Confirm_Exit();
            break;
        }
    } while (menu1 != 'S' && menu1 != 's');

    system("cls");

    save_data(&livro, &leitor, &requisicao);

    printf("\n\n\n\t\t-----FIM-----\n\n\n\n\n");
}

char Menu_Pincipal()
{
    char menu;

    // ############## UI ##############
    system("cls");
    system("color 70");
    printf("%c", 201); // canto superior esquerdo
    for (uint8_t i = 1; i < 92; i++)
    {
        printf("%c", 205); // linha horizontal
    }
    printf("%c", 187);   // canto superior direito
    printf("\n%c", 186); // linha vertical
    for (uint8_t i = 1; i < 12; i++)
    {
        printf("\t");
    }
    printf("    %c", 186); // linha vertical
    printf("\n%c\t\t\t-- Gest%co de Requisi%c%ces de uma Biblioteca --\t\t\t    %c", 186, 198, 135, 228, 186);
    printf("\n%c", 186); // linha vertical
    for (uint8_t i = 1; i < 12; i++)
    {
        printf("\t");
    }
    printf("    %c\n", 186); // linha vertical
    printf("%c\tTotal de Livros: %d \t\t\tTotal de Leitores: %d \t\t\t    %c\n", 186, livro_count, leitor_count, 186);
    printf("%c\tTotal de Requisi%c%ces ativas: %d\t", 186, 135, 228, requisicao_count);
    for (uint8_t i = 1; i < 7; i++)
    {
        printf("\t");
    }
    printf("    %c\n", 186); // linha vertical
    printf("%c", 186);       // linha vertical
    for (uint8_t i = 1; i < 12; i++)
    {
        printf("\t");
    }
    printf("    %c", 186); // linha vertical
    printf("\n%c", 200);   // canto inferior esquerdo
    for (uint8_t i = 1; i < 92; i++)
    {
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

char Registar_Livro(Livro_t livro[])
{

    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 66; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("  %c\n", 186);

    printf("%c\t\t\t-- Registar Livro --\t\t\t  %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("  %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 66; i++)
    {
        printf("%c", 205);
    }
    printf("%c", 188);
    // ################################

    char menu;
    livro_count++;

    printf("\n\n\t%c ISBN: ", 175);
    fflush(stdin);
    fgets(livro[livro_count].ISBN, sizeof(livro->ISBN), stdin);

    printf("\t%c Titulo do Livro: ", 175);
    fflush(stdin);
    fgets(livro[livro_count].titulo, sizeof(livro->titulo), stdin);

    printf("\t%c Autor do Livro: ", 175);
    fflush(stdin);
    fgets(livro[livro_count].autor, sizeof(livro->autor), stdin);

    printf("\t%c Editora do Livro: ", 175);
    fflush(stdin);
    fgets(livro[livro_count].editora, sizeof(livro->editora), stdin);

    printf("\t%c Estado do Livro: DISPONIVEL\n\n", 175);
    livro[livro_count].estado[0] = 'D';

    printf("\tDeseja confirmar registo ? [S/N]\n");

    char sim_nao = S_or_N();

    switch (sim_nao)
    {
    case 'S':
        printf("\n\tLivro Registado com Sucesso!\n\n");
        usleep(500000); // delay de 500ms

        break;
    case 'N':
        for (int i = 0; i < 100; i++)
        {
            livro[livro_count].ISBN[i] = 0;
            livro[livro_count].titulo[i] = 0;
            livro[livro_count].autor[i] = 0;
            livro[livro_count].editora[i] = 0;
            livro[livro_count].estado[i] = 0;
        }
        livro_count--;
        printf("\n\tLivro N%co Registado!\n\n", 198);
        usleep(500000); // delay de 500ms
        break;
    }

    printf("\tDeseja Continuar? [S/N]\n");

    char sim_nao2 = S_or_N();

    if (sim_nao2 == 'S')
    {
        menu = 1;
        return menu;
    }
    else if (sim_nao2 == 'N')
    {
        menu = 0;
        return menu;
    }
}

char Registar_Leitor(Leitor_t leitor[])
{

    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);

    printf("%c\t\t\t-- Registar Leitor --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c", 188);
    // ################################

    char menu;
    leitor_count++;

    printf("\n\n\t%c Codigo de Leitor: ", 175);
    fflush(stdin);
    fgets(leitor[leitor_count].codigo_leitor, sizeof(leitor->codigo_leitor), stdin);

    printf("\t%c Nome: ", 175);
    fflush(stdin);
    fgets(leitor[leitor_count].nome, sizeof(leitor->nome), stdin);

    printf("\t%c Data nascimento: ", 175);
    fflush(stdin);
    fgets(leitor[leitor_count].data_nascimento, sizeof(leitor->data_nascimento), stdin);

    printf("\t%c Localidade: ", 175);
    fflush(stdin);
    fgets(leitor[leitor_count].localidade, sizeof(leitor->localidade), stdin);

    printf("\t%c Numero de Telefone: ", 175);
    fflush(stdin);
    fgets(leitor[leitor_count].contato_telefonico, sizeof(leitor->contato_telefonico), stdin);

    // printf("\t%c Email: **\n\n",175);

    printf("\tDeseja confirmar registo%? [S/N]\n");
    char sim_nao = S_or_N();
    switch (sim_nao)
    {
    case 'S':
        printf("\n\tLeitor Registado com Sucesso!\n\n");
        usleep(500000); // delay de 500ms

        break;
    case 'N':
        for (int i = 0; i < 100; i++)
        {
            livro_count--;
            leitor[leitor_count].codigo_leitor[i] = 0;
            leitor[leitor_count].nome[i] = 0;
            leitor[leitor_count].data_nascimento[i] = 0;
            leitor[leitor_count].localidade[i] = 0;
            leitor[leitor_count].contato_telefonico[i] = 0;
        }
        printf("\n\tLeitor N%co Registado!\n\n", 198);
        usleep(500000); // delay de 500ms
        break;
    }

    printf("\tDeseja Continuar? [S/N]\n");

    char sim_nao2 = S_or_N();

    if (sim_nao2 == 'S')
    {
        menu = 1;
        return menu;
    }
    else if (sim_nao2 == 'N')
    {
        menu = 0;
        return menu;
    }
}

char Requisitar_Livro(Leitor_t leitor[], Livro_t livro[], Requisicao_t requisicao[])
{

    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);

    printf("%c\t\t\t-- Requisitar livro --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    // ################################

    char menu;
    int flag = 0;
    requisicao_count++;

    // Opção que permite um leitor já registado requisitar um livro disponível. Nesta opção, além das identificações do livro e do leitor, deverá ser solicitada a data de requisição.
    printf("\t\nCodigos de leitor disponiveis:\n");

    for (int i = 1; i < leitor_count + 1; i++)
    {
        printf("\t\tCodigo: %s\n", leitor[i].codigo_leitor);
    }

    printf("\n\tInserir Codigo do Leitor:");
    // percorrer o array de leitores e verificar se o codigo existe
    char codigo_leitor_compare[100];
    fflush(stdin);
    fgets(codigo_leitor_compare, sizeof(codigo_leitor_compare), stdin);

    for (uint8_t i = 1; i < leitor_count + 1; i++)
    {
        if (strcmp(codigo_leitor_compare, leitor[i].codigo_leitor) == 0)
        {
            strcpy(requisicao[requisicao_count].codigo_leitor, leitor[i].codigo_leitor);
            printf("\tCodigo de Leitor Encontrado!\n\n");
            //requisicao[requisicao_count].index_livro[0]= i;
            flag = 1;
            break;
        }
    }

    if (flag == 0 || leitor_count == 0)
    {
        printf("\tCodigo de Leitor N%co Encontrado!\n", 198);
        printf("\tA voltar ao menu principal...");
        sleep(1);
        menu = 0;
        return menu;
    }

    flag = 0;
    printf("\t\nCodigos de livro disponiveis:\n");

    for (int i = 1; i < livro_count + 1; i++)
    {
        printf("\t\tCodigo: %s\n", livro[i].ISBN);
    }
    printf("\n\tInserir Codigo do Livro:");
    char codigo_livro_compare[100];
    fflush(stdin);
    fgets(codigo_livro_compare, sizeof(codigo_livro_compare), stdin);

    for (int i = 1; i < livro_count + 1; i++)
    {
        if (strcmp(codigo_livro_compare, livro[i].ISBN) == 0)
        {
            strcpy(requisicao[requisicao_count].ISBN, livro[i].ISBN);
            printf("\tCodigo de Livro Encontrado!\n\n");
            flag = 1;
            break;
        }
    }

    if (flag == 0 || livro_count == 0)
    {
        printf("\tCodigo de Livro N%co Encontrado!\n", 198);
        printf("\tA voltar ao menu principal...");
        sleep(1);
        menu = 0;
        return menu;
    }
    // data de requisição

    printf("\tData da requisicao:");
    fflush(stdin);
    fgets(requisicao[requisicao_count].data_requisicao, sizeof(requisicao->data_requisicao), stdin);

    // ler data de requisição e adicionar 15 dias

    int dia = 0, mes = 0, ano = 0;

    sscanf(requisicao[requisicao_count].data_requisicao, "%d/%d/%d", &dia, &mes, &ano);
    dia += 15;
    if (dia > 30)
    {
        dia -= 30;
        mes += 1;
        if (mes > 12)
        {
            mes -= 12;
            ano += 1;
        }
    }
    printf("\tData de devolucao: %d/%d/%d\n", dia, mes, ano);
    sprintf(requisicao[requisicao_count].data_devolucao, "%d/%d/%d", dia, mes, ano);
    // estado do livro
    strcpy(requisicao[requisicao_count].estado_livro, "Requisitado");

    // confirmar requisicao

    printf("\tDeseja confirmar requisicao ? [S/N]\n");
    char sim_nao = S_or_N();
    switch (sim_nao)
    {
    case 'S':
        printf("\tRequisicao confirmada!\n");
        usleep(500000);
        break;
    case 'N':
        for (int i = 0; i < 100; i++)
        {
            requisicao_count--;
            requisicao[requisicao_count].codigo_leitor[i] = 0;
            requisicao[requisicao_count].ISBN[i] = 0;
            requisicao[requisicao_count].data_requisicao[i] = 0;
            requisicao[requisicao_count].data_devolucao[i] = 0;
            requisicao[requisicao_count].estado_livro[i] = 0;
        }
        printf("\tRequisicao cancelada!\n");
        usleep(500000);
        break;
    }

    printf("\tDeseja Continuar ? [S/N]\n");

    char sim_nao2 = S_or_N();
    if (sim_nao2 == 'S')
    {
        menu = 1;
        return menu;
    }
    else if (sim_nao2 == 'N')
    {
        menu = 0;
        return menu;
    }

    /*
        else
        {
            printf("\tDeseja Registar novo Leitor%? [Y/N]\n");
            char sim_nao2 = S_or_N();

            if (sim_nao2 == 'S')
            {
                menu = 1;
                return menu;
            }
            else if (sim_nao2 == 'N')
            {
                menu = 0;
                return menu;
            }
        }
    */
}

char Devolver_Livro(Leitor_t leitor[], Livro_t livro[], Requisicao_t requisicao[])
{
    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);

    printf("%c\t\t\t-- Devolver Livro --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    // ################################

    printf("\t\nCodigos de livro disponiveis:\n");

    for (int i = 1; i < livro_count + 1; i++)
    {
        printf("\t\tCodigo: %s\n", requisicao[i].ISBN);
    }
    printf("\n\tInserir Codigo do Livro:");
    char codigo_livro_compare[100];
    fflush(stdin);
    fgets(codigo_livro_compare, sizeof(codigo_livro_compare), stdin);

    int flag = 0;

    for (int i = 1; i < requisicao_count + 1; i++)
    {
        if (strcmp(codigo_livro_compare, requisicao[i].ISBN) == 0)
        {
            strcpy(requisicao[requisicao_count].ISBN, livro[i].ISBN);
            printf("\tCodigo de Livro Encontrado!\n\n");
            flag = 1;
            break;
        }
    }

    if (flag == 0 || requisicao_count == 0)
    {
        printf("\tCodigo de Livro N%co Encontrado!\n", 198);
        printf("\tA voltar ao menu principal...");
        sleep(1);
        char menu = 0;
        return menu;
    }

    // print da estrutura requisicao
    printf("\tISBN: %s\n", requisicao[requisicao_count].ISBN);
    printf("\tData da entrega: %s\n", requisicao[requisicao_count].data_requisicao);
    printf("\tDias de devolucao: %s\n", requisicao[requisicao_count].data_devolucao);
    // calcular dias de utilizacao e dar print
    int dia, mes, ano;
    sscanf(requisicao[requisicao_count].data_requisicao, "%d/%d/%d", &dia, &mes, &ano);
    int dia2, mes2, ano2;
    sscanf(requisicao[requisicao_count].data_devolucao, "%d/%d/%d", &dia2, &mes2, &ano2);
    int dias = (dia2 - dia) + (mes2 - mes) * 30 + (ano2 - ano) * 365;
    printf("\tDias de utilizacao: %d\n", dias);
    // calcular dias de atraso e dar print
    int dias_atraso = dias - 15;
    if (dias_atraso < 0)
    {
        dias_atraso = 0;
    }
    printf("\tDias de atraso: %d\n", dias_atraso);

    // perguntar o estado do livro e alterar na estrutura livro e na estrutura requisicao
    printf("\tEstado do Livro: [1-inutilizavel/2-utilizavel]\n");
   // fflush(stdin);
   // int index = 
//
   // fgets(livro[livro_count].estado_livro, sizeof(livro[livro_count].estado_livro), stdin);
   // fgets(requisicao[requisicao_count].estado_livro, sizeof(requisicao[requisicao_count].estado_livro), stdin);

    // confirmar devolucao
    printf("\tDeseja confirmar devolucao ? [S/N]\n");
    char sim_nao = S_or_N();
    if (sim_nao == 'S')
    {
        printf("\tDevolucao confirmada!\n");
    }
    else if (sim_nao == 'N')
    {
        printf("\tDevolucao cancelada!\n");
    }

    // voltar ao menu principal
    printf("\tDeseja Continuar ? [S/N]\n");
    char sim_nao2 = S_or_N();
    if (sim_nao2 == 'S')
    {
        char menu = 0;
        return menu;
    }
    else if (sim_nao2 == 'N')
    {
        char menu = 0;
        return menu;
    }
}

char Listagens(void)
{

    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Listagens --\t\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    // ################################

    // menu para apresentar as listas

    char menu;
    printf("\t1 - Lista de Livros\n");
    printf("\t2 - Lista de Leitores\n");
    printf("\t3 - Lista de Requisicoes\n");
    printf("\t4 - Lista de ultimas Requisicoes\n\n");
    printf("\t0 - Voltar ao menu principal\n\n");
    printf("\tOpcao: ");

    menu = keyboard_Read();
    return menu;
}

void Listagem_livros(Livro_t livro[])
{

    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Livros --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 188);
    // ################################

    // apresentar todos dos livros existentes na estrutura de dados
    for (uint8_t i = 1; i < livro_count + 1; i++)
    {
        printf("ISBN: %s\n", livro[i].ISBN);
        printf("Titulo: %s\n", livro[i].titulo);
        printf("Autor: %s\n", livro[i].autor);
        printf("Editora: %s\n", livro[i].editora);
        // se dentro do livro[i].estado == D, entao o livro esta disponivel
        // se dentro do livro[i].estado == R, entao o livro esta requisitado
        // se dentro do livro[i].estado == I, entao o livro esta inutilizavel

        char estado = livro[i].estado;
        switch (estado)
        {
        case 'D':
            printf("Estado: Disponivel\n");
            break;
        case 'R':
            printf("Estado: Requisitado\n");
            break;
        case 'I':
            printf("Estado: Inutilizavel\n");
            break;
        default:
            printf("Estado: Desconhecido\n");
            break;
        }
        printf("-----------------------------\n");
    }
    if (livro_count == 0)
    {
        printf("\n\tNao existem livros registados!\n\n");
    }

    printf("\n\n\tPressione qualquer tecla para voltar ao menu das listagens...");

    _getch();
}

void Listagem_leitores(Leitor_t leitor[])
{
    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Leitores --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
    // ################################

    // apresentar todos dos leitores existentes na estrutura de dados
    for (uint8_t i = 1; i < leitor_count + 1; i++)
    {
        printf("Numero de leitor: %s\n", leitor[i].codigo_leitor);
        printf("Nome: %s\n", leitor[i].nome);
        printf("Data de nascimento: %s\n", leitor[i].data_nascimento);
        printf("Morada: %s\n", leitor[i].localidade);
        printf("Telefone: %s\n", leitor[i].contato_telefonico);
        printf("-----------------------------\n");
    }
    if (leitor_count == 0)
    {
        printf("\n\tNao existem leitores registados!\n");
    }

    printf("\n\n\tPressione qualquer tecla para voltar ao menu das listagens...");
    _getch();
}

void Listagem_livros_requisitados(Livro_t livro[], Requisicao_t requisicao[])
{
    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Livros Requisitados --\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
    // ################################

    // apresenta todos os livros requisitados na estrutura de dados

    for (uint8_t i = 1; i < requisicao_count + 1; i++)
    {
        printf("Numero de leitor: %s\n", requisicao[i].codigo_leitor);
        printf("ISBN: %s\n", requisicao[i].ISBN);
        printf("Data de requisicao: %s\n", requisicao[i].data_requisicao);
        printf("Data de devolucao: %s\n", requisicao[i].data_devolucao);
        printf("-----------------------------\n");
    }
    if (requisicao_count == 0)
    {
        printf("\n\tNao existem livros requisitados!\n");
    }
    printf("\n\n\tPressione qualquer tecla para voltar ao menu das listagens...");
    _getch();
}

void Listagem_ultimas_requisicoes(Leitor_t leitor[])
{
    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Ultimas Requisicoes --\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
    printf("\t1: ");
    printf("\n\n\n\n\t2: ");
    // ################################

    // lista de ultimas requisicoes

    char menu;
}

void Listagem_requisicoes(Leitor_t leitor[])
{
    // ############## UI ##############
    system("cls");
    printf("%c", 201);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c\n", 186);
    printf("%c\t\t\t-- Lista de Requisicoes --\t\t\t   %c\n", 186, 186);
    printf("%c", 186);
    for (uint8_t i = 1; i < 9; i++)
    {
        printf("\t");
    }
    printf("   %c", 186);
    printf("\n%c", 200);
    for (uint8_t i = 1; i < 67; i++)
    {
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
    printf("\t1: ");
    printf("\n\n\n\n\t2: ");
    // ################################

    // lista de livros que estao requisitados

    char menu;
}

char keyboard_Read()
{
    char data_dec[10];

    do
    {
        // gotoxy(23,16);
        // printf("\33[2K\r");
        // data_dec = _getch();
        // printf("\t\tOP%c%cO: ",128,199);
        fflush(stdin);
        fgets(data_dec, sizeof(data_dec), stdin);
        // gets(data_dec);
    } while (!(isdigit(data_dec[0]) || toupper(data_dec[0]) == 'S') || data_dec[1] != '\n');

    return toupper(data_dec[0]);
}

char keyboard_Read_str()
{
    char data_srt;

    fflush(stdin);
    do
    {
        data_srt = _getch();
    } while (!(isalpha(data_srt)));
    return data_srt;
}

void load_data(Livro_t *livros, Leitor_t *leitores, Requisicao_t *requisicoes)
{
    // ler ficheiro binario e se nao existir criar um novo
    FILE *fileptr = fopen("data.dat", "rb");
    if (fileptr == NULL)
    {
        fileptr = fopen("data.dat", "wb");
        printf("Erro a abrir o ficheiro!\n");
        fclose(fileptr);
        return;
    }
    fread(livros, sizeof(Livro_t), MAX_NUM_LIVROS, fileptr);
    fread(leitores, sizeof(Leitor_t), MAX_NUM_LEITORES, fileptr);
    fread(requisicoes, sizeof(Requisicao_t), MAX_NUM_LEITORES, fileptr);
    fclose(fileptr);
}

void save_data(Livro_t *livros, Leitor_t *leitores, Requisicao_t *requisicoes)
{
    // guardar ficheiro binario
    FILE *fileptr = fopen("data.dat", "wb");
    if (fileptr == NULL)
    {
        printf("Erro a guardar o ficheiro!\n");
        return;
    }
    fwrite(livros, sizeof(Livro_t), MAX_NUM_LIVROS, fileptr);
    fwrite(leitores, sizeof(Leitor_t), MAX_NUM_LEITORES, fileptr);
    fwrite(requisicoes, sizeof(Requisicao_t), MAX_NUM_LEITORES, fileptr);
    fclose(fileptr);
    printf("\n\tDados guardados com sucesso!\n");
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char S_or_N(void)
{
    // recebe S ou N e retorna S ou N
    char c[10];
    do
    {
        printf("\tResposta:");
        fflush(stdin);
        fgets(c, sizeof(c), stdin);
    } while (!(toupper(c[0]) == 'S' || toupper(c[0]) == 'N') || c[1] != '\n');

    return toupper(c[0]);
}
