#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../src/string_utils.h"

// The test structure is really simple a test should not output anything to stdout.
// Use freopen if output should be tested. All tests should be void functions and print to
// stderr on error as well as return a non zero return code. The problem is that the first failing
// test halts the complete test run, maybe the output will be improved but it is sufficient for now 

void test_substr_eq(void);
void test_spliterator_0(void);
void test_spliterator_1(void);
void test_spliterator_2(void);
void test_spliterator_3(void);
void test_foreach_split(void);
void test_spliterate(void);

int main(int argc, char **argv) {
    test_substr_eq();
    test_spliterator_0();
    test_spliterator_1();
    test_spliterator_2();
    test_spliterator_3();
    test_foreach_split();
}

void test_substr_eq(void) {
    assert(substr_eq("hello", "hello", strlen("hello")));
    assert(substr_eq("hello123", "hello456", strlen("hello")));
    assert(!substr_eq("hello", "wello", strlen("hello")));
}

void test_spliterator_0(void) {
    char text[] = "ahellob";
    Spliterator sp = spliterator_new(text, "hello");
    assert(substr_eq("a", spliterator_next(&sp), 1));
    assert(substr_eq("b", spliterator_next(&sp), 1));
}

void test_spliterator_1(void) {
    char text[] = "hello,world,42";
    Spliterator sp = spliterator_new(text, ",");
    assert(substr_eq("hello", spliterator_next(&sp), strlen("hello")));
    assert(substr_eq("world", spliterator_next(&sp), strlen("world")));
    assert(substr_eq("42", spliterator_next(&sp), strlen("42")));
}

void test_spliterator_2(void) {
    char text[] = "hello, world, 42";
    Spliterator sp = spliterator_new(text, ", ");
    assert(substr_eq("hello", spliterator_next(&sp), strlen("hello")));
    assert(substr_eq("world", spliterator_next(&sp), strlen("world")));
    assert(substr_eq("42", spliterator_next(&sp), strlen("42")));
}

void test_spliterator_3(void) {
    char text[] = "hello,world,,,42";
    Spliterator sp = spliterator_new(text, ",");
    assert(substr_eq("hello", spliterator_next(&sp), strlen("hello")));
    assert(substr_eq("world", spliterator_next(&sp), strlen("world")));
    assert(substr_eq("", spliterator_next(&sp), strlen("")));
    assert(substr_eq("", spliterator_next(&sp), strlen("")));
    assert(substr_eq("42", spliterator_next(&sp), strlen("42")));
}

void test_foreach_split(void) {
    char text[] = "hello,world,42";
    char *splits[] = {"hello", "world", "42"};

    int i = 0;
    Spliterator sp = spliterator_new(text, ",");
    FOREACH_SPLIT(sp, split, {
        if(!substr_eq(split, splits[i], strlen(splits[i]))) {
            fprintf(
                stderr, 
                "test_foreach_split: Assertion failed: for split i=%d, %s != %s in range %ld\n",
                i,
                split,
                splits[i], 
                strlen(splits[i])
            );
            exit(EXIT_FAILURE);
        }
        i += 1;
    });
}

void test_spliterate(void) {
    char text[] = "hello,world,42";
    char *splits[] = {"hello", "world", "42"};

    int i = 0;
    SPLITERATE(text, ",", split, {
        if(!substr_eq(split, splits[i], strlen(splits[i]))) {
            fprintf(
                stderr, 
                "test_foreach_split: Assertion failed: for split i=%d, %s != %s in range %ld\n",
                i,
                split,
                splits[i], 
                strlen(splits[i])
            );
            exit(EXIT_FAILURE);
        }
        i += 1;
    });
}
