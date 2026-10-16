#include <stdio.h>

int main() {
    double num1, num2;
    char operator;

    // Get operator and numbers from the user
    printf("Enter an operator (+, -, *, /): ");
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

    return 0;
}
