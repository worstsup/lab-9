#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "struct.h"

int main() {
    srand(time(NULL));
    int action;
    printf("Choose action:\n1. Sort\n2. Search\n");
    scanf("%d", &action);
    switch(action){
        case 1: 
            EmitSortMenu();
            break;
        case 2: 
            EmitSearchMenu();
            break;
        default: printf("Incorrect choice. Try again.\n");
    }
    return 0;
}