#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../string.h"
#include "string_view.h"
#include "util.h"


bool sv_is_null(const StringView* sv) { 
    return !sv || str_is_null(sv->parent); 
}

bool sv_is_valid(const StringView* sv) {
    if (sv_is_null(sv)) return false;
    return sv->ver == sv->parent->ver;
}

char sv_at(const StringView* sv, size_t index) {
    SV_REQUIRE_VALID(sv);
    if (!sv_is_valid(sv)) return '\0';
    if (index >= sv->len) return '\0';
    return sv->data[index];
}

int sv_indexof(const StringView* sv, const char* substr) {
    SV_REQUIRE_VALID(sv);
    if (!sv_is_valid(sv)) return -1;
    return strnidxof(sv->data, substr, sv->len);
}

int sv_rindexof(const StringView* sv, const char* substr) {
    SV_REQUIRE_VALID(sv);
    if (!sv_is_valid(sv)) return -1;
    return strnridxof(sv->data, substr, sv->len);
}

bool sv_startswith(const StringView* sv, const char* prefix) {
    SV_REQUIRE_VALID(sv);
    if (!sv_is_valid(sv)) return false;
    return strnstarts(sv->data, prefix, sv->len);
}

bool sv_endswith(const StringView* sv, const char* suffix) {
    SV_REQUIRE_VALID(sv);
    if (!sv_is_valid(sv)) return false;
    return strnends(sv->data, suffix, sv->len);
}

int sv_comp(const StringView* a, const StringView* b) {
    SV_REQUIRE_VALID(a);
    SV_REQUIRE_VALID(b);
    if (!sv_is_valid(a) || !sv_is_valid(b))
        return (int)(sv_is_valid(a) - sv_is_valid(b));

    size_t min_len = a->len < b->len ? a->len : b->len;
    int cmp = strncmp(a->data, b->data, min_len);
    return cmp ? cmp : (int)(a->len - b->len);
}

String sv_to_str(const StringView* sv) {
    SV_REQUIRE_VALID(sv);
    if (!sv_is_valid(sv)) return str_new();
    return str_nfrom(sv->data, sv->len);
}

String sv_upper(const StringView* sv) {
    if (sv_is_valid(sv)) return str_new();
    String result = sv_to_str(sv);
    str_to_upper(&result);
    return result;
}
String sv_lower(const StringView* sv) {
    if (svm_is_valid(sv)) return str_new();
    String result = sv_to_str(sv);
    str_to_lower(&result);
    return result;
}