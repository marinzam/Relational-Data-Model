
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct COURSE_ROOM {
    char CourseName[7];
    char Room[20];
    struct COURSE_ROOM *next;
};
struct COURSE_ROOM *COURSE_ROOM_TABLE[1009];


void roomIntoTable(struct COURSE_ROOM *room, struct COURSE_ROOM *course){
    while(course->next){
        course = course->next;
    }
    course->next= room;
    
    
}

void insertRoom(char courseName[7], char preReqName[7]){
    struct COURSE_ROOM *newRoom = (struct COURSE_ROOM*) malloc(sizeof(struct COURSE_ROOM));
    strcpy(newRoom->CourseName, courseName);
    strcpy(newRoom->Room, preReqName);
    newRoom->next = NULL;
    int hashCheck;
    sscanf(courseName, "%x", &hashCheck);
    hashCheck = hashCheck%1009;


    
        if(!COURSE_ROOM_TABLE[hashCheck]){
            COURSE_ROOM_TABLE[hashCheck] = newRoom;
            COURSE_ROOM_TABLE[hashCheck]->next = NULL;
            return;
        }
        roomIntoTable(newRoom, COURSE_ROOM_TABLE[hashCheck]);
    
}

void printRooms(){
    int a;
    struct COURSE_ROOM *current;
    for( a = 0; a < 1009; a = a + 1 ){
    current = COURSE_ROOM_TABLE[a];
        while(current){
            printf("\nInserted course room:");
            printf("\nCourse: %s", current->CourseName);
            printf(" ");
            printf(" Room: %s\n", current->Room);
            current = current->next;
        }
        
    }
}

void saveCourseRooms(){
    int a;
    struct COURSE_ROOM *current;
    FILE *filePointer;
    filePointer = fopen("course_room.txt", "w");
    for( a = 0; a < 1009; a = a + 1 ){
    current = COURSE_ROOM_TABLE[a];
        while(current){
            fprintf(filePointer,"%s\t", current->CourseName);
            fprintf(filePointer,"%s\n", current->Room);
            current = current->next;
        }
        
    }
    a = fclose(filePointer);
}

void loadCourseRooms(){
char buf[1000];
char courseName[7], roomName[20];
FILE *filePointer;
    filePointer = fopen("course_room.txt", "r");
    if(filePointer == NULL){
    printf("Error!");
    return;
    }

while (fgets(buf, sizeof(buf), filePointer) != NULL)
{
    buf[strlen(buf) - 1] = '\0'; 
    sscanf(buf, "%s\t%[^\n]", courseName, roomName);
    insertRoom(courseName, roomName);
    
}
fclose(filePointer);

return;
}


