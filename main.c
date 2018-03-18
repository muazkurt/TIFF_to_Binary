#include "headers/seewhat.h"

int main(int argc, char ** argv)
{
    /*if(argc == 1)
    {
        fprintf(sys_err, "Usage: %s <filename>", *(argv + 1));
        return -1;
    }*/
    int fd;
    string temp;
    get_firstIFD(temp = get_all(fd = open(argv[1], O_RDONLY)));
  //  printf("%s\n", temp);
    close(fd);
    return 0;
}