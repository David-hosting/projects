#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include for string functions
#define CHARS 26

typedef struct _node
{
    char *number;
    //char *name;
    struct _node *node[CHARS];
} Trie;

int HashFunc(char letter);
void insert(Trie *trie, char *key, char *value, int index);
int search(Trie *trie, char *key, char *value, int index);
void initTrieNodes(Trie *trie, int hash);
void freeTrie(Trie *trie, int index);

int main(void)
{
    Trie *trie = malloc(sizeof(Trie));
    if (trie == NULL)
    {
        printf("Not enoght memory to create a trie.");
        return 1;
    }

    trie->number = NULL;
    for(int i = 0; i < CHARS; i++)
        trie->node[i] = NULL;

    insert(trie, "David", "+972-50-4910-999", 0);
    // int res = search(trie, "David", "+972-50-4910-999", 0);
    // printf("%d", res);
    (search(trie, "david", "+972-50-4910-999", 0) == 0) ? printf("Found!\n") : printf("Not Found!\n");
    freeTrie(trie, 0);
}

int search(Trie *trie, char *key, char *value, int index)
{
    int hash = HashFunc(key[index]);
    if (key[index] == '\0')
    {
        if (trie->node[hash] == NULL && trie->number != NULL)
            return (strcmp(trie->number, value) == 0) ? 0 : 1;
        else if (trie->node[hash] == NULL)
            return 1;
    }

    if (trie->node[hash] == NULL)
        return 1;  // Key not found in the trie

    return search(trie->node[hash], key, value, ++index);
}

void initTrieNodes(Trie *trie, int hash)
{
    for(int i = 0; i < CHARS; i++)
        trie->node[hash]->node[i] = NULL;
}

void insert(Trie *trie, char *key, char *value, int index)
{
    if (key[index] == '\0')
    {
        trie->number = malloc(strlen(value) + 1);
        strcpy(trie->number, value);
        return;
    }

    int hash = HashFunc(key[index]);
    if (trie->node[hash] == NULL)
    {
        trie->node[hash] = malloc(sizeof(Trie));
        trie->node[hash]->number = NULL;
        initTrieNodes(trie, hash);
    }

    insert(trie->node[hash], key, value, ++index);
}

int HashFunc(char letter)
{
    // Assuming the outpus are correct.
    return ( letter >= 'a' && letter <= 'z' ) ? (letter % 'a') % CHARS : (letter % 'A') % CHARS;
}

void freeTrie(Trie *trie, int index)
{
    if (index == 25 || trie == NULL)
        return;

    int hash = HashFunc('a' + index);

    // Check if it is the last index
    if (trie->node[hash] != NULL || trie->number != NULL)
    {
        // If trie->node[hash] is a single Trie node
        if (trie->node[hash] != NULL)
        {
            for (int i = 0; i < CHARS; i++)
            {
                if (trie->node[hash]->node[i] != NULL && trie->node[hash]->node[i]->number != NULL)
                    free(trie->node[hash]->node[i]->number);  // Free the memory for the 'number' field
            }

            freeTrie(trie->node[hash], 0);
        }

        free(trie);
        return;
    }

    freeTrie(trie, index + 1);  // Adjusted the recursive call
}

