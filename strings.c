#include "strings.h"


int my_strlen(const char *str){
	int len = 0;
	while(*str++){
		len++;
	}
	return len;
}
void my_itoa(int num, char *str){
	int i = 0;
	int is_negative = 0;
	if(num == 0){
		str[i++] = '0';
		str[i] = '\0';
		return;
}
if (num < 0){
	is_negative = 1;
	num = -num;
}
while(num != 0){
	int rem = num % 10;
	str[i++] = rem + '0';
	num = num / 10;
}
if(is_negative){
	str[i++] = '-';
}
	str[i] = '\0';
	int start = 0;
	int end = i -1;
	while(start < end){
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
}
}
int my_strcmp(const char *s1, const char *s2){
	while (*s1 && (*s1 == *s2)){
		s1++;
		s2++;
	}
	return (unsigned char)*s1 - (unsigned char)*s2;
}
int my_strncmp(const char *s1, const char *s2, size_t n){
	while (n > 0){
		if(*s1 != *s2){
			return (unsigned char)*s1 - (unsigned char)*s2;
		}
		if (*s1 == '\0'){
			return 0;
		}
		s1++;
		s2++;
		n--;
	}
	return 0;
}
void my_strcpy(char *dest, const char *src){
	while(*src){
		*dest++ = *src++;
	}
	*dest = '\0';
}
// Приєднує src до кінця dest та повертає dest.
char *my_strcat(char *dest, const char *src) {
    char *ptr = dest;
    // Знаходимо кінець рядка dest
    while (*ptr != '\0') {
        ptr++;
    }
    // Копіюємо src до кінця dest
    while (*src != '\0') {
        *ptr++ = *src++;
    }
    // Завершуємо рядок символом завершення '\0'
    *ptr = '\0';
    return dest;
}
// Повертає вказівник на останнє входження символу c у рядку s
char *my_strrchr(const char *s, int c) {
    const char *last = NULL;
    do {
        if (*s == (char)c) {
            last = s;
        }
    } while (*s++);
    return (char *)last;
}

