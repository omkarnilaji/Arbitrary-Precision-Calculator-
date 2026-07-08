#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    // Initialize borrow with zero
    int borrow = 0;

    while (tail1 != NULL || tail2 != NULL)
    {
        // Store the current digits of both numbers
        int digit1 = 0, digit2 = 0;

        // Get the current digit from the first number
        if (tail1 != NULL)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        // Get the current digit from the second number
        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        // Subtract the previous borrow from the current digit
        digit1 -= borrow;

        // Check if borrowing is needed for this subtraction
        if (digit1 < digit2)
        {
            digit1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        // Insert the subtraction result at the beginning of the result list
        if (insert_first(headR, tailR, digit1 - digit2) == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(headR, tailR);
            return;
        }
    }

    // Remove unnecessary leading zeros from the result
    remove_pre_zeros(headR);

    // If the result becomes empty, store zero as the result
    if (*headR == NULL)
    {
        insert_first(headR, tailR, 0);
    }
}