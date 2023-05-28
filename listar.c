

#include "shell.h"

void getFileCreationTime(char *path, char *fileName)
{
    struct stat attr;
    char filePath[1024];
    sprintf(filePath, "%s/%s", path, fileName);

    stat(filePath, &attr);

    printf("%s", ctime(&attr.st_ctime));
}

void listar(char *pasta)
{
    if (pasta == NULL)
        pasta = ".";

    DIR *di;
    struct dirent *dir;
    di = opendir(pasta);
    if (di)
    {
        while ((dir = readdir(di)) != NULL)
        {
            printf("%15s %li %i ", dir->d_name, dir->d_ino, dir->d_reclen);
            getFileCreationTime(pasta, dir->d_name);
        }
        closedir(di);
    }
}