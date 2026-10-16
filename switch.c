#include <stdio.h>
int main ()

 {
    char grade;
    printf ("enter your grade");
     scanf ("%c",&grade);


     switch(grade)
     {

    case 'A':
    printf ("excelent, congrats");
    break;

    case 'B':
    printf ("merit");
    break;

    case 'C':
    printf ("justpass");
    break;

    case 'D':
    printf ("good");
    break;


    case 'E':
    printf ("work hard");
    break;

    case 'F':
    printf ("fail ,worst");
    break;
    }
    return 0;
    }

