#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_stu 100
#define max_course 100
#define max_selectCourse 20

#define min_lim 5
#define max_lim 7
void loadData();

void addStudent();
void viewStudent();
void deleteStudent();

void addcourse();
void viewCourse();
void DeleteCourse();

void SelectCourse();
void view_Selected_Course(); 
typedef struct student {
    char name[20];
    int id;
    char major[20];
    int age;
    char email[20];
}student;
typedef struct course {
    char code[10];
    char name[20];
    int credits;
}course;

typedef struct SelectedCourse{
	int student_id;
	char course_code[max_selectCourse][20];
    int select_count;
}SelectedCourse;

SelectedCourse Selected[max_stu];

student students[max_stu];
int stu_count=0;//For counting how many students have been stored
course courses[max_course];
int course_count=0;//for course

    int num;//for course count in Selectcourse()
    
    



int main() {
    loadData();
    int choice;
	while(1){
        printf("Enter 1 to Add students\n");
        printf("Enter 2 view Students\n");
        printf("Enter 3 delete students\n");
        printf("Enter 4 Add course\n");
        printf("Enter 5 view Courses\n");
        printf("Enter 6 delete courses\n");
        printf("Enter 7 to select course\n");
        printf("Enter 8 to View Course\n");
        printf("Enter 9 to exit\n");
        printf("Enter Your choice: ");
        scanf("%d",&choice);
        if(choice == 1) {
            addStudent();
        }
        else if(choice == 2) {
            viewStudent();
        }
        else if(choice == 3) {
            deleteStudent();
        }
        else if(choice == 4) {
            addcourse();
        }
        else if(choice == 5) {
            viewCourse();
        }
        else if(choice == 6) {
            DeleteCourse();
        }
        else if(choice ==7 ) {
		SelectCourse() ;  
        }
        else if (choice==8){
		view_Selected_Course();
		}
		else if (choice==9){
        	printf("Exiting...?");
			break;
		}
		else{
			printf("\n Invalid ");
		}
        
    }
    return 0;
}

void addStudent() {
 

    if (stu_count >= max_stu) {
        printf("maxmimum limit reached.\n");
        return;
}
        student s;
        printf("Enter Student name: " );
        scanf(" %19[^\n]", s.name);
        printf("Enter Student id: " );
        scanf("%d", &s.id);
        for(int i=0;i<stu_count;i++)
        {
        	if(students[i].id==s.id){
        		printf("Already Exist..\n");
        		return;
			}
		}
		printf("Enter Student major\n1:CY(Cyber Security)\t"
		"2:DS(DATA SCIENCE)\t"
		"3:AI(ARTIFICIAL INTELLIGENCE)\t"
		"4:CS(COMPUTER SCIENCE)\t"
		"5:SE(SOFTWARE ENGINEERING)\t"
		"\nEnter Your choice: " );
    while (1) {
        int choice;
        scanf("%d",&choice);
        if(choice == 1) {
            strcpy(s.major,"CY");
        }
        else if(choice == 2) {

            strcpy(s.major,"DS");
        }
        else if(choice == 3) {
            strcpy(s.major,"AI");
        }
        else if(choice == 4) {
            strcpy(s.major,"CS");
        }
        else if(choice == 5) {
            strcpy(s.major,"SE");
        }
        else {
            printf("Invalid choice.\n");
              continue;
        }
        break;
    }
        printf("Enter Student age: " );
        scanf("%d", &s.age);
        printf("Enter Student email: " );
        scanf(" %[^\n]", s.email);
        students[stu_count] = s;
        stu_count++;
        printf("\nStudent added.\n");
    FILE *fp;
    fp = fopen("students.txt", "w");
    if (!fp) { printf("Error saving students!\n"); return; }
    for (int i = 0; i < stu_count; i++) {
        fprintf(fp, "%d,%s,%d,%s,%s\n",
                students[i].id,
                students[i].name,students[i].age,
                students[i].major,students[i].email);
    }
    fclose(fp);

    }

void viewStudent() {
 if ( stu_count==0) {
     printf("NO student added.\n");
     return;
 }
    printf("--STUDENTS--\n");
    printf("________________________________________________________________________________________________________________________\n");
         printf("Id  | Name\t\t\t\t | AGE\t | MAJOR\t| EMAIL\t\n");
    for (int i = 0; i < stu_count; i++) {
         printf("%d  | %s\t\t\t | %d\t | %s\t\t| %s\t\t\t\n",
            students[i].id,
            students[i].name,
            students[i].age,
            students[i].major,students[i].email);
    }
    printf("________________________________________________________________________________________________________________________\n");

}
void deleteStudent() {

    int id,found=0;
    printf("Enter Id of Student: ");
    scanf("%d",&id);
    if (stu_count==0) {
        printf("\nNO student deleted.\n");
    }
    for (int i = 0; i < stu_count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < stu_count-1; j++) {
                students[j] = students[j+1];
            }
            stu_count--;
            found=1;
            break;

    }
        }
        if (found) {
            printf("\nStudent deleted.\n");
        }
        else {
            printf("Student not found.\n");
        }
    FILE *fp;
    fp = fopen("students.txt", "a");
    if (!fp) { printf("Error saving students!\n"); return; }
    for (int i = 0; i < stu_count; i++) {
        fprintf(fp, "%d,%s,%d,%s,%s\n",
                students[i].id,
                students[i].name,students[i].age,
                students[i].major,students[i].email);
    }
    fclose(fp);

}

void addcourse() {
    if (course_count>=max_course) {
        printf("\nlimit exceed.\n");
        return;
    }
    course c;
    printf("Enter Course code: " );
    scanf("%s", c.code);
    printf("Enter Course name: " );
    scanf("%s", c.name);
    printf("Enter Course credit hours: " );
    scanf("%d",&c.credits);
   courses[course_count++] = c;
    printf("\nCourse succesfully added\n");
    
    FILE *fc;
    fc = fopen("courses.txt", "w");
    if (!fc) {
        printf("Course not found!\n");
        return;
    }
    for (int i = 0; i < course_count; i++) {
        fprintf(fc,"%s,%s,%d\n",courses[i].code,courses[i].name,courses[i].credits);
    }
    fclose(fc);
}
void viewCourse() {
    if (course_count==0) {
        printf("\nEmpty,NO course added.\n");
        return;
    }
    printf("\n--COURSES--\n");
    printf("_________________________________________________________________\n");
    printf("CODE\t | COURSE NAME       | CREDITS HRS\n");
    for (int i = 0; i < course_count; i++) {
        printf("%s\t | %s                | %d\n",courses[i].code,courses[i].name,courses[i].credits);
	}
        printf("_________________________________________________________________\n");
    
    
}

void DeleteCourse() {
    char code[10],found=0;
    printf("Enter Code of course: ");
    scanf("%s",code);
    if (course_count==0) {
        printf("\nEmpty,No course Added\n");
        return;
    }
    for (int i = 0; i < course_count; i++) {
        if (strcmp(courses[i].code,code)==0) {
            for (int j = i; j < course_count-1; j++) {
                courses[j] = courses[j+1];
        }
        		course_count--;
                found=1;
                break;
            }
    }
    if (found==1) {
        printf("\nCourse Deletred\n");
    }
    else {
        printf("\nCourse not found.\n");
    }
     FILE *fc;
    fc = fopen("courses.txt", "w");
    if (!fc) {
        printf("Course not found!\n");
        return;
    }
    
    for (int i = 0; i < course_count; i++) {
        fprintf(fc,"%d | %s | %d\n",courses[i].code,courses[i].name,courses[i].credits);
    }
    fclose(fc);
}

void SelectCourse() {
 	viewStudent();
    if (stu_count==0||course_count==0) {
        printf("\nNo Stdent and No course Added\n");
    }
    int id;
    printf("Enter Student id to select course: ");
    scanf("%d",&id);

    int found=-1;
    for (int i = 0; i < stu_count; i++) {
        if (students[i].id ==id) {
            found=i;
            break;
        }
    }
    if (found==-1) {
        printf("Student not found.\n");
        return;
    }
    Selected[found].student_id = id;
    printf("Courses available\n");
    for (int i = 0; i < course_count; i++) {
        printf("%d  %s(%s)\n",i+1,courses[i].name,courses[i].code);
    }
    printf("\n");
    printf("HOW many course you want to select(max: %d):",max_selectCourse );
    while(1){
	printf("\nEnter number of courses you want to select: ");
    scanf("%d",&num);
       if (num < min_lim) {
        printf("\nSelect at least %d courses.\n", min_lim);
        continue;
    }
    if (num > max_lim) {
        printf("\n?Select at most %d courses\n", max_lim);
        continue;
	}
	break;
    }
    
  if (Selected[found].select_count+num>max_selectCourse) {
      printf("\n max course limit reached");
      return;
  }
    
    int choice;
    
    //also check for duplicate
    for (int i = 0; i < num; i++) {
    printf("\nEnter no. of course you want to select: ");
	scanf("%d",&choice);
    if (choice < 1 || choice > course_count) {
        printf("Invalid course number. Try again.\n");
        i--;
        continue;


    }
     int duplicate=0;
     for(int j=0;j<Selected[found].select_count;j++){
     	if(strcmp(Selected[found].course_code[j],courses[choice-1].code)==0){
     		duplicate=1;
     		break;
		 }
	 }
	 if (duplicate){
	 	printf("Coures already selected.");
	 	i--;
	 	continue;
	 }
    
        int count=Selected[found].select_count;
        strcpy(Selected[found].course_code[count],courses[choice-1].code);
        Selected[found].select_count++;
    
    printf("\nCourses selected.");
}
	FILE *fn;
	fn=fopen("SelectCourse.txt","w");
	if (!fn) {
        printf("Empty\n");
        return;
    }
    for (int i = 0; i <stu_count; i++) {
    	if(Selected[i].select_count==0)
		continue;	
		for(int j=0;j<Selected[i].select_count;j++){
			{
		char course_name[20]="";
				for (int z=0;z<course_count;z++){
				if(strcmp(Selected[i].course_code[j],courses[z].code)==0){
					strcpy(course_name,courses[z].name);
					break;
				}
			}
        fprintf(fn,"%d,%s,%s,%s\n",Selected[i].student_id,students[i].name,Selected[i].course_code[j],course_name);
        
		}
	}	
		}
		fclose(fn);
    }
	    
void view_Selected_Course() 
{
	if(stu_count==0){
		return;
	}
    printf("\n--SELECTED COURSES--\n");
    printf("_________________________________________________________________\n");
    printf("ID |STUDENT NAME\t| CODE | COURSE NAME\n");
	for (int i = 0; i <stu_count; i++) {
	//this will ship students who didn't choose courses. 
		if(Selected[i].select_count==0){
		continue;
		}
		for (int j=0;j<Selected[i].select_count;j++){
			char cname[20]="";
			for(int z=0;z<course_count;z++){
				if(strcmp(Selected[i].course_code[j],courses[z].code)==0){
					strcpy(cname,courses[z].name);
					break;
				}
			}
			printf("%d |  %s\t\t|  %s |  %s\n",
			students[i].id,
			students[i].name,Selected[i].course_code[j],cname);
		}
			    printf("_________________________________________________________________\n");
	}

}	



  void loadData(){
  	// for students
  	  FILE *fp;
    fp = fopen("students.txt", "r");
    if (!fp) { printf("\nError saving students!\n"); 
	return; }
    if(fp!=NULL){
    	while (fscanf(fp, "%d,%[^,],%d,%[^,],%[^\n]\n",
                      &students[stu_count].id,
                      students[stu_count].name,
                      &students[stu_count].age,
                      students[stu_count].major,
					  students[stu_count].email) == 5){
					  	stu_count++;
					  }
					  
	}
    fclose(fp);
    
    //for course
     FILE *fc;
    fc = fopen("courses.txt", "r");
    if (!fc) {
        printf("\nError Saving Course!\n");
        return;
    }
    if(fc!=NULL){
   while (fscanf(fc, "%[^,],%[^,],%d\n", courses[course_count].code, courses[course_count].name, &courses[course_count].credits) == 3) {
    course_count++;
}
    }
    fclose(fc);
   
// for selecting course
    FILE *fn = fopen("SelectCourse.txt", "r");
    if (!fn) {
        printf("No previous selections found.\n");
        return;
    }

    int stu_id;
    char sname[20], code[20], cname[20];
    while (fscanf(fn, "%d,%[^,],%[^,],%[^\n]\n", &stu_id, sname, code, cname) == 4) {
        int Id = -1;
        for (int i = 0; i < stu_count; i++) {
            if (students[i].id == stu_id)
			 {
                Id = i;
                break;
            }
        }
        //skip student if they are not store in file
        if (Id == -1){ 
		continue;
		}
        if (Selected[Id].student_id == 0) {
            Selected[Id].student_id = stu_id;
            Selected[Id].select_count = 0;
        }
        if (Selected[Id].select_count < max_selectCourse) {
            strcpy(Selected[Id].course_code[Selected[Id].select_count], code);
            Selected[Id].select_count++;
        }
    }

    fclose(fn);

}


	
	
