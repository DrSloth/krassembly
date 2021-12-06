#ifndef STRING_UTILS_H
#define STRING_UTILS_H

char *next_token(char* content, const char * delim, char **next_out);
int substr_eq(const char *a, const char *b, unsigned long len);
int string_empty(const char* s);

typedef struct Spliterator {
    char *content;
    const char *delim;
} Spliterator;

Spliterator spliterator_new(char *content, const char *delimiter);
char *spliterator_next(Spliterator *self);
#endif //STRING_UTILS_H

#define FOREACH_SPLIT(SPLITERATOR, VAR, BLOCK) while(1) { \
    char *VAR = spliterator_next(&SPLITERATOR); \
    if(VAR == NULL) break; \
    BLOCK \
}

#define SPLITERATE(TEXT, DELIM, VAR, BLOCK) do { \
    Spliterator __spliterator__sp__tmp_ = spliterator_new(TEXT, DELIM); \
    FOREACH_SPLIT(__spliterator__sp__tmp_, VAR, BLOCK) \
} while(0);
