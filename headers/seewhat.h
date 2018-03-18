#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define OOO2_H 42
#define TAG_SIZE 12

#define BYTE 1
#define ASCII 2
#define SHORT 3
#define LONG 4
#define RATIONAL 5
#define SBYTE 6
#define UNDEFINE 7
#define SSHORT 8
#define SLONG 9
#define SRATIONAL 10
#define FLOAT 11
#define DOUBLE 12






typedef char * string;



typedef char ONE_BYTE;
typedef unsigned short TWO_BYTES;
typedef unsigned int FOUR_BYTES;
typedef unsigned long long EIGHT_BYTES;

typedef struct tiff_head
{
    ONE_BYTE id_one;
    ONE_BYTE id_two;
    TWO_BYTES version;
    FOUR_BYTES IFD_offset;
} HEADER;

typedef struct ifd_tag
{
    TWO_BYTES id;
    TWO_BYTES type;
    FOUR_BYTES count;
    FOUR_BYTES offset;
} TAG;

typedef struct tiff_ifd
{
    TWO_BYTES counter;
    TAG * tag_head;
    FOUR_BYTES next_ifd;
} IMAGE_FILE_DIRECTORY;

typedef struct tiff
{
    HEADER _header;
    IMAGE_FILE_DIRECTORY _ifd;
    
} TIFF;


/**
 * 0 for read in order of II
 * 1 for read in order of MM
 **/
static char byte_order = 0;
static off_t file_size = 0;

/**
 *  This function gets a filedescriptor and reads all bytes
 * to a string (aka char * ... bkz: line 29) 
 **/
string get_all(int fp);


TIFF parse(string input);

FOUR_BYTES get_firstIFD(string input);






void read_charly(int);



void update_bytes(HEADER * updated);



int get_header(int, HEADER *);

int get_ifd(int, IMAGE_FILE_DIRECTORY *);

int get_allTags(int, IMAGE_FILE_DIRECTORY *);

int getAtag(int, TAG *);

