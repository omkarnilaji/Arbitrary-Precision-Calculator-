#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp2 = tail2;
    int shift = 0;

    while (temp2 != NULL)
    {
        node *headTemp = NULL;
        node *tailTemp = NULL;
        node *temp1 = tail1;

        int carry = 0;

        /* Append zeros according to place value */
        for (int i = 0; i < shift; i++)
        {
            insert_first(&headTemp, &tailTemp, 0);
        }

        /* Multiply one digit of second operand with first operand */
        while (temp1 != NULL)
        {
            int product = (temp1->data * temp2->data) + carry;

            if (insert_first(&headTemp, &tailTemp, product % 10) == FAILURE)
            {
                printf("Memory allocation failed\n");
                delete_list(&headTemp, &tailTemp);
                return;
            }

            carry = product / 10;
            temp1 = temp1->prev;
        }

        /* Insert remaining carry */
        while (carry)
        {
            if (insert_first(&headTemp, &tailTemp, carry % 10) == FAILURE)
            {
                printf("Memory allocation failed\n");
                delete_list(&headTemp, &tailTemp);
                return;
            }
            carry /= 10;
        }

        /* First partial product */
        if (*headR == NULL)
        {
            *headR = headTemp;
            *tailR = tailTemp;
        }
        else
        {
            node *headSum = NULL;
            node *tailSum = NULL;

            addition(*tailR, tailTemp, &headSum, &tailSum);

            delete_list(headR, tailR);
            delete_list(&headTemp, &tailTemp);

            *headR = headSum;
            *tailR = tailSum;
        }

        temp2 = temp2->prev;
        shift++;
    }

    remove_pre_zeros(headR);

    if (*headR == NULL)
    {
        insert_first(headR, tailR, 0);
    }
}