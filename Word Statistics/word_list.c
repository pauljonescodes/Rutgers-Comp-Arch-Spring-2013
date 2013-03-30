/*
 * word_list.c
 *
 * Paul Jones
 * Professor Brian Russell
 * Computer Architecture (01:198:211)
 * Rutgers University
 *
 * February 13th, 2013
 *
 */

#include "word_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

word_list_node * new_word_list() {
    word_list_node *node = malloc(sizeof(word_list_node));
    node->next = NULL;
    node->case_sensitive_word = NULL;
    return node;
}

word_list_node * new_word_list_node(char * case_sensitive_word) {
    word_list_node *node = new_word_list();
    node->case_sensitive_word = malloc(strlen(case_sensitive_word) + 1);
    node->case_sensitive_word = strcpy(node->case_sensitive_word, case_sensitive_word);
    node->next = NULL;
    return node;
}

word_list_node * add (word_list_node * head, char * case_sensitive_word)
{
    word_list_node *node;
    node = new_word_list_node(case_sensitive_word);
    
    if (head == NULL) {
        head=node;
        head->next=NULL;
    } else {
        node->next=head;
        head=node;
    }
    
    return node;
}


bool word_list_contains (word_list_node * head, char * case_sensitive_word) {
    bool word_list_contains = false;
    
    while (head != NULL) {
        
        if (strcmp(head->case_sensitive_word, case_sensitive_word) == 0) {
            word_list_contains = true;
        }
        
        head = head->next;
    }
    
    return word_list_contains;
}