# AcadTrack
### Student Academic Tracking & Performance Analysis System

AcadTrack is a C-based academic tracking system designed to help students monitor, evaluate and understand their academic progress. It combines academic record management with performance analysis, attendance monitoring, academic goal calculation and study priority recommendations.

Rather than simply storing student records, AcadTrack transforms academic data into meaningful insights, helping students identify their strengths, recognise areas that need improvement and make more informed decisions about their academic progress.


## Features

### 1. Student Profile Management
- Create and manage multiple student profiles.
- Search students using unique roll numbers.
- Update student information.
- Delete student profiles.

### 2. Academic Record Management
- Add multiple subjects to each student profile.
- Record obtained and maximum marks.
- Track classes held and classes attended.
- View subject-wise academic records.

### 3. Performance Analysis
- Calculate overall academic percentage.
- Identify strongest and weakest subjects.
- Classify overall academic performance.

### 4. Attendance Analysis
- Calculate subject-wise attendance percentages.
- Identify attendance below the 75% threshold.
- Calculate additional consecutive classes required to reach 75%.

### 5. Academic Target Calculator
- Set a desired academic percentage.
- Calculate the marks required to achieve the target.
- Compare current performance with the selected target.

### 6. Personalized Study Priorities
- Identify subjects requiring additional attention.
- Assign study priority levels based on marks and attendance.
- Display subject-specific study suggestions.

### 7. Data Persistence
- Save academic records using binary file handling.
- Automatically load previously saved records when the program starts.

## Technologies & Concepts Used

- C Programming Language
- Structures and Arrays
- Pointers
- Functions and Modular Programming
- String Handling
- File Handling (`fread`, `fwrite`)
- Input Validation

## Project Specifications

| Specification | Limit |
|---|---|
| Maximum students | 100 |
| Maximum subjects per student | 20 |
| Maximum name length | 49 characters |
| Maximum subject name length | 49 characters |
| Maximum roll number length | 19 characters |

## How to Compile and Run

**Requirements:** GCC compiler.

Compile using:

```bash
gcc project.c -o AcadTrack
```

Run on Windows:

```bash
AcadTrack.exe
```

## Data Storage

AcadTrack stores records locally in a binary file named `acadtrack_v3.dat`. Existing records are loaded when the program starts.

## Sample Program Output

### Main Menu

```text
ACADEMIC PERFORMANCE & PLANNING           
====================================================

Welcome to AcadTrack!
Manage academic records and track student progress.

Total saved student profiles: 0

====================================================
                    MAIN MENU                       
====================================================
 1. Add New Student Profile
 2. View All Student Profiles
 3. Search and Manage a Student
 4. Update Student Profile
 5. Delete Student Profile
 6. Save Records
 7. Exit Program
====================================================

Enter your choice (1-7):
```


### Student Academic Menu

```text
====================================================
              STUDENT ACADEMIC MENU
====================================================
Student: [Student Name]
Roll No: [Student Roll Number]

1. Add Subject and Marks
2. View Academic Records
3. Analyze Overall Performance
4. Attendance Analysis
5. Academic Target Calculator
6. Study Priorities
7. Update Student Profile
8. Back to Main Menu
====================================================

Enter your choice (1-8): [User Input]
```

### Key Capabilities

- Manage student profiles using unique roll numbers.
- Maintain subject-wise marks and attendance records.
- Analyse academic performance and identify strong and weak subjects.
- Monitor attendance percentages and attendance requirements.
- Calculate marks required to reach an academic target.
- Identify subjects that need more attention.
- Store records locally using binary file handling.


## Developer

**Falak Sinha**

B.Tech, Computer Science and Engineering  
Specialization in Artificial Intelligence

## Project Status

Current version: 3.0

AcadTrack is an independently developed C programming project.


## Conclusion

AcadTrack is a C-based academic management system designed to simplify the process of maintaining and analysing student academic records. It brings together student profile management, subject-wise marks, attendance tracking, performance analysis, and academic goal planning in one application.

The project demonstrates the practical use of C programming concepts such as structures, arrays, functions, input validation, and file handling. It also provides a foundation for future improvements, including a graphical interface, database integration, and multi-user accessibility.

AcadTrack aims to make academic record management more organised, accessible, and efficient.