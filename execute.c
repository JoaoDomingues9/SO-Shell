/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"
#include <sys/wait.h>

int ultimo(int *numargs, char **args)
{
  if (args[*numargs - 1][0] == '&')
  {
    *numargs = *numargs - 1;
    args[*numargs] = NULL;
    return BG;
  }
  return FG; /*return FG ou BG definidos no shell.h */
}

/* Detect PIPE SYMBOL in array of Strings return its index or -1 if it does not exist */

int containsPipe(int numArgs, char **args)
{
  int index;
  for (index = 0; index < numArgs; index++)
    if (args[index][0] == '|')
    {
      return index;
    }
  return -1;
}
void execute(int argv, char **args)
{
  int code = ultimo(&argv, args);
  int pid, pidFilho, status, fd[2];

  if ((pid = fork()) < 0)
  {                  /* cria um processo progenito */
    perror("forks"); /* NOTE: perror() produz uma pequema mensagem de erro para o stream */
    exit(1);         /* estandardizado de erros que descreve o ultimo erro encontrado */
                     /* durante uma chamada ao sistema ou funcao duma biblioteca */
  }

  if (pid == 0)
  {
    int indice = containsPipe(argv, args);
    if (indice == -1)
    {
      redirects(argv, args);
      execvp(*args, args);
    }
    if (indice > 0)
    {
      args[indice] = NULL;
      pipe(fd);
      pidFilho = fork();
      if (pidFilho == 0)
      { // write
        argv = indice;
        redirects(argv, args);
        // O output do primeiro comando, em vez de ir para o sdout, vair para o input do segundo
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
      }
      else
      { // read
        args = args + indice + 1;
        argv = argv - indice - 1;
        redirects(argv, args);
        // O input do segundo comando, em vez de ir vir do stdin, vem do output do primeiro
        dup2(fd[0], STDIN_FILENO); // duplicar o descritor de ficheiro de leitura do PIPE para a posição na tabele de FD do STDIN
        close(fd[1]);
        close(fd[0]); // fechar o descritor do ficheiro do pipe que este processo não necessita.
      }
      execvp(*args, args); // Chamar a função execvp() para executar os comandos agora ligados via um pipe.
    }

    execvp(*args, args);
    perror(*args);
    exit(1);
  }

  if (FG == code)
    while (wait(&status) != pid)
      ;
  /*spin fazer nada */;

  // NOTE: as versoes execv() e
  // execvp() de execl() sao uteis quando
  // o numero de argumentos nao e. conhecido
  // Os argumentos de execv() e execvp()
  // sao o nome do ficheiro a ser executado e um
  // vector de strings que contem os
  // argumentos. O ultimo argument */

  return;
}