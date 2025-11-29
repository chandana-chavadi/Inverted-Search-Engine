/***************************************************************************************************************************************************
* Function       : display_database
* --------------------------------------------------------------------------------------------------------------------------------------------------
* What it does   :
*       Prints the entire inverted index in a structured tabular format. It walks through all 27 hash table
*       indices and displays each word, the number of files it appears in, and detailed per-file occurrence counts.
*
* Why it’s needed:
*       Provides a complete visualization of the database, making it easier to debug, verify, and understand
*       the indexed output. Also ensures user-friendly readability of the inverted search structure.
*
* Workflow       :
*       1. Print table headers.
*       2. Loop through all hash indices.
*       3. For each mainnode (word):
*               - Print its index, word, and file count.
*               - Print all subnodes (files) where the word appears and how many times.
*       4. If all buckets were empty, display "Database is empty!".
*
* Returns        :
*       Nothing. Only prints output to console.
****************************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "inverted_search.h"

void display_database(hashtable *table)
{
    printf("--------------------------->> DATABASE <<----------------------------\n");
    printf("---------------------------------------------------------------------\n");
    printf("Index   Word         File Count          File Details\n");
    printf("---------------------------------------------------------------------\n");

    int empty = 1;                                      // Track whether any data exists

    for (int i = 0; i < 27; i++)                        // Loop through all hash buckets
    {
        mainnode *temp1 = table[i].link;                // Points to the word list in current bucket

        if (temp1 == NULL)                              // If bucket empty, skip
            continue;

        empty = 0;                                      // At least one entry exists

        while (temp1 != NULL)                           // Traverse each mainnode (each word)
        {
            subnode *temp2 = temp1->sublink;            // First subnode for this word

            // Print primary row for the word (first file only)
            printf("[%-2d]   %-20s %-10d",
                   table[i].index,                      // Index (0-26)
                   temp1->word,                         // The word
                   temp1->file_count);                  // Number of files containing this word

            if (temp2)                                  // If at least one file entry exists
            {
                printf(" | File:%-15s : %d\n",
                       temp2->file_name,                // File name
                       temp2->word_count);              // Count in that file
                temp2 = temp2->sub_sublink;             // Move to next subnode
            }
            else
            {
                printf("\n");                           // No subnodes, end row
            }

            // Print additional file entries for same word
            while (temp2 != NULL)
            {
                printf("       %-20s %-10s | File:%-15s : %d\n",
                       "",                              // Indentation placeholders
                       "",
                       temp2->file_name,                // File name
                       temp2->word_count);              // Word count in that file

                temp2 = temp2->sub_sublink;             // Move to next file
            }

            printf("\n");                               // Blank line between words
            temp1 = temp1->main_next_link;              // Move to next word in the bucket
        }
    }

    if (empty)
        printf("Database is empty!\n");

    printf("---------------------------------------------------------------------\n");
}
