#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"


// TODO: function definitions here for ls2
void mode1(const char *path, int depth) {
    //open directory from path
    DIR *dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "Error: Could not open directory %s\n", path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build full path and stat it
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(full_path, &statbuf) != 0) {
            continue;  // Skip if stat fails
        }

        // Print the entry with indentation, makes it look like a tree
        for (int i = 0; i < depth; i++) {
            printf(INDENT);
        }

        if (S_ISDIR(statbuf.st_mode)) {
            printf("%s/ (directory)\n", entry->d_name);
            mode1(full_path, depth + 1);
        }
        else if (S_ISREG(statbuf.st_mode)) {
            printf("%s (%ld bytes)\n", entry->d_name, statbuf.st_size);
        }
    }

    closedir(dir);
}

void mode2(const char *path, const char *pattern, stack_t *results) {
    //open directory from path
    DIR *dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "Error: Could not open directory %s\n", path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
    //for each entry:
        //skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        //build full_path
        //stat()
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(full_path, &statbuf) != 0) {
            continue;  // Skip if stat fails
        }
        //if regular file:

        if (S_ISREG(statbuf.st_mode)) {
            //if name matches pattern:
            if (strcmp(entry->d_name, pattern) == 0) {

                //push(full_path)
                push(results, full_path);
            }
        }
        //if directory:
            //recurse
        else if (S_ISDIR(statbuf.st_mode)) {
            mode2(full_path, pattern, results);
        }
    }

    closedir(dir);
}

void print_chain(char *path)
{

    //check if path is valid
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return;
    }

    //tokenize path by "/"
    if (strncmp(path, "./", 2) == 0) {
        path += 2;
    }

    //count number of tokens to know how many times to indent
    char *copy = strdup(path);
    int count = 0;
    char *token = strtok(copy, "/");
    while (token != NULL) {
        count++;
        token = strtok(NULL, "/");
    }
    free(copy);

    int depth = 0;
    token = strtok(path, "/");
    //print each token with indentation based on depth
    while (token != NULL) {

        for (int i = 0; i < depth; i++) {
            printf("    ");
        }

        if (depth < count - 1) {
            printf("%s/ (directory)\n", token);
        }
        else {
            printf("%s (%ld bytes)\n",
                   token,
                   statbuf.st_size);
        }

        depth++;
        token = strtok(NULL, "/");
    }
}