#include "apc.h"

// Validate command line arguments 
int cla_validation(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Invalid Command line arguments\n");
        printf("Usage: ./a.out <operand1> <operator> <operand2>\n");
        return FAILURE;
    }

    int i, start;

    //Validate operand1 
    start = 0;
    if (argv[1][0] == '+' || argv[1][0] == '-')
        start = 1;

    if (argv[1][start] == '\0')
        return FAILURE;

    for (i = start; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Invalid first operand\n");
            return FAILURE;
        }
    }

    // Validate operator 
    if (strlen(argv[2]) != 1)
    {
        printf("Invalid operator\n");
        return FAILURE;
    }

    if (argv[2][0] != '+' &&
        argv[2][0] != '-' &&
        argv[2][0] != 'x' &&
        argv[2][0] != 'X' &&
        argv[2][0] != '/')
    {
        printf("Invalid operator\n");
        return FAILURE;
    }

    // Validate operand2 
    start = 0;
    if (argv[3][0] == '+' || argv[3][0] == '-')
        start = 1;

    if (argv[3][start] == '\0')
        return FAILURE;

    for (i = start; argv[3][i] != '\0'; i++)
    {
        if (!isdigit(argv[3][i]))
        {
            printf("Invalid second operand\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}

// Insert at end 
int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
    }

    return SUCCESS;
}

// Insert at beginning 
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }

    return SUCCESS;
}

// Create list 
void create_list(char *opr, node **head, node **tail)
{
    while (*opr)
    {
        insert_last(head, tail, *opr - '0');
        opr++;
    }
}

// Print list 
void print_list(node *head)
{

    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

// Compare two numbers 
int compare_list(node *head1, node *head2)
{
    int len1 = 0, len2 = 0;

    node *temp = head1;
    while (temp)
    {
        len1++;
        temp = temp->next;
    }

    temp = head2;
    while (temp)
    {
        len2++;
        temp = temp->next;
    }

    if (len1 > len2)
        return OPERAND1;

    if (len2 > len1)
        return OPERAND2;

    while (head1 && head2)
    {
        if (head1->data > head2->data)
            return OPERAND1;

        if (head2->data > head1->data)
            return OPERAND2;

        head1 = head1->next;
        head2 = head2->next;
    }

    return SAME;
}

// Delete list 
int delete_list(node **head, node **tail)
{
    node *temp;

    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
    return SUCCESS;
}

// Remove leading zeros 
void remove_pre_zeros(node **head)
{
    if (*head == NULL)
        return;

    while ((*head)->next && (*head)->data == 0)
    {
        node *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

// Get sign 
int get_sign(char **str)
{
    if (**str == '-')
    {
        (*str)++;
        return 1;
    }

    if (**str == '+')
        (*str)++;

    return 0;
}

// Handle Addition
void handle_addition(node *head1, node *tail1,node *head2, node *tail2,node **headR, node **tailR,int sign1, int sign2)
{
    if (sign1 == 0 && sign2 == 0)            //+A + +B 
    {
        addition(tail1, tail2, headR, tailR);
        printf("Result = ");
    }
    else if (sign1 == 1 && sign2 == 1)       // -A + -B 
    {
        addition(tail1, tail2, headR, tailR);
        printf("Result = -");
    }
    else if (sign1 == 0 && sign2 == 1)       // +A + -B 
    {
        if (compare_list(head1, head2) != OPERAND2)
        {
            subtraction(tail1, tail2, headR, tailR);
            printf("Result = ");
        }
        else
        {
            subtraction(tail2, tail1, headR, tailR);
            printf("Result = -");
        }
    }
    else                                     // -A + +B 
    {
        if (compare_list(head2, head1) != OPERAND2)
        {
            subtraction(tail2, tail1, headR, tailR);
            printf("Result = ");
        }
        else
        {
            subtraction(tail1, tail2, headR, tailR);
            printf("Result = -");
        }
    }

    remove_pre_zeros(headR);

    if (*headR == NULL)
        insert_first(headR, tailR, 0);

    print_list(*headR);
}

// Handle Subtraction 
void handle_subtraction(node *head1, node *tail1,node *head2, node *tail2,node **headR, node **tailR,int sign1, int sign2)
{
    if (sign1 == 0 && sign2 == 0)            // +A - +B 
    {
        if (compare_list(head1, head2) != OPERAND2)
        {
            subtraction(tail1, tail2, headR, tailR);
            printf("Result = ");
        }
        else
        {
            subtraction(tail2, tail1, headR, tailR);
            printf("Result = -");
        }
    }
    else if (sign1 == 0 && sign2 == 1)       // +A - -B 
    {
        addition(tail1, tail2, headR, tailR);
        printf("Result = ");
    }
    else if (sign1 == 1 && sign2 == 0)       // -A - +B 
    {
        addition(tail1, tail2, headR, tailR);
        printf("Result = -");
    }
    else                                     // -A - -B 
    {
        if (compare_list(head2, head1) != OPERAND2)
        {
            subtraction(tail2, tail1, headR, tailR);
            printf("Result = ");
        }
        else
        {
            subtraction(tail1, tail2, headR, tailR);
            printf("Result = -");
        }
    }

    remove_pre_zeros(headR);

    if (*headR == NULL)
        insert_first(headR, tailR, 0);

    print_list(*headR);
}