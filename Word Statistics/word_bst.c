/*
 * word_bst.c
 *
 * Paul Jones
 * Professor Brian Russell
 * Computer Architecture (01:198:211)
 * Rutgers University
 *
 * February 13th, 2013
 *
 */


#include "word_bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

word_tree_node * new_word_tree() {
    word_tree_node *node = malloc(sizeof(word_tree_node));
    node->left = node->right = NULL;
    return node;
}

word_tree_node * new_word_tree_node(char * word){
    word_tree_node *node = new_word_tree();
    node->case_insensitive_word = malloc(strlen(word) + 1);
    node->case_insensitive_word = strcpy(node->case_insensitive_word, word);
    node->left = node->right = NULL;
    node->total_instances = 1;
    return node;
}

word_tree_node * put_word_tree_node(word_tree_node *node, char * case_insensitive_word){
    if(node == NULL){
        return new_word_tree_node(case_insensitive_word);
    } else {
        if (0 > strcasecmp(case_insensitive_word, node->case_insensitive_word)) {
            node->left = put_word_tree_node(node->left, case_insensitive_word);
            return node;
        } else if (0 < strcasecmp(case_insensitive_word, node->case_insensitive_word)) {
            node->right =  put_word_tree_node(node->right, case_insensitive_word);
            return node;
        } else {
            node->total_instances++;
            return node;
        }
    }
}

word_tree_node * get_word_tree_node(word_tree_node * root, char * word) {
    while (strcasecmp(root->case_insensitive_word, word) != 0) {
        if (0 > strcasecmp(word, root->case_insensitive_word)) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    return root;
}
