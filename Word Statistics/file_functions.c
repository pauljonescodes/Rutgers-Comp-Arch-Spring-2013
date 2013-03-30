/*
 * file_functions.c
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
#include "file_functions.h"
#include <sys/stat.h>

int file_size(const char * filename) {
    struct stat file_stat;
    
    if(stat(filename, &file_stat) != 0) {
        return 1;
    }
    
    return (int) file_stat.st_size;
}

int file_exists(const char * filename) {
    FILE *file;
    
    if ((file = fopen(filename, "r"))) {
        fclose(file);
        return 1;
    }
    
    return 0;
}