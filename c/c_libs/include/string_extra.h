#ifndef __STRING_EXTRA_H__
#define __STRING_EXTRA_H__

#include <stdlib.h>

/* replaces each occurence of str1 with str2 in dest (UNSAFE) */
char *strrpl(char *dest, const char *str1, const char *str2);

/* replaces each occurence of str1 with str2 in dest 
   for a maximum of n bytes */
char *strnrpl(char *dest, const char *str1, const char *str2, size_t n);

/* returns a new dynamically allocated string with
   each occurence of str1 in dest replaced with str2 */
char *strrpl_d(const char *dest, const char *str1, const char *str2);

#endif