#include "headers/seewhat.h"

int main(int argc, char ** argv)
{
    if(argc == 1)
    {
        printf("Usage: %s <filename>\n", *(argv + 1));
        return -1;
    }
    int fd;
    string file_input;
    if((fd = open(argv[1], O_RDONLY)) > 0)
    {
        file_input = get_all(fd);
        if(parse != NULL)
        {
            parse(file_input);
            free(file_input);
            file_input = NULL;
        }
        close(fd);
    }
    else
        fprintf(stderr, "No such file.\n");
    return 0;
}