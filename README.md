# AcadTrack
### Academic Performance & Planning System

AcadTrack is a menu-driven academic management system developed using C. It helps organize student academic records, monitor attendance, analyze performance, and identify areas that need improvement.

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

## Developer

**Falak Sinha**

B.Tech, Computer Science and Engineering  
Specialization in Artificial Intelligence

## Project Status

Current version: 3.0

AcadTrack is an independently developed C programming project.