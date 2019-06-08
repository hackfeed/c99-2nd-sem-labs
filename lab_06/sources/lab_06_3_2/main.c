#include <stdio.h>
#include <string.h>

#define OK 0
#define GOT_ARG 1
#define INPUT_ERROR -1
#define STRING_LEN_ERROR -2
#define EMPTY_STRING_ERROR -3
#define WORD_LEN_ERROR -4

#define MAX_STRING_LEN 256
#define MAX_WORD_LEN 16

#define FALSE 0
#define TRUE 1

int input_string(char *const string_arr)
{
    int i = 0;

    scanf("%c", &string_arr[i]);

    while (string_arr[i] != '\n' && i < MAX_STRING_LEN)
    {
        i++;
        if (scanf("%c", &string_arr[i]) != GOT_ARG)
            return INPUT_ERROR;
    }

    if (!i)
        return EMPTY_STRING_ERROR;

    if (string_arr[i] != '\n')
        return STRING_LEN_ERROR;

    string_arr[i] = '\0';

    return OK;
}

int split(const char *const string_arr, char matrix[MAX_STRING_LEN][MAX_WORD_LEN], \
    const char *const splashes)
{
    int row = 0, col = 0, k = 0, j = 0;
    int splash_found = TRUE;

    while (string_arr[k])
    {
        while (splashes[j])
        {
            if (string_arr[k] == splashes[j])
            {
                splash_found = FALSE;
                break;
            }
            j++;
        }
        
        if (splash_found)
            matrix[row][col++] = string_arr[k];
        else
        {
            matrix[row++][col] = '\0';
            col = 0;
        }

        k++;
        j = 0;
        splash_found = TRUE;
    }

    matrix[row][col] = '\0';

    return ++row;
}

int check_word_matrix(char matrix[MAX_STRING_LEN][MAX_WORD_LEN], const int words_num)
{
    for (int i = 0; i < words_num; ++i)
    {
        int k = 0;
        while (matrix[i][k])
            k++;

        if (matrix[i][k] != '\0' || k > MAX_WORD_LEN)
            return WORD_LEN_ERROR;
    }

    return OK;
}

int find_num_of_reps(const char *const string_arr, \
    char f_matrix[MAX_STRING_LEN][MAX_WORD_LEN], const int f_words_num, \
    char s_matrix[MAX_STRING_LEN][MAX_WORD_LEN], const int s_words_num)
{
    int number_of_reps = -1;

    for (int i = 0; i < f_words_num; ++i)
        if (f_matrix[i][0] != '\0')
            if (!strcmp(string_arr, f_matrix[i]))
                number_of_reps++;

    for (int i = 0; i < s_words_num; ++i)
        if (s_matrix[i][0] != '\0')
            if (!strcmp(string_arr, s_matrix[i]))
                number_of_reps++;

    return number_of_reps;
}

int main()
{
    char f_str[MAX_STRING_LEN] = { 0 }, s_str[MAX_STRING_LEN] = { 0 };

    char f_str_word_matrix[MAX_STRING_LEN][MAX_WORD_LEN] = { 0 };
    char s_str_word_matrix[MAX_STRING_LEN][MAX_WORD_LEN] = { 0 };

    char splashes[] = " ,;:-.!?";

    int f_str_words_count = 0, s_str_words_count = 0;

    if (input_string(f_str) != OK || input_string(s_str) != OK)
        return INPUT_ERROR;

    f_str_words_count = split(f_str, f_str_word_matrix, splashes);
    s_str_words_count = split(s_str, s_str_word_matrix, splashes);

    if (check_word_matrix(f_str_word_matrix, f_str_words_count) != OK || \
        check_word_matrix(s_str_word_matrix, s_str_words_count) != OK)
        return WORD_LEN_ERROR;

    printf("Result:\n");

    for (int i = 0; i < f_str_words_count; ++i)
        if (!find_num_of_reps(f_str_word_matrix[i], \
            f_str_word_matrix, f_str_words_count, \
            s_str_word_matrix, s_str_words_count))
            printf("%s ", f_str_word_matrix[i]);


    for (int i = 0; i < s_str_words_count; ++i)
        if (!find_num_of_reps(s_str_word_matrix[i], \
            f_str_word_matrix, f_str_words_count, \
            s_str_word_matrix, s_str_words_count))
            printf("%s ", s_str_word_matrix[i]);

    return OK;
}