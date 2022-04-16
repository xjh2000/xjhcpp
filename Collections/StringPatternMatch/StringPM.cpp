#include "StringPM.h"

int StringPM::brute_force_match(const char* patter, const char* text)
{
    int i = 0;
    while (text[i] != '\0')
    {
        int j = 0;
        while (patter[j] != '\0')
        {
            if (text[i + j] != patter[j])
                break;
            j++;
        }
        if (patter[j] == '\0')
            return i;
        i++;
    }
    return -1;
}
