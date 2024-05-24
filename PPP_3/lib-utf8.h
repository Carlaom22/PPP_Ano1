//
// Created by tqsco on 13/06/2021.
//

#ifndef PPP_LIB_UTF8_H
#define PPP_LIB_UTF8_H

#include <stdio.h>

void strtobase_u8(char *dest, const char *orig);


void maiusculas_u8(char *dest, const char *orig);


void minusculas_u8(char *dest, const char *orig);


size_t strlen_u8(const char *s);

char *fgets_u8(char *s, int count, FILE *stream);


char *fgets_c_u8(char *s, int count, FILE *stream);

#endif //PPP_LIB_UTF8_H
