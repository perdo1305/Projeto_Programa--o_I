
# Programa de Gestão de Requisições de Livros

Este programa em linguagem C foi desenvolvido para auxiliar na gestão de requisições de livros de uma biblioteca pelos seus leitores. O programa possui um limite máximo de NLIVROS livros e NLEITORES leitores. Além disso, para cada leitor, as últimas 10 requisições efetuadas serão armazenadas. O programa permite a realização das seguintes operações:

## 1. Registar Livro

Opção que permite, se possível, registar a seguinte informação referente a um livro (dados introduzidos através do teclado com exceção do estado):

- ISBN (International Standard Book Number), será um número único
- Título;
- Autor;
- Editora;
- Estado, que poderá ser: disponível, requisitado ou inutilizado. No entanto, no ato do registo, o estado do livro deverá ser automaticamente “disponível”

## 2. Registar Leitor

Opção que permite, se possível, registar um leitor. Para tal deverão ser solicitados os seguintes dados (introduzidos através do teclado):

- Código de leitor (único)
- Nome;
- Data de Nascimento;
- Localidade
- Contacto telefónico

## 3. Requisitar Livro

Opção que permite um leitor já registado requisitar um livro disponível. Nesta opção, além das identificações do livro e do leitor, deverá ser solicitada a data de requisição.

## 4. Devolver Livro

Opção que permite registar a devolução de um livro requisitado bem como o número de dias que esteve requisitado. Nesta opção deverá ser tido em conta se o livro regressa inutilizado

## 5. Listagens

Esta opção deverá apresentar um submenu com as seguintes opções:

- Listagem de todos os dados de todos os Livros.
- Listagem de todos os dados de todos os Leitores.
- Listagem dos livros já requisitados e no final a quantidade total desses livros.
- Listagem das 10 últimas requisições efetuadas por um determinado leitor.

## 0. Sair

Opção que permite ao utilizador sair do programa e guardar para um ficheiro binário todos os dados do programa.

### Notas Importantes

- Ao iniciar o programa todos os dados armazenados no ficheiro binário deverão ser carregados para o programa.
- Se achar pertinente poderá acrescentar outros campos nas estruturas criadas.