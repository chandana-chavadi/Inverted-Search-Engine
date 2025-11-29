# Inverted-Search-Engine
A modular C project that builds an inverted index from multiple text files, allowing fast search of words and the files in which they appear.

---

## 🧠 Overview  
The project creates a miniature search engine using an inverted index data structure:
WORD → [List of files containing the word + occurrences in each file]

Implementation uses:
- A **linked list of filenames**
- A **27-bucket hash table** (a–z + non-alphabet bucket)  
- **mainnode** for each unique word  
- **subnode** for its file-wise details  

The system reads words from multiple `.txt` files, builds a searchable index, and allows displaying, searching, saving, and restoring the entire database.

---

## ✨ Features  

### 1️⃣ Create Database  
Reads all provided text files, extracts words, and inserts them into the hash table.  
Words are stored as mainnodes, and each file–occurrence pair is stored as subnodes.  

### 2️⃣ Display Database  
Shows the inverted index in a clean, formatted table with:
- Word  
- Number of files  
- File names + frequency  

### 3️⃣ Search a Word  
Searches for a word and prints:
- Hash index  
- Total file count  
- File-wise word occurrences  

### 4️⃣ Save Database  
Saves the entire structure to **backup.txt** in a structured format:  
#index;
word; file_count; filename; count; filename; count; #

### 5️⃣ Update Database  
Rebuilds the database from **backup.txt**, reconstructing all mainnodes and subnodes.  

### 6️⃣ Validation  
- Checks `.txt` extension  
- Checks file existence  
- Checks non-empty  
- Avoids duplicates  

---

## 🧩 Concepts & Technologies Used  
- Hashing (27-bucket hash table)  
- Single & double linked lists  
- String tokenization  
- File handling  
- Dynamic memory allocation  
- Word indexing  
- Modular C design  
- Persistent storage (backup.txt)  

---

## 💡 Future Scope  
- Add stop-word removal  
- Add case-insensitive search  
- Support binary search trees instead of linked lists  
- Add partial-word search (prefix search)  
- Export index to JSON  
- Add colored CLI UI for readability  

---

## 📌 Conclusion  
This project demonstrates strong fundamentals in data structures, hashing, modular C design, text processing, and file-based persistence. It simulates the core architecture behind real search engines and indexing systems.




