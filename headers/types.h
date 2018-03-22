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
/*
typedef union eightB
{
    unsigned long long data;
    ONE_BYTE field [8];
} EIGHT_BYTES;
*/


struct bps
{
    FOUR_BYTES count;
    FOUR_BYTES offset_p;
};








/*
le = 101 (COL+1)

ll = 101 (ROW+1)

ie = 1

il = 1

*/
















