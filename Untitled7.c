#include <stdio.h>

int main() {
    double num1, num2;
    char operator;
    char choice = 'y';

    printf("=============================\n");
    printf("   WELCOME TO C CALCULATOR   \n");
    printf("=============================\n");

    // Loop to keep the calculator running until the user wants to quit
    while (choice == 'y' || choice == 'Y') {
        printf("\nEnter operator (+, -, *, /): ");
        scanf(" %c", &operator);

        printf("Enter two numbers: ");
        scanf("%lf %lf", &num1, &num2);

        // Perform calculation based on the operator
        switch(operator) {
            case '+':
                printf("Result: %.2lf\n", num1 + num2);
                break;
            case '-':
                printf("Result: %.2lf\n", num1 - num2);
                break;
            case '*':
                printf("Result: %.2lf\n", num1 * num2);
                break;
            case '/':
                if(num2 != 0)
                    printf("Result: %.2lf\n", num1 / num2);
                else
                    printf("Error! Division by zero is not allowed.\n");
                break;
            default:
                printf("Error! Invalid operator entered.\n");
        }

        printf("\nDo you want to calculate again? (y/n): ");
        scanf(" %c", &choice);
    }

    printf("\nCalculator closed. Thanks for using!\n");
    return 0;
}
