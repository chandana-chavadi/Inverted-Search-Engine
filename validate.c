/*****************************************************************************************************
 * Function       : check_txt_file
 * ---------------------------------------------------------------------------------------------------
 * What it does   :
 *      Checks whether the given filename ends with the ".txt" extension.
 *
 * Why it’s needed:
 *      Ensures only text files are accepted for building the inverted index. Prevents processing
 *      of unsupported file types.
 *
 * Returns:
 *      SUCCESS if file has a .txt extension.
 *      FAILURE otherwise (and prints an error).
 *****************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "inverted_search.h"

int check_txt_file(const char *filename)
{
    const char *ext = strrchr(filename, '.');        // Find last dot in filename
    if (!ext || strcmp(ext, ".txt") != 0)            // Check extension validity
    {
        printf("ERROR : %s is not a .txt file!\n", filename);
        return FAILURE;
    }
    return SUCCESS;
}


/*****************************************************************************************************
 * Function       : validate
 * ---------------------------------------------------------------------------------------------------
 * What it does   :
 *      Validates command-line arguments. Ensures that filenames are provided and that each one is
 *      a valid .txt file.
 *
 * Why it’s needed:
 *      Prevents invalid inputs from entering the workflow early, reducing runtime errors during
 *      file creation, scanning, and indexing.
 *
 * Returns:
 *      SUCCESS if arguments are valid.
 *      FAILURE if no files or invalid extensions are provided.
 *****************************************************************************************************/
int validate(int argc, char *argv[])
{
    if (argc < 1)                                     // Check if files were passed
    {
        printf("ERROR : No files provided!\n");
        printf("USAGE : ./a.out file1.txt file2.txt ...\n");
        return FAILURE;
    }

    for (int i = 1; i < argc; i++)                    // Validate each file extension
    {
        if (check_txt_file(argv[i]) == FAILURE)
        {
            continue;                                 // Skip invalid file
        }
    }

    return SUCCESS;                                   // All good
}






   
