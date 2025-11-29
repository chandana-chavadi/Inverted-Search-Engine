/***************************************************************************************************************************************************
* PROJECT DESCRIPTION
* ----------------------------------------------------------------------------------------------------------------
*  PROJECT NAME : INVERTED SEARCH ENGINE
*
*  PURPOSE :
*      The project builds a miniature search engine using the concept of an **Inverted Index**, which maps:
*
*          WORD  --->  LIST OF FILES IN WHICH THE WORD APPEARS + COUNT IN EACH FILE
*
*  DATA STRUCTURE SUMMARY :
*      filenode   - Linked list storing valid .txt file names.
*      hashtable  - 27 buckets (a–z + non-alphabet bucket).
*      mainnode   - Stores unique word + count of files containing that word.
*      subnode    - Stores filename + how many times word appears in that file.
*
*  FEATURES :
*      1. Create Database       – Reads words from files and builds inverted index.
*      2. Display Database      – Prints in formatted table style.
*      3. Search a Word         – Shows all files containing the word.
*      4. Save Database         – Saves entire structure to "backup.txt".
*      5. Update Database       – Rebuilds DB from backup.txt.
*      6. Exit
*
*  FILE STRUCTURE :
*      main.c                  → Menu + driver
*      create_database.c       → Reads files & builds DB
*      createSLL.c             → Builds linked list of files
*      display_output.c        → Prints DB
*      search.c                → Searches a word
*      save.c                  → Saves DB to file
*      update.c                → Loads DB from file
*      validate.c              → Validates arguments
*      inverted_search.h       → Structures + prototypes
*
* Name          : C Chandana
* Date          : 22/11/2025
****************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "inverted_search.h"

#define SIZE 27


/*****************************************************************************************************
 * Function       : main
 * ---------------------------------------------------------------------------------------------------
 * What it does   :
 *      Acts as the driver for the entire inverted search system. It:
 *          - Validates command-line arguments
 *          - Creates the file linked list
 *          - Initializes the hash table
 *          - Shows menu options repeatedly
 *          - Calls respective modules based on user choice
 *
 * Why it’s needed:
 *      Coordinates all modules and provides user interaction via menu-driven approach.
 *
 * Returns:
 *      0 on successful termination.
 *****************************************************************************************************/
int main(int argc, char *argv[])
{
    filenode *head = NULL;              // Head for linked list of file names
    hashtable table[27];                // Hash table with 27 buckets
    int choice;                         // Menu choice
    int db_flag = 0;                    // Indicates if DB is created or loaded
    int created_flag = 0;               // Prevents double creation
    int updated_flag = 0;               // Prevents update → create conflicts

    // Validate command-line arguments and create file list
    if (validate(argc, argv) == SUCCESS)
    {
        head = create_file_linked_list(argc, argv);
        if (head == NULL)
        {
            printf("No valid files to process.\n");
            return 0;
        }
    }
    else
    {
        printf("ERROR : Validation failed.\n");
        return 0;
    }

    init_hashtable(table);              // Initialize hash table before any operation

    // -------------------------- MENU LOOP --------------------------
    do
    {
        printf("\n");
        printf("\n-----------------------------------------\n");
        printf("            INVERTED SEARCH MENU           ");
        printf("\n-----------------------------------------\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search a Word\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("\n-----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // ---------------- CREATE DATABASE ----------------
            case 1:
                if (created_flag == 1)
                {
                    printf("ERROR : Database already created. Cannot create again!\n");
                    break;
                }
                if (updated_flag == 1 && created_flag == 1)
                {
                    printf("ERROR : Cannot Create again!\n");
                    break;
                }
                create_database(table, head);   // Build inverted index
                db_flag = 1;
                created_flag = 1;
                break;

            // ---------------- DISPLAY DATABASE ----------------
            case 2:
                if (db_flag)
                    display_database(table);
                else
                    printf("Please create the database first!\n");
                break;

            // ---------------- SEARCH A WORD ----------------
            case 3:
                if (db_flag)
                {
                    char word[50];
                    printf("Enter the word to search: ");
                    scanf("%49s", word);
                    search_database(table, word);
                }
                else
                    printf("Please create the database first!\n");
                break;

            // ---------------- SAVE DATABASE ----------------
            case 4:
                if (db_flag)
                {
                    save_database(table);
                }
                else
                    printf("Please create the database first!\n");
                break;

            // ---------------- UPDATE DATABASE ----------------
            case 5:
                if(updated_flag == 1)
                {
                    printf("ERROR: Database already updated once. Cannot update again!\n");
                    break;
                }
                if(created_flag == 1)
                {
                    printf("ERROR : Cannot Create after update!\n");
                    break;
                }
                
                update_database(table);         // Reload from backup.txt
                db_flag = 1;
                updated_flag = 1;
                printf("Database updated successfully.\n");
                break;

            // ---------------- EXIT ----------------
            case 6:
                printf("Exiting program...\n");
                break;

            // ---------------- INVALID OPTION ----------------
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);              // Loop until user selects exit

    return 0;
}
