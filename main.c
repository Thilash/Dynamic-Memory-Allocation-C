//
//  main.c
//  Q4
//
//  Created by Thilash Yohathasan on 2019-10-27.
//  Copyright © 2019 Thilash Yohathasan. All rights reserved.
//

#include <stdio.h>

void print(char* c) {
    while (*c != '\0') {
        printf("%c",*c);
        c++;
    }
    printf("\n");
}


void main() {
    
    char C[20] = "Thilash";
    print(C);

}
