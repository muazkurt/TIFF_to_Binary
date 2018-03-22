//ALL Possible type values.
#define BYTE 1
#define ASCII 2
#define SHORT 3
#define LONG 4
#define RATIONAL 5




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

struct bps
{
    FOUR_BYTES count;
    FOUR_BYTES offset_p;
};

