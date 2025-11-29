#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "inverted_search.h"


/**************************************************************************************************************
 * Function       : is_duplicate_file
 * ----------------------------------------------------------------------------------------------------------------
 * What it does   :
 *      Traverses the filenode linked list and checks if the given filename already exists.
 *
 * Why it’s needed:
 *      Prevents duplicate entries in the file list. Ensures the same file is not indexed twice.
 *
 * Returns        :
 *      FAILURE if filename already exists in the list.
 *      SUCCESS if filename is unique.
 **************************************************************************************************************/
int is_duplicate_file(filenode *head, char *filename)
{
    filenode *temp = head;

    while (temp)                                // Traverse entire linked list
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            return FAILURE;                     // Duplicate found
        }
        temp = temp->link;
    }

    return SUCCESS;                             // No duplicate found
}


/**************************************************************************************************************
 * Function       : check_empty_file
 * ----------------------------------------------------------------------------------------------------------------
 * What it does   :
 *      Opens the file, checks its size using ftell(), and determines if it's empty.
 *
 * Why it’s needed:
 *      Empty files contribute nothing to the database, so skipping them improves efficiency and avoids noise.
 *
 * Returns        :
 *      SUCCESS if file exists and is not empty.
 *      FAILURE if file does not exist or has zero size.
 **************************************************************************************************************/
int check_empty_file(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)                             // Cannot open file
        return FAILURE;

    fseek(fp, 0, SEEK_END);                     // Move to end to measure size

    if (ftell(fp) == 0)                         // File size is zero means empty
    {
        fclose(fp);
        return FAILURE;
    }

    rewind(fp);                                 // Reset pointer for safety
    fclose(fp);
    return SUCCESS;
}


/**************************************************************************************************************
 * Function       : check_file_exists
 * ----------------------------------------------------------------------------------------------------------------
 * What it does   :
 *      Tries to open the file in read mode to verify its existence.
 *
 * Why it’s needed:
 *      Prevents attempting to index files that are not available on disk.
 *
 * Returns        :
 *      SUCCESS if file can be opened.
 *      FAILURE if file does not exist.
 **************************************************************************************************************/
int check_file_exists(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)                             // File open failed
        return FAILURE;

    return SUCCESS;
}


/**************************************************************************************************************
 * Function       : create_file_linked_list
 * ----------------------------------------------------------------------------------------------------------------
 * What it does   :
 *      Creates a linked list of file names from command-line arguments.
 *      Performs three validations for each file:
 *          1. File exists
 *          2. File is not empty
 *          3. File is not a duplicate
 *
 * Why it’s needed:
 *      Builds the initial list of valid files to be indexed. Ensures the database only processes clean,
 *      non-duplicate, non-empty inputs.
 *
 * Returns        :
 *      Pointer to the head of the constructed filenode linked list.
 **************************************************************************************************************/
filenode *create_file_linked_list(int argc, char *argv[])
{
    filenode *head = NULL, *new = NULL, *temp = NULL;

    for (int i = 1; i < argc; i++)                      // Skip argv[0], which is program name
    {
        if (check_file_exists(argv[i]) == FAILURE)      // Validate file existence
        {
            printf("ERROR : Cannot open %s\n", argv[i]);
            continue;
        }

        if (check_empty_file(argv[i]) == FAILURE)       // Validate non-empty file
        {
            printf("Empty File : skipping %s!\n", argv[i]);
            continue;
        }

        if (is_duplicate_file(head, argv[i]) == FAILURE) // Validate uniqueness
        {
            printf("Duplicate File : skipping %s!\n", argv[i]);
            continue;
        }

        // Create a new filenode for the validated file
        new = malloc(sizeof(filenode));
        strcpy(new->filename, argv[i]);
        new->link = NULL;

        // Insert into the linked list
        if (head == NULL)
        {
            head = new;                                  // First node
        }
        else
        {
            temp = head;
            while (temp->link)                           // Traverse to last node
            {
                temp = temp->link;
            }
            temp->link = new;                            // Append new node
        }

        printf("VALID : %s\n", argv[i]);                 // Status message
    }

    return head;                                         // Return head of list
}
