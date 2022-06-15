#include <stdio.h>
#include <stdlib.h>
#include <string.h> // para ler os binários e não usei na procurar.

struct DataDeNascimento
{
  char diamesano[100];
};
struct contatos
{ //estrutura de cada contato
  char NomeDoContato[100];
  char NumeroDoContato[100];
  struct DataDeNascimento data;
};

struct contatos *carregararquivo(char x, int *contador) {
  int i = 0, j = 0, k, l, m;
  char buffer[1000];
  char contatao[135];
  FILE *arqvagenda;
  struct contatos *carregararquivo = NULL;

  if (x == 't')
  {
    arqvagenda = fopen("aqrvagenda.txt", "r");

    fgets(buffer, 10, arqvagenda);
    int numeroContatos = atoi(buffer);

    carregararquivo = (struct contatos *)malloc(numeroContatos * sizeof(struct contatos)); // agenda será um vetor de contatos, representada por este ponteiro

    if (carregararquivo == NULL)
    {
      printf("Erro de alocacao\n");
    }

    int i = 0;
    fgets(buffer, 1000, arqvagenda); //pego uma linha do arquivo
    while (!feof(arqvagenda))
    {

      char *nome = strtok(buffer, ";");
      char *celular = strtok(NULL, ";");
      char *diamesano = strtok(NULL, ";");

      strcpy(carregararquivo[i].NomeDoContato, nome);
      strcpy(carregararquivo[i].NumeroDoContato, celular);
      strcpy(carregararquivo[i].data.diamesano, diamesano);

      printf("%s;%s;%s\n", nome, celular, diamesano);

      i = i + 1;

      fgets(buffer, 1000, arqvagenda); //pego uma linha do arquivo
    }

    *contador = i;

    fclose(arqvagenda);

    return carregararquivo;
  }
  if (x == 'b')
  {
    int numeroContatos;
    arqvagenda = fopen("aqrvagenda.bin", "rb");
    struct contatos *carregararquivo;

    fread(&numeroContatos, sizeof(int), 1, arqvagenda);                                    //a primeira informação armazenada é o número de contatos da lista
    carregararquivo = (struct contatos *)malloc(numeroContatos * sizeof(struct contatos)); // agenda será um vetor de contatos, representada por este ponteiro

    if (carregararquivo == NULL)
    {
      printf("Erro de alocacao\n");
    }

    for (int i = 0; i < numeroContatos; i++)
    {
      struct contatos contato;
      fread(&contato, sizeof(struct contatos), 1, arqvagenda);

      strcpy(carregararquivo[i].NomeDoContato, contato.NomeDoContato);
      strcpy(carregararquivo[i].NumeroDoContato, contato.NumeroDoContato);
      strcpy(carregararquivo[i].data.diamesano, contato.data.diamesano);
    }

    *contador = numeroContatos;

    fclose(arqvagenda);

    return carregararquivo;
  }
}

void salvararquivo(struct contatos *agenda, int contador, char x)
{
  int dimensao = 1, j = 0;
  FILE *arqvagenda;
  if (x == 't')
  { //comandos para salvar arquivos de texto
    arqvagenda = fopen("aqrvagenda.txt", "w");

    fprintf(arqvagenda, "%d\n", contador);

    for (int i = 0; i < contador; i++)
    {
      char *nome = agenda[i].NomeDoContato;
      char *celular = agenda[i].NumeroDoContato;
      char *diamesano = agenda[i].data.diamesano;

      //https://stackoverflow.com/questions/30260986/how-to-print-a-string-using-printf-without-it-printing-the-trailing-newline
      nome[strcspn(nome, "\n")] = 0;
      celular[strcspn(celular, "\n")] = 0;
      diamesano[strcspn(diamesano, "\n")] = 0;

      printf("%s;%s;%s\n", nome, celular, diamesano);

      fprintf(arqvagenda, "%s;%s;%s\n", nome, celular, diamesano);
    }
    fclose(arqvagenda);
  }
  if (x == 'b')
  { //comandos para salvar arquivos binarios
    arqvagenda = fopen("aqrvagenda.bin", "wb");

    fwrite(&contador, sizeof(int), 1, arqvagenda); //guardo inicialmente a quantidade de contatos
    for (int i = 0; i < contador; i++)
    {
      struct contatos contato = agenda[i];
      fwrite(&contato, sizeof(struct contatos), 1, arqvagenda); //a cada iteração armazeno um objeto de Contato
  
    }
    fclose(arqvagenda);
  }
}

struct contatos *inserircontato(struct contatos *agenda, int contador)
{
  agenda = realloc(agenda, contador + 1 * sizeof(struct contatos)); //realoco a memória para aumentar o tamanho da agenda de acordo com que os contatos são inseridos

  printf("Nome:\n"); //inserindo nome do contato
  getchar();
  fgets(agenda[contador].NomeDoContato, 100, stdin);
  printf("Numero:{(XX) X XXXX-XXXX}\n"); //inserindo numero do contato
  fgets(agenda[contador].NumeroDoContato, 100, stdin);
  printf("Data de nascimento:(dd/mm/aa)\n");          //inserindo data de nascimento do contato
  fgets(agenda[contador].data.diamesano, 100, stdin); //o usuario insere o contato e ele já é salvo no vetor de contatos da agenda

  return agenda;
}

int procurarcontato(struct contatos *agenda, char *inserido, int contador, int x)
{ //função char para procurar contato e retornar string
  int inicializador = 0, comparacao = 0, tamanhonome = 0;
  int j, parametro, k;

  for (j = 0; inserido[j] != '\0'; j++)
  {
    inicializador++; //inicializador é um vetor do tamanho da string inserida, para posteriores comparações
  }
  inicializador--;
  for (parametro = x; parametro < contador; parametro++)
  {
    for (int i = 0; agenda[parametro].NomeDoContato[i] != '\0'; i++)
    {

      if (agenda[parametro].NomeDoContato[i] == inserido[0])
      { //busca um caracter igual ao nome no que foi inserido para comparação
        k = i;
        for (j = 0; j < inicializador; j++)
        {
          if (inserido[j] == agenda[parametro].NomeDoContato[k])
          { //a partir do igual conta todos os contatos que são iguais para testar posteriormente
            comparacao++;
          }
          k++;
        }
      }
      if (inicializador == comparacao)
      {                   //comparo se a string inserida tem o mesma quantidade da quantidade de caracteres iguais
        return parametro; //retona as posições dos contatos encontrados
      }
      comparacao = 0;
    }
  }
}

int excluircontato(char *excluido, struct contatos *agenda, int contador)
{ //função para excluir contato
  int j, i, k, excluir = 0;
  for (k = 0; k < contador; k++)
  {
    excluir = procurarcontato(agenda, excluido, contador, k); //passando parametros para funçao procurar contatos
    if (k == excluir)
    {
      for (j = excluir; j < contador; j++)
      {                            // ler a agenda a partir da posição que precisa ser excluida
        agenda[j] = agenda[j + 1]; //a posição do contato a ser excluido, recebe a próxima posição até a ultima posição da agenda estar vazia
      }
      agenda = realloc(agenda, (contador - 1) * sizeof(struct contatos)); // apaga a ultima posição da agenda
      return 1;
    }
  }
}

void exibircontatos(struct contatos *agenda, int contador)
{
  printf("Sua agenda sera exibida em sequencia\n");
  for (int i = 0; i < contador; i++)
  {                                          //percorre a agenda
    printf("%s\n", agenda[i].NomeDoContato); //acessa os contatos e printa de acordo com o que foi salvo na agenda
    printf("%s\n", agenda[i].NumeroDoContato);
    printf("%s\n", agenda[i].data.diamesano);
  }
}

int main() {
  //int tamanho = 1, contador = 0;
  int contador = 0;
  struct contatos *agenda = NULL;
  agenda = (struct contatos *)malloc(sizeof(struct contatos)); // agenda será um vetor de contatos, representada por este ponteiro
  if (agenda == NULL)
  {
    printf("Erro de alocacao\n");
  }

  int teste = 0, verdade = 0, ok = 0, entrada, menu; // chamando a struct na main
  printf("Deseja abrir o menu da sua agenda de contatos? (Prescione um numero maior que 0)\n");
  while (scanf("%d", &entrada) != 0)
  { //sempre que quiser encerrar o programa prescione 0.
    printf("Para carregar os contatos do arquivo, digite 1.\n");
    printf("Para exibir todos os contatos, digite 2.\n");
    printf("Para inserir um contato, digite 3.\n");
    printf("Para procurar um contato, digite 4.\n");
    printf("Para excluir um contato, digite 5.\n");
    printf("Para salvar no arquivo, digite 6.\n");
    scanf("%d", &menu);

    if (menu == 1)
    {
      char x;
      printf("Voce deseja carregar a agenda do arquivo texto ou do arquivo binario? (escreva t para texto ou b para binario)\n");
      scanf(" %c", &x);                       //encaminha o usuário para carregar um arquivo texto ou binario
      agenda = carregararquivo(x, &contador); //vai para função carregar contatos do arquivo
    }

    if (menu == 2)
    {
      exibircontatos(agenda, contador); // encaminha para a fução exibir que imprime os contatos da agenda
      printf("Contatos printados na agenda.\n");
    }

    if (menu == 3)
    {
      printf("Insira um contato na sua agenda\n");
      agenda = inserircontato(agenda, contador); // encaminha para a fução inserir que insere os contatos da agenda
      contador++;
      /*if (ok == 1)
      {
        printf("Seu contato foi inserido com sucesso\n");
      }*/
    }

    char partesNomeDoContato[100], partesnomeparaexcluir[100];

    if (menu == 4)
    {
      printf("Pesquise o nome do seu contato\n");
      getchar();
      fgets(partesNomeDoContato, 100, stdin); //recebendo nome para procurar contato
      for (int i = 0; i < contador; i++)
      {
        verdade = procurarcontato(agenda, partesNomeDoContato, contador, i); //passando parametros para funçao procurar contatos
        if (i == verdade)
        {
          printf("%s\n", agenda[verdade].NomeDoContato);
          printf("%s\n", agenda[verdade].NumeroDoContato);
          printf("%s\n", agenda[verdade].data.diamesano);
        }
      }
    }

    if (menu == 5)
    {
      int excluido;
      printf("Pesquise o nome do contato que voce deseja excluir (escreva identico ao que esta na agenda para excluir o contato correto)\n");
      getchar();
      fgets(partesnomeparaexcluir, 100, stdin);
      excluido = excluircontato(partesnomeparaexcluir, agenda, contador); // encaminha para a fução excluir que exclui os contatos da agenda
      contador--;
      if (excluido == 1)
      {
        printf("%sexcluido da sua agenda\n", partesnomeparaexcluir);
      }
    }

    if (menu == 6)
    {
      char x;
      printf("Voce deseja salvar a agenda no formato texto ou binario? (escreva t para texto ou b para binario)\n");
      scanf(" %c", &x);                   //da ao usuario opção de salvar como arquivo binario ou texto
      salvararquivo(agenda, contador, x); //encaminha para função salvar arquivo
      printf("Seus contatos foram salvos no arquivo\n");
    }
  }
  free(agenda);
  return 0;
}