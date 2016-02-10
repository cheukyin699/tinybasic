#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

using namespace std;

/* The clamp function takes a lower bound (inclusive) and an upper bound
 * (exclusive) and checks to see if the number is within these 2 bounds. If it
 * is, it returns the number. If it isn't, it returns either the upper or lower
 * bound, depending on which one it violated, effectively 'clamping' it to
 * between those values.
 */
template <typename T>
T clamp(T lo, T hi, T x) {
    if (x >= lo && x < hi)  return x;
    else if (x >= hi)       return hi;
    else                    return lo;
}

/* Takes a string and a starting index (it assumes the index is within range of
 * the string) and goes through it to find the next non-space character. Returns
 * the size of the string if it can't find it.
 */
unsigned nextToken(string, unsigned);


#endif
