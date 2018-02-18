

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct COURSE_DAY_HOUR { //structure for the course time
    char CourseName[7];
    char Day[12];
    char Hour[7];
    struct COURSE_DAY_HOUR *next;
};
struct COURSE_DAY_HOUR *COURSE_DAY_HOUR_TABLE[1009];


void courseTimeIntoTable(struct COURSE_DAY_HOUR *courseTime, struct COURSE_DAY_HOUR *course){ //inserts the course time info into the table
    while(course->next){
        course = course->next;
    }
    course->next= courseTime;
    
    
}

void insertCourseTime(char courseName[7], char day[12], char hour[7]){ //takes the data and inserts the course times
    struct COURSE_DAY_HOUR *newPrereq = (struct COURSE_DAY_HOUR*) malloc(sizeof(struct COURSE_DAY_HOUR));
    strcpy(newPrereq->CourseName, courseName);
    strcpy(newPrereq->Day, day);
    strcpy(newPrereq->Hour, hour);
    newPrereq->next = NULL;
    int hashCheck;
    sscanf(courseName, "%x", &hashCheck);
    hashCheck = hashCheck%1009;

    
        if(!COURSE_DAY_HOUR_TABLE[hashCheck]){
            COURSE_DAY_HOUR_TABLE[hashCheck] = newPrereq;
            COURSE_DAY_HOUR_TABLE[hashCheck]->next = NULL;
            return;
        }
        courseTimeIntoTable(newPrereq, COURSE_DAY_HOUR_TABLE[hashCheck]);
    
}

void printCourseTimes(){
    int a;
    struct COURSE_DAY_HOUR *current;
    for( a = 0; a < 1009; a = a + 1 ){
    current = COURSE_DAY_HOUR_TABLE[a];
        while(current){
            printf("\nInserted course time:");
            printf("\nCourse: %s", current->CourseName);
            printf(" Day: %s", current->Day);
            printf(" Hour: %s\n", current->Hour);
            current = current->next;
        }
        
    }
    return;
}

void saveCourseTime(){ //saves the course times to a file
    int a;
    struct COURSE_DAY_HOUR *current;
    FILE *filePointer;
    filePointer = fopen("course_day_hour.txt", "w");
    for( a = 0; a < 1009; a = a + 1 ){
    current = COURSE_DAY_HOUR_TABLE[a];
        while(current){
            fprintf(filePointer,"%s\t", current->CourseName);
            fprintf(filePointer,"%s\t", current->Day);
            fprintf(filePointer,"%s\n", current->Hour);
            current = current->next;
        }
        
    }
    a = fclose(filePointer);
}

void loadCourseTimes(){ // loads the course times from file
char buf[1000];
char course[7], day[12], hour[7];
FILE *filePointer;
    filePointer = fopen("course_day_hour.txt", "r");
    if(filePointer == NULL){
    printf("Error!");
    return;
    }

while (fgets(buf, sizeof(buf), filePointer) != NULL)
{
    buf[strlen(buf) - 1] = '\0'; 
    sscanf(buf, "%s%s%s", course, day, hour);
    insertCourseTime(course, day, hour);
    
}
fclose(filePointer);

return;
}
