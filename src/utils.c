#include "../include/main.h"

char *chem_strdup(const char *src) {
    if (!src) {
        char *empty = (char *)malloc(1);
        if (!empty) {
            fprintf(stderr, "Out of memory in chem_strdup\n");
            exit(EXIT_FAILURE);
        }
        empty[0] = '\0';
        return empty;
    }

    size_t len = strlen(src);
    char *copy = (char *)malloc(len + 1);
    if (!copy) {
        fprintf(stderr, "Out of memory in chem_strdup\n");
        exit(EXIT_FAILURE);
    }
    memcpy(copy, src, len + 1);
    return copy;
}

char *chem_concat2(const char *a, const char *b) {
    size_t la = a ? strlen(a) : 0;
    size_t lb = b ? strlen(b) : 0;
    char *buf = (char *)malloc(la + lb + 1);
    if (!buf) {
        fprintf(stderr, "Out of memory in chem_concat2\n");
        exit(EXIT_FAILURE);
    }
    buf[0] = '\0';
    if (a) strcat(buf, a);
    if (b) strcat(buf, b);
    return buf;
}

char *chem_concat3(const char *a, const char *b, const char *c) {
    size_t la = a ? strlen(a) : 0;
    size_t lb = b ? strlen(b) : 0;
    size_t lc = c ? strlen(c) : 0;

    char *buf = (char *)malloc(la + lb + lc + 1);
    if (!buf) {
        fprintf(stderr, "Out of memory in chem_concat3\n");
        exit(EXIT_FAILURE);
    }

    buf[0] = '\0';
    if (a) strcat(buf, a);
    if (b) strcat(buf, b);
    if (c) strcat(buf, c);
    return buf;
}

char *chem_trim_quotes(const char *src) {
    if (!src) {
        return chem_strdup("");
    }

    size_t len = strlen(src);
    if (len >= 2 && src[0] == '"' && src[len - 1] == '"') {
        char *buf = (char *)malloc(len - 1);
        if (!buf) {
            fprintf(stderr, "Out of memory in chem_trim_quotes\n");
            exit(EXIT_FAILURE);
        }
        memcpy(buf, src + 1, len - 2);
        buf[len - 2] = '\0';
        return buf;
    }
    return chem_strdup(src);
}
