#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "string.h"
#include "util.h"

#define STRINGGROW 2

bool str_is_null(const String* s) { 
    return !s || !s->data; 
}

bool str_is_empty(const String* s) { 
    return str_is_null(s) || s->len == 0; 
}

static bool str_resize(String* s, size_t new_cap) {
    if (s->cap >= new_cap) return true;
    void* new_data = realloc(s->data, new_cap);
    if (!new_data) return false;
    s->data = new_data;
    s->cap = new_cap;
    return true;
}

String str_new() {
    String s;
    s.len = 0;
    s.cap = 1;
    s.data = malloc(s.cap);
    if (!s.data) {  
        s.cap = 0;
        s.len = 0;
        return s;
    }
    s.data[0] = '\0';
    return s;
}

String str_from(const char* chars) {
    String s = {0};
    if (!chars) return s;
    s.len = strlen(chars);
    s.cap = s.len + 1;
    s.data = malloc(s.cap);
    if (!s.data) {
        s.len = 0;
        s.cap = 0;
        return s;
    }
    memcpy(s.data, chars, s.len);
    s.data[s.len] = '\0';
    return s;
}

String str_nfrom(const char* chars, size_t n) {
    String s;
    s.len = n;
    s.cap = s.len + 1;
    s.data = malloc(s.cap);
    if (!s.data) {
        s.len = 0;
        s.cap = 0;
        return s;
    }
    memcpy(s.data, chars, n);
    s.data[n] = '\0';
    return s;
}

void str_free(String* s) {
    if (str_is_empty(s)) return;
    free(s->data);
    s->data = NULL;
    s->len = s->cap = 0;
}

String str_clone(const String* s) {
    String new;
    new.cap = s->len + 1;
    new.len = s->len;
    new.data = malloc(new.cap);
    if (!new.data) {
        new.len = 0;
        new.cap = 0;
        return new;
    }
    memcpy(new.data, s->data, new.cap);
    return new;
}

String str_format(const char* chars, ...) {
    char buf[1024];
    va_list args;
    va_start(args, chars);
    vsnprintf(buf, sizeof(buf), chars, args);
    va_end(args);
    return str_from(buf);
}

void str_trim(String* s) {
    if (str_is_null(s)) return;
    str_trim_start(s);
    str_trim_end(s);
}

void str_trim_start(String* s) {
    if (str_is_null(s)) return;
    size_t start = 0, new_len;
    while (start < s->len && is_whitespace(s->data[start])) {
        start++;
    }
    
    if (start > 0) {
        size_t new_len = s->len - start;
        memmove(s->data, s->data + start, new_len);
        s->data[new_len] = '\0';
        s->len = new_len;
    }
}

void str_trim_end(String* s) {
    if (str_is_null(s)) return;
    size_t end = s->len;
    while (end > 0 && is_whitespace(s->data[end - 1])) {
        end--;
    }

    s->data[end] = '\0';
    s->len = end;
}

void str_push(String* s, char c) {
    if (str_is_null(s)) return;
    if (!s->data) {
        s->cap = 16;
        s->len = 0;
        s->data = malloc(16);
        if (!s->data) return;
        s->data[0] = '\0';
    }

    if (s->len + 2 > s->cap && 
        !str_resize(s, s->cap * STRINGGROW + 2)) 
        return;

    s->data[s->len++] = c;
    s->data[s->len] = '\0';
    s->ver++;
}

void str_append(String* s, const char* chars) {
    if (!s) return;
    size_t len = strlen(chars);
    if (!s->data) {
        s->cap = len + 1;
        s->len = len;
        s->data = malloc(s->cap);
        if (!s->data) return;
        memcpy(s->data, chars, len);
        s->data[s->len] = '\0';
    }
    else {
        if (s->len + len + 1 > s->cap && 
            !str_resize(s, s->cap * STRINGGROW + len + 1)) 
            return;

        memcpy(s->data + s->len, chars, len);
        s->len += len;
        s->data[s->len] = '\0';
    }
    s->ver++;
}

void str_concat(String* dest, const String* src) {
    if (str_is_null(dest) || str_is_null(src)) return;
    if (src->len == 0) return;

    if (dest->len + src->len + 1 > dest->cap && 
        !str_resize(dest, dest->cap * STRINGGROW + src->len)) 
        return;
    
    memcpy(dest->data + dest->len, src->data, src->len);
    dest->len += src->len;
    dest->data[dest->len] = '\0';
    dest->ver++;
}

void str_insert(String* s, char c, size_t index) {
    if (str_is_null(s)) return;
    if (s->len < index) return;

    if (s->len + 2 > s->cap && !str_resize(s, s->cap * STRINGGROW + 2)) 
        return;

    memmove(s->data + index + 1, s->data + index, s->len - index + 1);
    s->data[index] = c;
    s->len++;
    s->ver++;
}

bool str_push_safe(String* s, char c) {
    if (str_is_null(s)) return false;
    
    String tmp = str_clone(s);
    if (!tmp.data) return false;

    str_push(&tmp, c); 
    if (str_is_null(&tmp)) 
        return false;

    str_free(s);
    *s = tmp;
    return true;
}

bool str_append_safe(String* s, const char* chars) {
    if (str_is_null(s) || !chars) return false;
    
    String tmp = str_clone(s);
    if (!tmp.data) return false;

    str_append(&tmp, chars); 
    if (str_is_null(&tmp)) 
        return false;

    str_free(s);
    *s = tmp;
    return true;
}

bool str_insert_safe(String* s, char c, size_t index) {
    if (str_is_null(s) || index > s->len) return false;

    String tmp = str_clone(s);
    if (!tmp.data) return false;

    str_insert(&tmp, c, index);
    if (!tmp.data) return false;

    str_free(s);
    *s = tmp;
    return true;
}

bool str_concat_safe(String* dest, const String* src) {
    if (str_is_null(dest) || str_is_null(src)) return false;

    String tmp = str_clone(dest);
    if (!tmp.data) return false;

    str_concat(&tmp, src);
    if (!tmp.data) return false;

    str_free(dest);
    *dest = tmp;
    return true;
}

char str_at(const String* s, size_t index) {
    if (str_is_null(s) || s->len <= index) return '\0';
    return s->data[index];
}

char str_set(String* s, size_t index, char c) {
    if (str_is_null(s) || s->len <= index) return '\0';
    return s->data[index] = c;
}

void str_swap(String* s, size_t i, size_t j) {
    if (str_is_null(s) || s->len <= i || s->len <= j) return;

    char tmp = s->data[i];
    s->data[i] = s->data[j];
    s->data[j] = tmp; 
}

String str_slice(const String* s, size_t from, size_t to) {
    String new = str_new();
    if (str_is_null(s) || from > to || from >= s->len) return new;

    if (to > s->len) to = s->len;

    new.len = to - from;
    new.cap = new.len + 1;
    new.data = malloc(new.cap);
    if (!new.data) return new;

    memcpy(new.data, s->data + from, new.len);
    new.data[new.len] = '\0';

    return new;
}

StringView str_slicev(const String* s, size_t from, size_t to) {
    StringView new = {0};
    if (str_is_null(s) || from > to || from >= s->len) return new;
    if (to > s->len) to = s->len;

    new.len = to - from;
    new.data = s->data + from;
    new.ver = s->ver;
    new.parent = s;

    return new;
}

StringViewMut str_slicevm(String* s, size_t from, size_t to) {
    StringViewMut new = {0};
    if (str_is_null(s) || from > to || from >= s->len) return new;
    if (to > s->len) to = s->len;

    new.len = to - from;
    new.data = s->data + from;
    new.ver = s->ver;
    new.parent = s;

    return new;
}

void str_replace(String* s, const char* from, const char* to) {
    if (str_is_null(s) || !from || !to) return;
    if (*from == '\0') return;
    if (strcmp(from, to) == 0) return;
    
    char* pos = s->data;
    size_t from_len = strlen(from), to_len = strlen(to);

    while ((pos = strstr(pos, from))) {
        size_t offset = pos - s->data;
        size_t tail_len = s->len - (pos - s->data) - from_len;

        if (to_len > from_len && s->len + (to_len - from_len) + 1 > s->cap) {
            size_t new_cap = s->cap * STRINGGROW;
            if (new_cap < s->len + (to_len - from_len) + 1)
                new_cap = s->len + (to_len - from_len) + 1;

            if (!str_resize(s, new_cap)) 
                return;

            pos = s->data + offset; 
        }

        memmove(s->data + offset + to_len, s->data + offset + from_len, tail_len + 1);
        memcpy(s->data + offset, to, to_len);

        s->len += (to_len - from_len);
        pos = s->data + offset + to_len;
    }
}

bool str_replace_safe(String* s, const char* from, const char* to) {
    if (str_is_null(s) || !from || !to || *from == '\0') return false;

    String tmp = str_clone(s);
    if (!tmp.data) return false;

    str_replace(&tmp, from, to); 
    if (!tmp.data) return false;

    str_free(s);
    *s = tmp;
    return true;
}

void str_rev(String* s) {
    for (size_t i = 0; i < s->len / 2; i++)
        str_swap(s, i, s->len-i-1);
}

void str_clear(String* s) {
    if (str_is_null(s)) return;

    s->len = 0;
    s->data[0] = '\0';
} 

int str_indexof(const String* s, const char* find) {
    return stridxof(s->data, find);
}

int str_rindexof(const String* s, const char* find) {
    return strridxof(s->data, find);
}

int str_count(const String* s, const char* find) {
    return strcount(s->data, find);
}

bool str_contains(const String* s, const char* find) {
    return stridxof(s->data, find) != -1;
}

bool str_endswith(const String* s, const char* suffix) {
    return strends(s->data, suffix);
}

bool str_startswith(const String* s, const char* prefix) {
    return strstarts(s->data, prefix);
}

int str_comp(const String* s1, const String* s2) {
    if (!s1 && !s2) return 0;
    if (!s1) return -1;
    if (!s2) return 1;
    if (!s1->data && !s2->data) return 0;
    if (!s1->data) return -1;
    if (!s2->data) return 1;

    return strcmp(s1->data, s2->data);
}

String str_upper(const String* s) {
    String result = str_clone(s);
    str_to_upper(&result);
    return result;
}

String str_lower(const String *s) {
    String result = str_clone(s);
    str_to_lower(&result);
    return result;
}

void str_to_upper(String* s) {
    if (str_is_null(s)) return;

    for (size_t i = 0; i < s->len; i++) {
        s->data[i] = to_upper(s->data[i]);
    }
}

void str_to_lower(String *s){
    if (str_is_null(s)) return;

    for (size_t i = 0; i < s->len; i++) {
        s->data[i] = to_lower(s->data[i]);
    }
}