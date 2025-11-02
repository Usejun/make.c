#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct String {
    char* data;
    size_t len;
    size_t cap;
    size_t ver;
} String;

#include "view/string_view_mut.h"
#include "view/string_view.h"

bool str_is_null(const String* s);
bool str_is_empty(const String* s);

String str_new();
String str_from(const char* chars);
String str_nfrom(const char* chars, size_t n);
void str_free(String* s);

String str_clone(const String* s);
String str_format(const char* chars, ...);

void str_trim(String* s);
void str_trim_start(String* s);
void str_trim_end(String* s);

void str_push(String* s, char c);
void str_append(String* s, const char* chars);
void str_insert(String* s, char c, size_t index);
void str_concat(String* dest, const String* src);

bool str_push_safe(String* s, char c);
bool str_append_safe(String* s, const char* chars);
bool str_insert_safe(String* s, char c, size_t index);
bool str_concat_safe(String* dest, const String* src);

char str_at(const String* s, size_t index);
char str_set(String* s, size_t index, char c);
void str_swap(String* s, size_t i, size_t j);
String str_slice(const String* s, size_t from, size_t to);
StringView str_slicev(const String* s, size_t from, size_t to);
StringViewMut str_slicevm(String* s, size_t from, size_t to);

void str_replace(String* s, const char* from, const char* to);
bool str_replace_safe(String* s, const char* from, const char* to);

void str_rev(String* s);
void str_clear(String* s);       

int str_indexof(const String* s, const char* find);
int str_rindexof(const String* s, const char* find);
int str_count(const String* s, const char* find);
bool str_contains(const String* s, const char* find);
bool str_endswith(const String* s, const char* suffix);
bool str_startswith(const String* s, const char* prefix);

int str_comp(const String* s1, const String* s2);

String str_upper(const String* s);
String str_lower(const String *s);
void str_to_upper(String* s);
void str_to_lower(String *s);