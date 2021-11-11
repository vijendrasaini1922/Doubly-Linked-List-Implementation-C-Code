// doubly linked list implementation

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// creating a structure for doubly linked list
struct node
{
    int data;
    struct node *next;
    struct node *pre;
};

struct node *head;

// function prototype
bool is_empty();
struct node *add__to_empty(struct node *headRef, int newdata);
struct node *insert_at_beginning(struct node *headRef, int newdata);
struct node *insert_at_end(struct node *headRef, int newdata);
struct node *insert_at_random_position(struct node *headRef, int position, int newdata);
struct node *deletion_at_random_position(struct node *headRef, int position);
void search(struct node *headRef, int element);
int max_value(struct node *headRef);
int min_value(struct node *headRef);
void display(struct node *headRef);

// ********************MAIN FUNCTION*****************************
int main()
{
    head = NULL;
    int n, newdata, operation, position;

    printf("Enter the number of nodes of doubly linked list: ");
    scanf("%d", &n);
    printf("Enter the element at position 1: ");
    scanf("%d", &newdata);

    head = add__to_empty(head, newdata);

    for (int i = 1; i < n; i++)
    {
        printf("Enter the element at position %d: ", (i + 1));
        scanf("%d", &newdata);
        head = insert_at_end(head, newdata);
    }
    display(head);

    printf("\nHotkeys to call operation::\n");
    printf("Press 1 for insert element at any given position.\n");
    printf("Press 2 for delete element at any given position.\n");
    printf("Press 3 for search element.\n");
    printf("Press 4 for find Max value element.\n");
    printf("Press 5 for find Min value element.\n");
    printf("Press 6 for list display.\n");
    printf("Press 7 for exit.\n");

Loop:

    printf("\nEnter the operation number: ");
    scanf("%d", &operation);
    printf("\n");
    switch (operation)
    {
    case 1:
        printf("Enter the position and new element respectively: ");
        scanf("%d %d", &position, &newdata);
        head = insert_at_random_position(head, position, newdata);
        goto Loop;

    case 2:
        printf("Enter the deletion position: ");
        scanf("%d", &position);
        head = deletion_at_random_position(head, position);
        goto Loop;

    case 3:
        printf("Enter the element to be search: ");
        scanf("%d", &newdata);
        search(head, newdata);
        goto Loop;

    case 4:
        printf("Maximum value is: %d", max_value(head));
        goto Loop;

    case 5:
        printf("Minimum value is: %d", min_value(head));
        goto Loop;

    case 6:
        display(head);
        goto Loop;

    case 7:
        break;
    goto Loop;
    default:
        printf("You have entered invalid operation.\n\n");
        
    }
    return 0;
}
// **********************END****************************

bool is_empty()
{
    return head == NULL;
}

// Function definitions
struct node *add__to_empty(struct node *headRef, int newdata)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = newdata;
    temp->next = NULL;
    temp->pre = NULL;
    headRef = temp;
    return headRef;
}
// End of add_to_empty function;

struct node *insert_at_beginning(struct node *headRef, int newdata)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));

    temp->data = newdata;
    temp->next = headRef;
    temp->pre = NULL;

    // updating head address;
    headRef = temp;
    return headRef;
}
// End of insert_at_beginning function;

struct node *insert_at_end(struct node *headRef, int newdata)
{
    struct node *temp, *ran;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = newdata;
    ran = headRef;

    // traversing last element address
    while (ran->next != NULL)
        ran = ran->next;

    ran->next = temp;
    temp->next = NULL;
    temp->pre = ran;

    return headRef;
}
// End of insert_at_end function;

struct node *insert_at_random_position(struct node *headRef, int position, int newdata)
{
    int count = 0;
    struct node *temp, *ran;
    temp = (struct node *)malloc(sizeof(struct node));
    ran = headRef;

    if (position == 1)
    {
        temp->data = newdata;
        temp->pre = NULL;
        temp->next = ran;
        headRef = temp;
    }
    else
    {
        // Traversion to given position
        while (count++ != position - 2)
            ran = ran->next;
        temp->data = newdata;
        temp->next = ran->next;
        temp->pre = ran;
        ran->next = temp;
    }
    return headRef;
}
// End of insert_at_random_position function;

struct node *deletion_at_random_position(struct node *headRef, int position)
{
    int count = 0;
    struct node *ran, *temp;
    ran = headRef;

    if (position == 1)
    {
        ran = ran->next;
        ran->pre = NULL;
        headRef = ran;
    }
    else
    {
        // Traversion to given position
        while (count++ != position - 2)
            ran = ran->next;
        if (ran->next->next == NULL)
        {
            temp = ran;
            ran->next = NULL;
            ran->pre = temp;
        }
        else
        {
            temp = ran;
            ran->next->pre = temp;
            ran->next = temp->next->next;
            
        }
    }
    return headRef;
}
// End of deletion_at_random_position;

void search(struct node *headRef, int element)
{
    struct node *temp;
    int position = 0, flag = 0;
    temp = headRef;
    while (temp)
    {
        if (temp->data == element)
        {
            printf("Element found at position: %d", position + 1);
            flag = 1;
            break;
        }
        else
            temp = temp->next;
        position++;
    }
    if (flag == 0)
        printf("Element not found!!");
}
// End of search function

int max_value(struct node *headRef)
{
    struct node *temp;
    temp = headRef;
    int max = INT_MIN; // Initialize the max value with minimum value;

    while (temp)
    {
        if (max < temp->data)
            max = temp->data; // updating the max value;
        temp = temp->next;
    }
    return max;
}
// End of max_value function

int min_value(struct node *headRef)
{
    struct node *temp;
    temp = headRef;
    int min = INT_MAX; // Initialize the min value with the max value;

    while (temp)
    {
        if (min > temp->data)
            min = temp->data; // updating the min value;
        temp = temp->next;
    }
    return min;
}
// End of min_value function;

void display(struct node *headRef)
{
    struct node *temp;
    temp = headRef;
    printf("Element\t Address\n");
    while (temp)
    {
        printf("%d\t%u\n", temp->data, temp);
        temp = temp->next;
    }
}
// Endn of Display function
//****************************************Code Written By Vijendra Saini****************