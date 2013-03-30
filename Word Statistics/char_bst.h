/*
 * char_bst.h
 *
 * Paul Jones
 * Professor Brian Russell
 * Computer Architecture (01:198:211)
 * Rutgers University
 *
 * February 13th, 2013
 *
 */


/* BST which olds a character and points to another
 * node to the left and right. */
typedef struct char_tree_node {
    /* [a-z] to be stored lowercase */
    char letter;
    
    /* to make this a search tree */
    struct char_tree_node *left, *right;
    
    /* case insensitive tree of words starting
     * with this node's character */
    struct word_tree_node *words;
} alph_tree_node;

/* This imitates object oriented new [ObjectName]() methods. */
alph_tree_node * new_char_tree();

/* Returns a node with the character passed. */
alph_tree_node * new_char_tree_node(char c);

/* Puts a node with character `c` in tree `root` */
alph_tree_node * put_char_tree_node(alph_tree_node *tree, char c);

/* This returns the node for any given character [a-z] */
alph_tree_node * get_char_tree_node(alph_tree_node *tree, char word_first_letter);

/* This is a method that gets put_char_node all chars [a-z] */
alph_tree_node * bld_char_tree(alph_tree_node *tree);
