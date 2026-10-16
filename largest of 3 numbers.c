#include<stdio.h>
#include<conio.h>
void main()
{
    int a,b,c;
    printf("enter the first number\n");
    scanf("%d",&a);
    printf("enter the second number\n");
    scanf("%d",&b);
    printf("enter the third number\n");
    scanf("%d",&c);
    if(a>b && a>c)
    printf("a is the largest number");
    else if (b>a&&b>c)
    printf("b is the largest number");
    else
        printf("c is the largest number");


}
