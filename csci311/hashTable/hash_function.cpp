/* This assignment originated at UC Riverside.*/
 
#include <string>
#include "hash.h"
#include <cmath>

using std::string;

/**
 *  Hashing a string is very different from hashing an integer. 
 *  The trick to hashing an integer is performing a controlled randomizer,
 *  Which is why the example shown in class | floor(m(k A mod 1)) | is so good.
 *  But the key to hashing a string is getting to a number in the first place.
 *
 *  The obvious first step is doing an ascii conversion,
 *  But you have to be very careful about how you do it,
 *  Because straight ascii conversion treats "abcde" the same as "edcba".
 *  There are only 52 letters, so on large datasets this will happen often.
 *
 *  Another thing to note is the size of the resultant number.
 *  With straight addition, the maximum word "zzzzz" will sum to 610.
 *  If we just added like this, any slots above 609 are wasted.
 *  So we want the resultant number to be much larger than the table size.
 *
 *  With these things in mind, I can define the foundation of my hash function.
 *  It needs to convert the string using ascii in an order-significant way,
 *  And the resultant number should be much larger than the table size.
 *
 *
 *  ***NOTE The "order matters" constraint is only partially implemented
 *          It is possible to achieve a unique resultant for every permutation,
 *          Particularly on a 5-letter only set like this one.
 *          But collisions would still occur (due to the necessity of modulo)
 *          And the point of a hash function is to be fast,
 *          So I didn't want to make it unnecessarily complex
 */
int Hash::hf(string ins)
{
    int slot = ins[0] * ins[2] * ins[4];
    slot -= (ins[1] * ins[3]);
    return (slot % HASH_TABLE_SIZE);
}

