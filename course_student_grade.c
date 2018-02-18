

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct COURSE_STUDENT_GRADE {
    char CourseName[7];
    int StudentId;
    char Grade[4];
    struct COURSE_STUDENT_GRADE *next;
};
struct COURSE_STUDENT_GRADE *COURSE_STUDENT_GRADE_TABLE[1009];


void gradeIntoTable(struct COURSE_STUDENT_GRADE *courseTime, struct COURSE_STUDENT_GRADE *course){
    while(course->next){
        course = course->next;
    }
    course->next= courseTime;
    
    
}

void insertCourseGrade(char courseName[7], int studentId, char grade[3]){
    struct COURSE_STUDENT_GRADE *newPrereq = (struct COURSE_STUDENT_GRADE*) malloc(sizeof(struct COURSE_STUDENT_GRADE));
    strcpy(newPrereq->CourseName, courseName);
    newPrereq->StudentId = studentId;
    strcpy(newPrereq->Grade, grade);
    newPrereq->next = NULL;
    int hashCheck = studentId % 1009;

    
        if(!COURSE_STUDENT_GRADE_TABLE[hashCheck]){
            COURSE_STUDENT_GRADE_TABLE[hashCheck] = newPrereq;
            COURSE_STUDENT_GRADE_TABLE[hashCheck]->next = NULL;
            return;
        }
        gradeIntoTable(newPrereq, COURSE_STUDENT_GRADE_TABLE[hashCheck]);
    
}

void printCourseGrades(){
    int a;
    struct COURSE_STUDENT_GRADE *current;
    for( a = 0; a < 1009; a = a + 1 ){
    current = COURSE_STUDENT_GRADE_TABLE[a];
        while(current){
            printf("\nInserted new grade:");
            printf("\nCourse: %s", current->CourseName);
            printf(" StudentID: %d", current->StudentId);
            printf(" Grade: %s\n", current->Grade);
            current = current->next;
        }
        
    }
}

void findGradeFromId(int studentId, char courseName[7]){
    struct COURSE_STUDENT_GRADE *current;
    int hashCheck = studentId % 1009;
    printf("\nId: %d ", studentId);
    printf(" Course: %s", courseName);
    current = COURSE_STUDENT_GRADE_TABLE[hashCheck];

    while(current){
        if(strcmp(courseName, current->CourseName) == 0){
            printf(" Grade: %s\n", current->Grade);
            return;
        }
        current = current->next;
    }
    printf("\nGrade not found");
}

void saveGrade(){
    int a;
    struct COURSE_STUDENT_GRADE *current;
    FILE *filePointer;
    filePointer = fopen("course_student_grade.txt", "w");
    for( a = 0; a < 1009; a = a + 1 ){
    current = COURSE_STUDENT_GRADE_TABLE[a];
        while(current){
            fprintf(filePointer,"%s\t", current->CourseName);
            fprintf(filePointer,"%d\t", current->StudentId);
            fprintf(filePointer,"%s\n", current->Grade);
            current = current->next;
        }
        
    }
    a = fclose(filePointer);
}

void loadGrades(){
char buf[1000];
int id;
char field1[7], field3[4];
FILE *filePointer;
    filePointer = fopen("course_student_grade.txt", "r");
    if(filePointer == NULL){
    printf("Error!");
    return;
    }

while (fgets(buf, sizeof(buf), filePointer) != NULL)
{
    buf[strlen(buf) - 1] = '\0'; 
    sscanf(buf, "%s%d%s", field1, &id, field3);
    insertCourseGrade(field1, id, field3);
    
}
fclose(filePointer);

return;
}

void deleteGrades(int studentId){
    struct COURSE_STUDENT_GRADE *current;
    int hashCheck = studentId % 1009;
    current = COURSE_STUDENT_GRADE_TABLE[hashCheck];
    if(current->StudentId == studentId){
        if(current->next){
            COURSE_STUDENT_GRADE_TABLE[hashCheck] = current->next;
        }else{
            COURSE_STUDENT_GRADE_TABLE[hashCheck] = NULL;
        }
    }
        while(current){
            if(current->StudentId == studentId){
                if(current->next){
                    COURSE_STUDENT_GRADE_TABLE[hashCheck] = current->next;
                    
                }else{
                    COURSE_STUDENT_GRADE_TABLE[hashCheck] = NULL;
                }
            }
            current = current->next;
        }
}




