#include <string.h>
#include <stdio.h>

#include "string_utils.h"

/// Both Strings have to contain at least len characters 
int substr_eq(const char *a, const char *b, unsigned long len) {
    for(unsigned long i = 0;i < len; i++) {
        if(a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

int string_empty(const char* s) {
    return *s == '\0';
}

Spliterator spliterator_new(char *content, const char *delim) {
    Spliterator self = {
        .content = content,
        .delim = delim,
    };

    return self;
}

char *next_token(char* content, const char * delim, char **next_out) {
    //TODO use the libc version of strtok_r if it is defined
    //This is just a very naive version
    if(*content == '\0') {
        return NULL;
    }

    char *end = content;
    unsigned long delim_len = strlen(delim);

    while(1) {
        if(*end == '\0') {
            *next_out = end;
            return content;
        }

        if(substr_eq(end, delim, delim_len)) {
            break;
        }

        end += 1;
    }

    for (unsigned long i = 0; i < delim_len; i++) {
        *end = '\0';
        end += 1;
    }

    *next_out = end;

    return content;
}

char *spliterator_next(Spliterator *self) {
    //return strtok_r(self->content, self->delim, &self->content);
    return next_token(self->content, self->delim, &self->content);
}
