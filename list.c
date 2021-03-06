//
// Created by colin on 5/14/2021.
//
#include "list.h"
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include "util.h"

long int* addToVarList(varList_t* list, char* name, int len, int val) {
    long int* exists = find(list, name, len);
    if(exists == NULL) {
        var_t *new = malloc(sizeof(var_t));
        if (new == NULL) {
            printf("Runtime error: Unable to allocate memory");
            return NULL;
        } else if (list->size == 0) {
            new->next = NULL;
        } else {
            new->next = list->first;
        }
        new->val = val;
        exists = &(new->val);
        new->name = malloc(sizeof(char) * (len + 1));
        strncpy(new->name, name, len);
        (new->name)[len] = 0; //add null terminator
        list->first = new;
        list->size++;
    }
    else {
        *exists = val;
    }
    return exists;
}

char* addToFuncList(funcList_t* list, char* name, int len, char* location) {
    func_t* exists = findFunc(list, name, len);
    if(exists == NULL) {
        exists = malloc(sizeof(func_t));
        if (exists == NULL) {
            printf("Runtime error: Unable to allocate memory");
            return NULL;
        } else if (list->size == 0) {
            exists->next = NULL;
        } else {
            exists->next = list->first;
        }
        //exists->location = location;
        int i = 0;
        while(location[i] != ';'){
            if(location[i] == 0){
                printf("Function definition is not terminated"); //TODO: crash
                return NULL;
            }
            i++;
        } i++;
        exists->location = malloc(i + 2);
        strncpy(exists->location, location, i);
        (exists->location)[i] = ' '; (exists->location)[i + 1] = 0; //TODO: test changes.
        exists->len = len;
        exists->name = malloc(sizeof(char) * (len + 1));
        strncpy(exists->name, name, len);
        (exists->name)[len] = 0; //add null terminator
        list->first = exists;
        list->size++;
    }
    else {
        printf("Illegal second declaration.\n"); //TODO: crash
        return NULL;
    }
    return exists->location;
}

long int* find(varList_t* list, char* name, int len) {
    var_t* iterator = list->first;
    while(iterator != NULL) {
        if(!strncmp(name, iterator->name, max(len, strlen(iterator->name)))) {
            return &(iterator->val);
        }
        iterator = iterator->next;
    }
    return NULL;
}

func_t* findFunc(funcList_t* list, char* name, int len) {
    //printf("Running\n");
    func_t* iterator = list->first;
    //printf("Running2\n");
    while(iterator != NULL) {
        if(!strncmp(name, iterator->name, max(len, strlen(iterator->name)))) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

void del(varList_t* list) {
    var_t* iterator = list->first;
    while(iterator != NULL) {
        free(iterator->name);
        free(iterator);
        iterator = iterator->next;
    }
}

void delFuncs(funcList_t* list) {
    func_t* iterator = list->first;
    while(iterator != NULL) {
        free(iterator->name);
        free(iterator);
        iterator = iterator->next;
    }
}

void dumpVars(varList_t* vars) {
    var_t* var = vars->first;
    while (var != NULL) {
        printf("(%s,", var->name);
        printf(" %d)\n", var->val);
        var = var->next;
    }
}

void dumpFunc(funcList_t* list) {
    func_t* func = list->first;
    while (func != NULL) {
        printf(": %s %s\n", func->name, func->location);
        func = func->next;
    }
}
