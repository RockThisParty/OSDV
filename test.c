#include <stdio.h>
#include <stdlib.h>

void main()
{
    char s[20];
    int a, b, sum;
    puts("Enter a");
    scanf("%d", &a);
    puts("Enter b");
    scanf("%d", &b);
    asm volatile
    (
	".intel_syntax\n"
        "add %0, %1 \n"
        ".att_syntax \n"
        :"+r"(a)
        :"r"(b)
    );
    printf("\n Sum is %d\n", a);
}
