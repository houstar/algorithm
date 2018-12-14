#include <hash/int_hash.h>

/*
 * This hash multiplies the input by a large odd number and takes the
 * high bits.  Since multiplication propagates changes to the most
 * significant end only, it is essential that the high bits of the
 * product be used for the hash value.
 *
 * Chuck Lever verified the effectiveness of this technique:
 * http://www.citi.umich.edu/techreports/reports/citi-tr-00-1.pdf
 *
 * Although a random odd number will do, it turns out that the golden
 * ratio phi = (sqrt(5)-1)/2, or its negative, has particularly nice
 * properties.  (See Knuth vol 3, section 6.4, exercise 9.)
 *
 * These are the negative, (1 - phi) = phi**2 = (3 - sqrt(5))/2,
 * which is very slightly easier to multiply by and makes no
 * difference to the hash distribution.
 */

static inline uint32_t hash_32(uint32_t val, unsigned int bits)
{
    return (val * GOLDEN_RATIO_32 ) >> (32 - bits);
}

static inline uint64_t hash_64(uint64_t val, unsigned int bits)
{
    return (val * GOLDEN_RATIO_64) >> (64 - bits);
}
