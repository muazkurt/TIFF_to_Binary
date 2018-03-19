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

typedef union twoB
{
    unsigned short data;
    ONE_BYTE field [2];
} TWO_BYTES;
typedef union fourB
{
    unsigned int data;
    ONE_BYTE field [4];
} FOUR_BYTES;

typedef union eightB
{
    unsigned long long data;
    ONE_BYTE field [8];
} EIGHT_BYTES;

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
    FOUR_BYTES this_offset;
    TWO_BYTES counter;
    TAG * tag_head;
    FOUR_BYTES next_offset;
} IMAGE_FILE_DIRECTORY;

typedef struct tiff
{
    HEADER _header;
    IMAGE_FILE_DIRECTORY _ifd;
    
} TIFF;


/**
 * 0 for read in order of II
 * 8 for read in order of MM
 **/
static char byte_order = 0;
static off_t file_size = 0;

/**
 *  This function gets a filedescriptor and reads all bytes
 * to a string (aka char * ... bkz: line 29) 
 **/
string get_all(int fp);

TIFF parse(const string const input);

FOUR_BYTES get_firstIFD(const string const input);

/**
 * return value is 0 or another ifd's offset.
 **/
FOUR_BYTES get_tags(const string const input, IMAGE_FILE_DIRECTORY * output);


int getAtag(string, TAG *);




TWO_BYTES get_two(const string const order_reader);

FOUR_BYTES get_four(const string const order_reader);


