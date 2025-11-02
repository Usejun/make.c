#include "util.h"
#include <string.h>
#include <stdlib.h>

bool is_whitespace(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

char to_upper(char c) {
    if (c >= 'a' && c <= 'z') return c - ('a' - 'A');
    return c;
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    return c;
}

int stridxof(const char* s1, const char* s2) {
    if (!s1 || !s2) return -1;
    if (*s2 == '\0') return 0;  

    const char* pos = strstr(s1, s2);
    if (!pos) return -1;

    return (int)(pos - s1);
}

int strridxof(const char* s1, const char* s2) {
    if (!s1 || !s2) return -1;
    if (*s2 == '\0') return 0;  

    size_t len1 = strlen(s1), len2 = strlen(s2);
    if (len1 < len2) return -1;

    for (size_t i = len1 - len2 + 1; i-- > 0;) {
        if (strncmp(s1 + i, s2, len2) == 0)
            return (int)i;
    }

    return -1;
}

int strcount(const char* s1, const char* s2) {
    if (!s1 || !s2 || *s2 == '\0') return 0;

    const char* pos = s1;
    int count = 0;
    size_t find_len = strlen(s2);

    while ((pos = strstr(pos, s2)) != NULL) {
        count++;
        pos += find_len; 
    }

    return count;
}

bool strstarts(const char* s1, const char* s2) {
    if (!s1 || !s2) return 0;
    
    size_t len1 = strlen(s1), len2 = strlen(s2);
    
    if (len1 < len2) return false;
    
    return strncmp(s1, s2, len2) == 0;
}

bool strends(const char* s1, const char* s2){
    if (!s1 || !s2) return 0;

    size_t len1 = strlen(s1), len2 = strlen(s2);

    if (len1 < len2) return false;

    return strcmp(s1 + (len1 - len2), s2) == 0;
}

#include <string.h>
#include <stddef.h>

int strnidxof(const char* s1, const char* s2, size_t n) {
    if (!s1 || !s2) return -1;
    if (*s2 == '\0') return 0;  
    size_t len1 = strlen(s1), len2 = strlen(s2);

    if (len2 > n || len2 > len1) return -1;

    size_t limit = len1 < n ? len1 : n;  

    for (size_t i = 0; i + len2 <= limit; i++) {
        if (strncmp(s1 + i, s2, len2) == 0)
            return (int)i;
    }

    return -1; 
}

int strnridxof(const char* s1, const char* s2, size_t n) {
    if (!s1 || !s2) return -1;
    if (*s2 == '\0') return 0;

    size_t len2 = strlen(s2);
    if (n < len2) return -1;

    for (size_t i = n - len2 + 1; i-- > 0;) {
        if (strncmp(s1 + i, s2, len2) == 0)
            return (int)i;
    }

    return -1;
}

int strncount(const char* s1, const char* s2, size_t n) {
    if (!s1 || !s2 || *s2 == '\0') return 0;

    int count = 0;
    size_t len2 = strlen(s2);

    for (size_t i = 0; i + len2 <= n; ) {
        if (strncmp(s1 + i, s2, len2) == 0) {
            count++;
            i += len2;
        } else {
            i++;
        }
    }
    return count;
}

bool strnstarts(const char* s1, const char* s2, size_t n) {
    if (!s1 || !s2) return false;

    size_t len1 = strlen(s1), len2 = strlen(s2);
    size_t limit = (len1 < n) ? len1 : n;

    if (limit < len2) return false;

    return strncmp(s1, s2, len2) == 0;
}

bool strnends(const char* s1, const char* s2, size_t n) {
    if (!s1 || !s2) return false;

    size_t len1 = strlen(s1), len2 = strlen(s2);
    size_t limit = (len1 < n) ? len1 : n;

    if (limit < len2) return false;

    return strncmp(s1 + (limit - len2), s2, len2) == 0;
}

char* strupper(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char* result = malloc(len + 1);
    if (!result) return NULL;
    for (size_t i = 0; i < len; i++) {
        result[i] = to_upper(s[i]);
    }
    result[len] = '\0';
    return result;
}

char* strlower(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char* result = malloc(len + 1);
    if (!result) return NULL;
    for (size_t i = 0; i < len; i++) {
        result[i] = to_lower(s[i]);
    }
    result[len] = '\0';
    return result;
}

void strtoupper(char* s) {
    if (!s) return;
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++) {
        s[i] = to_upper(s[i]);
    }
}

void strtolower(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++) {
        s[i] = to_lower(s[i]);
    }
}

char* strnupper(const char* s, size_t n) {
    if (!s) return NULL;
    char* result = malloc(n + 1);
    if (!result) return NULL;
    for (size_t i = 0; i < n; i++) {
        result[i] = to_upper(s[i]);
    }
    result[n] = '\0';
    return result;
}

char* strnlower(const char* s, size_t n) {
    if (!s) return NULL;
    char* result = malloc(n + 1);
    if (!result) return NULL;
    for (size_t i = 0; i < n; i++) {
        result[i] = to_lower(s[i]);
    }
    result[n] = '\0';
    return result;
}

void strtonupper(char* s, size_t n) {
    if (!s) return;
    for (size_t i = 0; i < n; i++) {
        s[i] = to_upper(s[i]);
    }
}

void strtonlower(char *s, size_t n) {
    if (!s) return;
    for (size_t i = 0; i < n; i++) {
        s[i] = to_lower(s[i]);
    }
}
