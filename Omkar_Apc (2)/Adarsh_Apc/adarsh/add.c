#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    // Initialize carry with zero
    int carry = 0;


    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        // Start the current sum with the carry value
        int sum = carry;

        if (tail1 != NULL)
        {
            // Add the current digit from the first number
            sum += tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            // Add the current digit from the second number
            sum += tail2->data;
            tail2 = tail2->prev;
        }

        carry = sum / 10;

        // Insert the current result digit at the beginning of the result list
        if (insert_first(headR, tailR, sum % 10) == FAILURE)
        {
            
            printf("Memory allocation failed\n");
            delete_list(headR, tailR);
            return;
        }
    }

    // Remove unwanted leading zeros from the final result
    remove_pre_zeros(headR);

    // Insert zero if the result list becomes empty.
    if (*headR == NULL)
    {
        insert_first(headR, tailR, 0);
    }
}