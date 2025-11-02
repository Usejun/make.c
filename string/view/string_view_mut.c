#include "../string.h"
#include "string_view_mut.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

bool svm_is_null(const StringViewMut* svm) { 
    return !svm || str_is_null(svm->parent); 
}

bool svm_is_valid(const StringViewMut* svm) {
    if (svm_is_null(svm)) return false;
    return svm->ver == svm->parent->ver;
}

char svm_at(const StringViewMut* svm, size_t index) {
    SVM_REQUIRE_VALID(svm);
    if (!svm_is_valid(svm)) return '\0';
    if (index >= svm->len) return '\0';
    return svm->data[index];
}

char svm_set(StringViewMut* svm, size_t index, char c) {
    SVM_REQUIRE_VALID(svm);
    if (!svm_is_valid(svm)) return '\0';
    if (index >= svm->len) return '\0';
    return str_set(svm->parent, index, c);
}

void svm_fill(StringViewMut* svm, char c) {
    SVM_REQUIRE_VALID(svm);
    if (!svm_is_valid(svm)) return;
    
    for (size_t i = 0; i < svm->len; i++) {
        svm->data[i] = c;
    }
}

int svm_indexof(const StringViewMut* svm, const char* s) {
    SVM_REQUIRE_VALID(svm);
    if (!svm_is_valid(svm)) return -1;
    return strnidxof(svm->data, s, svm->len);
}

int svm_rindexof(const StringViewMut* svm, const char* s) {
    SVM_REQUIRE_VALID(svm);
    if (!svm_is_valid(svm)) return -1;
    return strnridxof(svm->data, s, svm->len);
}

bool svm_startswith(const StringViewMut* svm, const char* prefix) {
    SVM_REQUIRE_VALID(svm);
    if (!svm_is_valid(svm)) return false;
    return strstarts(svm->data, prefix);
}

bool svm_endswith(const StringViewMut* svm, const char* suffix) {
    SVM_REQUIRE_VALID(svm);
    if (!svm_is_valid(svm)) return false;
    return strnends(svm->data, suffix, svm->len);
}

int svm_comp(const StringViewMut* a, const StringViewMut* b) {
    SVM_REQUIRE_VALID(a);
    SVM_REQUIRE_VALID(b);
    if (!svm_is_valid(a) || !svm_is_valid(b))
        return (int)(svm_is_valid(a) - svm_is_valid(b));

    size_t min_len = a->len < b->len ? a->len : b->len;
    int cmp = strncmp(a->data, b->data, min_len);
    return cmp ? cmp : (int)(a->len - b->len);
}

String svm_upper(const StringViewMut* svm) {
    if (!svm_is_valid(svm)) return str_new();
    String result = svm_to_str(svm);
    str_to_upper(&result);
    return result;
}
String svm_lower(const StringViewMut* svm) {
    if (!svm_is_valid(svm)) return str_new();
    String result = svm_to_str(svm);
    str_to_lower(&result);
    return result;
}
void svm_to_upper(StringViewMut* svm) {
    if (!svm_is_valid(svm)) return;
    strnupper(svm->data, svm->len);
}
void svm_to_lower(StringViewMut* svm){
    if (!svm_is_valid(svm)) return;
    strnlower(svm->data, svm->len);
}

String svm_to_str(const StringViewMut* svm) {
    SVM_REQUIRE_VALID(svm);
    if (!svm_is_valid(svm)) return str_new();
    return str_nfrom(svm->data, svm->len);
}
