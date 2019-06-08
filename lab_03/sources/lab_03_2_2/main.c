#include <stdio.h>

#define OK 0
#define GOT_ARG 1
#define WRONG_ARG -1
#define EMPTY_FILE -2
#define FILE_ERROR -3
#define FILE_NOT_EXIST_ERROR -4

int check_file(FILE *const f)
{
    double cur_num = 0;

    if (!f)
        return FILE_NOT_EXIST_ERROR;

    if (feof(f))
        return EMPTY_FILE;

    while (!feof(f))
    {
        if (fscanf(f, "%lf", &cur_num) != GOT_ARG)
        {
            fseek(f, 0, SEEK_SET);

            return WRONG_ARG;
        }
    }

    fseek(f, 0, SEEK_SET);

    return OK;
}

double calc_average(FILE *const f, int *const n)
{
    double cur_num = 0, cur_sum = 0, avg = 0;

    while (!feof(f))
    {
        fscanf(f, "%lf", &cur_num);
        cur_sum += cur_num;
        (*n)++;
    }

    avg = cur_sum / (*n);

    fseek(f, 0, SEEK_SET);

    return avg;
}

double calc_disp(FILE *const f, const int n, const double avg)
{
    double cur_num = 0, cur_part_disp = 0, disp = 0;

    while (!feof(f))
    {
        fscanf(f, "%lf", &cur_num);
        cur_part_disp += (cur_num - avg) * (cur_num - avg);
    }

    disp = cur_part_disp / n;

    fseek(f, 0, SEEK_SET);

    return disp;
}

int main(int argc, char **argv)
{
    FILE *f;
    int n = 0;
    double avg = 0, disp = 0;

    f = fopen(argv[1], "rt");

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

    avg = calc_average(f, &n);
    disp = calc_disp(f, n, avg);

    printf("%lf", disp);

    fclose(f);

    return OK;
}