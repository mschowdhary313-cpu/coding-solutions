//write a c program whether the person is eligible to vote or not
#include<stdio.h>
#include<conio.h>
void main()
{
    int age;
    printf("enter the age of the respective person\n");
    scanf("%d",&age);
    if (age>=18)
    {
        printf("the person is eligible to vote\n");
    }
    else
    {
        printf("the person is not eligible to vote\n");
    }
}
