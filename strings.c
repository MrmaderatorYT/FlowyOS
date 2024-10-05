#include "strings.h"


int my_strlen(const char *str){
	int len = 0;
	while(*str++){
		len++;
	}
	return len;
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

