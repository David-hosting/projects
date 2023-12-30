#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef struct node node;

typedef struct node
{
    int value;
    node *p;
} Node;

typedef Node *lList;


void addItem(int n, lList *lst);
void removeItem(int n);
void print(lList lst);
bool isEqual(lList lst);

/*const int SPACE = 10;*/

unsigned int lListLen = 1;

int main(void)
{
    lList lst = malloc(lListLen * sizeof(Node));
    if (lst == NULL)
    {
        return 1;
    }
    addItem(8, &lst);
    addItem(8, &lst);
    addItem(16, &lst);
    addItem(0, &lst);

    print(lst);
    bool res = isEqual(lst);
    (res) ? printf("Equal\n") : printf("Not Equal\n");
    free(lst);
    return 0;
}

void print(lList lst)
{
    node *curr = lst;  // Corrected line

    while(curr != NULL)
    {
        printf("%i->", (*curr).value);
        curr = (*curr).p;
    }
    printf("NULL\n");
}

void addItem(int n, lList *lst)
{
    // Reallocate memory for one more node
    *lst = realloc(*lst, (lListLen + 1) * sizeof(Node));

    // Update pointers and add a new node at the end
    (*(*lst + lListLen - 1)).p = NULL;
    (*(*lst + lListLen)).p = NULL;
    (*(*lst + lListLen - 1)).value = n;

    // Update the last node's pointer to point to the new node
    if (lListLen > 1) {
        node *curr = *lst;
        while (curr->p != NULL) {
            curr = curr->p;
        }
        curr->p = &(*(*lst + lListLen - 1));
    }

    lListLen++;
}

bool isEqual(lList lst)
{
    node *curr = lst;
    int sumL = 0, sumR = 0;
    int tmpLen = lListLen;
    int halfL = tmpLen / 2;
    int halfR = tmpLen;
    for(int i = 0; i < halfL; i++)
    {
        sumL += (*curr).value;
        curr = (*curr).p;
    }

    for(int i = halfL; i < halfR - 1; i++)
    {
        sumR += (*curr).value;
        curr = (*curr).p;
    }

    return (sumL == sumR) ? true : false;
}
