#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS     1
#define FAILURE     0

#define SAME        0
#define OPERAND1    1
#define OPERAND2   -1

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} node;

/* Arithmetic functions */
void addition(node *tail1, node *tail2, node **headR, node **tailR);
void subtraction(node *tail1, node *tail2, node **headR, node **tailR);
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);
void division(node *head1, node *head2, node *tail2, node **headR, node **tailR);

/* Validation */
int cla_validation(int argc, char *argv[]);
int get_sign(char **str);

/* List operations */
void create_list(char *opr, node **head, node **tail);
int insert_first(node **head, node **tail, int data);
int insert_last(node **head, node **tail, int data);
int delete_list(node **head, node **tail);
void print_list(node *head);
void remove_pre_zeros(node **head);

/* Utility functions */
int compare_list(node *head1, node *head2);

/* Handler functions */
void handle_addition(node *head1, node *tail1,node *head2, node *tail2,node **headR, node **tailR,int sign1, int sign2);

void handle_subtraction(node *head1, node *tail1,node *head2, node *tail2,node **headR, node **tailR,int sign1, int sign2);

#endif