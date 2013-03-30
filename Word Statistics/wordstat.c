/*
 * wordstat.c
 *
 * Paul Jones
 * Professor Brian Russell
 * Computer Architecture (01:198:211)
 * Rutgers University
 *
 * February 13th, 2013
 *
 */

#include "wordstat.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "char_bst.h"
#include "word_bst.h"
#include "word_list.h"
#include "file_functions.h"

void print_word_list(word_list_node * node);
void print_word_tree(word_tree_node * node);
void print_alph_tree(alph_tree_node * node);
char * strtolower(char *str);

int main (int argc, char **argv) {
    int i = 0;
    for (; i < argc; i++) {
        char const *option =  argv[i];
        
        if (option[0] == '-') {
            switch (option[1])
            {
                case 'h': 
                    printf("This program finds all the unique words a file (whose path is passed as an argument), prints them in lexicographical order along with the total number of times each word appears (case-insensitive) and a count of different case-sensitive versions of the word. \n\nUse the following interface: \n\nwordstat <argument>\n\nwhere <argument> is either the name of the file that wordstat should process, or -h, which prints this menu. \n\n");
                    return 0;
                    break;
                default: 
                    printf("flag not recognized %s", option);
                    return 1;
                    break;
            }
        }
        else if (i == 1) {
            if (file_exists(option)) {
                print_word_stats(option);
            } else {
                printf("This file, %s, does not exist.\n", option);
                return 1;
            }
        }
    }
    
    return 0;
}


void print_word_stats (const char * filename) {
    
    FILE *f = fopen (filename, "r");
    
    char word[128] = "";
    char c;
    size_t count = 0;
    bool started = false;
    
    alph_tree_node *root;
    
    root = new_char_tree();
    root = bld_char_tree(root);
    
    while ((c = fgetc(f)) != EOF) {
        
        if (started) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
                word[count] = c;
                count++;
            } else {
                
                get_char_tree_node(root, word[0])->words = put_word_tree_node(get_char_tree_node(root, word[0])->words, word);
                
                if (!word_list_contains(get_word_tree_node(get_char_tree_node(root, word[0])->words, word)->case_sensitive_list, word)) {
                    get_word_tree_node(get_char_tree_node(root, word[0])->words, word)->case_sensitive_list = add(get_word_tree_node(get_char_tree_node(root, word[0])->words, word)->case_sensitive_list, word);
                    get_word_tree_node(get_char_tree_node(root, word[0])->words, word)->cases_instances++;
                }
                
                memset(word, 0, count);
                count = 0;
                started = false;
            }
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            word[count] = c;
            count++;
            started = true;
        }
    }
    
    if (started) {
        get_char_tree_node(root, word[0])->words = put_word_tree_node(get_char_tree_node(root, word[0])->words, word);
        
        if (!word_list_contains(get_word_tree_node(get_char_tree_node(root, word[0])->words, word)->case_sensitive_list, word)) {
            get_word_tree_node(get_char_tree_node(root, word[0])->words, word)->case_sensitive_list = add(get_word_tree_node(get_char_tree_node(root, word[0])->words, word)->case_sensitive_list, word);
            get_word_tree_node(get_char_tree_node(root, word[0])->words, word)->cases_instances++;
        }
        
        memset(word, 0, count);
        count = 0;
        started = false;
    }
    
    printf("%-25s %-25s %-25s \n", "Word", "Total No. Occurrences", "No. Case-Sensitive Versions");
    print_alph_tree(root);
    
    
    
    fclose(f);
}

void print_word_list(word_list_node * node) {
    while (node != NULL) {
        printf("%s ->", node->case_sensitive_word);
        node = node->next;
    }
    
    printf("\n");
}

void print_word_tree(word_tree_node * node) {
    if (node == NULL)
        return;
    print_word_tree(node->left);
    printf("%-25s %-25i %-25i\n", strtolower(node->case_insensitive_word), node->total_instances, node->cases_instances);
    /*print_word_list(node->case_sensitive_list);*/
    print_word_tree(node->right);
}

void print_alph_tree(alph_tree_node * node) {
    if (node == NULL)
        return;
    print_alph_tree(node->left);
    print_word_tree(node->words);
    print_alph_tree(node->right);
}

char * strtolower(char *str) {
    char *p;
    for (p = str; *p != '\0'; ++p)
        *p = tolower(*p);
    return str;
}
