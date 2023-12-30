#include <stdio.h>
#include <cs50.h>

int reverse(int num);

int main(void) {
    int n;
    do {
        n = get_int("Enter a number(10 and above): ");
        printf("reversed: ");
        reverse(n);
        printf("\n");
    } while(n > 10);
}

int reverse(int num) {
    if (num == 0) {
        return 0;
    }
    printf("%i", num % 10);
    return reverse(num / 10);
}
