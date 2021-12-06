#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "string_utils.h"

int info(char *info);
int error(char *error);
void panic(char *panic_msg);
long get_file_size(FILE *f);

int main(int argc, char **argv) {
    const char* file_name;
    FILE *input = NULL;
    if(argc == 1) {
        input = stdin;
        file_name = "stdin";
        info("Using stdin as input file");
    } else {
        file_name = argv[1];
        input = fopen(file_name, "r");
    }

    if(input == NULL) {
        panic("Error opening input file");
    }

    long size = get_file_size(input);
    char *program = malloc(size * sizeof(*program));

    fread(program, size, sizeof(*program), input);

    //printf("File %s with size %ld contains:\n%s", file_name, size, program);

    //Spliterator lines = spliterator_new(program, " ");

    // Well this already does a lot. This give all lines without comments, now parse!
    // The grammar of the language is very simple, for now we just have labels and instructions
    // So i just need to check if it contains a : if yes check that there is nothing, 
    // besides whitespace after the :
    // TODO For now an AST would be completely useless, we compile to bytecode and intermediate
    // AST is not needed at all. AST will only be needed as soon as we have Macros and only
    // for the macros and not at all for anything else.
    SPLITERATE("aaaaaa\n\n\n", "\n", line, { 
        /* Spliterator comment_split = spliterator_new(line, ";");
        line = spliterator_next(&comment_split);
        //printf("PTR: %p\n", line);
        if(line == NULL || *line == '\0') {
            continue;
        } */
        info(line);
    });
}

/// Write info message to stdout. Return number of written bytes.
int info(char *info) { 
    return printf("[INFO] %s\n", info);
}

int error(char *error) {
    return printf("[ERROR] %s\n", error);
}

void panic(char *panic_msg) {
    printf("The program has paniced:\n");
    error(panic_msg);
    exit(EXIT_FAILURE);
}

long get_file_size(FILE *f) {
    long pos = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, pos, SEEK_SET);

    return size; 
}
