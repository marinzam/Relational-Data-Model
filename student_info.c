
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ID_NAME_ADDRESS_PHONE { //structure for student info
    
    int StudentId;
    char Name[30];
    char Address[50];
    char PhoneNumber[9];
    struct ID_NAME_ADDRESS_PHONE *next;
};
struct ID_NAME_ADDRESS_PHONE *STUDENT_INFO_TABLE[1009];

struct NAME { //structure for student name (tree)
    char Name[30];
    struct NAME *left;
    struct NAME *right;
    struct ID_NAME_ADDRESS_PHONE *studentInfo;
};
struct NAME *NAME_TREE;


void printInfo(struct ID_NAME_ADDRESS_PHONE *toStudentInfo){
        printf("\nInserted new student:");
        printf("\nID: %d\n", toStudentInfo->StudentId);
        printf("Name: %s\n", toStudentInfo->Name);
        printf("Address: %s\n", toStudentInfo->Address);
        printf("Phone: %s\n", toStudentInfo->PhoneNumber);
     

    

}
void printtreenode(struct NAME *root){
    if(!root){
        return;
    }else{
        printtreenode(root -> left);
        printInfo(root->studentInfo);
        printtreenode(root ->right);
    }
}
    
    
    
void insertName(struct ID_NAME_ADDRESS_PHONE *newStudentInfo){ // inserts student name into tree from student info and sets the pointer to the student info
    struct NAME *newName = (struct NAME*) malloc(sizeof(struct NAME));
    newName->left = NULL;
    newName->right = NULL;
    strcpy(newName->Name, newStudentInfo->Name);
    newName->studentInfo = newStudentInfo;
    if(!NAME_TREE){
        NAME_TREE = newName;
        return;
    }
    struct NAME *root = NAME_TREE;
    while(NAME_TREE){
        if(strcmp(NAME_TREE->Name, newName->Name) > 0){ //traverse alphabetically
            if(!NAME_TREE->right){
                NAME_TREE->right = newName;
                NAME_TREE = root;
                return;
            }
            NAME_TREE = NAME_TREE->right;
        }else{
            if(!NAME_TREE->left){
                NAME_TREE->left = newName;
                NAME_TREE = root;
                return;
            }
            NAME_TREE = NAME_TREE->left;
        }
    }
    
}

void studentIntoTable(struct ID_NAME_ADDRESS_PHONE *newStudentInfo, struct ID_NAME_ADDRESS_PHONE *current){ //inserts the student info into the hash table
    while(current->next){
        current = current->next;
    }
    current->next= newStudentInfo;
    insertName(newStudentInfo);
    
    
}



void printStudents(){
    
    printtreenode(NAME_TREE);
    
}



void insertStudentInfo(int studentId, char name[30], char address[50], char phoneNumber[9]){ //takes the information and inserts it into the student info table
    
    struct ID_NAME_ADDRESS_PHONE *newStudentInfo = (struct ID_NAME_ADDRESS_PHONE*) malloc(sizeof(struct ID_NAME_ADDRESS_PHONE));
    newStudentInfo->StudentId = studentId;
    strcpy(newStudentInfo->Name, name);
    strcpy(newStudentInfo->Address, address);
    strcpy(newStudentInfo->PhoneNumber, phoneNumber);
    
    int hashCheck = studentId % 1009;
    
        if(!STUDENT_INFO_TABLE[hashCheck]){
            STUDENT_INFO_TABLE[hashCheck] = newStudentInfo;
            STUDENT_INFO_TABLE[hashCheck]->next = NULL;
            insertName(newStudentInfo); //insert the name for the student into the tree
            return;
        }
        studentIntoTable(newStudentInfo, STUDENT_INFO_TABLE[hashCheck]);
    
}

void saveStudentInfo(){ //saves the student info table to a file
    int a;
    struct ID_NAME_ADDRESS_PHONE *current;
    FILE *filePointer;
    filePointer = fopen("student_info.txt", "w");
    for( a = 0; a < 1009; a = a + 1 ){
      current = STUDENT_INFO_TABLE[a];
        while(current){
            fprintf(filePointer,"%d\t", current->StudentId);
            fprintf(filePointer,"%s\t", current->Name);
            fprintf(filePointer,"%s\t", current->Address);
            fprintf(filePointer,"%s\n", current->PhoneNumber);
            current = current->next;
        }
        
    }
    a = fclose(filePointer);
}

void loadStudentInfo(){ //loads the student info from the file
  char buf[1000];
  int id;
  char name[30], address[50], phone[9];
  FILE *filePointer;
    filePointer = fopen("student_info.txt", "r");
    if(filePointer == NULL){
      printf("Error!");
      return;
    }
 
  while (fgets(buf, sizeof(buf), filePointer) != NULL)
  {
    buf[strlen(buf) - 1] = '\0'; 
    sscanf(buf, "%d%s\t%[^\t]%s", &id, name, address, phone);
    insertStudentInfo(id, name, address, phone); //insert the student info into the table
  }
  fclose(filePointer);
  
  return;
}

struct NAME *search(char name[30], struct NAME *current) //the structure for searching based on name
{
  if(current)
  {
      if(strcmp(name, current->Name) == 0)
      {
          return current;
      }
      else if(strcmp(name, current->Name) > 1)
      {
          return search(name, current->left);
      }
      else
      {
          return search(name, current->right);
      }
  }
  else return 0;
}

int findIdFromName(char name[30]){ //finds the student id from the name
    struct NAME *temp;
    temp = search(name, NAME_TREE);

    if(temp){
        return temp->studentInfo->StudentId;
    }else{
        return 0;
    }
    
    
}

void projectFromStudentInfo(int row){ //projects the student info based on which rows are wanted
    int a;
    struct ID_NAME_ADDRESS_PHONE *current;
    for( a = 0; a < 1009; a = a + 1 ){
      current = STUDENT_INFO_TABLE[a];
        while(current){
            if(row==1){
                printf("%d\n", current->StudentId);
            }else if(row==2){
                printf("%s\n", current->Name);
            }else if(row==3){
                printf("%s\n", current->Address);
            }
            else if(row==41){
                printf("%s\n", current->PhoneNumber);
            }
            current = current->next;
        }
        
    }
}







