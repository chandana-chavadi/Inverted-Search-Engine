/*****************************************************************************************************
 * Function       : search_database
 * ---------------------------------------------------------------------------------------------------
 * What it does   :
 *      Searches for a specific word inside the hash table and prints all file details associated
 *      with that word. It locates the correct hash bucket, finds the mainnode for the word, and
 *      then displays all subnodes (filenames + word counts).
 *
 * Why it’s needed:
 *      Enables end-users to query the inverted index and retrieve file-level information about any
 *      word that was indexed. This is one of the core functionalities of inverted search.
 *
 * Workflow       :
 *      1. Validate input word.
 *      2. Compute hash index.
 *      3. Search mainnode in corresponding bucket.
 *      4. If found, display file counts and per-file frequency details.
 *
 * Returns        :
 *      Nothing. Prints directly to console.
 *****************************************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "inverted_search.h"

void search_database(hashtable *table, const char *word)
{
    if (word == NULL || word[0] == '\0')               // Validate if user entered a non-empty word
    {
        printf("Please Provide a valid word !\n");
        return;
    }

    int index = get_index(word);                       // Compute hash index for the word
    if (index < 0 || index > 26)                       // Safety check (should not fail)
    {
        return;
    }

    // Look for the word in the corresponding bucket
    mainnode *m = search_mainnode(table[index].link, (char *)word);
    if (m == NULL)                                     // Word not found
    {
        printf("Word %s is not present in database.\n", word);
        return;
    }

    // Print the word summary (bucket index, word, file count)
    printf("[%-2d]   %-20s %-10d",
           table[index].index,
           m->word,
           m->file_count);

    // Print all file entries (subnodes) for this word
    subnode *s = m->sublink;
    while (s)
    {
        printf(" | File:%-15s : %d",
               s->file_name,
               s->word_count);
        s = s->sub_sublink;                            // Move to next file entry
    }

    printf("\n");                                      // Final newline for clean output
}
