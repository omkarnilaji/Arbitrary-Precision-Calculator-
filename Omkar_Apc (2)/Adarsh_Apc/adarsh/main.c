

#include "apc.h"

int main(int argc, char *argv[])
{
    // Check  the command line arguments are valid
    if (cla_validation(argc, argv) == FAILURE)
    {
        return FAILURE;
    }

    // Store the input numbers from the command line
    char *num1 = argv[1];
    char *num2 = argv[3];

    // Find the sign of both input numbers
    int sign1 = get_sign(&num1);
    int sign2 = get_sign(&num2);

    // Create head and tail pointers for input and result linked lists
    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;
    node *headR = NULL, *tailR = NULL;

    // Convert the input strings into linked lists
    create_list(num1, &head1, &tail1);
    create_list(num2, &head2, &tail2);

    // Remove leading zeros from both input numbers
    remove_pre_zeros(&head1);
    remove_pre_zeros(&head2);

    // Store the arithmetic operator
    char oper = argv[2][0];

    printf("OPERAND1 = %s", (sign1 == -1) ? "-" : ""); // Print the sign of operand1 if it is negative
    print_list(head1); // print the digits of operand1

    printf("OPERATOR = %s\n", argv[2]); // print the operator

    printf("OPERAND2 = %s", (sign2 == -1) ? "-" : ""); // Print the sign of operand2 if it is negative
    print_list(head2); // print the digits of operand2

    // Perform the required operation based on the operator
    switch (oper)
    {
        case '+':
            handle_addition(head1, tail1, head2, tail2, &headR, &tailR, sign1, sign2);
            break;

        case '-':
            handle_subtraction(head1, tail1, head2, tail2, &headR, &tailR, sign1, sign2);
            break;

        case 'x':
        case 'X':
            // Perform multiplication operation
            multiplication(tail1, tail2, &headR, &tailR);

            // Remove leading zeros from the result
            remove_pre_zeros(&headR);

            // Store zero if the result list becomes empty
            if (headR == NULL)
                insert_first(&headR, &tailR, 0);

            printf("Result = ");

            // Print negative sign if only one input number is negative
            if ((sign1 ^ sign2) == 1)
                printf("-");

            // Display the multiplication result
            print_list(headR);
            break;

        case '/':
            // Perform division operation
            division(head1, head2, tail2, &headR, &tailR);

            // Remove leading zeros from the result
            remove_pre_zeros(&headR);

            // Store zero if the result list becomes empty
            if (headR == NULL)
                insert_first(&headR, &tailR, 0);

            printf("Quotient = ");

            // Print negative sign if only one input number is negative
            if ((sign1 ^ sign2) == 1)
                printf("-");

            // Display the quotient
            print_list(headR);
            break;

        default:
            // Display an error for an invalid operator
            printf("Invalid operator\n");
            break;
    }

    // Free all allocated linked list memory
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);

    return SUCCESS;
}