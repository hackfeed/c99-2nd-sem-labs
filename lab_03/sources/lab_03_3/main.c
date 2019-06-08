#include <stdio.h>
#include <string.h>

#define OK 0
#define GOT_ARG 1
#define WRONG_ARG -1
#define EMPTY_FILE -2
#define FILE_ERROR -3
#define FILE_NOT_EXIST_ERROR -4
#define EXECUTION_ERROR -5
#define TOO_FEW_CL_ARGS_ERROR -6
#define FILENAME_LEN 256

int create_file(FILE *f, char filename[FILENAME_LEN])
{
    int magic_number = 47;

    f = fopen(filename, "wb");

    if (!f)
        return FILE_ERROR;
    
    for (int i = 0; i < 47; ++i)
        fwrite(&magic_number, sizeof(int), 1, f);

    fclose(f);

    return OK;
}

int get_file_size(FILE *const f)
{
    int size = 0;
    fseek(f, 0, SEEK_END);
    size = ftell(f) / sizeof(int);
    fseek(f, 0, SEEK_SET);

    return size;
}

int check_file(FILE *const f)
{
    int cur_num = 0;

    if (!f)
        return FILE_NOT_EXIST_ERROR;

    int size = get_file_size(f);

    if (size == 0)
        return EMPTY_FILE;

    for (int i = 0; i < size; ++i)
    {
        if (fread(&cur_num, sizeof(int), 1, f) != GOT_ARG)
        {
            fseek(f, 0, SEEK_SET);

            return WRONG_ARG;
        }
    }

    fseek(f, 0, SEEK_SET);

    return OK;
}

void get_number_by_pos(FILE *const f, const int pos, int *const get_num)
{
    fseek(f, pos * sizeof(int), SEEK_SET);
    fread(get_num, sizeof(int), 1, f);
}

void put_number_by_pos(FILE *const f, const int pos, const int number)
{   
    fseek(f, pos * sizeof(int), SEEK_SET);
    fwrite(&number, sizeof(int), 1, f);
}

void print_file(FILE *const f)
{
    int cur_num, size = get_file_size(f);

    for (int i = 0; i < size; ++i)
    {
        fread(&cur_num, sizeof(int), 1, f);
        printf("%d ", cur_num);
    }
}

void sort_file(FILE *const f)
{
    int size = get_file_size(f);
    int f_num = 0, s_num = 0;

    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            get_number_by_pos(f, i, &f_num);
            get_number_by_pos(f, j, &s_num);

            if (f_num > s_num)
            {
                put_number_by_pos(f, i, s_num);
                put_number_by_pos(f, j, f_num);
            }
        }
    }
}

int main(int argc, char **argv)
{
    FILE *f = NULL;

    setbuf(stdout, NULL);

    if (argc != 3)
        return TOO_FEW_CL_ARGS_ERROR;

    if (!strcmp(argv[1], "c"))
    {
        create_file(f, argv[2]);

        return OK;
    }

    if (!strcmp(argv[1], "p"))
    {
        f = fopen(argv[2], "rb");

        int file_status = check_file(f);

        if (file_status != OK)
        {
            if (file_status == FILE_NOT_EXIST_ERROR)
                return FILE_ERROR;

            if (file_status == WRONG_ARG || file_status == EMPTY_FILE)
            {
                fclose(f);

                return FILE_ERROR;
            }
        }

        print_file(f);

        return OK;
    }

    if (!strcmp(argv[1], "s"))
    {
        f = fopen(argv[2], "rb+");

        int file_status = check_file(f);

        if (file_status != OK)
        {
            if (file_status == FILE_NOT_EXIST_ERROR)
                return FILE_ERROR;

            if (file_status == WRONG_ARG || file_status == EMPTY_FILE)
            {
                fclose(f);

                return FILE_ERROR;
            }
        }

        sort_file(f);

        return OK;
    }

    return EXECUTION_ERROR;
}