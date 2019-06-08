#include <stdio.h>

#define OK 0
#define GOT_ARG 1
#define GOT_TWO_ARGS 2
#define WRONG_ARG -1
#define EMPTY_FILE -2
#define FILE_ERROR -3
#define EXECUTION_ERROR -4
#define CANT_FIND_LOCAL_MAXS_ERROR -5

int find_local_maximum_count(FILE *const f, int *const local_max_count)
{
    int current_num = 0, previous_num = 0, next_num = 0, local_max_count_file = 0;

    if (!f)
        return FILE_ERROR;

    if (feof(f))
        return EMPTY_FILE;

    if (fscanf(f, "%d%d", &previous_num, &current_num) == GOT_TWO_ARGS)
    {
        if (feof(f))
            return CANT_FIND_LOCAL_MAXS_ERROR;

        while (!feof(f))
        {
            if (fscanf(f, "%d", &next_num) == GOT_ARG)
            {
                if (current_num > previous_num && current_num > next_num)
                    local_max_count_file++;
                previous_num = current_num;
                current_num = next_num;
            }
            else
                return WRONG_ARG;
        }

        *local_max_count = local_max_count_file;

        return OK;
    }

    return WRONG_ARG;
}

int main()
{
    int max_count = 0;

    if (find_local_maximum_count(stdin, &max_count) == OK)
    {
        printf("%d", max_count);

        return OK;
    }

    return EXECUTION_ERROR;
}