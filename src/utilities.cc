#include <cctype>

#include "utilities.h"

unsigned nextToken(string s, unsigned start) {
    for (; start < s.size(); start++) {
        // Break if not space, or else go on
        if (!isspace(s[start])) break;
    }
    return start;
}
