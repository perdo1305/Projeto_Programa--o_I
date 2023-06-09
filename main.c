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
#include <time.h>
#include <ctype.h>

#define MAX_NUM_LIVROS 20
#define MAX_NUM_LEITORES 20

unsigned int livro_count = 0;
unsigned int leitor_count = 0;
unsigned int requisicao_count = 0;

// ESTRUTURAS DE DADOS
typedef struct
{
    char ISBN[20];
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
    char contato_telefonico[20];
} Leitor_t;

typedef struct
{
    char codigo_leitor[20];
    char ISBN[20];
    // char data_requisicao[20];
    char data_requisicao_dia[5];
    char data_requisicao_mes[5];
    char data_requisicao_ano[6];
    char data_devolucao[20];
    char estado_livro[10]; // D-disponivel, R-requisitado, I-inutilizado
    char index_livro[10];
    char index_leitor[10];

} Requisicao_t;

// FUNCOES
char Menu_Pincipal(void);
char Registar_Livro(Livro_t livro[], Leitor_t leitor[], Requisicao_t requisicao[]);
char Registar_Leitor(Livro_t livro[], Leitor_t leitor[], Requisicao_t requisicao[]);
char Requisitar_Livro(Leitor_t leitor[], Livro_t livro[], Requisicao_t requisicao[]);
char Devolver_Livro(Leitor_t leitor[], Livro_t livro[], Requisicao_t requisicao[]);
char Listagens(void);
void Listagem_livros(Livro_t livro[]);
void Listagem_leitores(Leitor_t leitor[]);
void Listagem_livros_requisitados(Livro_t livro[], Requisicao_t requisicao[]);
void Listagem_ultimas_requisicoes(Leitor_t leitor[], Livro_t livro[], Requisicao_t requisicao[]);
char keyboard_Read();
char S_or_N(void);
void formatar_data(char *data);
int Validar_data(Requisicao_t requisicao[]);

void load_data(Livro_t *livros, Leitor_t *leitores, Requisicao_t *requisicoes);
void save_data(Livro_t *livros, Leitor_t *leitores, Requisicao_t *requisicoes);

int main()
{
    // ecra com nome do projeto e nome dos alunos, que dura 2 segundos e depois limpa o ecra e continua o codigo
    system("cls");
    system("color 70");
    printf("\n\n\n\n\t\t\t\t\tProjeto de Programacao I\n\n\n\n");
    printf("\t\tPedro Ferreira - 2222035 \t\t Bernardo Santos - 2222033");

    sleep(3);
    system("cls");

    char menu1, menu2;

    Livro_t livro[MAX_NUM_LIVROS];             // inicializar a estrutura livro com tamanho MAX_NUM_LIVROS
    Leitor_t leitor[MAX_NUM_LEITORES];         // inicializar a estrutura leitor com tamanho MAX_NUM_LEITORES
    Requisicao_t requisicao[MAX_NUM_LEITORES]; // inicializar a estrutura requisicao com tamanho MAX_NUM_LEITORES

    // Copies the character 0 to the first n characters of the string pointed to, by the argument str.
    memset(&livro, 0, sizeof(livro));           // Coloca todos os bytes da estrutura a 0
    memset(&leitor, 0, sizeof(leitor));         // Coloca todos os bytes da estrutura a 0
    memset(&requisicao, 0, sizeof(requisicao)); // Coloca todos os bytes da estrutura a 0

    load_data(livro, leitor, requisicao); // load the data from the file

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
        if (leitor[i].codigo_leitor[0] != 0 && leitor[i].contato_telefonico[0] != 0)
        {
            leitor_count++;
        }
    }
    // Check the struck and count the number of requisitions
    for (int i = 0; i < MAX_NUM_LEITORES; i++)
    {
        if (requisicao[i].ISBN[0] != 0 && requisicao[i].ISBN[0] != '0')
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
                menu2 = Registar_Livro(livro, leitor, requisicao);

            } while (menu2 != 0 && menu2 != '0');
            break;
        case '2':
            do
            {
                menu2 = Registar_Leitor(livro, leitor, requisicao);

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
                    Listagem_ultimas_requisicoes(leitor, livro, requisicao);
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

    save_data(livro, leitor, requisicao);

    printf("\n\n\n\t\t-----FIM-----\n\n\n\n\n");
    return 0;
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
    // ################################
    do
    {
        printf("\t\tOP%c%cO: ", 128, 199);
        menu = keyboard_Read();
    } while (menu != '1' && menu != '2' && menu != '3' && menu != '4' && menu != '5' && menu != 'S' && menu != 's');
    return menu;
}

char Registar_Livro(Livro_t livro[], Leitor_t leitor[], Requisicao_t requisicao[])
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
    printf("%c\n", 188);
    // ################################

    char menu;
    int flag;
    livro_count++;
    do
    {
        printf("\n\t%c ISBN: ", 175);
        flag = 0;
        fflush(stdin);
        fgets(livro[livro_count].ISBN, sizeof(livro->ISBN), stdin);

        // printf("\n %d", strlen(livro[livro_count].ISBN)); //debug

        if ((strlen(livro[livro_count].ISBN)) != 14)
        {
            printf("ISBN deve ter 13 digitos!\n");
            flag = 1;
        }

        for (int i = 0; i < 13; i++)
        {
            if (!isdigit(livro[livro_count].ISBN[i]))
            {
                printf("ISBN deve ser composto apenas por digitos!\n");
                flag = 1;
                break;
            }
        }
    } while (flag == 1);

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
        printf("\n\tLivro Registado com Sucesso!\n");
        save_data(livro, leitor, requisicao);
        sleep(1);

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
        sleep(1);
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
    return 99;
}

char Registar_Leitor(Livro_t livro[], Leitor_t leitor[], Requisicao_t requisicao[])
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
    int barra_count = 0, flag = 0;
    int dia = 0, mes = 0, ano = 0;
    leitor_count++;

    printf("\n\n\t%c Codigo de Leitor: ", 175);
    fflush(stdin);
    fgets(leitor[leitor_count].codigo_leitor, sizeof(leitor->codigo_leitor), stdin);

    printf("\t%c Nome: ", 175);
    fflush(stdin);
    fgets(leitor[leitor_count].nome, sizeof(leitor->nome), stdin);

    do
    {
        barra_count = 0;
        flag = 0;
        // data nascimento deve ser inserida no formato dd/mm/aaaa
        // o programa le os digitos ate encontrar uma barra depois le mais 2 digitos e depois mais uma barra e depois mais 4 digitos
        printf("\t%c Data nascimento dd/mm/aaaa", 175);
        printf("\n\tReposta:");
        fflush(stdin);
        fgets(leitor[leitor_count].data_nascimento, sizeof(leitor->data_nascimento), stdin);
        if (strlen(leitor[leitor_count].data_nascimento) != 11)
        {
            printf("Data de nascimento deve ser inserida no formato dd/mm/aaaa\n");
            flag = 1;
        }
        for (int i = 0; i < 12; i++)
        {
            if (leitor[leitor_count].data_nascimento[i] == '/')
            {
                barra_count++;
            }
        }
        if (barra_count != 2)
        {
            printf("Data de nascimento deve ser inserida no formato dd/mm/aaaa\n");
            flag = 1;
        }
        sscanf(leitor[leitor_count].data_nascimento, "%d/%d/%d", &dia, &mes, &ano);
        if (dia < 1 || dia > 31)
        {
            printf("Dia invalido...\n");
            flag = 1;
        }
        if (mes < 1 || mes > 12)
        {
            printf("Mes invalido...\n");
            flag = 1;
        }
        if (ano < 1900 || ano > 2023)
        {
            printf("Ano invalido...\n");
            flag = 1;
        }

    } while (flag == 1);

    printf("\t%c Localidade: ", 175);
    fflush(stdin);
    fgets(leitor[leitor_count].localidade, sizeof(leitor->localidade), stdin);

    // o numero de telefone deve ser inserido no formato 9xxxxxxxx e tem de ter 9 digitos
    int flag2 = 0;
    do
    {
        flag2 = 0;
        printf("\t%c Numero de Telefone: ", 175);
        fflush(stdin);
        fgets(leitor[leitor_count].contato_telefonico, sizeof(leitor->contato_telefonico), stdin);

        // printf("%d", strlen(leitor[leitor_count].contato_telefonico)); // debug

        if (strlen(leitor[leitor_count].contato_telefonico) != 10)
        {
            printf("Numero de telefone deve ser inserido no formato 9xxxxxxxx\n");
            flag2 = 1;
        }
    } while (flag2 == 1);

    // printf("\t%c Email: **\n\n",175);

    printf("\tDeseja confirmar registo? [S/N]\n");
    char sim_nao = S_or_N();
    switch (sim_nao)
    {
    case 'S':
        printf("\n\tLeitor Registado com Sucesso!\n\n");
        save_data(livro, leitor, requisicao);
        sleep(1);

        break;
    case 'N':

        for (int i = 0; i < 100; i++)
        {
            leitor[leitor_count].codigo_leitor[i] = 0;
            leitor[leitor_count].nome[i] = 0;
            leitor[leitor_count].data_nascimento[i] = 0;
            leitor[leitor_count].localidade[i] = 0;
            leitor[leitor_count].contato_telefonico[i] = 0;
        }
        printf("\n\tLeitor N%co Registado!\n\n", 198);
        leitor_count--;
        sleep(1);
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
    return 99;
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

    for (int i = 1; i < leitor_count + 1; i++)
    {
        if (strcmp(codigo_leitor_compare, leitor[i].codigo_leitor) == 0)
        {
            strcpy(requisicao[requisicao_count].codigo_leitor, leitor[i].codigo_leitor);
            requisicao[requisicao_count].index_leitor[0] = i;
            printf("\tCodigo de Leitor Encontrado!\n\n");
            // requisicao[requisicao_count].index_livro[0]= i;
            flag = 1;
            break;
        }
    }

    if (flag == 0 || leitor_count == 0)
    {
        printf("\tCodigo de Leitor N%co Encontrado!\n", 198);
        printf("\tA voltar ao menu principal...");
        sleep(4);
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
            requisicao[requisicao_count].index_livro[0] = i;
            printf("\tCodigo de Livro Encontrado!\n\n");
            flag = 1;
            break;
        }
    }

    if (flag == 0 || livro_count == 0)
    {
        printf("\tCodigo de Livro N%co Encontrado!\n", 198);
        printf("\tA voltar ao menu principal...");
        sleep(4);
        menu = 0;
        return menu;
    }
    // data de requisição deve ser introduzida pelo utilizador da seguinte forma: dd/mm/aaaa
    int dia_requisicao = 0, mes_requisicao = 0, ano_requisicao = 0;
    int flag_dia = 0, flag_mes = 0, flag_ano = 0;
    int flag_data = 0;
    do
    {
        printf("\t%c Data de Requisicao:", 175);
        flag_data = 0;
        do
        {

            printf("\n\tDia:");
            fflush(stdin);
            fgets(requisicao[requisicao_count].data_requisicao_dia, sizeof(requisicao[requisicao_count].data_requisicao_dia), stdin);
            dia_requisicao = atoi(requisicao[requisicao_count].data_requisicao_dia);
            if (dia_requisicao > 31 || dia_requisicao < 1)
            {
                printf("\tDia Invalido!\n");
                flag_dia = 1;
            }
            else
            {
                flag_dia = 0;
            }

        } while (flag_dia == 1);

        do
        {

            printf("\tMes:");
            fflush(stdin);
            fgets(requisicao[requisicao_count].data_requisicao_mes, sizeof(requisicao[requisicao_count].data_requisicao_mes), stdin);
            mes_requisicao = atoi(requisicao[requisicao_count].data_requisicao_mes);
            if (mes_requisicao > 12 || mes_requisicao < 1)
            {
                printf("\tMes Invalido!\n");
                flag_mes = 1;
            }
            else
            {
                flag_mes = 0;
            }
        } while (flag_mes == 1);

        do
        {

            printf("\tAno:");
            fflush(stdin);
            fgets(requisicao[requisicao_count].data_requisicao_ano, sizeof(requisicao[requisicao_count].data_requisicao_ano), stdin);
            ano_requisicao = atoi(requisicao[requisicao_count].data_requisicao_ano);
            if (ano_requisicao > 2023 || ano_requisicao < 1900)
            {
                printf("\tAno Invalido!\n");
                flag_ano = 1;
            }
            else
            {
                flag_ano = 0;
            }
        } while (flag_ano == 1);

        // verificar data de hoje e verificar se a data inserida é superior a data de hoje, ter em conta os anos bissextos
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int dia = tm.tm_mday;
        int mes = tm.tm_mon + 1;
        int ano = tm.tm_year + 1900;

        //  verificar se a data inserida é superior a data de hoje
        if (ano_requisicao > ano)
        {
            printf("\tData de requisicao superior a data de hoje!\n");
            flag_data = 1;
        }
        else if (ano_requisicao == ano)
        {
            if (mes_requisicao > mes)
            {
                printf("\tData de requisicao superior a data de hoje!\n");
                flag_data = 1;
            }
            else if (mes_requisicao == mes)
            {
                if (dia_requisicao > dia)
                {
                    printf("\tData de requisicao superior a data de hoje!\n");
                    flag_data = 1;
                }
            }
        }
    } while (flag_data == 1);

    printf("\tData de Requisicao: %d/%d/%d\n", atoi(requisicao[requisicao_count].data_requisicao_dia), atoi(requisicao[requisicao_count].data_requisicao_mes), atoi(requisicao[requisicao_count].data_requisicao_ano));
    // acrescentar 15 dias a data de requisição para obter a data de devolução, ter em atencao á mudanca de mes e de anos bisextos
    int dia_devolucao = 0, mes_devolucao = 0, ano_devolucao = 0;
    int dias_para_devolucao = 15;

    dia_devolucao = atoi(requisicao[requisicao_count].data_requisicao_dia);
    mes_devolucao = atoi(requisicao[requisicao_count].data_requisicao_mes);
    ano_devolucao = atoi(requisicao[requisicao_count].data_requisicao_ano);

    // verificar se o dia de devolução é superior ao numero de dias do mes

    if (mes_devolucao == 1 || mes_devolucao == 3 || mes_devolucao == 5 || mes_devolucao == 7 || mes_devolucao == 8 || mes_devolucao == 10 || mes_devolucao == 12)
    {
        if (dia_devolucao + dias_para_devolucao > 31)
        {
            dia_devolucao = (dia_devolucao + dias_para_devolucao) - 31;
            if (mes_devolucao == 12)
            {
                mes_devolucao = 1;
                ano_devolucao = ano_devolucao + 1;
            }
            else
            {
                mes_devolucao = mes_devolucao + 1;
            }
        }
        else
        {
            dia_devolucao = dia_devolucao + dias_para_devolucao;
        }
    }
    else if (mes_devolucao == 4 || mes_devolucao == 6 || mes_devolucao == 9 || mes_devolucao == 11)
    {
        if (dia_devolucao + dias_para_devolucao > 30)
        {
            dia_devolucao = (dia_devolucao + dias_para_devolucao) - 30;
            mes_devolucao = mes_devolucao + 1;
        }
        else
        {
            dia_devolucao = dia_devolucao + dias_para_devolucao;
        }
    }
    else if (mes_devolucao == 2)
    {
        if (dia_devolucao + dias_para_devolucao > 28)
        {
            dia_devolucao = (dia_devolucao + dias_para_devolucao) - 28;
            mes_devolucao = mes_devolucao + 1;
        }
        else
        {
            dia_devolucao = dia_devolucao + dias_para_devolucao;
        }
    }
    printf("\tData de Devolucao: %d/%d/%d\n", dia_devolucao, mes_devolucao, ano_devolucao);
    char data_devolucao[20];
    sprintf(data_devolucao, "%d/%d/%d", dia_devolucao, mes_devolucao, ano_devolucao);
    strcpy(requisicao[requisicao_count].data_devolucao, data_devolucao);

    // estado do livro

    strcpy(requisicao[requisicao_count].estado_livro, "R");

    // confirmar requisicao

    printf("\tDeseja confirmar requisicao ? [S/N]\n");
    char sim_nao = S_or_N();
    switch (sim_nao)
    {
    case 'S':

        printf("\tRequisicao confirmada!\n");
        save_data(livro, leitor, requisicao);
        sleep(1);
        break;
    case 'N':
        for (int i = 0; i < 100; i++)
        {

            requisicao[requisicao_count].codigo_leitor[i] = 0;
            requisicao[requisicao_count].ISBN[i] = 0;
            requisicao[requisicao_count].data_requisicao_dia[i] = 0;
            requisicao[requisicao_count].data_requisicao_mes[i] = 0;
            requisicao[requisicao_count].data_requisicao_ano[i] = 0;
            requisicao[requisicao_count].data_devolucao[i] = 0;
            requisicao[requisicao_count].estado_livro[i] = 0;
        }
        printf("\tRequisicao cancelada!\n");
        requisicao_count--;
        sleep(1);
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
    return 99;
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

    int flag = 0;
    int indice_requisicao;
    do
    {
        indice_requisicao = 0;
        printf("\t\nCodigos de livros requisitados disponiveis:\n");

        for (int i = 1; i < requisicao_count + 1; i++)
        {
            printf("\t\tCodigo: %s\n", requisicao[i].ISBN);
        }
        printf("\n\tInserir Codigo do Livro:");
        char codigo_livro_compare[100];
        fflush(stdin);
        fgets(codigo_livro_compare, sizeof(codigo_livro_compare), stdin);

        flag = 0;

        for (int i = 1; i < requisicao_count + 1; i++)
        {
            if (strcmp(codigo_livro_compare, requisicao[i].ISBN) == 0)
            {

                indice_requisicao = i;
                printf("\tCodigo de Livro Encontrado!\n\n");
                // print da estrutura requisicao
                printf("\t\tCodigo de Leitor: %s", requisicao[i].codigo_leitor);
                printf("\t\tISBN: %s", requisicao[i].ISBN);
                printf("\t\tData de requisicao: %d/%d/%d\n", atoi(requisicao[i].data_requisicao_dia), atoi(requisicao[i].data_requisicao_mes), atoi(requisicao[i].data_requisicao_ano));
                printf("\t\tData de devolucao: %s\n", requisicao[i].data_devolucao);

                flag = 1;
                break;
            }
        }

        if (flag == 0 || requisicao_count == 0)
        {
            printf("\tCodigo de Livro N%co Encontrado!\n", 198);
        }
    } while (flag == 0 || requisicao_count == 0);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int dia1 = tm.tm_mday;
    int mes1 = tm.tm_mon + 1;
    int ano1 = tm.tm_year + 1900;
    printf("\tData de hoje: %d/%d/%d\n", dia1, mes1, ano1);

    // sscanf(requisicao[requisicao_count].data_requisicao, "%d/%d/%d", &dia, &mes, &ano);
    // sscanf(requisicao[indice_requisicao].data_requisicao_dia, "%d", &dia1);
    // sscanf(requisicao[indice_requisicao].data_requisicao_mes, "%d", &mes1);
    // sscanf(requisicao[indice_requisicao].data_requisicao_ano, "%d", &ano1);
    int dia2, mes2, ano2;
    sscanf(requisicao[indice_requisicao].data_devolucao, "%d/%d/%d", &dia2, &mes2, &ano2);
    int dias1 = (dia1 - dia2) + ((mes1 - mes2) * 30) + ((ano1 - ano2) * 365);
    // printf("\tDias de utilizacao: %d\n", dias1);
    //  calcular dias de atraso e dar print
    int dias_atraso = dias1 - 15;
    if (dias_atraso < 0)
    {
        dias_atraso = 0;
    }
    printf("\t\tDias de atraso: %d\n\n", dias_atraso);
    printf("\t\tDois euros por dia de atraso\n");
    printf("\t\tValor a pagar: %d$\n\n ", dias_atraso * 2); // 2 euros por dia de atraso
    // perguntar o estado do livro e alterar na estrutura livro e na estrutura requisicao
    printf("\tEstado do Livro: [1-inutilizavel/2-utilizavel]\n");
    fflush(stdin);
    // faz scanf e recebe apenas ou 1 ou 2
    int estado_livro;
    int estado_flag1, estado_flag2;
    do
    {
        estado_flag1 = 0;
        estado_flag2 = 0;
        printf("\tResposta: ");
        scanf("%d", &estado_livro);

        if (estado_livro == 1) // inutilizavel
        {
            estado_flag1 = 1;
        }
        else if (estado_livro == 2) // utilizavel/disponivel
        {
            estado_flag2 = 1;
        }
        else
        {
            printf("\t\tEstado invalido!\n");
        }
    } while (estado_livro != 1 && estado_livro != 2);

    // confirmar devolucao
    printf("\tDeseja confirmar devolucao ? [S/N]\n");
    char sim_nao = S_or_N();
    if (sim_nao == 'S')
    {
        if (estado_flag1 == 1)
        {
            int var = atoi(requisicao[indice_requisicao].index_livro);
            strcpy(livro[var].estado, "I");
            strcpy(requisicao[indice_requisicao].estado_livro, "I");
        }
        else if (estado_flag2 == 1)
        {
            int var = atoi(requisicao[indice_requisicao].index_livro);
            strcpy(livro[var].estado, "D");
            strcpy(requisicao[indice_requisicao].estado_livro, "D");
        }
        // coloca a 0 os dados da estrutura requisicao
        strcpy(requisicao[indice_requisicao].codigo_leitor, "0");
        strcpy(requisicao[indice_requisicao].ISBN, "0");
        strcpy(requisicao[indice_requisicao].data_requisicao_dia, "0");
        strcpy(requisicao[indice_requisicao].data_requisicao_mes, "0");
        strcpy(requisicao[indice_requisicao].data_requisicao_ano, "0");
        strcpy(requisicao[indice_requisicao].data_devolucao, "0");
        strcpy(requisicao[indice_requisicao].estado_livro, "0");
        requisicao_count--;
        printf("\tDevolucao confirmada!\n");
        save_data(livro, leitor, requisicao);
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
    return 99;
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
    printf("\n\n\t%c 1-Lista de Livros\n", 175);
    printf("\t%c 2-Lista de Leitores\n", 175);
    printf("\t%c 3-Lista de Requisicoes\n", 175);
    printf("\t%c 4-Lista de ultimas Requisicoes\n", 175);
    printf("\t%c 0-Voltar ao menu principal\n\n", 175);

    do
    {
        printf("\t\tOP%c%cO: ", 128, 199);
        menu = keyboard_Read();
    } while (menu != '1' && menu != '2' && menu != '3' && menu != '4' && menu != '0');
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
    printf("%c\n\n", 188);
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

        char estado = livro[i].estado[0];
        switch (estado)
        {
        case 'D':
        case 'd':
            printf("Estado: Disponivel\n");
            break;
        case 'R':
        case 'r':
            printf("Estado: Requisitado\n");
            break;
        case 'I':
        case 'i':
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

    for (int i = 1; i < requisicao_count + 1; i++)
    {
        printf("Numero de leitor: %s\n", requisicao[i].codigo_leitor);
        printf("ISBN: %s\n", requisicao[i].ISBN);
        printf("Data de requisicao: %d/%d/%d\n\n", atoi(requisicao[i].data_requisicao_dia), atoi(requisicao[i].data_requisicao_mes), atoi(requisicao[i].data_requisicao_ano));
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

void Listagem_ultimas_requisicoes(Leitor_t leitor[], Livro_t livro[], Requisicao_t requisicao[])
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

    // lista de ultimas requisicoes por leitor
    for (int i = 1; i < requisicao_count; i++)
    {
        printf("Numero de leitor: %s\n", requisicao[i].codigo_leitor);
        for (int j = 1; j < livro_count; j++)
        {
            // ########################ESTou aqui################################
        }
    } 
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
    printf("\n\tDados guardados com sucesso!\n\n");
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
