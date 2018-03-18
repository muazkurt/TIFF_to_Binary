#include "../headers/seewhat.h"
string get_all(int fp)
{
    string file_info = NULL;
    if(((file_size = lseek(fp, 0, SEEK_END)) == -1) || (lseek(fp, 0, SEEK_SET) == -1))
        perror("Error to get filesize");
    else
    {
        file_info = (string) malloc(sizeof(ONE_BYTE) * (file_size + 1));
        for(int i = 0; read(fp, (file_info + i), sizeof(ONE_BYTE)); ++i)
        *(file_info + file_size + 1) = 0;
    }
    return file_info;
}


FOUR_BYTES get_firstIFD(string input)
{
    FOUR_BYTES fdoffset = 0;
    unsigned short ver = 0;
    TWO_BYTES counter = 0;
    if((*input == *(input + 1)) && (*input == 'M'))
        byte_order = 1;
    //0000 0000 0000 0000 | 0010 1010 0000 0000
    //-----------------------------------------
    //0010 1010 0000 0000 >> 8 * 1
    //-----------------------------------------
    //0000 0000 0010 1010 (42)
    ver = ((ver | *(input + 2)) >> (8 * byte_order));
    ver |= *(input + 3);

    if(ver == 42)
        for(counter = 4; counter < 8; ++counter)
        {
            fdoffset |= *(input + counter);            
            if(counter < 7)
                fdoffset >>= (8 * byte_order);
        }
    else fdoffset = -1;
    printf("%d\n", fdoffset);
    return fdoffset;
}






void read_charly(int fd)
{
    double search;
    int counter = 0;
    char id;
    unsigned short version = 0;
    int fimg_dir = 0;
    unsigned short tag_c = 0;
    HEADER _head;
    IMAGE_FILE_DIRECTORY _filedir;
    int temp = 0;

    printf("|\t\t\tFORMAT\t\t\t|");
    printf("\n-------------------------------------------------\n");
    printf("|\t\tHead\t\t\t\t|");
    printf("\n-------------------------------------------------\n");
    printf("|Offset\t|Value\t|\tInfo\t\t\t|");
    printf("\n-------------------------------------------------\n");
    
    if(!get_header(fd, &_head) || !lseek(fd, _head.IFD_offset, SEEK_SET))
        perror("Failed to get first informations");
    else 
    {
        printf("|%c%c\t|%d\t|\t%d\t\t\t|", _head.id_one, _head.id_two, _head.version, _head.IFD_offset);
        printf("\n-------------------------------------------------\n");
    
  /*  if(get_ifd(fd, &_filedir))
        printf("|\t\tIFD\t\t\t\t|");
        printf("\n-------------------------------------------------\n");
        printf("|Offset\t\t|Value\t|\tInfo\t\t|");
        printf("\n-------------------------------------------------\n");
        printf("|%d..%d\t\t|%d\t|\tTagCounter\t|", _head.IFD_offset, counter, _filedir.counter);
        printf("\n-------------------------------------------------\n");
        for(int i = 0; i < _filedir.counter; ++i)
        {
            printf("|\t\tTAG %d\t\t\t\t|", i);
            printf("\n-------------------------------------------------\n");
            printf("|Offset\t\t|Value\t| \tInfo\t\t|");
            printf("\n-------------------------------------------------\n");
            printf("|\t\t|%d\t|\tTag ID\t\t|\n",  _filedir.tag_head[i].id);
            printf("|\t\t|%d\t|\tData Type\t|\n", _filedir.tag_head[i].type);
            printf("|\t\t|%d\t|\tDaya Count\t|\n",_filedir.tag_head[i].count);
            printf("|\t\t|%d\t|\tData Offset\t|", _filedir.tag_head[i].offset);
            printf("\n-------------------------------------------------\n");
        }*/
    }
    return;
}


int get_header(int fd, HEADER * updater)
{
    int ret_val = 0;
    if((read(fd, updater, sizeof(HEADER))) < sizeof(HEADER))
        perror("There is an error in file");
    else
    {
        if(updater->id_one == 'M') byte_order = 8;
        update_bytes(updater);
        ret_val = 8;
        if(updater->version != 42)
            ret_val = -1;
    }
    return ret_val;
}


int get_ifd(int fd, IMAGE_FILE_DIRECTORY * updater)
{
    int ret_val = 0;
    if((read(fd, &(updater->counter), sizeof(TWO_BYTES)) < sizeof(TWO_BYTES)) && !(ret_val = -1))
        perror("Filedir Tags can't be readen");
    else if((get_allTags(fd, updater) < 0) && !(ret_val = -1))
        perror("Failed to get Tags");
    else if((read(fd, &(updater->next_ifd), sizeof(FOUR_BYTES)) < 0) && !(ret_val = -1))
        perror("Failed to get next ifd's offset");
    else
        ret_val = sizeof(TWO_BYTES) + (updater->counter * TAG_SIZE) + sizeof(FOUR_BYTES);
    return ret_val;
}


int get_allTags(int fd, IMAGE_FILE_DIRECTORY * updater)
{
    int ret_val = 0;
    if(updater->counter < 0 && (ret_val = -1))
        perror("There is no tag count");
    else
    {
        updater->tag_head = (TAG *) malloc(TAG_SIZE * updater->counter);
        for(int i = 0; i < updater->counter; ++i)
            ret_val += getAtag(fd, &(updater->tag_head)[i]);
    }
    return ret_val;
}


int getAtag(int fd, TAG * next_node)
{
    int ret_val = 0;
    if((ret_val = read(fd, next_node, TAG_SIZE) < 0) && !(ret_val = -1))
        perror("Tag can't be readen");
    return ret_val;
}

void update_bytes(HEADER * updated)
{
    updated->version >>= byte_order; 
    updated->IFD_offset >>= ((sizeof(FOUR_BYTES) - 1) * byte_order);
}
