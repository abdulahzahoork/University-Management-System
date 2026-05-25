# University Management System (UMS)

A **C++ Object-Oriented Programming** semester project that simulates a fully functional university management system. The system models a real university hierarchy — from the top-level university down to individual student assessments — and persists all data using CSV files.

---

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [OOP Concepts](#oop-concepts)
  - [Encapsulation](#encapsulation)
  - [Inheritance](#inheritance)
  - [Polymorphism](#polymorphism)
  - [Abstraction](#abstraction)
  - [Association and Composition](#association-and-composition)
- [Authority Hierarchy](#authority-hierarchy)
- [Data Files](#data-files)
- [How to Run](#how-to-run)

---

## Introduction

The **University Management System** is a console-based application built entirely in C++ (single translation unit). It manages the complete lifecycle of a university — including faculties, departments, degree programs, semesters, courses, teachers, and students. Users log in with one of five roles (Admin, Dean, HOD, Teacher, Student) and are presented with a role-specific menu. All data is loaded from and saved back to CSV files at runtime, so nothing is hardcoded.

The university modelled in the sample data is **The Superior University, Lahore**. It has one faculty (*Faculty of CS & IT*), three departments, and seven BS degree programs across those departments, each spanning 8 semesters (40 courses per program).

---

## Project Structure

```
UMS/
├── UMS.cpp                  # Entire source code (single file)
└── data/
    ├── university.csv       # University name and location
    ├── admin.csv            # Admin credentials
    ├── faculties.csv        # Faculty names
    ├── departments.csv      # Departments and their parent faculty
    ├── degree_programs.csv  # Degree programs and their parent department
    ├── semesters.csv        # Semesters belonging to each degree program
    ├── courses.csv          # Courses with credit hours, semester, and assigned teacher
    ├── teachers.csv         # Teacher profiles with roles (TEACHER / HOD / DEAN)
    ├── students.csv         # Student profiles and enrolled degree program
    ├── enrollments.csv      # Student-to-course enrollment mappings
    └── assessments.csv      # Per-student, per-course marks (quizzes, assignments, mid, final)
```

### Classes at a Glance

| Class | Responsibility |
|---|---|
| `University` | Root container; holds faculties and the admin |
| `Faculty` | Groups departments; has a Dean |
| `Department` | Groups degree programs and teachers; has an HOD |
| `DegreeProgram` | Holds semesters for one program (e.g. BS Computer Science) |
| `Semester` | Holds courses for one semester of a program |
| `Course` | Holds enrollments and is assigned to one teacher |
| `Person` | Abstract base class for all users |
| `Student` | Extends `Person`; holds enrollments and CGPA |
| `Teacher` | Extends `Person`; holds assigned courses and a role enum |
| `Admin` | Extends `Person`; manages the entire university structure |
| `Enrollment` | Links one student to one course and holds their `Assessment` |
| `Assessment` | Stores quiz, assignment, mid-term, and final marks; computes grade |
| `FileHandler` | Static utility class for all CSV read/write operations |

---

## OOP Concepts

### Encapsulation

Every class keeps its data members `private` and exposes them only through public getters and setters. No outside code reads or writes an object's fields directly.

```cpp
// Assessment — all marks are private
class Assessment {
private:
    float quizzes[4];
    float assignments[4];
    float midTerm;
    float finalExam;
    float totalMarks;
    char  grade;
public:
    float getQuiz(int i) const { return quizzes[i]; }
    void  setQuiz(int i, float m) { if (i>=0&&i<4) quizzes[i]=m; }
    // ...
};
```

The setter for `setQuiz` also validates the index before writing, preventing out-of-bounds access — a direct benefit of encapsulation.

Similarly, `Person` keeps `name`, `email`, `phone`, and `password` `protected` so only its own methods (and derived-class methods) can touch them directly.

---

### Inheritance

`Person` is the common base class for all user types. `Student`, `Teacher`, and `Admin` all inherit from `Person`, reusing the shared profile fields and virtual interface.

```
Person  (abstract)
├── Student
├── Teacher
└── Admin
```

```cpp
class Person {
protected:
    string name, email, phone, password;
public:
    virtual void showMenu() = 0;   // pure virtual
    virtual void display() const;  // virtual with default body
    virtual ~Person() {}
};

class Student : public Person { /* ... */ };
class Teacher : public Person { /* ... */ };
class Admin   : public Person { /* ... */ };
```

`Student` and `Teacher` also override `display()` to extend the base output with role-specific fields (reg number / CGPA for students; employee ID / role for teachers).

---

### Polymorphism

#### Runtime (Dynamic) Polymorphism

The application stores logged-in users as `Person*` and then uses `dynamic_cast` to confirm the actual runtime type before granting access to role-specific menus:

```cpp
Person* loggedInUser = uni.findPerson(email, students);

Admin*   a = dynamic_cast<Admin*>(loggedInUser);   // succeeds only if Admin
Teacher* t = dynamic_cast<Teacher*>(loggedInUser); // succeeds only if Teacher
Student* s = dynamic_cast<Student*>(loggedInUser); // succeeds only if Student
```

Each concrete class provides its own implementation of `showMenu()` and `display()`, which are resolved at runtime through the virtual function table.

#### Compile-time (Static) Polymorphism

`Course` and `Enrollment` both provide two overloads of `findEnrollment()` — one accepting a `Student*` and one accepting a `string` (reg number) — resolved at compile time:

```cpp
Enrollment* findEnrollment(Student* student) const;
Enrollment* findEnrollment(string regNo)     const;
```

`FileHandler` uses overloaded static methods to save different entity types without naming conflicts.

---

### Abstraction

`Person` is an **abstract class** — it cannot be instantiated directly because `showMenu()` is declared as a pure virtual function:

```cpp
virtual void showMenu() = 0;
```

This forces every concrete user type to define its own menu, while callers that hold a `Person*` need not know which concrete type they are dealing with. The internal complexity of grading (`calculateTotalMarks()`, `calculateGrade()`, `calculateGPA()`, `calculateCGPA()`) is hidden behind simple method calls.

`FileHandler` abstracts all I/O behind static methods. The rest of the application calls `FileHandler::saveAll(...)` or `FileHandler::loadAll(...)` without knowing anything about how CSV files are opened, parsed, or written.

---

### Association and Composition

#### Composition (owns and manages lifetime)

| Owner | Owned | Reason |
|---|---|---|
| `University` | `Admin*` | Deleted in `University::~University()` |
| `Department` | `Teacher*` list | Deleted in `Department::~Department()` |
| `Enrollment` | `Assessment` | Value member; dies with the enrollment |

Example — `Department` composes teachers and deletes them on destruction:

```cpp
Department::~Department() {
    for (Teacher* t : teachers) {
        delete t;
    }
}
```

`Semester` composes `Course` objects by value (`vector<Course>`), so courses are destroyed when the semester is destroyed.

#### Association (references without ownership)

| Class | Reference | Meaning |
|---|---|---|
| `Course` | `Teacher*` | A course is *taught by* a teacher, but does not own them |
| `Enrollment` | `Student*`, `Course*` | Links the two without owning either |
| `Student` | `DegreeProgram*` | A student *belongs to* a program, but does not own it |
| `Teacher` | `Department*` | A teacher *works in* a department, but does not own it |
| `Department` | `Teacher* hod` | HOD pointer is an alias into the teachers list |
| `Faculty` | `Teacher* dean` | Same pattern for the dean |

These raw-pointer associations let objects refer to each other across the object graph without duplicating data or creating ownership conflicts.

---

## Authority Hierarchy

The system enforces a strict authority hierarchy at both the data-model and the login levels.

```
University
└── Admin  (full control: add/remove any entity)
    └── Faculty  (managed by Dean)
        └── Department  (managed by HOD)
            ├── Teachers
            └── Degree Programs
                └── Semesters
                    └── Courses
                        └── Enrollments  (managed by Teacher)
                            └── Student
```

### Role Capabilities

| Role | What they can do |
|---|---|
| **Admin** | Add / remove faculties, departments, degree programs, semesters, courses, teachers, students; assign HOD / Dean; assign teachers to courses |
| **Dean** | View all departments, teachers, students, and degree programs in their faculty; view faculty-wide performance |
| **HOD** | View teachers, students, courses, and degree programs in their department; view department and individual student performance |
| **Teacher** | View own courses and enrolled students; enter quiz, assignment, mid-term, and final marks; view course and student performance |
| **Student** | View own profile, enrolled courses, marks, grades, GPA, and CGPA |

Role assignment is enforced at login through the `TeacherRole` enum (`TEACHER`, `HOD`, `DEAN`) and verified with `dynamic_cast` before any menu is shown:

```cpp
// Only a Teacher whose role is HOD can access the HOD menu
Teacher* t = dynamic_cast<Teacher*>(loggedInUser);
if (!t || t->getRole() != TeacherRole::HOD) {
    cout << "Access denied!" << endl;
    continue;
}
```

### Grading Scheme

Assessments follow a 100-point scale:

| Component | Marks |
|---|---|
| 4 Quizzes (5 each) | 20 |
| 4 Assignments (5 each) | 20 |
| Mid-Term | 20 |
| Final Exam | 40 |
| **Total** | **100** |

Grades: A ≥ 90 · B ≥ 80 · C ≥ 70 · D ≥ 60 · F < 60  
GPA: A = 4.0 · B = 3.0 · C = 2.0 · D = 1.0 · F = 0.0  
CGPA = average GPA across all enrolled courses.

---

## Data Files

All CSV files must be placed in a `data/` subdirectory relative to the executable. The application reads them on startup and writes them back whenever a change is made.

```
data/university.csv      data/admin.csv
data/faculties.csv       data/departments.csv
data/degree_programs.csv data/semesters.csv
data/courses.csv         data/teachers.csv
data/students.csv        data/enrollments.csv
data/assessments.csv
```

---

## How to Run

**Requirements:** Any C++11-compatible compiler (g++, clang++, MSVC).

```bash
# Compile
g++ -std=c++11 -o UMS UMS.cpp

# Make sure the data/ folder is in the same directory as the executable
# Then run:
./UMS          # Linux / macOS
UMS.exe        # Windows
```

On startup the system loads all CSV files and presents the role-selection menu. Sample credentials from the provided data:

| Role | Email | Password |
|---|---|---|
| Admin | admin@superior.edu.pk | 1234 |
| Dean | ahmad.raza@superior.edu.pk | 1234 |
| HOD (CS) | sara.khan@superior.edu.pk | 1234 |
| Teacher | ahmed.khan@superior.edu.pk | 1234 |
| Student | ahmed@superior.edu.pk | 1234 |
