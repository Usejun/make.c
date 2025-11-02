#pragma once
#include <stddef.h>

#ifdef DEBUG
#define SVM_REQUIRE_VALID(svm) \
    do { \
        if (!svm_is_valid(svm)) { \
            fprintf(stderr, "Invalid StringViewMut at %s:%d\n", __FILE__, __LINE__); \
            abort(); \
        } \
    } while (0)
#else
#define SVM_REQUIRE_VALID(svm) ((void)0)
#endif

typedef struct String String; 
typedef struct {
    char* data;
    size_t len;
    size_t ver;
    String* parent;
} StringViewMut;

bool svm_is_null(const StringViewMut* svm);
bool svm_is_valid(const StringViewMut* svm);

char svm_at(const StringViewMut* svm, size_t index);
char svm_set(StringViewMut* svm, size_t index, char c);
void svm_fill(StringViewMut* svm, char c);

int svm_indexof(const StringViewMut* svm, const char* s);
int svm_rindexof(const StringViewMut* svm, const char* s);
bool svm_startswith(const StringViewMut* svm, const char* prefix);
bool svm_endswith(const StringViewMut* svm, const char* suffix);
int svm_comp(const StringViewMut* a, const StringViewMut* b); 

String svm_upper(const StringViewMut* svm);
String svm_lower(const StringViewMut* svm); 
void svm_to_upper(StringViewMut* svm);
void svm_to_lower(StringViewMut* svm);

String svm_to_str(const StringViewMut* svm);