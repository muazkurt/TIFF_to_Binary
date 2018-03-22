#include "types.h"


#define OOO2_H 42
#define TAG_SIZE 12



#define NEWIFD          254
#define IMAGEWIDTH      256
#define IMAGELENGTH     257
#define BitsPerSample   258
#define COMPRESSION     259

/**
 * Image bit sequance information that
 * tells if 0 is white or black.
 **/
#define PhotometricInterpretation 262



#define DOC_NAME        269
/**
 * Offset to real image.
 **/
#define StripOffsets    273
#define Oriantetion     274


#define SamplesPerPixel 277
#define RowsPerStrip    278
#define StripByteCounts 279


#define XResolution     282
#define YResolution     283
#define PlannerConf     284
#define ResolutionUnit  296







typedef char * string;








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
    FOUR_BYTES offset; //value
} TAG;

typedef struct tiff_ifd
{
    FOUR_BYTES                  this_offset;
    FOUR_BYTES                  width;
    FOUR_BYTES                  length;
    struct bps                  bitsPsample;
    TWO_BYTES                   compress;
    TWO_BYTES                   pi;
    FOUR_BYTES                  stripOffset;
    TWO_BYTES                   samplesPP;
    FOUR_BYTES                  rowsperS;
    FOUR_BYTES                  stripByteC;
    FOUR_BYTES                  next_offset;
} IMAGE_FILE_DIRECTORY;

typedef struct tiff
{
    IMAGE_FILE_DIRECTORY _ifd;
    
} TIFF;