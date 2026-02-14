#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

/* Function Prototypes */
void addStudent();
void studentRecord();
void searchStudent();
void deleteStudent();
void spinner();
void pauseAndClear();

/* Spinner Animation */
void spinner()
{
  char spin[] = "|/-\\";
  for (int i = 0; i < 12; i++)
  {
    printf("%c", spin[i % 4]);
    fflush(stdout);
    Sleep(200);
    printf("\b");
  }
}

/* Utility function for pause + clear screen */
void pauseAndClear()
{
  printf("\nPress Enter to continue...");
  getchar();     // replaces getch()
  system("cls"); // clear screen
}

/* Student Structure */
struct student
{
  char firstName[30];
  char lastName[30];
  char className[30];
  char vill[30];
  int rollNo;
  float per;
};

int main()
{
  int choice = 0;
  time_t now;
  time(&now);

  system("color 05");
  printf("\nDate and time: %s\n", ctime(&now));

  while (choice != 5)
  {
    printf("---------------------------------------------------\n");
    printf("Student Database Management System\n");
    printf("---------------------------------------------------\n\n");
    printf("1. Add Student Record\n");
    printf("2. Display All Student Records\n");
    printf("3. Search Student Record\n");
    printf("4. Delete Student Record\n");
    printf("5. Exit\n");

    printf("\nEnter your choice: ");
    if (scanf("%d", &choice) != 1)
    {
      printf("Invalid input! Please enter a number.\n");
      while (getchar() != '\n')
        ;
      continue;
    }
    getchar(); // clear newline

    switch (choice)
    {
    case 1:
      addStudent();
      break;
    case 2:
      studentRecord();
      break;
    case 3:
      searchStudent();
      break;
    case 4:
      deleteStudent();
      break;
    case 5:
      printf("\nExiting program...\n");
      break;
    default:
      printf("\nInvalid choice! Please choose again.\n");
      pauseAndClear();
    }
  }

  return 0;
}

/* Add Student */
void addStudent()
{
  char another;
  struct student info;
  FILE *fp;

  fp = fopen("StudentDB.txt", "a"); // text mode
  if (fp == NULL)
  {
    printf("Cannot open file!\n");
    return;
  }

  do
  {
    system("cls");
    printf("---------------------------------------------------\n");
    printf("Add Student Info\n");
    printf("---------------------------------------------------\n\n");

    printf("1. Enter first name : ");
    fgets(info.firstName, sizeof(info.firstName), stdin);
    info.firstName[strcspn(info.firstName, "\n")] = 0;

    printf("2. Enter last name  : ");
    fgets(info.lastName, sizeof(info.lastName), stdin);
    info.lastName[strcspn(info.lastName, "\n")] = 0;

    printf("3. Enter roll no    : ");
    while (scanf("%d", &info.rollNo) != 1)
    {
      printf("Invalid input! Enter a number: ");
      while (getchar() != '\n')
        ;
    }
    getchar();

    printf("4. Enter class name : ");
    fgets(info.className, sizeof(info.className), stdin);
    info.className[strcspn(info.className, "\n")] = 0;

    printf("5. Enter address    : ");
    fgets(info.vill, sizeof(info.vill), stdin);
    info.vill[strcspn(info.vill, "\n")] = 0;

    printf("6. Enter percentage : ");
    while (scanf("%f", &info.per) != 1)
    {
      printf("Invalid input! Enter a valid percentage: ");
      while (getchar() != '\n')
        ;
    }
    getchar();

    printf("\nSaving record ");
    spinner();

    fprintf(fp, "%d|%s|%s|%s|%s|%.2f\n",
            info.rollNo,
            info.firstName,
            info.lastName,
            info.className,
            info.vill,
            info.per);

    printf("\nRecord stored successfully!\n");

    printf("\nAdd another student? (y/n): ");
    scanf(" %c", &another);
    getchar();

  } while (another == 'y' || another == 'Y');

  fclose(fp);
  pauseAndClear();
}

/* Display All Students */
void studentRecord()
{
  FILE *fp;
  struct student info;
  char line[200];

  fp = fopen("StudentDB.txt", "r");
  if (fp == NULL)
  {
    printf("No records found.\n");
    pauseAndClear();
    return;
  }

  system("cls");
  printf("---------------------------------------------------\n");
  printf("All Student Records\n");
  printf("---------------------------------------------------\n\n");

  // printf("RollNo | First Name | Last Name | Class | Address | Percentage\n");
  // printf("---------------------------------------------------------------\n");

  while (fgets(line, sizeof(line), fp))
  {
    // parse the line
    sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%f",
           &info.rollNo,
           info.firstName,
           info.lastName,
           info.className,
           info.vill,
           &info.per);

    printf("\n1. Roll no    :  %d", info.rollNo);
    printf("\n2. First name :  %s", info.firstName);
    printf("\n3. Last name  :  %s", info.lastName);
    printf("\n4. Address    :  %s", info.vill);
    printf("\n5. Percentage :  %.2f", info.per);
    printf("\n------------------------------------------\n");
    // printf(" %d |   %s |   %s |  %s |   %s |   %.2f\n",
    //        info.rollNo,
    //        info.firstName,
    //        info.lastName,
    //        info.className,
    //        info.vill,
    //        info.per);
  }

  fclose(fp);
  pauseAndClear();
}

/* Search Student */
void searchStudent()
{
  FILE *fp;
  struct student info;
  char line[200];
  int roll;
  int found = 0;

  printf("\nEnter roll number to search: ");
  scanf("%d", &roll);
  getchar();

  fp = fopen("StudentDB.txt", "r");
  if (fp == NULL)
  {
    printf("No records found.\n");
    pauseAndClear();
    return;
  }

  while (fgets(line, sizeof(line), fp))
  {
    sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%f",
           &info.rollNo,
           info.firstName,
           info.lastName,
           info.className,
           info.vill,
           &info.per);

    if (info.rollNo == roll)
    {
      printf("\nRecord Found:\n");
      printf("RollNo: %d\n", info.rollNo);
      printf("Name: %s %s\n", info.firstName, info.lastName);
      printf("Class: %s\n", info.className);
      printf("Address: %s\n", info.vill);
      printf("Percentage: %.2f\n", info.per);
      found = 1;
      break;
    }
  }

  if (!found)
    printf("\nRecord not found.\n");

  fclose(fp);
  pauseAndClear();
}

/* Delete Student */
void deleteStudent()
{
  FILE *fp, *temp;
  struct student info;
  char line[200];
  int roll;
  int found = 0;

  printf("\nEnter roll number to delete: ");
  scanf("%d", &roll);
  getchar();

  fp = fopen("StudentDB.txt", "r");
  if (fp == NULL)
  {
    printf("No records found.\n");
    pauseAndClear();
    return;
  }

  temp = fopen("temp.txt", "w");
  if (temp == NULL)
  {
    printf("Cannot create temp file!\n");
    fclose(fp);
    return;
  }

  while (fgets(line, sizeof(line), fp))
  {
    sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%f",
           &info.rollNo,
           info.firstName,
           info.lastName,
           info.className,
           info.vill,
           &info.per);

    if (info.rollNo == roll)
    {
      found = 1;
      printf("\nRecord with RollNo %d deleted.\n", roll);
      continue; // skip writing this line
    }

    fprintf(temp, "%d|%s|%s|%s|%s|%.2f\n",
            info.rollNo,
            info.firstName,
            info.lastName,
            info.className,
            info.vill,
            info.per);
  }

  fclose(fp);
  fclose(temp);

  remove("StudentDB.txt");
  rename("temp.txt", "StudentDB.txt");

  if (!found)
    printf("\nRecord not found.\n");

  pauseAndClear();
}
