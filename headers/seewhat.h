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

/**
 *  This function gets a filedescriptor and reads all bytes
 * to a string (aka char * ... bkz: line 29) 
 **/
string get_all(int fp);


/**
 * Get a string and read all info in it.
 * Some of the information will be ignored(If unnecessary).
 * Print readen and necessary info to the system output.
 **/
void parse(const string const input);

/**
 *  Find the first ifd's position in the given string.
 **/
FOUR_BYTES get_firstIFD(const string const input);


/**
 *  Get a tag and select if it is necessary or not.
 * If it's necessary, then update secount parameter's
 * declared position with it.
 **/
void parse_tag(TAG *, IMAGE_FILE_DIRECTORY * );


/**
 * return value is 0 or another ifd's offset.
 **/
FOUR_BYTES get_tags(const string const input, IMAGE_FILE_DIRECTORY * output);


/**
 *  Read 12 byte from string.
 *  If and only if the value fit into 4 bytes, 
 * then offset will be the value.
 **/
int getAtag(string, TAG *);



/**
 *  Read two bytes into TWO_BYTES type.
 **/
TWO_BYTES get_two(const string const order_reader);


/**
 *  Read four bytes in byte order.
 *  Return it.
 **/
FOUR_BYTES get_four(const string const order_reader);



/**
 *  Search input with given ifd.
 * Ifd' s fields should be updated before using this.
 * StripOffset value will declare where does the real image starts.
 **/
int get_value(const string const input, IMAGE_FILE_DIRECTORY * const search);