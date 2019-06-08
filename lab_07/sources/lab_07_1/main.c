#include <stdio.h>
#include <string.h>
#include <math.h>

#define OK 0
#define WRONG_ARG -1
#define FILE_NOT_EXIST_ERROR -2
#define EMPTY_FILE_ERROR -3
#define FILE_ERROR -4
#define NO_MATCHES_ERROR -5
#define WRONG_CL_ARGUMENTS_ERROR 53

#define GOT_ARG 1

#define MAX_SURNAME_LEN 26
#define MAX_NAME_LEN 11
#define MARKS_COUNT 4
#define EPS 1e-6

typedef struct student
{
    char surname[MAX_SURNAME_LEN];
    char name[MAX_NAME_LEN];
    unsigned int marks[MARKS_COUNT];
} student_t;

void print_array(const unsigned int *const array, const int array_size)
{
    for (int i = 0; i < array_size; ++i)
        printf("%u ", array[i]);
}

void print_struct(const student_t student)
{
    printf("%s\n", student.surname);
    printf("%s\n", student.name);
    print_array(student.marks, MARKS_COUNT);
    printf("\n\n");
}

int get_struct_file_size(FILE *const f)
{
    int size = 0;
    fseek(f, 0, SEEK_END);
    size = ftell(f) / sizeof(student_t);
    fseek(f, 0, SEEK_SET);

    return size;
}

int check_file(FILE *const f)
{
    student_t cur_student;

    if (!f)
        return FILE_NOT_EXIST_ERROR;

    int size = get_struct_file_size(f);

    fseek(f, 0, SEEK_SET);

    if (size == 0)
        return EMPTY_FILE_ERROR;

    for (int i = 0; i < size; ++i)
    {
        if (fread(&cur_student, sizeof(student_t), 1, f) != GOT_ARG)
        {
            fseek(f, 0, SEEK_SET);

            return WRONG_ARG;
        }
    }

    fseek(f, 0, SEEK_SET);

    return OK;
}

void print_file(FILE *const f)
{
    fseek(f, 0, SEEK_SET);

    int size = get_struct_file_size(f);
    student_t student;

    for (int i = 0; i < size; ++i)
    {
        fread(&student, sizeof(student_t), 1, f);
        print_struct(student);
    }
}

void get_student_by_pos(FILE *const f, const int pos, student_t *const get_student)
{
    fseek(f, pos * sizeof(student_t), SEEK_SET);
    fread(get_student, sizeof(student_t), 1, f);
}

void put_student_by_pos(FILE *const f, const int pos, const student_t put_student)
{   
    fseek(f, pos * sizeof(student_t), SEEK_SET);
    fwrite(&put_student, sizeof(student_t), 1, f);
}

void sort_file(FILE *const f)
{
    int size = get_struct_file_size(f);
    student_t f_student, s_student;

    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            get_student_by_pos(f, i, &f_student);
            get_student_by_pos(f, j, &s_student);

            if (strcmp(f_student.surname, s_student.surname) > 0)
            {
                put_student_by_pos(f, i, s_student);
                put_student_by_pos(f, j, f_student);
            }
            else
            {
                if (strcmp(f_student.surname, s_student.surname) == 0)
                {
                    if (strcmp(f_student.name, s_student.name) > 0)
                    {
                        put_student_by_pos(f, i, s_student);
                        put_student_by_pos(f, j, f_student);
                    }
                }
            }
        }
    }
}

int fill_substr_file(FILE *const f_in, FILE *const f_out, const char *substr)
{
    int size = get_struct_file_size(f_in);
    student_t student;
    int sub_count = 0; 

    for (int i = 0; i < size; ++i)
    {
        get_student_by_pos(f_in, i, &student);
        char *sub = strstr(student.surname, substr);
        int pos = sub - student.surname;

        if (pos == 0)
        {
            fwrite(&student, sizeof(student_t), 1, f_out);
            sub_count++;
        }
    }

    return sub_count;
}

double find_array_average(const unsigned int *const array, const int array_size)
{
    double sum = 0;
    double average = 0;

    for (int i = 0; i < array_size; ++i)
        sum += array[i];

    average = sum / array_size;

    return average;
}

int find_array_sum(const unsigned int *const array, const int array_size)
{
    double sum = 0;

    for (int i = 0; i < array_size; ++i)
        sum += array[i];

    return sum;
}

double find_students_average(FILE *const f)
{
    int size = get_struct_file_size(f);
    student_t student;

    double sum = 0;
    double average = 0;

    for (int i = 0; i < size; ++i)
    {
        get_student_by_pos(f, i, &student);
        sum += find_array_sum(student.marks, MARKS_COUNT);
    }

    average = sum / (size * MARKS_COUNT);

    return average;
}

void delete_losers(FILE *const f, FILE *const f_new)
{
    double overall_average = find_students_average(f);

    fseek(f, 0, SEEK_SET);

    int size = get_struct_file_size(f);
    student_t student;

    for (int i = 0; i < size; ++i)
    {
        get_student_by_pos(f, i, &student);
        if (fabs(find_array_average(student.marks, MARKS_COUNT) - overall_average) < EPS || \
            (find_array_average(student.marks, MARKS_COUNT) - overall_average) >= EPS)
            fwrite(&student, sizeof(student_t), 1, f_new);
    }
}

void copy_file(FILE *const f_to, FILE *const f_from)
{
    int size = get_struct_file_size(f_from);
    student_t student;

    for (int i = 0; i < size; ++i)
    {
        get_student_by_pos(f_from, i, &student);
        fwrite(&student, sizeof(student_t), 1, f_to);
    }
}

/*void fill_binary_file(FILE *const f)
{
    student_t s1 = { "Gamma", "Ivan", {2, 3, 3, 3} };
    student_t s2 = { "Charly", "Sidr", {5, 5, 5, 5} };
    student_t s3 = { "Beta", "Petr", {3, 4, 5, 3} };
    student_t s4 = { "Alpha", "Petr", {4, 3, 4, 4} };

    fwrite(&s1, sizeof(student_t), 1, f);
    fwrite(&s2, sizeof(student_t), 1, f);
    fwrite(&s3, sizeof(student_t), 1, f);
    fwrite(&s4, sizeof(student_t), 1, f);
}*/

int main(int argc, char **argv)
{
    FILE *f_in = NULL, *f_out = NULL, *f_new = NULL;

    /*f_in = fopen("binary.bin", "wb");
    fill_binary_file(f_in);
    fclose(f_in);*/

    setbuf(stdout, NULL);

    if (argc == 3 && !strcmp(argv[1], "sb"))
    {
        f_in = fopen(argv[2], "rb+");
        int file_status = check_file(f_in);

        if (file_status != OK)
        {
            if (file_status == FILE_NOT_EXIST_ERROR)
                return FILE_ERROR;

            if (file_status == WRONG_ARG || file_status == EMPTY_FILE_ERROR)
            {
                fclose(f_in);

                return FILE_ERROR;
            }
        }

        sort_file(f_in);
        print_file(f_in);

        fclose(f_in);

        return OK;
    }

    if (argc == 5 && !strcmp(argv[1], "fb"))
    {
        f_in = fopen(argv[2], "rb");
        f_out = fopen(argv[3], "wb");
        int file_status = check_file(f_in);

        if (file_status != OK)
        {
            if (file_status == FILE_NOT_EXIST_ERROR)
                return FILE_ERROR;

            if (file_status == WRONG_ARG || file_status == EMPTY_FILE_ERROR)
            {
                fclose(f_in);

                return FILE_ERROR;
            }
        }

        if (fill_substr_file(f_in, f_out, argv[4]) == 0)
        {
            fclose(f_in);
            fclose(f_out);

            return NO_MATCHES_ERROR;
        }

        /*fclose(f_out);

        f_out = fopen(argv[3], "rb");
        print_file(f_out);*/

        fclose(f_in);
        fclose(f_out);

        return OK;
    }

    if (argc == 3 && !strcmp(argv[1], "db"))
    {
        f_in = fopen(argv[2], "rb");
        f_new = fopen("temp.bin", "wb");
        int file_status = check_file(f_in);

        if (file_status != OK)
        {
            if (file_status == FILE_NOT_EXIST_ERROR)
                return FILE_ERROR;

            if (file_status == WRONG_ARG || file_status == EMPTY_FILE_ERROR)
            {
                fclose(f_in);

                return FILE_ERROR;
            }
        }

        delete_losers(f_in, f_new);

        fclose(f_in);
        fclose(f_new);

        f_in = fopen(argv[2], "wb");
        f_new = fopen("temp.bin", "rb");

        copy_file(f_in, f_new);

        fclose(f_in);
        fclose(f_new);

        /*f_in = fopen(argv[2], "rb");

        print_file(f_in);

        fclose(f_in);*/

        return OK;
    }

    return WRONG_CL_ARGUMENTS_ERROR;
}
