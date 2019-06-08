#include <stdio.h>

#define FLATS_PER_ENTRANCE 36
#define FLATS_PER_FLOOR 4

#define OK 0

int main()
{
    int flat_num;
    int entrance_num, floor_num;

    printf("Input flat number: ");
    scanf("%d", &flat_num);

    entrance_num = ((flat_num - 1) / FLATS_PER_ENTRANCE) + 1;
    floor_num = ((flat_num - 1) % FLATS_PER_ENTRANCE) / FLATS_PER_FLOOR + 1;

    printf("Entrance number: %-12d\n"
        "Floor number: %-12d", entrance_num, floor_num);

    return OK;
}

