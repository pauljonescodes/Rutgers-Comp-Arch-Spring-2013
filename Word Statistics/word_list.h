/*
 * word_list.h
 *
 * Paul Jones
 * Professor Brian Russell
 * Computer Architecture (01:198:211)
 * Rutgers University
 *
 * February 13th, 2013
 *
 */

#include <stdbool.h>

/* Holds a case sensitive word
 * and points to another one. Linked list. */
typedef struct word_list_node {
    /* to be stored as it's found */
    char *case_sensitive_word;
    
    /* this is linked list */
    struct word_list_node *next;
} word_list_node;

/* This imitates object oriented new [ObjectName]() methods. */
word_list_node * new_word_list();
word_list_node * new_word_list_node(char * case_sensitive_word);
bool word_list_contains (word_list_node * head, char * case_sensitive_word);
word_list_node * add (word_list_node * head, char * case_sensitive_word);