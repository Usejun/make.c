#pragma once
#include <stddef.h>
#include <stdbool.h>

bool is_whitespace(char c);
char to_upper(char c);
char to_lower(char c);

int stridxof(const char* s1, const char* s2);
int strridxof(const char* s1, const char* s2);
int strcount(const char* s1, const char* s2);

int strnidxof(const char* s1, const char* s2, size_t n);
int strnridxof(const char* s1, const char* s2, size_t n);
int strncount(const char* s1, const char* s2, size_t n);

bool strstarts(const char* s1, const char* s2);
bool strends(const char* s1, const char* s2);

bool strnstarts(const char* s1, const char* s2, size_t n);
bool strnends(const char* s1, const char* s2, size_t n);

char* strupper(const char* s);
char* strlower(const char* s);
void strtoupper(char* s);
void strtolower(char *s);

char* strnupper(const char* s, size_t n);
char* strnlower(const char* s, size_t n);
void strtonupper(char* s, size_t n);
void strtonlower(char *s, size_t n);

