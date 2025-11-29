/*****************************************************************************************************
 * Function       : update_database
 * ---------------------------------------------------------------------------------------------------
 * What it does   :
 *      Reconstructs the hash table by reading previously saved data from "backup.txt". Each bucket
 *      index, word, file count, and associated file details (subnodes) are parsed and loaded back
 *      into the in-memory data structure.
 *
 * Why it’s needed:
 *      Enables persistent storage and later restoration of the inverted index. Without this routine,
 *      the database would be lost between executions.
 *
 * Input Format (backup.txt):
 *      #index; word; file_count;
 *         file_name; word_count;
 *         file_name; word_count;
 *      #
 *
 * Returns:
 *      Nothing. Constructs hash table directly.
 *****************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "inverted_search.h"

void update_database(hashtable *table)
{
    FILE *fp = fopen("backup.txt", "r");        // Open saved database file
    if (fp == NULL)
    {
        printf("ERROR: backup.txt not found!\n");
        return;
    }

    init_hashtable(table);                      // Reset table before loading

    int index;
    char word[50];
    int file_count;

    // Read "#index; word; file_count;"
    while (fscanf(fp, "#%d; %[^;]; %d;", &index, word, &file_count) == 3)
    {
        mainnode *m = create_mainnode(word);    // Create word node
        m->file_count = file_count;             // Set number of files for this word

        // Insert mainnode into bucket at head
        m->main_next_link = table[index].link;
        table[index].link = m;

        char file_name[100];
        int word_count;

        // Read 'file_count' number of "file_name; word_count;" entries
        for (int i = 0; i < file_count; i++)
        {
            if (fscanf(fp, " %[^;]; %d;", file_name, &word_count) != 2)
                break;

            subnode *s = create_subnode(file_name);  // Create file entry node
            s->word_count = word_count;             // Assign stored count

            s->sub_sublink = m->sublink;            // Insert at head of subnode list
            m->sublink = s;
        }

        fscanf(fp, " #\n");                         // Consume trailing '#'
    }

    fclose(fp);                                     // Close backup file
    printf("Database updated from backup.txt successfully!\n");
}
