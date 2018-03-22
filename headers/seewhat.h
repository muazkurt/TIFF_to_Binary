#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "tags.h"


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

void parse_tag(TAG *, IMAGE_FILE_DIRECTORY * );


/**
 * return value is 0 or another ifd's offset.
 **/
FOUR_BYTES get_tags(const string const input, IMAGE_FILE_DIRECTORY * output);


int getAtag(string, TAG *);



/**
 *  Read two bytes into TWO_BYTES type.
 **/
TWO_BYTES get_two(const string const order_reader);


FOUR_BYTES get_four(const string const order_reader);


int get_value(const string const input, IMAGE_FILE_DIRECTORY * const search);