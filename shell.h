#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <ctype.h>
#define BUFFSIZE 128

int parse(char *buf, char **args);

void execute(int argv, char **args);

int builtin(char **args, int argn);

void socp(char *, char *);

void ioCopy(int, int);

void calc(char *value1, char *op, char *value2);

void bits(char *op1, char *op, char *op2);

int isjpeg(int fileDescriptor);

int redirects(int numargs, char *args[]);

void aviso(char *mesg, int tempo);

void *avisowrapper(void *args);

void *socpwrapper(void *args);

void listar(char *pasta);

long int findSize(char file_name[]);

typedef struct
{
    char msg[100];
    int tempo;
} aviso_t;

typedef struct
{
    char fonte[100];
    char destino[100];
} copiar_t;


/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1


///Red
#define RED "\x1B[0;31m"
///Green
#define GRN "\x1B[0;32m"
///Yellow
#define YEL "\x1B[0;33m"
///Blue
#define BLU "\x1B[0;34m"
///Magenta
#define MAG "\x1B[0;35m"
///Cyan
#define CYN "\x1B[0;36m"
///White
#define MR_WHITE "\x1B[0;37m"
///Reset
#define RST "\x1B[0m"
//Bold
///Bold Red
#define B_RED "\x1B[1;31m"
///Bold Green
#define B_GRN "\x1B[1;32m"
///Bold Yellow
#define B_YEL "\x1B[1;33m"
///Bold Blue
#define B_BLU "\x1B[1;34m"
///Bold Magenta
#define B_MAG "\x1B[1;35m"
///Bold Cyan
#define B_CYN "\x1B[1;36m"
///Bold White
#define B_MR_WHITE "\x1B[37m"
