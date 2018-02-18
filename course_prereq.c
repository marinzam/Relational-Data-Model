
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct COURSE_PREREQ {
    char CourseName[7];
    char PrereqName[7];
    struct COURSE_PREREQ *next;
};
struct COURSE_PREREQ *COURSE_PREREQ_TABLE[1009];

void prereqIntoTable(struct COURSE_PREREQ *prereq, struct COURSE_PREREQ *course){
    while(course->next){
        course = course->next;
    }
    course->next= prereq;
    
    
}

void insertPrereq(char courseName[7], char preReqName[7]){
    struct COURSE_PREREQ *newPrereq = (struct COURSE_PREREQ*) malloc(sizeof(struct COURSE_PREREQ));
    strcpy(newPrereq->CourseName, courseName);
    strcpy(newPrereq->PrereqName, preReqName);
    newPrereq->next = NULL;
    int hashCheck;
    sscanf(courseName, "%d", &hashCheck);
    hashCheck = hashCheck%1009;

    
        if(!COURSE_PREREQ_TABLE[hashCheck]){
            COURSE_PREREQ_TABLE[hashCheck] = newPrereq;
            COURSE_PREREQ_TABLE[hashCheck]->next = NULL;
            return;
        }
        prereqIntoTable(newPrereq, COURSE_PREREQ_TABLE[hashCheck]);
    
}

void printPrereqs(){
    int a;
    struct COURSE_PREREQ *current;
    for( a = 0; a < 1009; a = a + 1 ){
    current = COURSE_PREREQ_TABLE[a];
        while(current){
            printf("\nInserted prereq:");
            printf("\nCourse: %s", current->CourseName);
            printf(" ");
            printf(" Prereq: %s\n", current->PrereqName);
            current = current->next;
        }
        
    }
}

void savePrereqs(){
    int a;
    struct COURSE_PREREQ *current;
    FILE *filePointer;
    filePointer = fopen("course_prereq.txt", "w");
    for( a = 0; a < 1009; a = a + 1 ){
    current = COURSE_PREREQ_TABLE[a];
        while(current){
            fprintf(filePointer,"%s\t", current->CourseName);
            fprintf(filePointer,"%s\n", current->PrereqName);
            current = current->next;
        }
        
    }
    a = fclose(filePointer);
}

void loadPrereqs(){
char buf[1000];
char course[7], prereq[7];
FILE *filePointer;
    filePointer = fopen("course_prereq.txt", "r");
    if(filePointer == NULL){
    printf("Error!");
    return;
    }

while (fgets(buf, sizeof(buf), filePointer) != NULL)
{
    buf[strlen(buf) - 1] = '\0'; 
    sscanf(buf, "%s%s", course, prereq);
    insertPrereq(course, prereq);
    
}
fclose(filePointer);

return;
}
