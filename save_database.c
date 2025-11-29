/*****************************************************************************************************
 * Function       : save_database
 * ---------------------------------------------------------------------------------------------------
 * What it does   :
 *      Writes the entire inverted index (hash table) into a backup text file called "backup.txt".
 *      Each hash bucket is written with a bucket marker (#index;), followed by every word stored
 *      inside that bucket and all corresponding file entries (subnodes).
 *
 * Why it’s needed:
 *      Allows persistent storage of the database so it can be reloaded later using the update
 *      functionality. This preserves word-file mappings across program executions.
 *
 * Format stored  :
 *      #bucket_index;
 *      word; file_count; filename; word_count; filename; word_count;  #
 *
 * Returns        :
 *      Nothing. Writes data directly to backup.txt.
 *****************************************************************************************************/
#include "inverted_search.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>


void save_database(hashtable *table)
{
    FILE *fp = fopen("backup.txt","w");      // Open backup file in write mode
    {
        if(fp == NULL)                       // Check for file open failure
        {
            printf("ERROR : Couldn't open the file");
        }
    }

    for(int i=0 ; i<27 ; i++)                // Loop through all hash table buckets
    {
        mainnode *m = table[i].link;         // Pointer to first word in this bucket
        if((m) == NULL)                      // Skip empty buckets
        {
            continue;
        }

        fprintf(fp, "#%d;\n", i);            // Write bucket marker

        while((m) != NULL)                   // Traverse each mainnode (word)
        {  
            fprintf(fp,"%s; %d;",            // Write word and file count
                    m->word,
                    m->file_count);         
                    
            subnode *s = m->sublink;         // Pointer to first file entry

            while(s != NULL)                 // Traverse subnodes (file details)
            {
                fprintf(fp," %s; %d;",       // Write file name and occurrence count
                        s->file_name,
                        s->word_count);
                s = s->sub_sublink;          // Move to next subnode
            }

            fprintf(fp," #\n");              // End marker for this word
            m = m->main_next_link;           // Move to next word in this bucket
        }
   }

   printf("Saved Successfully in backup.txt\n");  // Status update
   fclose(fp);                                    // Close the file

}
