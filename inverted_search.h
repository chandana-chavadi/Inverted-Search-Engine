#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#define SUCCESS 1     // Indicates successful operation
#define FAILURE 0     // Indicates failed operation


// Node storing a single file name in a linked list of files
typedef struct filenode
{
    char filename[100];         // File name
    struct filenode *link;      // Pointer to next file
} filenode;


// One bucket of the hash table (0–26)
typedef struct hashtable
{
    int index;                  // Bucket index
    struct mainnode *link;      // Pointer to first word in this bucket
} hashtable;


// Stores a unique word and the list of files containing it
typedef struct mainnode
{
    char word[30];              // The word being indexed
    int file_count;             // Number of files containing this word
    struct subnode *sublink;    // Linked list of file details
    struct mainnode *main_next_link;   // Next word in same hash bucket
} mainnode;


// Stores file-specific details for a word
typedef struct subnode
{
    char file_name[100];        // Name of file
    int word_count;             // Number of occurrences in that file
    struct subnode *sub_sublink; // Next file entry for same word
} subnode;


// Initializes all 27 hash table buckets
void init_hashtable(hashtable *table);

// Computes hash index for a word based on first character
int get_index(const char *word);

// Searches for a word in a linked list of mainnodes
mainnode* search_mainnode(mainnode *head, char *word);

// Creates a new mainnode for a word
mainnode* create_mainnode(char *word);

// Creates a new subnode for a filename
subnode* create_subnode(char *filename);

// Inserts or updates a subnode under a mainnode
void insert_subnode(mainnode *mnode, char *filename);

// Inserts a word (creates/updates nodes)
void insert_word(hashtable *table, char *word, char *filename);

// Validates command-line arguments
int validate(int argc, char *argv[]);

// Creates linked list of validated files
filenode* create_file_linked_list(int argc, char *argv[]);

// Checks if file has .txt extension
int check_txt_file(const char *filename);

// Checks for duplicate filenames
int is_duplicate_file(filenode *head, char *filename);

// Checks whether a file exists on disk
int check_file_exists(char *filename);

// Builds the database by reading all files
void create_database(hashtable *table, filenode *head);

// Prints all words and file details
void display_database(hashtable *table);

// Saves entire database to file
void save_database(hashtable *table);

// Searches for a word in the database
void search_database(hashtable *table, const char *word);

// Updates an existing database by adding more files
void update_database(hashtable *table);

#endif
