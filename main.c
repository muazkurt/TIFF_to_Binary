#include "headers/seewhat.h"

int main(int argc, char ** argv)
{
    if(argc == 1)
    {
        printf("Usage: %s <filename>", *(argv + 1));
        return -1;
    }
    int fd;
    string temp;
    parse(temp = get_all(fd = open(argv[1], O_RDONLY)));
  
    close(fd);
    
    free(temp);
    temp = NULL;
    return 0;
}