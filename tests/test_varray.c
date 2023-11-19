#include "../src/varray.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool compareFloats(const float a, const float b);
int test_va_new(void);
int test_va_push(void);
int test_va_pop(void);
int test_va_free(void);
int test_va_grow(void);

#define ASSERT(condition)                                                  \
    do {                                                                   \
        if (!(condition)) {                                                \
            printf("Assertion failed: %s, line %d\n", __FILE__, __LINE__); \
            return 1;                                                      \
        }                                                                  \
    } while (0)

int test_va_new(void)
{
    varray_t *actual = va_new(1, sizeof(int));
    ASSERT(actual != NULL);
    ASSERT(actual->cap == 1);
    ASSERT(actual->len == 0);
    free(actual->data);
    free(actual);

    actual = va_new(0, sizeof(int));
    ASSERT(actual == NULL);

    actual = va_new(10, sizeof(int));
    ASSERT(actual != NULL);
    ASSERT(actual->cap == 10);
    ASSERT(actual->len == 0);
    free(actual->data);
    free(actual);

    return 0;
}

int test_va_push(void)
{
    int i1 = 1, i2 = 2, i3 = 3;

    varray_t *actual = va_new(5, sizeof(int));
    va_push(actual, &i1);
    ASSERT(actual->len == 1);
    int a1 = *((int *)actual->data);
    ASSERT(a1 == 1);
    free(actual->data);
    free(actual);

    actual = va_new(5, sizeof(int));
    va_push(actual, &i1);
    va_push(actual, &i2);
    va_push(actual, &i3);
    ASSERT(actual->len == 3);
    a1 = *((int *)actual->data);
    ASSERT(a1 == 1);
    int a2 = *((int *)actual->data + 1);
    ASSERT(a2 == 2);
    int a3 = *((int *)actual->data + 2);
    ASSERT(a3 == 3);
    free(actual->data);
    free(actual);

    char c1 = 'a', c2 = 'b', c3 = 'c', c4 = 'd';

    actual = va_new(3, sizeof(char));
    va_push(actual, &c1);
    va_push(actual, &c2);
    va_push(actual, &c3);
    va_push(actual, &c4);
    ASSERT(actual->len == 4);
    ASSERT(actual->cap == 6);
    char a4 = *((char *)actual->data);
    ASSERT(a4 == 'a');
    char a5 = *((char *)actual->data + 1);
    ASSERT(a5 == 'b');
    char a6 = *((char *)actual->data + 2);
    ASSERT(a6 == 'c');
    char a7 = *((char *)actual->data + 3);
    ASSERT(a7 == 'd');
    free(actual->data);
    free(actual);

    float f1 = 32.99991, f2 = 1.1, f3 = 55.2209;

    actual = va_new(3, sizeof(float));
    va_push(actual, &f1);
    va_push(actual, &f2);
    va_push(actual, &f3);
    ASSERT(actual->len == 3);
    float a8 = *((float *)actual->data);
    ASSERT(compareFloats(a8, 32.99991));
    float a9 = *((float *)actual->data + 1);
    ASSERT(compareFloats(a9, 1.1));
    float a10 = *((float *)actual->data + 2);
    ASSERT(compareFloats(a10, 55.2209));
    free(actual->data);
    free(actual);

    return 0;
}

int test_va_pop(void)
{
    int i1 = 1, i2 = 2, i3 = 3;

    varray_t *actual = va_new(3, sizeof(int));
    va_push(actual, &i1);
    va_push(actual, &i2);
    va_push(actual, &i3);
    int actual_pop = *(int *)va_pop(actual);
    ASSERT(actual->len == 2);
    ASSERT(actual_pop == 3);
    free(actual->data);
    free(actual);

    return 0;
}

int test_va_free(void)
{
    int i1 = 1, i2 = 2, i3 = 3;

    varray_t *actual = va_new(3, sizeof(int));
    va_push(actual, &i1);
    va_push(actual, &i2);
    va_push(actual, &i3);
    ASSERT(actual->len == 3);
    va_free(&actual);
    ASSERT(actual == NULL);

    return 0;
}

int test_va_grow(void)
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;

    varray_t *actual = va_new(3, sizeof(int));
    va_push(actual, &i1);
    va_push(actual, &i2);
    va_push(actual, &i3);
    ASSERT(actual->len == 3);
    va_grow(actual, 5);
    ASSERT(actual->cap == 5);
    va_push(actual, &i4);
    va_push(actual, &i5);
    int a1 = *(int *)va_pop(actual);
    ASSERT(a1 == 5);
    int a2 = *(int *)va_pop(actual);
    ASSERT(a2 == 4);
    int a3 = *(int *)va_pop(actual);
    ASSERT(a3 == 3);
    int a4 = *(int *)va_pop(actual);
    ASSERT(a4 == 2);
    ASSERT(actual->len == 1);
    va_free(&actual);

    return 0;
}

int main(void)
{
    int failed_tests = 0;

    printf("Running tests for 'va_new' function...\n");
    if (test_va_new() != 0) {
        printf("❌ Some tests for 'va_new' function failed.\n");
        failed_tests++;
    } else {
        printf("✅ All tests for 'va_new' function passed.\n");
    }

    printf("Running tests for 'va_push' function...\n");
    if (test_va_push() != 0) {
        printf("❌ Some tests for 'va_push' function failed.\n");
        failed_tests++;
    } else {
        printf("✅ All tests for 'va_push' function passed.\n");
    }

    printf("Running tests for 'va_pop' function...\n");
    if (test_va_pop() != 0) {
        printf("❌ Some tests for 'va_pop' function failed.\n");
        failed_tests++;
    } else {
        printf("✅ All tests for 'va_pop' function passed.\n");
    }

    printf("Running tests for 'va_free' function...\n");
    if (test_va_free() != 0) {
        printf("❌ Some tests for 'va_free' function failed.\n");
        failed_tests++;
    } else {
        printf("✅ All tests for 'va_free' function passed.\n");
    }

    printf("Running tests for 'va_grow' function...\n");
    if (test_va_grow() != 0) {
        printf("❌ Some tests for 'va_grow' function failed.\n");
        failed_tests++;
    } else {
        printf("✅ All tests for 'va_grow' function passed.\n");
    }

    if (failed_tests > 0) {
        printf("💀 Total failed tests: %d\n", failed_tests);
        return 1;
    }

    printf("✅ All tests passed successfully\n");

    return 0;
}

bool compareFloats(const float a, const float b)
{
    float epsilon = 1e-6;
    return fabs(a - b) < epsilon;
}
