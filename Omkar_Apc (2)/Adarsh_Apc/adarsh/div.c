#include "apc.h"

void division(node *head1, node *head2, node *tail2,node **headR, node **tailR)
{
    /* Divide by zero check */
    if (head2 == NULL || (head2->data == 0 && head2->next == NULL))
    {
        printf("Error: Division by zero\n");
        return;
    }

    node *headDividend = NULL;
    node *tailDividend = NULL;

    node *temp = head1;

    while (temp != NULL)
    {
        /* Bring down one digit */
        insert_last(&headDividend, &tailDividend, temp->data);
        remove_pre_zeros(&headDividend);

        int quotient_digit = 0;

        /* Repeated subtraction */
        while (compare_list(headDividend, head2) != OPERAND2)
        {
            node *headSub = NULL;
            node *tailSub = NULL;

            subtraction(tailDividend, tail2, &headSub, &tailSub);

            delete_list(&headDividend, &tailDividend);

            headDividend = headSub;
            tailDividend = tailSub;

            remove_pre_zeros(&headDividend);

            quotient_digit++;
        }

        insert_last(headR, tailR, quotient_digit);

        temp = temp->next;
    }

    remove_pre_zeros(headR);

    if (*headR == NULL)
    {
        insert_last(headR, tailR, 0);
    }

    delete_list(&headDividend, &tailDividend);
}