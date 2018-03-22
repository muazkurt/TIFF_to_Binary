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
    IMAGE_FILE_DIRECTORY first_ifd;
    //Declaring default values.
    first_ifd.compress.data = 1;
    first_ifd.samplesPP.data = 1;


    //end of declaring part.
    if((first_ifd.this_offset = get_firstIFD(input)).data == -1);
    else
    {
        get_tags(input + first_ifd.this_offset.data, &first_ifd);
        if(first_ifd.bitsPsample.count.data == 1 &&  first_ifd.compress.data == 1 &&  first_ifd.pi.data < 2)
        {
            printf("Image Width: %d\n", first_ifd.width.data);
            printf("Image Length: %d\n", first_ifd.length.data);
            printf("Byte format: %s\n", (byte_order == 8 ? "Motorola" : "Intel"));            
            get_value(input, &first_ifd);
        }
        else
            fprintf(stderr, "Unexpected file format.");
    }
}

FOUR_BYTES get_tags(const string const input, IMAGE_FILE_DIRECTORY * output)
{
    
    TWO_BYTES counter = get_two(input);
    TAG empty;
    for(int i = 0; i < counter.data; ++i)
    {
        getAtag(input + (TAG_SIZE * i) + sizeof(TWO_BYTES), &empty);
        parse_tag(&empty, output);
    }
}

void parse_tag(TAG * input, IMAGE_FILE_DIRECTORY * output)
{
    switch(input->id.data)
    {
    case IMAGEWIDTH:
        output->width = input->offset;
        break;
    case IMAGELENGTH:
        output->length = input->offset;       
        break;
    case BitsPerSample:
        output->bitsPsample.count = input->count;
        output->bitsPsample.offset_p.data = input->offset.data;
        break;
    case PhotometricInterpretation:
        output->pi.data = input->offset.data;
        break;
    case RowsPerStrip:
        output->rowsperS.data = input->offset.data;
        break;
    case SamplesPerPixel:
        output->samplesPP.data = input->offset.data;
        break;
    case StripOffsets:
    //DEFAULT = 1 so working on grayscale or bilevel.
        output->stripOffset.data = input->offset.data;
        break;
    case StripByteCounts:
        output->stripByteC.data = input->offset.data;
        break;

    /**
     * KNOWN ISSUES
     **/
    case NEWIFD:
    case DOC_NAME:
        //DON'T CARE
    case COMPRESSION:
        //DON'T CARE BECAUSE: ONLY WORKING ON UNCOMPRESSED.
    case XResolution:
    case YResolution:
    case ResolutionUnit:
    case Oriantetion:
    case 270://IMAGE DESCRIPTION.
    case PlannerConf:
        /**
         * DECLARE DON'T CARES.
         */
        break;
    default:
        #ifdef WATCH
            fprintf(stderr, "Unknown tag ID.\n");
        #endif
        break;
    }
    return;
}

int get_value(const string const input, IMAGE_FILE_DIRECTORY * const search)
{
    if(search->bitsPsample.count.data > 1)
        search->bitsPsample.offset_p.data = get_two(input + search->bitsPsample.offset_p.data).data;
    else if(search->bitsPsample.offset_p.data == 1)
        search->bitsPsample.offset_p.data = 8; 
    TWO_BYTES temp;
    for(int i = 0; i < search->length.data; i+=1)
    {
        for(int j = 0; j < search->width.data; j += 1)
        {
            temp.data = 0;            
            switch(search->bitsPsample.offset_p.data)
            {
            case 4:
                fprintf(stderr, "Unexpected image bit order\n");
                break;
            case 8:
            default:
                temp.field[0] = *(input + search->stripOffset.data + (i * search->width.data) + j) & 1;            
                if(search->pi.data == 0)
                    temp.field[0] != temp.field[0];
                break;
            }

            printf("%d ", temp.data);
        }
        printf("\n");
    }
    return 0;
}





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
        next_node->offset.data = get_two(input + (2 * sizeof(FOUR_BYTES))).data;
        break;
    case ASCII:
    case LONG:
        //CHECK THE COUNT OF VALUE
        //if(next_node->count.data == 1)
        //else    
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