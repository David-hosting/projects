#include <stdio.h>
#include <cs50.h>

void draw(int num);

int main(void) {
    draw(4);
}

void draw(int num)
{
    if (num <= 0)
    {
        return;
    }

    draw(num-1);

    for (int i = 0; i < num; i++)
    {
        printf("#");
    }
    printf("\n");
}
