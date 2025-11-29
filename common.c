#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "inverted_search.h"


/* =========================================================================================
 * Function: init_hashtable
 * -----------------------------------------------------------------------------------------
 * What it does:
 *     Initializes the hash table with 27 buckets (indices 0–25 for 'a'–'z', index 26 for
 *     non-alphabetic words). Each bucket starts with a NULL linked list.
 *
 * Why it’s required:
 *     Establishes a clean baseline data structure so the inverted index can store and
 *     categorize incoming words efficiently. Without this initialization, the indexing
 *     workflow would collapse.
 *
 * Returns:
 *     Nothing.
 * ========================================================================================= */
void init_hashtable(hashtable *table)
{
    for (int i = 0; i < 27; i++)
    {
        table[i].index = i;
        table[i].link = NULL;
    }
}


/* =========================================================================================
 * Function: get_index
 * -----------------------------------------------------------------------------------------
 * What it does:
 *     Determines the hash table index for a given word. Alphabetic words are mapped to
 *     0–25 based on their first letter. Any word starting with a non-alphabetic character
 *     is sent to index 26.
 *
 * Why it’s required:
 *     Provides deterministic placement of words into the appropriate bucket so operations
 *     like search and insert remain efficient.
 *
 * Returns:
 *     Integer index (0–26) indicating the bucket in which the word belongs.
 * ========================================================================================= */
int get_index(const char *word)
{
    if(isalpha(word[0]))
        return tolower(word[0]) - 'a';
    return 26;
}


/* =========================================================================================
 * Function: create_mainnode
 * -----------------------------------------------------------------------------------------
 * What it does:
 *     Allocates memory and initializes a mainnode structure that represents a unique word
 *     in the inverted index. Sets its counters and links to default values.
 *
 * Why it’s required:
 *     Every distinct word in the dataset needs a dedicated node to track all file-related
 *     information. This function ensures consistent creation and initialization of such
 *     nodes.
 *
 * Returns:
 *     Pointer to the newly allocated mainnode.
 *     Returns FAILURE (your macro) if memory allocation fails.
 * ========================================================================================= */
mainnode* create_mainnode(char *word)
{
    mainnode *new = malloc(sizeof(mainnode));
    if(new == NULL)
    {
        printf("ERROR: Couldn't allocate mainnode\n");
        return FAILURE;
    }

    strcpy(new->word, word);
    new->file_count = 0;
    new->sublink = NULL;
    new->main_next_link = NULL;

    return new;
}


/* =========================================================================================
 * Function: create_subnode
 * -----------------------------------------------------------------------------------------
 * What it does:
 *     Allocates memory and initializes a subnode structure representing a file in which
 *     the word appears. Sets default word count and link pointer.
 *
 * Why it’s required:
 *     Allows tracking of how many times a word appears in a particular file and supports
 *     the multi-file nature of the inverted index.
 *
 * Returns:
 *     Pointer to the newly created subnode.
 *     Returns FAILURE if memory allocation fails.
 * ========================================================================================= */
subnode* create_subnode(char *filename)
{
    subnode *new = malloc(sizeof(subnode));
    if(new == NULL)
    {
        printf("ERROR: Couldn't allocate subnode\n");
        return FAILURE;
    }

    strcpy(new->file_name, filename);
    new->word_count = 1;
    new->sub_sublink = NULL;

    return new;
}


/* =========================================================================================
 * Function: search_mainnode
 * -----------------------------------------------------------------------------------------
 * What it does:
 *     Traverses the linked list of mainnodes (words) in a hash bucket and finds the node
 *     corresponding to the given word.
 *
 * Why it’s required:
 *     Prevents the creation of duplicate word entries and enables efficient lookup during
 *     insertion or display operations.
 *
 * Returns:
 *     Pointer to the matching mainnode if found.
 *     Returns NULL if the word does not exist in the list.
 * ========================================================================================= */
mainnode* search_mainnode(mainnode *head, char *word)
{
    while (head)
    {
        if (strcmp(head->word, word) == 0)
            return head;
        head = head->main_next_link;
    }
    return NULL;
}


/* =========================================================================================
 * Function: insert_subnode
 * -----------------------------------------------------------------------------------------
 * What it does:
 *     Checks if the word already appears in the given file. If yes, increments word count.
 *     If not, creates a new subnode and links it into the subnode list of the mainnode.
 *
 * Why it’s required:
 *     Maintains accurate per-file word counts and ensures that each file is tracked exactly
 *     once under a specific word.
 *
 * Returns:
 *     Nothing.
 * ========================================================================================= */
void insert_subnode(mainnode *mnode, char *filename)
{
    subnode *temp = mnode->sublink;

    while (temp)
    {
        if (strcmp(temp->file_name, filename) == 0)
        {
            temp->word_count++;
            return;
        }
        temp = temp->sub_sublink;
    }

    subnode *new = create_subnode(filename);

    new->sub_sublink = mnode->sublink;
    mnode->sublink = new;
    mnode->file_count++;
}


/* =========================================================================================
 * Function: insert_word
 * -----------------------------------------------------------------------------------------
 * What it does:
 *     High-level control function that inserts a word from a specific file into the hash
 *     table. Locates or creates its mainnode, then adds or updates its subnode.
 *
 * Why it’s required:
 *     Orchestrates the full insertion flow and maintains the integrity of the inverted
 *     index by ensuring proper separation of concerns (hashing, node creation, linking).
 *
 * Returns:
 *     Nothing.
 * ========================================================================================= */
void insert_word(hashtable *table, char *word, char *filename)
{
    int index = get_index(word);

    mainnode *mnode = search_mainnode(table[index].link, word);

    if (mnode == NULL)
    {
        mnode = create_mainnode(word);

        mnode->main_next_link = table[index].link;
        table[index].link = mnode;
    }

    insert_subnode(mnode, filename);
}
