#include <stdio.h>
#include <math.h>

#define OK 0

int get_file_size(FILE *const f)
{
    int size = 0;

    fseek(f, 0, SEEK_END);
    size = ftell(f) / sizeof(int);
    fseek(f, 0, SEEK_SET);

    return size;
}

void print_file(FILE *const f)
{
    fseek(f, 0, SEEK_SET);

    int size = get_file_size(f);
    int cur_int;

    for (int i = 0; i < size; ++i)
    {
        fread(&cur_int, sizeof(int), 1, f);
        printf("%d ", cur_int);
    }
}

void get_int_by_pos(FILE *const f, const int pos, int *const get_int)
{
    fseek(f, pos * sizeof(int), SEEK_SET);
    fread(get_int, sizeof(int), 1, f);
}

void matrix_inc(FILE *const f_in, FILE *const f_out, const int matrix_dime)
{
    int inc_a, inc_b, cur_el;

    for (int i = 0; i < matrix_dime; ++i)
    {
        for (int j = 0; j < matrix_dime; ++j)
        {
            cur_el = 0;

            for (int k = 0; k < matrix_dime; ++k)
            {
                get_int_by_pos(f_in, k + matrix_dime * i, &inc_a);
                get_int_by_pos(f_in, j + matrix_dime * k, &inc_b);
                cur_el += inc_a * inc_b;
            }

            fwrite(&cur_el, sizeof(int), 1, f_out);
        }
    }
}

void fill_binary(FILE *const f)
{
    int one = 1, zero = 0;

    fwrite(&one, sizeof(int), 1, f);
    fwrite(&one, sizeof(int), 1, f);
    fwrite(&zero, sizeof(int), 1, f);

    fwrite(&zero, sizeof(int), 1, f);
    fwrite(&one, sizeof(int), 1, f);
    fwrite(&zero, sizeof(int), 1, f);

    fwrite(&zero, sizeof(int), 1, f);
    fwrite(&one, sizeof(int), 1, f);
    fwrite(&one, sizeof(int), 1, f);
}

int main()
{
    FILE *f_in, *f_out;

    f_in = fopen("in.bin", "wb");
    fill_binary(f_in);
    fclose(f_in);

    f_in = fopen("in.bin", "rb");
    f_out = fopen("out.bin", "wb");

    int size = get_file_size(f_in);
    int matrix_dime = (int) sqrt(size);

    matrix_inc(f_in, f_out, matrix_dime);

    fclose(f_in);
    fclose(f_out);

    f_out = fopen("out.bin", "rb");
    print_file(f_out);
    fclose(f_out);

    return 0;
}