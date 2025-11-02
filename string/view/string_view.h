#pragma once
#include <stddef.h>

#ifdef DEBUG
#define SV_REQUIRE_VALID(sv) \
    do { \
        if (!sv_is_valid(sv)) { \
            fprintf(stderr, "Invalid StringView at %s:%d\n", __FILE__, __LINE__); \
            abort(); \
        } \
    } while (0)
#else
#define SV_REQUIRE_VALID(sv) ((void)0)
#endif

typedef struct String String; 
typedef struct {
    const char* data;
    size_t len;
    size_t ver;
    const String* parent;
} StringView;

bool sv_is_null(const StringView* sv);
bool sv_is_valid(const StringView* sv);

char sv_at(const StringView* sv, size_t index);

int sv_indexof(const StringView* sv, const char* substr);
int sv_rindexof(const StringView* sv, const char* substr);
bool sv_startswith(const StringView* sv, const char* prefix);
bool sv_endswith(const StringView* sv, const char* suffix);
int sv_comp(const StringView* a, const StringView* b); 

String sv_to_str(const StringView* sv);

String sv_upper(const StringView* sv);
String sv_lower(const StringView* sv);