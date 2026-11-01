
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBJECTS 20
#define MAX_STUDENTS 100
#define FILE_NAME "acadtrack_v3.dat"

struct Subject {
    char name[50];
    float marks;
    float maxMarks;
    int classesHeld;
    int classesAttended;
};

struct Student {
    int profileCreated;
    char name[50];
    char rollNo[20];
    int semester;
    int subjectCount;
    struct Subject subjects[MAX_SUBJECTS];
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

// ---------- INPUT FUNCTIONS ----------

void readLine(char text[], int size) {
    if (fgets(text, size, stdin) == NULL) {
        text[0] = '\0';
        return;
    }

    if (strchr(text, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }

    text[strcspn(text, "\n")] = '\0';
}

int readInt(char message[]) {
    char input[100];
    int value;
    char extra;

    while (1) {
        printf("%s", message);
        readLine(input, sizeof(input));

        if (sscanf(input, " %d %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid input! Enter a whole number.\n");
    }
}

float readFloat(char message[]) {
    char input[100];
    float value;
    char extra;

    while (1) {
        printf("%s", message);
        readLine(input, sizeof(input));

        if (sscanf(input, " %f %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid input! Enter a number.\n");
    }
}

// ---------- FILE HANDLING ----------

void loadData() {
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        return;
    }

    int count;

    if (fread(&count, sizeof(int), 1, fp) != 1 ||
        count < 0 || count > MAX_STUDENTS) {
        printf("\nUnable to read saved records.\n");
        fclose(fp);
        return;
    }

    if (count > 0 &&
        fread(students, sizeof(struct Student), count, fp) != count) {
        printf("\nSaved data is incomplete. Starting with empty records.\n");
        studentCount = 0;
        fclose(fp);
        return;
    }

    studentCount = count;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].profileCreated != 1 ||
            students[i].subjectCount < 0 ||
            students[i].subjectCount > MAX_SUBJECTS) {
            printf("\nInvalid saved record found. Starting with empty records.\n");
            studentCount = 0;
            break;
        }
    }

    fclose(fp);
}

void saveData() {
    FILE *fp = fopen(FILE_NAME, "wb");

    if (fp == NULL) {
        printf("\nError! Unable to save records.\n");
        return;
    }

    fwrite(&studentCount, sizeof(int), 1, fp);

    if (studentCount > 0) {
        fwrite(students, sizeof(struct Student),
               studentCount, fp);
    }

    fclose(fp);

    printf("\nRecords saved successfully!\n");
}

// ---------- SEARCH FUNCTION ----------

int findStudent(char rollNo[]) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].rollNo, rollNo) == 0) {
            return i;
        }
    }

    return -1;
}

// ---------- WELCOME SCREEN ----------

void welcomeScreen() {
    printf("\n");
    printf("====================================================\n");
    printf("                     ACADTRACK                      \n");
    printf("          ACADEMIC PERFORMANCE & PLANNING           \n");
    printf("====================================================\n");

    printf("\nWelcome to AcadTrack!\n");
    printf("Manage academic records and track student progress.\n");
}

// ---------- MAIN MENU ----------

void showMainMenu() {
    printf("\n");
    printf("====================================================\n");
    printf("                    MAIN MENU                       \n");
    printf("====================================================\n");

    printf(" 1. Add New Student Profile\n");
    printf(" 2. View All Student Profiles\n");
    printf(" 3. Search and Manage a Student\n");
    printf(" 4. Update Student Profile\n");
    printf(" 5. Delete Student Profile\n");
    printf(" 6. Save Records\n");
    printf(" 7. Exit Program\n");

    printf("====================================================\n");
}

// ---------- CREATE STUDENT PROFILE ----------

void createProfile() {
    if (studentCount >= MAX_STUDENTS) {
        printf("\nMaximum student limit reached (100).\n");
        return;
    }

    struct Student newStudent = {0};

    printf("\n========== NEW STUDENT PROFILE ==========\n");

    printf("Enter student name: ");
    readLine(newStudent.name, sizeof(newStudent.name));

    while (strlen(newStudent.name) == 0) {
        printf("Name cannot be empty. Enter again: ");
        readLine(newStudent.name, sizeof(newStudent.name));
    }

    printf("Enter roll number: ");
    readLine(newStudent.rollNo, sizeof(newStudent.rollNo));

    while (strlen(newStudent.rollNo) == 0 ||
           findStudent(newStudent.rollNo) != -1) {

        if (strlen(newStudent.rollNo) == 0) {
            printf("Roll number cannot be empty.\n");
        } else {
            printf("This roll number already exists.\n");
        }

        printf("Enter a different roll number: ");
        readLine(newStudent.rollNo, sizeof(newStudent.rollNo));
    }

    newStudent.semester =
        readInt("Enter semester number (1-12): ");

    while (newStudent.semester < 1 ||
           newStudent.semester > 12) {

        printf("Enter a valid semester (1-12).\n");

        newStudent.semester =
            readInt("Enter semester number: ");
    }

    newStudent.profileCreated = 1;

    students[studentCount] = newStudent;
    studentCount++;

    printf("\nStudent profile created successfully!\n");

    saveData();
}

// ---------- VIEW ALL STUDENTS ----------

void viewAllStudents() {
    printf("\n========== ALL STUDENT PROFILES ==========\n");

    if (studentCount == 0) {
        printf("\nNo student profiles found.\n");
        return;
    }

    printf("%-5s %-25s %-18s %-12s %-10s\n",
           "NO.", "NAME", "ROLL NUMBER",
           "SEMESTER", "SUBJECTS");

    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        printf("%-5d %-25.25s %-18.18s %-12d %-10d\n",
               i + 1,
               students[i].name,
               students[i].rollNo,
               students[i].semester,
               students[i].subjectCount);
    }

    printf("---------------------------------------------------------------------\n");
    printf("Total Students: %d\n", studentCount);
}

// ---------- UPDATE STUDENT PROFILE ----------

void updateProfile(int index) {
    struct Student *s = &students[index];

    char newRollNo[20];

    printf("\n========== UPDATE STUDENT PROFILE ==========\n");

    printf("Current Name: %s\n", s->name);
    printf("Enter new name: ");
    readLine(s->name, sizeof(s->name));

    while (strlen(s->name) == 0) {
        printf("Name cannot be empty. Enter again: ");
        readLine(s->name, sizeof(s->name));
    }

    printf("\nCurrent Roll Number: %s\n", s->rollNo);
    printf("Enter new roll number: ");
    readLine(newRollNo, sizeof(newRollNo));

    while (strlen(newRollNo) == 0 ||
           (findStudent(newRollNo) != -1 &&
            findStudent(newRollNo) != index)) {

        printf("Invalid or already existing roll number.\n");
        printf("Enter a different roll number: ");
        readLine(newRollNo, sizeof(newRollNo));
    }

    strcpy(s->rollNo, newRollNo);

    s->semester = readInt("Enter new semester (1-12): ");

    while (s->semester < 1 || s->semester > 12) {
        printf("Enter a valid semester (1-12).\n");
        s->semester = readInt("Enter semester: ");
    }

    printf("\nStudent profile updated successfully!\n");

    saveData();
}

// ---------- DELETE STUDENT PROFILE ----------

void deleteProfile() {
    if (studentCount == 0) {
        printf("\nNo student profiles available to delete.\n");
        return;
    }

    char rollNo[20];
    char confirm[10];

    printf("\n========== DELETE STUDENT PROFILE ==========\n");

    printf("Enter roll number of student to delete: ");
    readLine(rollNo, sizeof(rollNo));

    int index = findStudent(rollNo);

    if (index == -1) {
        printf("\nStudent profile not found.\n");
        return;
    }

    printf("\nStudent Found:\n");
    printf("Name: %s\n", students[index].name);
    printf("Roll Number: %s\n", students[index].rollNo);
    printf("Semester: %d\n", students[index].semester);

    printf("\nAre you sure you want to delete this profile? (Y/N): ");
    readLine(confirm, sizeof(confirm));

    if (strcmp(confirm, "Y") == 0 ||
        strcmp(confirm, "y") == 0) {

        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }

        studentCount--;

        memset(&students[studentCount], 0,
               sizeof(struct Student));

        printf("\nStudent profile deleted successfully!\n");

        saveData();
    } else {
        printf("\nDeletion cancelled.\n");
    }
}

// ---------- DISPLAY ACADEMIC RECORDS ----------

void displayTable(struct Student *s) {
    printf("\n================ STUDENT DETAILS ==================\n");

    printf("Name      : %s\n", s->name);
    printf("Roll No.  : %s\n", s->rollNo);
    printf("Semester  : %d\n", s->semester);

    printf("\n%-24s %-13s %-15s\n",
           "SUBJECT", "MARKS", "ATTENDANCE");

    printf("----------------------------------------------------\n");

    if (s->subjectCount == 0) {
        printf("No subjects have been added yet.\n");
    }

    for (int i = 0; i < s->subjectCount; i++) {
        struct Subject sub = s->subjects[i];

        float attendance = 0;

        if (sub.classesHeld > 0) {
            attendance =
                (float)sub.classesAttended /
                sub.classesHeld * 100;
        }

        printf("%-24.24s %-13.2f %-14.2f%%\n",
               sub.name, sub.marks, attendance);

        printf("                         (Out of %.2f)\n",
               sub.maxMarks);
    }

    printf("----------------------------------------------------\n");
}

// ---------- ADD SUBJECT ----------

void addSubject(struct Student *s) {
    if (s->subjectCount >= MAX_SUBJECTS) {
        printf("\nMaximum subject limit reached (20).\n");
        return;
    }

    struct Subject *sub = &s->subjects[s->subjectCount];

    printf("\n========== ADD NEW SUBJECT ==========\n");

    printf("Enter subject name: ");
    readLine(sub->name, sizeof(sub->name));

    while (strlen(sub->name) == 0) {
        printf("Subject name cannot be empty. Enter again: ");
        readLine(sub->name, sizeof(sub->name));
    }

    sub->maxMarks =
        readFloat("Enter maximum marks: ");

    while (sub->maxMarks <= 0) {
        printf("Maximum marks must be greater than zero.\n");
        sub->maxMarks = readFloat("Enter maximum marks: ");
    }

    sub->marks =
        readFloat("Enter obtained marks: ");

    while (sub->marks < 0 || sub->marks > sub->maxMarks) {
        printf("Marks must be between 0 and %.2f.\n",
               sub->maxMarks);

        sub->marks = readFloat("Enter obtained marks again: ");
    }

    sub->classesHeld =
        readInt("Enter total classes held: ");

    while (sub->classesHeld < 0) {
        printf("Classes held cannot be negative.\n");
        sub->classesHeld = readInt("Enter total classes held: ");
    }

    sub->classesAttended =
        readInt("Enter classes attended: ");

    while (sub->classesAttended < 0 ||
           sub->classesAttended > sub->classesHeld) {

        printf("Attended classes must be between 0 and %d.\n",
               sub->classesHeld);

        sub->classesAttended =
            readInt("Enter classes attended again: ");
    }

    s->subjectCount++;

    printf("\nSubject added successfully!\n");

    saveData();
}

// ---------- PERFORMANCE ANALYSIS ----------

void analyzePerformance(struct Student *s) {
    if (s->subjectCount == 0) {
        printf("\nPlease add subjects first.\n");
        return;
    }

    float totalMarks = 0;
    float totalMaxMarks = 0;

    float highest = -1;
    float lowest = 101;

    int bestIndex = 0;
    int weakIndex = 0;

    printf("\n========== PERFORMANCE ANALYSIS ==========\n");

    printf("%-25s %-15s\n", "SUBJECT", "PERCENTAGE");
    printf("------------------------------------------\n");

    for (int i = 0; i < s->subjectCount; i++) {
        struct Subject sub = s->subjects[i];

        float percentage =
            (sub.marks / sub.maxMarks) * 100;

        totalMarks += sub.marks;
        totalMaxMarks += sub.maxMarks;

        printf("%-25.25s %.2f%%\n",
               sub.name, percentage);

        if (percentage > highest) {
            highest = percentage;
            bestIndex = i;
        }

        if (percentage < lowest) {
            lowest = percentage;
            weakIndex = i;
        }
    }

    float overall =
        (totalMarks / totalMaxMarks) * 100;

    printf("------------------------------------------\n");

    printf("Total Marks       : %.2f / %.2f\n",
           totalMarks, totalMaxMarks);

    printf("Overall Percentage: %.2f%%\n", overall);

    printf("\nStrongest Subject : %s (%.2f%%)\n",
           s->subjects[bestIndex].name, highest);

    printf("Needs Improvement : %s (%.2f%%)\n",
           s->subjects[weakIndex].name, lowest);

    printf("\nOverall Performance: ");

    if (overall >= 90)
        printf("Excellent\n");
    else if (overall >= 75)
        printf("Very Good\n");
    else if (overall >= 60)
        printf("Good\n");
    else if (overall >= 40)
        printf("Average\n");
    else
        printf("Needs Improvement\n");
}

// ---------- ATTENDANCE ANALYSIS ----------

void attendanceAnalysis(struct Student *s) {
    if (s->subjectCount == 0) {
        printf("\nPlease add subjects first.\n");
        return;
    }

    printf("\n========== ATTENDANCE ANALYSIS ==========\n");

    printf("%-25s %-15s %-15s\n",
           "SUBJECT", "ATTENDANCE", "STATUS");

    printf("-------------------------------------------------------\n");

    for (int i = 0; i < s->subjectCount; i++) {
        struct Subject sub = s->subjects[i];

        float percentage = 0;

        if (sub.classesHeld > 0) {
            percentage =
                (float)sub.classesAttended /
                sub.classesHeld * 100;
        }

        printf("%-25.25s ", sub.name);
        printf("%-14.2f%% ", percentage);

        if (percentage >= 75) {
            printf("Satisfactory\n");
        } else {
            printf("Below 75%%\n");

            int required =
                3 * sub.classesHeld -
                4 * sub.classesAttended;

            if (required > 0) {
                printf("  Attend at least %d consecutive "
                       "additional classes to reach 75%%.\n",
                       required);
            }
        }
    }

    printf("\nNote: 75%% is the minimum attendance requirement.\n");
}

// ---------- TARGET CALCULATOR ----------

void targetCalculator(struct Student *s) {
    if (s->subjectCount == 0) {
        printf("\nPlease add subjects first.\n");
        return;
    }

    printf("\n========== ACADEMIC TARGET CALCULATOR ==========\n");

    printf("This calculator uses the marks currently entered.\n");

    float target =
        readFloat("\nEnter your target percentage (0-100): ");

    while (target < 0 || target > 100) {
        printf("Target must be between 0 and 100.\n");
        target = readFloat("Enter target percentage again: ");
    }

    float totalMarks = 0;
    float totalMaxMarks = 0;

    for (int i = 0; i < s->subjectCount; i++) {
        totalMarks += s->subjects[i].marks;
        totalMaxMarks += s->subjects[i].maxMarks;
    }

    float required = (target / 100) * totalMaxMarks;

    float currentPercentage =
        (totalMarks / totalMaxMarks) * 100;

    printf("\n========== TARGET REPORT ==========\n");

    printf("Current Percentage : %.2f%%\n", currentPercentage);
    printf("Target Percentage  : %.2f%%\n", target);

    printf("Current Marks      : %.2f / %.2f\n",
           totalMarks, totalMaxMarks);

    printf("Target Marks       : %.2f\n", required);

    if (totalMarks >= required) {
        printf("\nCongratulations! You have achieved your target.\n");
    } else {
        printf("\nAdditional marks needed: %.2f\n",
               required - totalMarks);
    }

}

// ---------- STUDY PRIORITIES ----------

void studyPriorities(struct Student *s) {
    if (s->subjectCount == 0) {
        printf("\nPlease add subjects first.\n");
        return;
    }

    printf("\n========== PERSONALIZED STUDY PRIORITIES ==========\n");

    for (int i = 0; i < s->subjectCount; i++) {
        struct Subject sub = s->subjects[i];

        float marksPercentage =
            (sub.marks / sub.maxMarks) * 100;

        float attendance = 0;

        if (sub.classesHeld > 0) {
            attendance =
                (float)sub.classesAttended /
                sub.classesHeld * 100;
        }

        printf("\nSubject: %s\n", sub.name);
        printf("Marks: %.2f%%\n", marksPercentage);
        printf("Attendance: %.2f%%\n", attendance);

        if (marksPercentage < 40 || attendance < 75) {
            printf("Study Priority: VERY HIGH\n");
        } else if (marksPercentage < 60) {
            printf("Study Priority: HIGH\n");
        } else if (marksPercentage < 75) {
            printf("Study Priority: MODERATE\n");
        } else {
            printf("Study Priority: LOW\n");
        }

        if (marksPercentage < 60) {
            printf("Suggestion: Focus on understanding "
                   "the subject fundamentals.\n");
        } else if (marksPercentage < 75) {
            printf("Suggestion: Practice regularly and "
                   "revise important topics.\n");
        } else {
            printf("Suggestion: Maintain your current "
                   "performance.\n");
        }

        if (attendance < 75) {
            printf("Attendance Alert: Work towards improving "
                   "your attendance.\n");
        }
    }
}

// ---------- INDIVIDUAL STUDENT MENU ----------

void studentMenu(int index) {
    struct Student *s = &students[index];
    int choice;

    do {
        printf("\n");
        printf("====================================================\n");
        printf("              STUDENT ACADEMIC MENU                 \n");
        printf("====================================================\n");

        printf("Student: %s\n", s->name);
        printf("Roll No: %s\n", s->rollNo);

        printf("\n1. Add Subject and Marks\n");
        printf("2. View Academic Records\n");
        printf("3. Analyze Overall Performance\n");
        printf("4. Attendance Analysis\n");
        printf("5. Academic Target Calculator\n");
        printf("6. Study Priorities\n");
        printf("7. Update Student Profile\n");
        printf("8. Back to Main Menu\n");

        printf("====================================================\n");

        choice = readInt("\nEnter your choice (1-8): ");

        switch (choice) {
            case 1:
                addSubject(s);
                break;

            case 2:
                displayTable(s);
                break;

            case 3:
                analyzePerformance(s);
                break;

            case 4:
                attendanceAnalysis(s);
                break;

            case 5:
                targetCalculator(s);
                break;

            case 6:
                studyPriorities(s);
                break;

            case 7:
                updateProfile(index);
                break;

            case 8:
                printf("\nReturning to main menu...\n");
                break;

            default:
                printf("\nInvalid choice! Select 1-8.\n");
        }

    } while (choice != 8);
}

// ---------- SEARCH AND MANAGE STUDENT ----------

void searchAndManage() {
    char rollNo[20];

    if (studentCount == 0) {
        printf("\nNo student profiles available.\n");
        return;
    }

    printf("\n========== SEARCH STUDENT ==========\n");

    printf("Enter student roll number: ");
    readLine(rollNo, sizeof(rollNo));

    int index = findStudent(rollNo);

    if (index == -1) {
        printf("\nStudent profile not found.\n");
        return;
    }

    printf("\nStudent found successfully!\n");

    studentMenu(index);
}

// ---------- MAIN FUNCTION ----------

int main() {
    int choice;

    loadData();

    welcomeScreen();

    printf("\nTotal saved student profiles: %d\n", studentCount);

    do {
        showMainMenu();

        choice = readInt("\nEnter your choice (1-7): ");

        switch (choice) {
            case 1:
                createProfile();
                break;

            case 2:
                viewAllStudents();
                break;

            case 3:
                searchAndManage();
                break;

            case 4: {
                char rollNo[20];

                printf("\nEnter roll number to update: ");
                readLine(rollNo, sizeof(rollNo));

                int index = findStudent(rollNo);

                if (index == -1) {
                    printf("\nStudent profile not found.\n");
                } else {
                    updateProfile(index);
                }

                break;
            }

            case 5:
                deleteProfile();
                break;

            case 6:
                saveData();
                break;

            case 7:
                saveData();

                printf("\nThank you for using AcadTrack!\n");
                printf("Your academic records have been saved.\n");
                break;

            default:
                printf("\nInvalid choice! Please select 1-7.\n");
        }

    } while (choice != 7);

    return 0;
}
