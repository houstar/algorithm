#ifndef INT_HASH_H
#define INT_HASH_H

#include <stdint.h>

/* Hardcoded Bits per long  */
#define BITS_PER_LONG 64

/**
 * hash_long - get the hash value of long
 *
 * \param val  the key
 * \param bits the bucket size = 2^bits
 *
 * \return hash value
 */

#if BITS_PER_LONG == 32
#define hash_long(val, bits) hash_32(val, bits)
#elif BITS_PER_LONG == 64
#define hash_long(val, bits) hash_64(val, bits)
#else
#error Wordsize not 32 or 64
#endif
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
#define GOLDEN_RATIO_32 0x61C88647
#define GOLDEN_RATIO_64 0x61C8864680B583EBull

static inline uint32_t hash_32(uint32_t val, unsigned int bits);
static inline uint64_t hash_64(uint64_t val, unsigned int bits);

#endif //INT_HASH_H
