#include "../headers/seewhat.h"
string get_all(int fp)
{
    string file_info = NULL;
    if(((file_size = lseek(fp, 0, SEEK_END)) == -1) || (lseek(fp, 0, SEEK_SET) == -1))
        perror("Error to get filesize");
    else
    {
        file_info = (string) malloc(sizeof(ONE_BYTE) * file_size);
        for(int i = 0; read(fp, (file_info + i), sizeof(ONE_BYTE)); ++i);
    }
    return file_info;
}


FOUR_BYTES get_firstIFD(const string const input)
{
    FOUR_BYTES fdoffset;
    if((*input == *(input + 1)) && (*input == 'M'))
        byte_order = 8;
    //CHECK FOR IF VERSION == 42
    if(get_two(input + 2 * sizeof(ONE_BYTE)).data == 42)
        fdoffset = get_four(input + sizeof(FOUR_BYTES));
    else fdoffset.data = -1;
    
    return fdoffset;
}


TIFF parse(string input)
{
    IMAGE_FILE_DIRECTORY boii;
    if((boii.this_offset = get_firstIFD(input)).data == -1);
    else
    {
        get_tags(input + boii.this_offset.data, &boii);
    }
}

FOUR_BYTES get_tags(const string const input, IMAGE_FILE_DIRECTORY * output)
{
    
    output->counter = get_two(input);
    output->tag_head = (TAG *) malloc(sizeof(TAG) * output->counter.data);
    
    for(int i = 0; i < output->counter.data; ++i)
    {
        getAtag(input + (TAG_SIZE * i) + sizeof(TWO_BYTES), (output->tag_head + i));
        {
            printf("|\t\t|%d\t|\tTag ID\t\t|\n",  (*(output->tag_head + i)).id.data);
            printf("|\t\t|%d\t|\tData Type\t|\n", (*(output->tag_head + i)).type.data);
            printf("|\t\t|%d\t|\tDaya Count\t|\n",(*(output->tag_head + i)).count.data);
            printf("|\t\t|%d\t|\tData Offset\t|", (*(output->tag_head + i)).offset.data);
            printf("\n-------------------------------------------------\n");
            sleep(1);        
        }
    }
    free(output->tag_head);
}

int parse_tag(IMAGE_FILE_DIRECTORY * input, TIFF * output)
{
    for(int i = 0; i < input->counter.data; ++i)
    switch(input->counter.data)
    {
    case IMAGEWIDTH:

    case IMAGELENGTH:

    case COMPRESSION:

    case PhotometricInterpretation:

    case StripOffsets:

    case StripByteCounts:

    case XResolution:

    case YResolution:

    case ResolutionUnit:

    default:
        perror("Unknown tag ID");
        break;
    }
}
/*
int get_value(const string const input, const TAG * const search, void * const output)
{
    switch(search->type.data)
    {
        
    }
    return 0;
}

*/
int getAtag(const string const input, TAG * next_node)
{
    int ret_val = 0;
    next_node->id = get_two(input);    
    next_node->count = get_four(input + sizeof(FOUR_BYTES));
    //CHECK THE TYPE OF VALUE
    switch((next_node->type = get_two(input + sizeof(TWO_BYTES))).data)
    {
    case BYTE:
        break;
    case SHORT:
    case LONG:
        //CHECK THE COUNT OF VALUE
        if(next_node->count.data == 1)
            next_node->offset.data = get_two(input + (2 * sizeof(FOUR_BYTES))).data;
        else    
            next_node->offset = get_four(input + (2 * sizeof(FOUR_BYTES)));
        break;
    case RATIONAL:
        next_node->offset = get_four(input + (2 * sizeof(FOUR_BYTES)));
        break;
    default:
        perror("Unexpected Type");
        break;
    }
    return 0;
}



//0000 0000 0000 0000 | 0010 1010 0000 0000
//-----------------------------------------
//0010 1010 0000 0000 >> 8 * 1
//-----------------------------------------
//0000 0000 0010 1010 (42)
TWO_BYTES get_two(const string const order_reader)
{
    TWO_BYTES ret_val;
    switch (byte_order)
    {
        case 0:
            ret_val.field[0] = *(order_reader);
            ret_val.field[1] = *(order_reader + 1);
            break;
        case 8:
            ret_val.field[0] = *(order_reader + 1);
            ret_val.field[1] = *(order_reader);
            break;
        default:
            break;
    }
    return ret_val;
}

FOUR_BYTES get_four(const string const order_reader)
{
    FOUR_BYTES ret_val;
    TWO_BYTES temp;
    for(int i = 0; i < 2; ++i)
    {
        temp = get_two(order_reader + (sizeof(TWO_BYTES) * i));
        switch(byte_order)
        {
            case 0:
            // 0 - 0, 1 - 1 : 2 - 2, 3 - 3
                *(ret_val.field + 2 * i) = *(temp.field);
                *(ret_val.field + 2 * i + 1) = *(temp.field + 1);
                break;
            // 2 - 1, 3 - 0 : 0 - 3, 1 - 2
            case 8:
                *(ret_val.field + 2 - 2 * i) = *(temp.field);
                *(ret_val.field + 3 - 2 * i) = *(temp.field + 1);
                break;
            default:
                break;
        }   
    }
    
    return ret_val;
}