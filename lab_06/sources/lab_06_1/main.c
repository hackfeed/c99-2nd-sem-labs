#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define OK 0
#define NO_MATCHES 0
#define HAS_MATCHES 1
#define TESTS_COUNT 5
#define STR_MAX_LEN 256
#define TEST_COMPLETE 0
#define TEST_FAILED 1

char *my_strpbrk(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return NULL;

    int i = 0, j = 0;

    while (str1[i])
    {
        while (str2[j])
        {
            if (str2[j] == str1[i])
                return (char *)&str1[i];

            j++;
        }

        j = 0;
        i++;
    }

    return NULL;
}

size_t my_strspn(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return NO_MATCHES;

    size_t i = 0, j = 0;

    while (str1[i])
    {
        int is_in_str2 = NO_MATCHES;

        while (str2[j])
        {
            if (str2[j] == str1[i])
            {
                is_in_str2 = HAS_MATCHES;
                break;
            }

            j++;
        }

        if (is_in_str2 == NO_MATCHES)
            return i;
        else
        {
            j = 0;
            i++;
        }
    }

    return i;
}

size_t my_strcspn(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL)
        return NO_MATCHES;

    size_t i = 0, j = 0;

    while (str1[i])
    {
        int is_in_str2 = NO_MATCHES;

        while (str2[j])
        {
            if (str2[j] == str1[i])
            {
                is_in_str2 = HAS_MATCHES;
                break;
            }

            j++;
        }

        if (is_in_str2)
            return i;
        else
        {
            j = 0;
            i++;
        }
    }

    return i;
}

char *my_strchr(const char *str, int ch)
{
    char *res = NULL;

    if (str == NULL || ch < 0 || ch > 255)
        return NULL;

    int i = 0;

    while (str[i])
    {
        if (str[i] == ch)
            return (char *)&str[i];

        i++;
    }

    if (ch == 0)
    {
        res = (char *)&str[i];
        return res;
    }

    return NULL;
}

char *my_strrchr(const char *str, int ch)
{
    char *res = NULL;

    if (str == NULL || ch < 0 || ch > 255)
        return NULL;

    int i = 0;

    while (str[i])
    {
        if (str[i] == ch)
            res = (char *)&str[i];

        i++;
    }

    if (ch == 0)
        res = (char *)&str[i];

    return res;
}

const int test_mystrpbrk(const char *str1, const char *str2)
{
    if (strpbrk(str1, str2) == my_strpbrk(str1, str2))
        return TEST_COMPLETE;

    return TEST_FAILED;
}

const int test_mystrspn(const char *str1, const char *str2)
{
    if (strspn(str1, str2) == my_strspn(str1, str2))
        return TEST_COMPLETE;

    return TEST_FAILED;
}

const int test_mystrcspn(const char *str1, const char *str2)
{
    if (strcspn(str1, str2) == my_strcspn(str1, str2))
        return TEST_COMPLETE;

    return TEST_FAILED;
}

const int test_mystrchr(const char *str, int ch)
{
    if (strchr(str, ch) == my_strchr(str, ch))
        return TEST_COMPLETE;

    return TEST_FAILED;
}

const int test_mystrrchr(const char *str, int ch)
{
    if (strrchr(str, ch) == my_strrchr(str, ch))
        return TEST_COMPLETE;

    return TEST_FAILED;
}

void print_test_res(const int test_number, const int test_result)
{
    printf("Test #%d: Result - %d\n", test_number, test_result);
}

int main()
{
    const char tests_string[TESTS_COUNT][STR_MAX_LEN] = {
        "this is a test",
        "your dress is good",
        "time to get it get it tyga",
        "supa hot hella hillz",
        ""
        };

    const char tests_substring[TESTS_COUNT][STR_MAX_LEN] = {
        " absj",
        "osir",
        "tyga",
        "",
        " asdfre"
        };

    const char tests_char[TESTS_COUNT] = {
        't',
        'd',
        ' ',
        'h',
        'b',
        };

    printf("0 - Test completed, 1 - Test failed\n");

    printf("\nStrpbrk tests:\n");
    for (int i = 0; i < TESTS_COUNT; ++i)
        print_test_res(i + 1, test_mystrpbrk(tests_string[i], tests_substring[i]));

    printf("\nStrspn tests:\n");
    for (int i = 0; i < TESTS_COUNT; ++i)
        print_test_res(i + 1, test_mystrspn(tests_string[i], tests_substring[i]));

    printf("\nStrcspn tests:\n");
    for (int i = 0; i < TESTS_COUNT; ++i)
        print_test_res(i + 1, test_mystrcspn(tests_string[i], tests_substring[i]));

    printf("\nStrchr tests:\n");
    for (int i = 0; i < TESTS_COUNT; ++i)
        print_test_res(i + 1, test_mystrchr(tests_string[i], tests_char[i]));

    printf("\nStrrchr tests:\n");
    for (int i = 0; i < TESTS_COUNT; ++i)
        print_test_res(i + 1, test_mystrrchr(tests_string[i], tests_char[i]));

    return OK;
}