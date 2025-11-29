/***************************************************************************************************************************************************
* Function       : create_database
* --------------------------------------------------------------------------------------------------------------------------------------------------
* What it does   :
*       Iterates through the list of files (provided via the filenode linked list), opens each file, reads every
*       word inside it, and inserts those words into the hash table by calling insert_word(). This is the core
*       routine that builds the entire inverted index from scratch.
*
* Why it’s needed:
*       This function performs the initial full indexing operation. Without this step, the hash table remains empty
*       and no search or update operation can function. It converts raw file content into structured searchable data.
*
* Workflow       :
*       1. Traverse the file list beginning at 'head'.
*       2. For each file:
*              - Attempt to open it.
*              - If opening fails, skip to next file.
*              - Extract words using fscanf().
*              - Pass each word to insert_word() for hashing and node handling.
*       3. Close each file after processing.
*       4. Continue until all files are indexed.
*
* Returns        :
*       Nothing. All updates happen directly on the passed hash table.
***************************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "inverted_search.h"

void create_database(hashtable *table, filenode *head)
{
    filenode *temp = head;           // Start from the first file in the filenode list
    char word[50];                   // Buffer to store each extracted word

    while (temp != NULL)             // Loop through all files in the linked list
    {
        FILE *fp = fopen(temp->filename, "r");   // Open the current file in read mode
        if (fp == NULL)                           // If file cannot be opened
        {
            printf("ERROR : Cannot open the file !\n");
            temp = temp->link;                    // Move to next file
            continue;                             // Skip processing this file
        }

        // Read each word until EOF, max 49 chars per word
        while (fscanf(fp, "%49s", word) != EOF)
        {
            // Insert extracted word into the inverted index
            insert_word(table, word, temp->filename);
        }

        fclose(fp);                    // Close current file after processing all words
        temp = temp->link;             // Move to the next file in the list
    }

    printf("Database created Successfully!\n");   // Final confirmation message
}
