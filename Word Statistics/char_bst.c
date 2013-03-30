/*
 * char_bst.c
 *
 * Paul Jones
 * Professor Brian Russell
 * Computer Architecture (01:198:211)
 * Rutgers University
 *
 * February 13th, 2013
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "char_bst.h"


alph_tree_node * new_char_tree() {
    alph_tree_node *node = malloc(sizeof(alph_tree_node));
    node->left = node->right = NULL;
    return node;
}

alph_tree_node * new_char_tree_node(char c) {
    alph_tree_node *node = new_char_tree();
    node->letter = c;
    node->left = node->right = NULL;
    return node;
}

alph_tree_node * put_char_tree_node(alph_tree_node *node, char c) {
    if(node == NULL){
        return new_char_tree_node(c);
    } else {
        if (c < node->letter) {
            node->left = put_char_tree_node(node->left, c);
            return node;
        } else if (c > node->letter) {
            node->right =  put_char_tree_node(node->right, c);
            return node;
        }
    }
    
    return NULL;
}

alph_tree_node * get_char_tree_node(alph_tree_node *root, char word_first_letter) {
    word_first_letter = tolower(word_first_letter);
    
    while (root->letter != word_first_letter) {
        if (root->letter > word_first_letter) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    return root;
}

alph_tree_node * bld_char_tree(alph_tree_node *root) {
    root->letter = 'p';
    put_char_tree_node(root, 'h');
    put_char_tree_node(root, 't');
    put_char_tree_node(root, 'd');
    put_char_tree_node(root, 'l');
    put_char_tree_node(root, 'r');
    put_char_tree_node(root, 'x');
    put_char_tree_node(root, 'b');
    put_char_tree_node(root, 'f');
    put_char_tree_node(root, 'j');
    put_char_tree_node(root, 'n');
    put_char_tree_node(root, 'q');
    put_char_tree_node(root, 's');
    put_char_tree_node(root, 'v');
    put_char_tree_node(root, 'y');
    put_char_tree_node(root, 'a');
    put_char_tree_node(root, 'c');
    put_char_tree_node(root, 'e');
    put_char_tree_node(root, 'g');
    put_char_tree_node(root, 'i');
    put_char_tree_node(root, 'k');
    put_char_tree_node(root, 'm');
    put_char_tree_node(root, 'o');
    put_char_tree_node(root, 'u');
    put_char_tree_node(root, 'w');
    put_char_tree_node(root, 'z');
    return root;
}