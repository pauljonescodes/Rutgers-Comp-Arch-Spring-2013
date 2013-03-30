/*
 * word_bst.h
 *
 * Paul Jones
 * Professor Brian Russell
 * Computer Architecture (01:198:211)
 * Rutgers University
 *
 * February 13th, 2013
 *
 */

/* BST which holds a word as a string and points
 * to another node to the left and right. */

typedef struct word_tree_node {
    /* to be stored in all lowercase */
    char *case_insensitive_word;
    
    /* number of total instances of this word, regardless of case */
    int total_instances;
    
    /* to make this a tree */
    struct word_tree_node *left, *right;
    
    /* number of unique variations on capitalization,
     * also length of case_sensitive_list */
    int cases_instances;
    
    /* list of varitions on the case_insensitive_word */
    struct word_list_node *case_sensitive_list;
} word_tree_node;

/* Imitates object oriented new method for the word_tree struct */
word_tree_node * new_word_tree();

/* This mallocs a word tree with any given string */
word_tree_node * new_word_tree_node(char * word);

/* This puts a word into a word tree passed and returns the tree */
word_tree_node * put_word_tree_node(word_tree_node *root, char * case_insensitive_word);

/* This gets a word into a word tree passed and returns the tree */
word_tree_node * get_word_tree_node(word_tree_node *root, char * case_insensitive_word);