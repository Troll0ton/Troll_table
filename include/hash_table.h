//! @file hash_table.h

#ifndef   HASH_TABLE_H
#define   HASH_TABLE_H

//-----------------------------------------------------------------------------

#include "common.h"
#include "../include/hash_functions.h"

//-----------------------------------------------------------------------------

#define HEAD list->head 

//-----------------------------------------------------------------------------

typedef struct Node
{
   char *line;
   struct Node *next;
} Node;

//-----------------------------------------------------------------------------

typedef struct List
{
    Node *head;
    //uint32_t size;
} List;

//-----------------------------------------------------------------------------

typedef struct Hash_table
{
    List *bucket;
    uint32_t size;
} Hash_table;

//-----------------------------------------------------------------------------

const int num_of_searchs = 300;
const int num_of_hf = 1;
const unsigned int y_len = 20;

//-----------------------------------------------------------------------------

void listDtor (List *list);
unsigned int findListSize (List *list);

void hashTableCtor (Hash_table *hash_table, uint32_t size);
void hashTableDtor (Hash_table *hash_table);

void pushHead (char *line, List *list);
void insertNode (char *line, Hash_table hash_table, unsigned int hash_val);

void searchingAll (Text *text);
void searchingAll256 (Text_256 *text_256, Text *text);

void fillHashTable (char **buffer, 
                    unsigned int size,
                    Hash_table hash_table, 
                    uint32_t (*calc_hash)(char *line),
                    int (*comp_funct)(const char *s1, const char *s2));

Node *searchLine (char *line,     
                  Hash_table hash_table, 
                  unsigned int hash_val, 
                  int (*comp_funct)(const char *s1, const char *s2));

int strcmpAvx (const char *s1, const char *s2);

void compareHashFunctions (Text *text);
void drawOneFunctionGraph (Text *text, uint32_t (*calc_hash)(char *line), FILE *graph);
void fillInDataGraph (Hash_table hash_table, FILE *graph);

void hashTableDump (Hash_table hash_table);

//-----------------------------------------------------------------------------

#endif //HASH_TABLE_H