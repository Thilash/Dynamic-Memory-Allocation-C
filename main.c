//
//  main.c
//  Q2
//
//  Created by Thilash Yohathasan on 2019-10-29.
//  Copyright © 2019 Thilash Yohathasan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    
    int idNumber;
    char firstName[15];
    char lastName[15];
    int project1;
    int project2;
    float finalGrade;
    
}student;

student **create_class_list(char *filename, int *sizePtr) {
    
    
    // opens file and scans the first number into num. Allocates space for the amount of students using
    // *sizePtr = num and allocates it to list. List is a pointer to a pointer of students. Then list[i] allocates space for the actual struct of each student.
    int num;
    student **list= NULL;
    FILE *input_file = fopen(filename,"r");
    fscanf(input_file, "%d", &num);
    *sizePtr = num;
    list = malloc(num * sizeof(student*));
    for (int i =0; i<num; i++) {
        list[i] = malloc(sizeof(student));
        fscanf(input_file, "%d %s %s",&list[i]->idNumber, &list[i]->firstName, &list[i]->lastName);
        list[i]->project1 = 0;
        list[i]->project2 = 0;
        list[i]->finalGrade = 0;
    }
    fclose(input_file);
    return list;
}
// Checks if the id number given is equal to any id number in the list and returns the index. Otherwise -1.
int find(int idNo, student **list, int size){
    
    for (int i=0; i<size; i++) {
        if (idNo == (*list[i]).idNumber) {
            return i;
        }
    }
    return -1;
}

// opens the file, reads the project 1 and project 2 grades from the text file. Uses find() to get the id of the
//student and if it matches, check gives the position. Then the gr 1 and gr 2 are changed.
void input_grades(char *filename, student **list, int size){
    FILE *input_file =fopen(filename, "r");
    int ID, gr1, gr2, check;
    
    for (int i=0; i<size; i++) {
        fscanf(input_file, "%d %d %d", &ID, &gr1, &gr2);
        check = find(ID, list, size);
        if (check != -1) {
            (*list[check]).project1 = gr1;
            (*list[check]).project2 = gr2;
        }
    }
    fclose(input_file);
}

// Finds the average of the two project grades

void compute_final_course_grades(student **list, int size) {
    for (int i = 0; i<size; i++) {
        (*list[i]).finalGrade = ((*list[i]).project1 + (*list[i]).project2) / 2;
    }
}

// Opens the display file and prints the idnumber and finalgrade to the display file using a forloop.
void output_final_course_grades(student **list, int size, char *filename){
    FILE *input_file = fopen(filename, "w");
    fprintf(input_file, "%d\n", size);
    
    for (int i=0; i<size; i++) {
        fprintf(input_file, "%d %.1f\n",list[i]->idNumber,list[i]->finalGrade);
    }
    fclose(input_file);
}

void print_list(student **list, int size){
    for (int i=0; i<size; i++) {
        printf("ID: %d, name: %s %s, project 1 grade: %d, project 2 grade: %d, final grade: %.1f\n", (*list[i]).idNumber, (*list[i]).firstName, (*list[i]).lastName, (*list[i]).project1, (*list[i]).project2, (*list[i]).finalGrade);
    }
}

// posofremove finds the index for the id number that needs to be removed. it'll free the memory for the student pointer at the position given. It goes from i to the size of the list and changes the indexes of the arrays.
//Subtracts one from the size of the list to account for that
void withdraw(int idNo, student **list, int *sizePtr){
    
    int posofremove = find(idNo, list, *sizePtr);
    if (posofremove != -1) {
        free(list[posofremove]);
        if (posofremove != *sizePtr-1)
            for (int i = posofremove + 1; i < *sizePtr; i++) {
                list[i-1] = list[i];
            }
        *sizePtr = *sizePtr - 1;
        printf("The student with index: %d has been removed\ntt", posofremove);
    }
    else
        printf("There is no ID number matching that");
}

// Frees the student pointer at each spot of the array. Then frees the whole list itself.
void destroy_list(student **list, int *sizePtr){

    for (int i=0; i<*sizePtr ; i++){
        free(list[i]);
    }
    free(list);
    *sizePtr = 0;
}


void main() {
    
    // initialize variables
        char names[50], grades[50], outFile[100];
        int n, input;
        student **list = NULL;
    
        printf("Give the name of the file with the student names: ");
        scanf("%s", names);
        list = create_class_list(names, &n);
    
        printf("Give the name of the file with the grades: ");
        scanf("%s", grades);
        input_grades(grades, list, n);
    
        printf("Give the name of the file you want to display the text to: ");
        scanf("%s", outFile);
        compute_final_course_grades(list, n);
        output_final_course_grades(list, n, outFile);
    
    
        while(1){
            print_list(list, n);
            printf("If you want to stop removing just enter zero. Enter id number of student you want to withdraw: ");
            scanf("%d", &input);
    
            if (input == 0){
                break;
            }
            else{
                withdraw(input, list, &n);
            }
        }
    
        printf("The end of the program\n");
        destroy_list(list, &n);
        print_list(list, n);
        printf("Thilash\n");
    
    
     
     
    }
    

