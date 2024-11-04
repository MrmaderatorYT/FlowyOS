#ifndef STRINGS_H
#define STRINGS_H

#include <stddef.h>

int my_strlen(const char *str);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, size_t n);
void my_strcpy(char *dest, const char *src);
void my_itoa(int num, char *str);

#endif