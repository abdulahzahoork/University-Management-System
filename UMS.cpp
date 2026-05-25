#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//  -------------------------- Forward Declarations --------------------------

class Student;
class Teacher;
class Course;
class Enrollment;
class DegreeProgram;
class Semester;
class Department;
class Faculty;
class University;
class Admin;



//  -------------------------- ENUM --------------------------

enum class TeacherRole { TEACHER, HOD, DEAN };

string roleToString(TeacherRole role) {
    switch (role) {
        case TeacherRole::TEACHER: 
            return "TEACHER";
        case TeacherRole::HOD:     
            return "HOD";
        case TeacherRole::DEAN:    
            return "DEAN";
        default:                   
            return "TEACHER";
    }
}

TeacherRole stringToRole(string s) {
    if (s == "HOD") {
        return TeacherRole::HOD;
    }
    if (s == "DEAN") {
        return TeacherRole::DEAN;
    }
    return TeacherRole::TEACHER;
}



//  -------------------------- Person --------------------------

class Person {

protected:
    string name;
    string email;
    string phone;
    string password;

public:
    Person(string name, string email, string phone, string password) : name(name), email(email), phone(phone), password(password) {}
    
    // Getters
    string getName() const { 
        return name;     
    }

    string getEmail() const { 
        return email;     
    }

    string getPhone() const { 
        return phone;     
    }

    string getPassword() const { 
        return password;  
    }

    // Setters
    void setName(string n) { 
        name = n; 
    }

    void setEmail(string e) { 
        email = e; 
    }

    void setPhone(string p) { 
        phone = p; 
    }

    void setPassword(string p) { 
        password = p; 
    }

    // Virtual functions
    virtual void showMenu() = 0;
    virtual void display()  const;
    
    // Destructor
    virtual ~Person() {}
};
void Person::display() const {
    cout << "Name  : " << name  << endl;
    cout << "Email : " << email << endl;
    cout << "Phone : " << phone << endl;
}

//  -------------------------- Assessment --------------------------

class Assessment {

private:
    float quizzes[4];
    float assignments[4];
    float midTerm;
    float finalExam;
    float totalMarks;
    char  grade;

public:
    Assessment() : midTerm(0), finalExam(0), totalMarks(0), grade('F') {
        for (int i = 0; i < 4; i++) { 
            quizzes[i] = 0; 
            assignments[i] = 0; 
        }
    }

    // Getters
    float getQuiz(int i) const { 
        return quizzes[i];     
    }

    float getAssignment(int i) const { 
        return assignments[i]; 
    }

    float getMidTerm() const { 
        return midTerm;        
    }

    float getFinalExam() const { 
        return finalExam;      
    }

    float getTotalMarks() const { 
        return totalMarks;     
    }

    char getGrade() const { 
        return grade;          
    }

    // Setters
    void setQuiz(int i, float m) { 
        if (i>=0&&i<4) {
            quizzes[i]=m; 
        }
    }

    void setAssignment(int i, float m) { 
        if (i>=0&&i<4) {
            assignments[i]=m; 
        }
    }

    void setMidTerm(float m) { 
        midTerm   = m; 
    }

    void setFinal (float m)  { 
        finalExam = m; 
    }

    // Calculations
    void calculateTotalMarks() {
        float qt=0, at=0;
        for (int i=0;i<4;i++) { 
            qt+=quizzes[i]; 
            at+=assignments[i]; 
        }
        totalMarks = qt + at + midTerm + finalExam;
    }

    void calculateGrade() {
        if (totalMarks >= 90) {
            grade = 'A';
        } else if (totalMarks >= 80) {
            grade = 'B';
        } else if (totalMarks >= 70) {
            grade = 'C';
        } else if (totalMarks >= 60) {
            grade = 'D';
        } else {
            grade = 'F';
        }
    }

    void display() const {

        cout << "Quizzes     : ";
        for (int i=0;i<4;i++) {
            cout<<"Q"<<i+1<<": "<<quizzes[i]<<"/5  ";
        }
        cout << endl;

        cout << "Assignments : ";
        for (int i=0;i<4;i++) {
            cout<<"A"<<i+1<<": "<<assignments[i]<<"/5  ";
        }

        cout << endl;
        cout << "MidTerm: " << midTerm << " / 20"  << endl;
        cout << "Final: " << finalExam << " / 40"  << endl;
        cout << "Total Marks: " << totalMarks << " / 100" << endl;
        cout << "Grade: " << grade << endl;
    }
};

//  -------------------------- Enrollment --------------------------

class Enrollment {

private:
    Student* student;
    Course* course;
    Assessment assessment;
    float gpa;

public:
    Enrollment(Student* student, Course* course) : student(student), course(course), assessment(), gpa(0.0) {}

    // Getters
    Student* getStudent() const { 
        return student;    
    }

    Course* getCourse() const { 
        return course;     
    }

    Assessment& getAssessment() { 
        return assessment; 
    }

    const Assessment& getAssessment() const { 
        return assessment; 
    }

    float getGPA() const { 
        return gpa;
    }

    void setGPA(float g) { 
        gpa = g; 
    }

    void calculateGPA() {
        char g = assessment.getGrade();
        switch(g) {
            case 'A': 
                gpa=4.0; 
                break;
            case 'B': 
                gpa=3.0; 
                break;
            case 'C': 
                gpa=2.0; 
                break;
            case 'D': 
                gpa=1.0; 
                break;
            default:  
                gpa=0.0; 
                break;
        }
    }

    void display() const;
    
    // Destructor
    ~Enrollment() {}
};

//  -------------------------- Course --------------------------

class Course {

private:
    string courseCode;
    string title;
    int creditHours;
    Teacher* teacher;
    vector<Enrollment*> enrollments;

public:
    Course(string courseCode, string title, int creditHours) : courseCode(courseCode), title(title), creditHours(creditHours), teacher(nullptr) {}
    
    string getCourseCode() const { 
        return courseCode;  
    }

    // Getters
    string getTitle() const { 
        return title;       
    }


    int getCreditHours() const { 
        return creditHours; 
    }

    Teacher* getTeacher() const { 
        return teacher;
    }

    const vector<Enrollment*>& getEnrollments() const { 
        return enrollments; 
    }

    vector<Enrollment*>& getEnrollments() { 
        return enrollments; 
    }

    // Setters
    void setCourseCode (string c) { 
        courseCode = c; 
    }

    void setTitle (string t) { 
        title = t; 
    }

    void setCreditHours(int c) { 
        creditHours = c; 
    }

    void setTeacher(Teacher* t) { 
        teacher = t; 
    }

    void addEnrollment (Enrollment* e){ 
        enrollments.push_back(e); 
    }

    Enrollment* findEnrollment(Student* student) const;
    Enrollment* findEnrollment(string regNo) const;
    
    void display() const;
    
    // Destructor
    ~Course() {}
};

//  -------------------------- Semester --------------------------

class Semester {

private:
    string name;
    int semNumber;
    vector<Course> courses;

public:
    Semester(string name, int semNumber) : name(name), semNumber(semNumber) {}
    
    string getName() const { 
        return name;      
    }

    int getSemNumber() const { 
        return semNumber; 
    }

    const vector<Course>& getCourses() const { 
        return courses;   
    }

    vector<Course>& getCourses() { 
        return courses;   
    }

    void setName(string n) { 
        name = n; 
    }

    void setSemNumber(int s) { 
        semNumber = s; 
    }

    void addCourse(Course c) { 
        courses.push_back(c); 
    }

    void removeCourse(string courseCode) {
        for (int i=0;i<(int)courses.size();i++) {
            if (courses[i].getCourseCode()==courseCode) {
                courses.erase(courses.begin()+i);
                cout << "Course removed successfully!" << endl;
                return;
            }
        }
        cout << "Course not found!" << endl;
    }

    void display() const {
        cout << "Semester : " << name << " (Sem " << semNumber << ")" << endl;
        for (const Course& c : courses) {
            c.display();
        }
    }

    // Destructor
    ~Semester() {}
};

//  -------------------------- Degree Program --------------------------

class DegreeProgram {

private:
    string name;
    int duration;
    vector<Semester> semesters;

public:
    DegreeProgram(string name, int duration) : name(name), duration(duration) {}
    string getName() const { 
        return name;      
    }

    int getDuration() const { 
        return duration;  
    }

    const vector<Semester>& getSemesters() const { 
        return semesters; 
    }

    vector<Semester>& getSemesters() { 
        return semesters; 
    }

    void setName(string n) { 
        name = n; 
    }

    void setDuration(int d){ 
        duration = d; 
    }

    void addSemester(Semester s) { 
        semesters.push_back(s); 
    }

    void removeSemester(string semName) {
        for (int i=0;i<(int)semesters.size();i++) {
            if (semesters[i].getName()==semName) {
                semesters.erase(semesters.begin()+i);
                cout << "Semester removed successfully!" << endl;
                return;
            }
        }
        cout << "Semester not found!" << endl;
    }

    void display() const {
        cout << "Degree Program : " << name << " (" << duration << " semesters)" << endl;
        for (const Semester& s : semesters) {
            s.display();
        }
    }

    // Destructor
    ~DegreeProgram() {}
};

//  -------------------------- DEPARTMENT  (declarations only) --------------------------

class Department {

private:
    string                name;
    Teacher*              hod;
    vector<Teacher*>      teachers;
    vector<DegreeProgram> programs;

public:
    Department(string name) : name(name), hod(nullptr) {}
    string getName() const { 
        return name;     
    }

    // Getters
    Teacher* getHOD() const { 
        return hod;      
    }

    const vector<Teacher*>& getTeachers() const { 
        return teachers; 
    }

    vector<Teacher*>& getTeachers() { 
        return teachers; 
    }

    const vector<DegreeProgram>& getDegreePrograms() const { 
        return programs; 
    }

    vector<DegreeProgram>& getDegreePrograms() { 
        return programs; 
    }

    // Setters
    void setName(string n) { 
        name = n;              
    }

    void setHOD(Teacher* t) { 
        hod  = t;              
    }

    void addTeacher(Teacher* t) { 
        teachers.push_back(t); 
    }

    void addDegreeProgram(DegreeProgram p) { 
        programs.push_back(p); 
    }

    void removeTeacher(string employeeId);

    void removeDegreeProgram(string progName) {
        for (int i=0;i<(int)programs.size();i++) {
            if (programs[i].getName()==progName) {
                programs.erase(programs.begin()+i);
                cout << "Degree Program removed successfully!" << endl;
                return;
            }
        }
        cout << "Degree Program not found!" << endl;
    }

    void viewTeachers() const;
    void viewStudents() const;
    void viewDegreePrograms() const;
    void viewCourses() const;
    void viewDepartmentPerformance() const;
    void viewStudentPerformance(Student*) const;
    void display() const;

    // Destructor
    ~Department();
};

//  -------------------------- FACULTY  (declarations only) --------------------------

class Faculty {

private:
    string name;
    Teacher* dean;
    vector<Department> departments;

public:
    Faculty(string name) : name(name), dean(nullptr) {}
 
    // Getters
    string getName() const { 
        return name;        
    }

    Teacher* getDean() const { 
        return dean;        
    
    }
    const vector<Department>& getDepartments() const { 
        return departments; 
    }

    vector<Department>& getDepartments() { 
        return departments; 
    }

    // Setters
    void setName(string n) { 
        name = n;
    }

    void setDean(Teacher* t) { 
        dean = t;
    }

    void addDepartment(Department d) { 
        departments.push_back(d); 
    }

    void removeDepartment(string deptName) {
        for (int i=0;i<(int)departments.size();i++) {
            if (departments[i].getName()==deptName) {
                departments.erase(departments.begin()+i);
                cout << "Department removed successfully!" << endl;
                return;
            }
        }
        cout << "Department not found!" << endl;
    }

    void viewDepartments()  const;
    void viewTeachers() const;
    void viewStudents() const;
    void viewDegreePrograms() const;
    void viewFacultyPerformance() const;
    void display() const;
    
    // Destructor
    ~Faculty() {}
};

//  -------------------------- STUDENT --------------------------

class Student : public Person {

private:
    string regNo;
    string rollNo;
    DegreeProgram* program;
    vector<Enrollment*> enrollments;
    float cgpa;

public:
    Student(string name, string email, string phone, string password, string regNo, string rollNo) : Person(name, email, phone, password), regNo(regNo), rollNo(rollNo), program(nullptr), cgpa(0.0) {}
    
    // Getters
    string getRegNo() const { 
        return regNo;       
    }

    string getRollNo() const { 
        return rollNo;      
    }

    DegreeProgram* getProgram() const { 
        return program;     
    }

    vector<Enrollment*> getEnrollments() const { 
        return enrollments; 
    }

    float getCGPA() const { 
        return cgpa;        
    }

    // Setters
    void setRegNo(string r) { 
        regNo = r; 
    }

    void setRollNo(string r) { 
        rollNo  = r; 
    }

    void setProgram(DegreeProgram* p) { 
        program = p; 
    }

    void setCGPA(float c) { 
        cgpa = c; 
    }

    void addEnrollment(Enrollment* e) { 
        enrollments.push_back(e); 
    }

    void viewProfile() const;
    void viewCourses() const;
    void viewMarks() const;
    void viewGrade() const;
    void viewGPA() const;
    void viewCGPA() const;
    void calculateCGPA();
    void showMenu() override;
    void display() const override;

    // Destructor
    ~Student() {}
};

//  -------------------------- TEACHER --------------------------

class Teacher : public Person {

private:
    string employeeId;
    TeacherRole role;
    Department* department;
    vector<Course*> courses;

public:
    Teacher(string name, string email, string phone, string password, string employeeId, TeacherRole role = TeacherRole::TEACHER) : Person(name, email, phone, password), employeeId(employeeId), role(role), department(nullptr) {}

    // Getters
    string getEmployeeId() const { 
        return employeeId; 
    }

    TeacherRole getRole() const { 
        return role;       
    }

    Department* getDepartment() const { 
        return department; 
    }

    vector<Course*> getCourses() const { 
        return courses;    
    }

    // Setters
    void setEmployeeId(string e) { 
        employeeId = e; 
    }

    void setRole(TeacherRole r) { 
        role = r; 
    }

    void setDepartment(Department* d) { 
        department = d; 
    }

    void addCourse(Course* c) { 
        courses.push_back(c); 
    }

    void viewCourses() const;
    void viewStudents() const;
    void enterQuizMarks(Student* s, int index, float marks);
    void enterAssignmentMarks(Student* s, int index, float marks);
    void enterMidTermMarks(Student* s, float marks);
    void enterFinalMarks(Student* s, float marks);
    void viewCoursePerformance() const;
    void viewStudentPerformance(Student* s) const;
    void showMenu() override;
    void display() const override;

    // Destructor
    ~Teacher() {}
};

//  -------------------------- ADMIN --------------------------
class Admin : public Person {

private:
    string employeeId;

public:
    Admin(string name, string email, string phone, string password, string employeeId) : Person(name, email, phone, password), employeeId(employeeId) {}
    
    // Getter
    string getEmployeeId() const { 
        return employeeId; 
    }

    // Setter
    void setEmployeeId(string e) { 
        employeeId = e; 
    }

    // Admin functions
    void addFaculty(University* uni, string name);
    void removeFaculty(University* uni, string name);
    void addDepartment(University* uni, string facultyName, string deptName);
    void removeDepartment(University* uni, string facultyName, string deptName);
    void addDegreeProgram(University* uni, string deptName, string progName, int duration);
    void removeDegreeProgram(University* uni, string deptName, string progName);
    void addTeacher(University* uni, string deptName, string name, string email, string phone, string password, string employeeId);
    void removeTeacher(University* uni, string deptName, string employeeId);
    void assignTeacherToCourse(University* uni, string employeeId, string courseCode);
    void assignHOD(University* uni, string deptName, string employeeId);
    void assignDean(University* uni, string facultyName, string employeeId);
    void admitStudent(University* uni, vector<Student*>& students, string name, string email, string phone, string password, string regNo, string rollNo, string progName);
    void removeStudent(University* uni, vector<Student*>& students, string regNo);
    void addCourse(University* uni, string progName, string semName, string courseCode, string title, int creditHours);
    void removeCourse(University* uni, string progName, string semName, string courseCode);
    void showMenu(University* uni, vector<Student*>& students);
    
    void showMenu() override { 
        showMenu(nullptr, *(new vector<Student*>())); 
    }
    void display() const override;
    
    // Destructor
    ~Admin() {}
};


//  -------------------------- UNIVERSITY --------------------------

class University {

private:
    string name;
    string location;
    vector<Faculty> faculties;
    Admin* admin;

public:
    University(string name="", string location="") : name(name), location(location), admin(nullptr) {}
    
    // Getters
    string getName() const { 
        return name;      
    }

    string getLocation() const { 
        return location;  
    }

    vector<Faculty>& getFaculties() { 
        return faculties; 
    }

    Admin* getAdmin() const { 
        return admin;     
    }

    void setName(string n) { 
        name = n;           
    }

    void setLocation(string l)  { 
        location = l;
    }

    void setAdmin(Admin* a)  { 
        admin = a;
    }

    void addFaculty (Faculty f) { 
        faculties.push_back(f); 
    }

    void removeFaculty(string facultyName) {
        for (int i=0;i<(int)faculties.size();i++) {
            if (faculties[i].getName()==facultyName) {
                faculties.erase(faculties.begin()+i);
                cout << "Faculty removed successfully!" << endl;
                return;
            }
        }
        cout << "Faculty not found!" << endl;
    }

    Faculty* findFaculty(string name) {
        for (Faculty& f : faculties) {
            if (f.getName()==name) {
                return &f;
            }
        }
        return nullptr;
    }

    Department* findDepartment(string name) {
        for (Faculty& f : faculties) {
            for (Department& d : f.getDepartments()) {
                if (d.getName()==name) {
                    return &d;
                }
            }
        }
        return nullptr;
    }

    DegreeProgram* findDegreeProgram(string name) {
        for (Faculty& f : faculties) {
            for (Department& d : f.getDepartments()) {
                for (DegreeProgram& dp : d.getDegreePrograms()) {
                    if (dp.getName()==name) {
                        return &dp;
                    }
                }
            }
        }
        return nullptr;
    }

    Teacher* findTeacher(string employeeId) {
        for (Faculty& f : faculties) {
            for (Department& d : f.getDepartments()) {
                for (Teacher* t : d.getTeachers()) {
                    if (t->getEmployeeId()==employeeId) {
                        return t;
                    }
                }
            }
        }
        return nullptr;
    }
    
    Teacher* findTeacherByEmail(string email) {
        for (Faculty& f : faculties) {
            for (Department& d : f.getDepartments()) {
                for (Teacher* t : d.getTeachers()) {
                    if (t->getEmail()==email) {
                        return t;
                    }
                }
            }
        }
        return nullptr;
    }

    Course* findCourse(string courseCode) {
        for (Faculty& f : faculties) {
            for (Department& d : f.getDepartments()) {
                for (DegreeProgram& dp : d.getDegreePrograms()) {
                    for (Semester& s : dp.getSemesters()) {
                        for (Course& c : s.getCourses()) {
                            if (c.getCourseCode()==courseCode) {
                                return &c;
                            }
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    Semester* findSemester(string progName, string semName) {
        DegreeProgram* dp = findDegreeProgram(progName);
        if (!dp) {
            return nullptr;
        }
        for (Semester& s : dp->getSemesters()) {
            if (s.getName()==semName) {
                return &s;
            }
        }
        return nullptr;
    }

    Person* findPerson(string email, vector<Student*>& students) {
        if (admin && admin->getEmail()==email) {
            return admin;
        }
        for (Faculty& f : faculties) {
            for (Department& d : f.getDepartments()) {
                for (Teacher* t : d.getTeachers()) {
                    if (t->getEmail()==email) {
                        return t;
                    }
                }
            }
        }
        for (Student* s : students) {
            if (s->getEmail()==email) {
                return s;
            }
        }
        return nullptr;
    }

    void display() const {
        cout << "University : " << name     << endl;
        cout << "Location   : " << location << endl;
    }

    ~University() { 
        delete admin; 
    }
};

//  -------------------------- FILE HANDLER --------------------------

class FileHandler {
public:
    // ── Save functions ────────────────────────────────────────
    // This function saves the university details to a CSV file. It writes the name and location of the university.
    // Why is this function static? Answer: Because it does not depend on any instance of the FileHandler class. It can be called without creating an object of FileHandler, which makes it convenient for saving data from anywhere in the code.
    static void saveUniversity(University& uni) {
        ofstream f("data/university.csv");
        f << "name,location\n";
        f << uni.getName() << "," << uni.getLocation() << "\n";
    }

    static void saveAdmin(University& uni) {
        Admin* a = uni.getAdmin();
        if (!a) {
            return;
        }
        ofstream f("data/admin.csv");
        f << "employeeId,name,email,phone,password\n";
        f << a->getEmployeeId() << "," << a->getName() << ","
          << a->getEmail() << "," << a->getPhone() << ","
          << a->getPassword() << "\n";
    }

    static void saveFaculties(University& uni) {
        ofstream f("data/faculties.csv");
        f << "name\n";
        for (Faculty& fac : uni.getFaculties()) {
            f << fac.getName() << "\n";
        }
    }

    static void saveDepartments(University& uni) {
        ofstream f("data/departments.csv");
        f << "name,facultyName\n";
        for (Faculty& fac : uni.getFaculties()) {
            for (Department& d : fac.getDepartments()) {
                f << d.getName() << "," << fac.getName() << "\n";
            }
        }
    }

    static void saveTeachers(University& uni) {
        ofstream f("data/teachers.csv");
        f << "employeeId,name,email,phone,password,role,departmentName\n";
        for (Faculty& fac : uni.getFaculties()) {
            for (Department& d : fac.getDepartments()) {
                for (Teacher* t : d.getTeachers()) {
                    f << t->getEmployeeId() << "," << t->getName() << ","
                      << t->getEmail() << "," << t->getPhone() << ","
                      << t->getPassword() << "," << roleToString(t->getRole()) << ","
                      << d.getName() << "\n";
                }
            }
        }
    }

    static void saveDegreePrograms(University& uni) {
        ofstream f("data/degree_programs.csv");
        f << "name,duration,departmentName\n";
        for (Faculty& fac : uni.getFaculties()) {
            for (Department& d : fac.getDepartments()) {
                for (DegreeProgram& dp : d.getDegreePrograms()) {
                    f << dp.getName() << "," << dp.getDuration() << ","
                      << d.getName() << "\n";
                }
            }
        }
    }

    static void saveSemesters(University& uni) {
        ofstream f("data/semesters.csv");
        f << "name,semNumber,degreeProgramName\n";
        for (Faculty& fac : uni.getFaculties()) {   
            for (Department& d : fac.getDepartments()) {
                for (DegreeProgram& dp : d.getDegreePrograms()) {
                    for (Semester& s : dp.getSemesters()) {
                        f << s.getName() << "," << s.getSemNumber() << ","
                          << dp.getName() << "\n";
                    }
                }
            }
        }
    }

    static void saveCourses(University& uni) {
        ofstream f("data/courses.csv");
        f << "courseCode,title,creditHours,degreeProgramName,semesterName,teacherEmployeeId\n";
        for (Faculty& fac : uni.getFaculties()) {
            for (Department& d : fac.getDepartments()) {
                for (DegreeProgram& dp : d.getDegreePrograms()) {
                    for (Semester& s : dp.getSemesters()) {
                        for (Course& c : s.getCourses()) {
                            string tid = c.getTeacher() ? c.getTeacher()->getEmployeeId() : "";
                            f << c.getCourseCode() << "," << c.getTitle() << ","
                              << c.getCreditHours() << "," << dp.getName() << ","
                              << s.getName() << "," << tid << "\n";
                        }
                    }
                }
            }
        }
    }

    static void saveStudents(vector<Student*>& students) {
        ofstream f("data/students.csv");
        f << "regNo,rollNo,name,email,phone,password,degreeProgramName\n";
        for (Student* s : students) {
            string progName = s->getProgram() ? s->getProgram()->getName() : "";
            f << s->getRegNo() << "," << s->getRollNo() << "," << s->getName() << ","
              << s->getEmail() << "," << s->getPhone() << "," << s->getPassword() << ","
              << progName << "\n";
        }
    }

    static void saveEnrollments(vector<Student*>& students) {
        ofstream f("data/enrollments.csv");
        f << "regNo,courseCode\n";
        for (Student* s : students)
            for (Enrollment* e : s->getEnrollments())
                f << s->getRegNo() << "," << e->getCourse()->getCourseCode() << "\n";
    }

    static void saveAssessments(vector<Student*>& students) {
        ofstream f("data/assessments.csv");
        f << "regNo,courseCode,q1,q2,q3,q4,a1,a2,a3,a4,midTerm,finalExam\n";
        for (Student* s : students) {
            for (Enrollment* e : s->getEnrollments()) {
                const Assessment& a = e->getAssessment(); // const because we are only reading data, not modifying it.
                f << s->getRegNo() << "," << e->getCourse()->getCourseCode() << ","
                  << a.getQuiz(0) << "," << a.getQuiz(1) << ","
                  << a.getQuiz(2) << "," << a.getQuiz(3) << ","
                  << a.getAssignment(0) << "," << a.getAssignment(1) << ","
                  << a.getAssignment(2) << "," << a.getAssignment(3) << ","
                  << a.getMidTerm() << "," << a.getFinalExam() << "\n";
            }
        }
    }

    static void saveAll(University& uni, vector<Student*>& students) {
        saveUniversity(uni);
        saveAdmin(uni);
        saveFaculties(uni);
        saveDepartments(uni);
        saveTeachers(uni);
        saveDegreePrograms(uni);
        saveSemesters(uni);
        saveCourses(uni);
        saveStudents(students);
        saveEnrollments(students);
        saveAssessments(students);
    }

    // ── Helper: parse CSV line ────────────────────────────────
    static vector<string> parseCSVLine(const string& line) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        return fields;
    }

    // ── Load functions ────────────────────────────────────────
    static void loadUniversity(University& uni) {
        ifstream f("data/university.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        if (getline(f, line)) {
            auto fields = parseCSVLine(line);
            if (fields.size() >= 2) {
                uni.setName(fields[0]);
                uni.setLocation(fields[1]);
            }
        }
    }

    static void loadAdmin(University& uni) {
        ifstream f("data/admin.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        if (getline(f, line)) {
            auto fields = parseCSVLine(line);
            if (fields.size() >= 5) {
                Admin* a = new Admin(fields[1], fields[2], fields[3], fields[4], fields[0]);
                uni.setAdmin(a);
            }
        }
    }

    static void loadFaculties(University& uni) {
        ifstream f("data/faculties.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            uni.addFaculty(Faculty(line));
        }
    }

    static void loadDepartments(University& uni) {
        ifstream f("data/departments.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            auto fields = parseCSVLine(line);
            if (fields.size() < 2) {
                continue;
            }
            Faculty* fac = uni.findFaculty(fields[1]);
            if (fac) {
                fac->addDepartment(Department(fields[0]));
            }
        }
    }

    static void loadTeachers(University& uni) {
        ifstream f("data/teachers.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            auto fields = parseCSVLine(line);
            if (fields.size() < 7) {
                continue;
            }
            string eid=fields[0], name=fields[1], email=fields[2], phone=fields[3], pass=fields[4], roleStr=fields[5], deptName=fields[6];
            TeacherRole role = stringToRole(roleStr);
            Teacher* t = new Teacher(name, email, phone, pass, eid, role);
            Department* dept = uni.findDepartment(deptName);
            if (dept) {
                dept->addTeacher(t);
                t->setDepartment(dept);
                // assign HOD and Dean
                if (role == TeacherRole::HOD) {
                    dept->setHOD(t);
                }
                if (role == TeacherRole::DEAN) {
                    for (Faculty& fac : uni.getFaculties()) {
                        for (Department& d : fac.getDepartments()) {
                            if (d.getName() == deptName) {
                                fac.setDean(t);
                            }
                        }
                    }
                }
            }
        }
    }

    static void loadDegreePrograms(University& uni) {
        ifstream f("data/degree_programs.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            auto fields = parseCSVLine(line);
            if (fields.size() < 3) {
                continue;
            }
            Department* dept = uni.findDepartment(fields[2]);
            if (dept) {
                dept->addDegreeProgram(DegreeProgram(fields[0], stoi(fields[1])));
            }
        }
    }

    static void loadSemesters(University& uni) {
        ifstream f("data/semesters.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            auto fields = parseCSVLine(line);
            if (fields.size() < 3) {
                continue;
            }
            DegreeProgram* dp = uni.findDegreeProgram(fields[2]);
            if (dp) {
                dp->addSemester(Semester(fields[0], stoi(fields[1])));
            }
        }
    }

    static void loadCourses(University& uni) {
        ifstream f("data/courses.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            auto fields = parseCSVLine(line);
            if (fields.size() < 6) {
                continue;
            }
            string code=fields[0], title=fields[1], progName=fields[3],
                   semName=fields[4], teacherId=fields[5];
            int credits = stoi(fields[2]);
            Semester* sem = uni.findSemester(progName, semName);
            if (sem) {
                sem->addCourse(Course(code, title, credits));
                Course* c = uni.findCourse(code);
                if (c && !teacherId.empty()) {
                    Teacher* t = uni.findTeacher(teacherId);
                    if (t) {
                        c->setTeacher(t);
                        t->addCourse(c);
                    }
                }
            }
        }
    }

    static void loadStudents(University& uni, vector<Student*>& students) {
        ifstream f("data/students.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            auto fields = parseCSVLine(line);
            if (fields.size() < 7) {
                continue;
            }
            string regNo=fields[0], rollNo=fields[1], name=fields[2],
                   email=fields[3], phone=fields[4], pass=fields[5], progName=fields[6];
            Student* s = new Student(name, email, phone, pass, regNo, rollNo);
            DegreeProgram* dp = uni.findDegreeProgram(progName);
            if (dp) {
                s->setProgram(dp);
            }
            students.push_back(s); 
        }
    }

    static void loadEnrollments(University& uni, vector<Student*>& students) {
        ifstream f("data/enrollments.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            auto fields = parseCSVLine(line);
            if (fields.size() < 2) {
                continue;
            }
            string regNo=fields[0], courseCode=fields[1];
            // find student
            Student* student = nullptr;
            for (Student* s : students) {
                if (s->getRegNo()==regNo) { 
                    student=s; 
                    break; 
                }
            }
            // find course
            Course* course = uni.findCourse(courseCode);
            if (student && course) {
                Enrollment* e = new Enrollment(student, course);
                student->addEnrollment(e);
                course->addEnrollment(e);
            }
        }
    }

    static void loadAssessments(University& uni, vector<Student*>& students) { 
        ifstream f("data/assessments.csv");
        if (!f) {
            return;
        }
        string line;
        getline(f, line); // skip header
        while (getline(f, line)) {
            if (line.empty()) {
                continue;
            }
            auto fields = parseCSVLine(line);
            if (fields.size() < 12) {
                continue;
            }
            string regNo=fields[0], courseCode=fields[1];
            // find student
            Student* student = nullptr;
            for (Student* s : students) {
                if (s->getRegNo()==regNo) { 
                    student=s; 
                    break; 
                }
            }
            if (!student) {
                continue;
            }

            // find enrollment
            Course* course = uni.findCourse(courseCode);
            if (!course) {
                continue;
            }

            Enrollment* enroll = course->findEnrollment(student);
            if (!enroll) {
                continue;
            }

            // set marks
            Assessment& a = enroll->getAssessment();
            a.setQuiz(0, stof(fields[2]));  
            a.setQuiz(1, stof(fields[3]));
            a.setQuiz(2, stof(fields[4]));  
            a.setQuiz(3, stof(fields[5]));
            a.setAssignment(0, stof(fields[6])); 
            a.setAssignment(1, stof(fields[7]));
            a.setAssignment(2, stof(fields[8])); 
            a.setAssignment(3, stof(fields[9]));
            a.setMidTerm(stof(fields[10]));
            a.setFinal  (stof(fields[11]));
            a.calculateTotalMarks();
            a.calculateGrade();
            enroll->calculateGPA();
        }

        // calculate CGPA for all students
        for (Student* s : students) {
            s->calculateCGPA();
        }
    }

    static void loadAll(University& uni, vector<Student*>& students) {
        loadUniversity(uni);
        loadAdmin(uni);
        loadFaculties(uni);
        loadDepartments(uni);
        loadTeachers(uni);
        loadDegreePrograms(uni);
        loadSemesters(uni);
        loadCourses(uni);
        loadStudents(uni, students);
        loadEnrollments(uni, students);
        loadAssessments(uni, students);
    }
};



//  -------------------------- FUNCTION BODIES — all classes now complete --------------------------

// --- Enrollment ---

void Enrollment::display() const {
    cout << "Student: " << student->getName() << endl;
    cout << "Course: " << course->getTitle() << endl;
    cout << "GPA: " << gpa << endl;
    assessment.display();
}

// --- Course ---

Enrollment* Course::findEnrollment(Student* student) const {
    for (Enrollment* e : enrollments) {
        if (e->getStudent()==student) return e;
    }
    return nullptr;
}

Enrollment* Course::findEnrollment(string regNo) const {
    for (Enrollment* e : enrollments) {
        if (e->getStudent()->getRegNo()==regNo) {
            return e;
        }
    }
    return nullptr;
}

void Course::display() const {
    cout << "Course Code: " << courseCode  << endl;
    cout << "Title: " << title       << endl;
    cout << "Credit Hours: " << creditHours << endl;
    if (teacher) {
        cout << "Teacher: " << teacher->getName() << endl;
    } else {
        cout << "Teacher: Not Assigned" << endl;
    }
}

// --- Department ---

void Department::removeTeacher(string employeeId) {
    for (int i=0;i<(int)teachers.size();i++) {
        if (teachers[i]->getEmployeeId()==employeeId) {
            delete teachers[i];
            teachers.erase(teachers.begin()+i);
            cout << "Teacher removed successfully!" << endl;
            return;
        }
    }
    cout << "Teacher not found!" << endl;
}

void Department::viewTeachers() const {
    cout << "\n--- Teachers in " << name << " ---" << endl;
    for (Teacher* t : teachers) {
        t->display();
    }
}

void Department::viewStudents() const {
    cout << "\n--- Students in " << name << " ---" << endl;
    for (const DegreeProgram& dp : programs) {
        for (const Semester& s : dp.getSemesters()) {
            for (const Course& c : s.getCourses()) {
                for (Enrollment* e : c.getEnrollments()) {
                    e->getStudent()->display();
                }
            }
        }
    }
}

void Department::viewDegreePrograms() const {
    cout << "\n--- Degree Programs in " << name << " ---" << endl;
    for (const DegreeProgram& dp : programs) {
        dp.display();
    }
}

void Department::viewCourses() const {
    cout << "\n--- Courses in " << name << " ---" << endl;
    for (const DegreeProgram& dp : programs) {
        for (const Semester& s : dp.getSemesters()) {
            for (const Course& c : s.getCourses()) {
                c.display();
            }
        }
    }
}
void Department::viewDepartmentPerformance() const {
    cout << "\n--- Department Performance: " << name << " ---" << endl;
    for (const DegreeProgram& dp : programs) {
        for (const Semester& s : dp.getSemesters()) {
            for (const Course& c : s.getCourses()) {
                for (Enrollment* e : c.getEnrollments()) {
                    cout << "Student: " << e->getStudent()->getName()
                         << " | Course: " << c.getTitle()
                         << " | Grade: "  << e->getAssessment().getGrade()
                         << " | GPA: "    << e->getGPA() << endl;
                }
            }
        }
    }
}

void Department::viewStudentPerformance(Student* s) const {
    cout << "\n--- Student Performance ---" << endl;
    for (const DegreeProgram& dp : programs) {
        for (const Semester& sem : dp.getSemesters()) {
            for (const Course& c : sem.getCourses()) {
                Enrollment* e = c.findEnrollment(s);
                if (e) {
                    cout << "Course: " << c.getTitle()
                         << " | Grade: " << e->getAssessment().getGrade()
                         << " | GPA: "   << e->getGPA() << endl;
                }
            }
        }
    }
}

void Department::display() const {
    cout << "Department: " << name << endl;
    if (hod) {
        cout << "HOD: " << hod->getName() << endl;
    } else {
        cout << "HOD: Not Assigned" << endl;
    }
}
Department::~Department() {
    for (Teacher* t : teachers) {
        delete t;
    }
}

// --- Faculty ---

void Faculty::viewDepartments() const {
    cout << "\n--- Departments in " << name << " ---" << endl;
    for (const Department& d : departments) {
        d.display();
    }
}

void Faculty::viewTeachers() const {
    cout << "\n--- Teachers in " << name << " ---" << endl;
    for (const Department& d : departments) {
        for (Teacher* t : d.getTeachers()) {
            t->display();
        }
    }
}
void Faculty::viewStudents() const {
    cout << "\n--- Students in " << name << " ---" << endl;
    for (const Department& d : departments) {
        for (const DegreeProgram& dp : d.getDegreePrograms()) {
            for (const Semester& s : dp.getSemesters()) {
                for (const Course& c : s.getCourses()) {
                    for (Enrollment* e : c.getEnrollments()) {
                        e->getStudent()->display();
                    }
                }
            }
        }
    }
}

void Faculty::viewDegreePrograms() const {
    cout << "\n--- Degree Programs in " << name << " ---" << endl;
    for (const Department& d : departments) {
        for (const DegreeProgram& dp : d.getDegreePrograms()) {
            dp.display();
        }
    }
}

void Faculty::viewFacultyPerformance() const {
    cout << "\n--- Faculty Performance: " << name << " ---" << endl;
    for (const Department& d : departments) {
        for (const DegreeProgram& dp : d.getDegreePrograms()) {
            for (const Semester& s : dp.getSemesters()) {
                for (const Course& c : s.getCourses()) {
                    for (Enrollment* e : c.getEnrollments()) {
                        cout << "Student: " << e->getStudent()->getName()
                             << " | Course: " << c.getTitle()
                             << " | Grade: " << e->getAssessment().getGrade()
                             << " | GPA: " << e->getGPA() << endl;
                    }
                }
            }
        }
    }
}

void Faculty::display() const {
    cout << "Faculty: " << name << endl;
    if (dean) {
        cout << "Dean: " << dean->getName() << endl;
    } else {
        cout << "Dean: Not Assigned" << endl;
    }
}

// --- Student ---

void Student::display() const {
    Person::display();
    cout << "Reg No: " << regNo  << endl;
    cout << "Roll No: " << rollNo << endl;
    cout << "CGPA: " << cgpa   << endl;
}

void Student::showMenu() {
    int choice;
    do {
        cout << "\nStudent Menu: " << endl;
        cout << "1. View Profile" << endl;
        cout << "2. View Courses" << endl;
        cout << "3. View Marks" << endl;
        cout << "4. View Grades" << endl;
        cout << "5. View GPA" << endl;
        cout << "6. View CGPA" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter choice: ";
        cin  >> choice;
        switch(choice) {
            case 1: 
                viewProfile(); 
                break;
            case 2: 
                viewCourses(); 
                break;
            case 3: 
                viewMarks();   
                break;
            case 4: 
                viewGrade();   
                break;
            case 5: 
                viewGPA();     
                break;
            case 6: 
                viewCGPA();    
                break;
            case 0: 
                cout << "Logging out..." << endl; 
                break;
            default: 
                cout << "Invalid choice!" << endl;
        }
    } while(choice != 0);
}

void Student::viewProfile() const {
    cout << "\n--- Student Profile ---" << endl;
    display();
    if (program) {
        cout << "Program : " << program->getName() << endl;
    }
}

void Student::viewCourses() const {
    cout << "\n--- My Courses ---" << endl;
    for (Enrollment* e : enrollments) {
        e->getCourse()->display();
    }
}

void Student::viewMarks() const {
    cout << "\n--- My Marks ---" << endl;
    for (Enrollment* e : enrollments) {
        cout << "\nCourse: " << e->getCourse()->getTitle() << endl;
        e->getAssessment().display();
    }
}

void Student::viewGrade() const {
    cout << "\n--- My Grades ---" << endl;
    for (Enrollment* e : enrollments) {
        cout << e->getCourse()->getTitle() << " : "
             << e->getAssessment().getGrade() << endl;
    }
}

void Student::viewGPA() const {
    cout << "\n--- My GPA ---" << endl;
    for (Enrollment* e : enrollments) {
        cout << e->getCourse()->getTitle() << " : " << e->getGPA() << endl;
    }
}

void Student::viewCGPA() const {
    cout << "\n--- My CGPA ---" << endl;
    cout << "CGPA: " << cgpa << endl;
}

void Student::calculateCGPA() {
    if (enrollments.empty()) {
        return;
    }
    float total = 0;
    for (Enrollment* e : enrollments) {
        total += e->getGPA();
    }
    cgpa = total / enrollments.size();
}


// --- Teacher ---

void Teacher::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << endl;
    cout << "Role: " << roleToString(role) << endl;
}

void Teacher::showMenu() {
    int choice;
    do {
        cout << "\nTeacher Menu: " << endl;
        cout << "1. View Courses" << endl;
        cout << "2. View Students" << endl;
        cout << "3. Enter Quiz Marks" << endl;
        cout << "4. Enter Assignment Marks" << endl;
        cout << "5. Enter MidTerm Marks" << endl;
        cout << "6. Enter Final Marks" << endl;
        cout << "7. View Course Performance" << endl;
        cout << "8. View Student Performance" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter choice: ";
        cin  >> choice;
        switch(choice) {
            case 1: 
                viewCourses();  
                break;
            case 2: 
                viewStudents(); 
                break;
            case 3: {
                string regNo; int index; float marks;
                cout << "Enter Student Reg No: ";    
                cin >> regNo;
                cout << "Enter Quiz No (1-4): ";     
                cin >> index;
                cout << "Enter Marks (out of 5): ";  
                cin >> marks;
                for (Course* c : courses) {
                    for (Enrollment* e : c->getEnrollments()) {
                        if (e->getStudent()->getRegNo()==regNo) {
                            enterQuizMarks(e->getStudent(), index-1, marks);
                            break;
                        }
                    }
                 }
                break;
            }
            case 4: {
                string regNo; int index; float marks;
                cout << "Enter Student Reg No: ";          
                cin >> regNo;
                cout << "Enter Assignment No (1-4): ";     
                cin >> index;
                cout << "Enter Marks (out of 5): ";        
                cin >> marks;
                for (Course* c : courses) {
                    for (Enrollment* e : c->getEnrollments()) {
                        if (e->getStudent()->getRegNo()==regNo) {
                            enterAssignmentMarks(e->getStudent(), index-1, marks);
                            break;
                        }
                    }
                }
                break;
            }
            case 5: {
                string regNo; float marks;
                cout << "Enter Student Reg No: ";     
                cin >> regNo;
                cout << "Enter Marks (out of 20): ";  
                cin >> marks;
                for (Course* c : courses) {
                    for (Enrollment* e : c->getEnrollments()) {
                        if (e->getStudent()->getRegNo()==regNo) {
                            enterMidTermMarks(e->getStudent(), marks);
                            break;
                        }
                    }
                }
                break;
            }
            case 6: {
                string regNo; float marks;
                cout << "Enter Student Reg No: ";     
                cin >> regNo;
                cout << "Enter Marks (out of 40): ";  
                cin >> marks;
                for (Course* c : courses) {
                    for (Enrollment* e : c->getEnrollments()) {
                        if (e->getStudent()->getRegNo()==regNo) {
                            enterFinalMarks(e->getStudent(), marks);
                            break;
                        }
                    }
                }
                break;
            }
            case 7: 
                viewCoursePerformance(); 
                break;
            case 8: {
                string regNo;
                cout << "Enter Student Reg No: "; 
                cin >> regNo;
                for (Course* c : courses) {
                    for (Enrollment* e : c->getEnrollments()) {
                        if (e->getStudent()->getRegNo()==regNo) {
                            viewStudentPerformance(e->getStudent());
                            break;
                        }
                    }
                }
                break;
            }
            case 0: 
                cout << "Logging out..." << endl; 
                break;
            default: 
                cout << "Invalid choice!" << endl;
        }
    } while(choice != 0);
}

void Teacher::viewCourses() const {
    cout << "\n--- My Courses ---" << endl;
    for (Course* c : courses) {
        c->display();
    }
}

void Teacher::viewStudents() const {
    cout << "\n--- My Students ---" << endl;
    for (Course* c : courses) {
        cout << "\nCourse: " << c->getTitle() << endl;
        for (Enrollment* e : c->getEnrollments()) {
            e->getStudent()->display();
        }
    }
}

void Teacher::enterQuizMarks(Student* s, int index, float marks) {
    for (Course* c : courses) {
        Enrollment* e = c->findEnrollment(s);
        if (e) {
            e->getAssessment().setQuiz(index, marks);
            e->getAssessment().calculateTotalMarks();
            e->getAssessment().calculateGrade();
            e->calculateGPA();
            s->calculateCGPA();
            cout << "Quiz marks entered successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void Teacher::enterAssignmentMarks(Student* s, int index, float marks) {
    for (Course* c : courses) {
        Enrollment* e = c->findEnrollment(s);
        if (e) {
            e->getAssessment().setAssignment(index, marks);
            e->getAssessment().calculateTotalMarks();
            e->getAssessment().calculateGrade();
            e->calculateGPA();
            s->calculateCGPA();
            cout << "Assignment marks entered successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void Teacher::enterMidTermMarks(Student* s, float marks) {
    for (Course* c : courses) {
        Enrollment* e = c->findEnrollment(s);
        if (e) {
            e->getAssessment().setMidTerm(marks);
            e->getAssessment().calculateTotalMarks();
            e->getAssessment().calculateGrade();
            e->calculateGPA();
            s->calculateCGPA();
            cout << "MidTerm marks entered successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void Teacher::enterFinalMarks(Student* s, float marks) {
    for (Course* c : courses) {
        Enrollment* e = c->findEnrollment(s);
        if (e) {
            e->getAssessment().setFinal(marks);
            e->getAssessment().calculateTotalMarks();
            e->getAssessment().calculateGrade();
            e->calculateGPA();
            s->calculateCGPA();
            cout << "Final marks entered successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void Teacher::viewCoursePerformance() const {
    cout << "\n--- Course Performance ---" << endl;
    for (Course* c : courses) {
        cout << "\nCourse: " << c->getTitle() << endl;
        for (Enrollment* e : c->getEnrollments()) {
            cout << "  Student: " << e->getStudent()->getName()
                 << " | Grade: "  << e->getAssessment().getGrade()
                 << " | GPA: "    << e->getGPA() << endl;
        }
    }
}

void Teacher::viewStudentPerformance(Student* s) const {
    cout << "\n--- Student Performance ---" << endl;
    for (Course* c : courses) {
        Enrollment* e = c->findEnrollment(s);
        if (e) {
            cout << "Course: " << c->getTitle()
                 << " | Grade: " << e->getAssessment().getGrade()
                 << " | GPA: "   << e->getGPA() << endl;
        }
    }
}

// --- Admin ---

void Admin::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << endl;
}

void Admin::addFaculty(University* uni, string name) {
    uni->addFaculty(Faculty(name));
    FileHandler::saveFaculties(*uni);
    cout << "Faculty '" << name << "' added successfully!" << endl;
}

void Admin::removeFaculty(University* uni, string name) {
    uni->removeFaculty(name);
    FileHandler::saveFaculties(*uni);
}

void Admin::addDepartment(University* uni, string facultyName, string deptName) {
    Faculty* fac = uni->findFaculty(facultyName);
    if (!fac) { 
        cout << "Faculty not found!" << endl; 
        return; 
    }
    fac->addDepartment(Department(deptName));
    FileHandler::saveDepartments(*uni);
    cout << "Department '" << deptName << "' added successfully!" << endl;
}

void Admin::removeDepartment(University* uni, string facultyName, string deptName) {
    Faculty* fac = uni->findFaculty(facultyName);
    if (!fac) { 
        cout << "Faculty not found!" << endl; 
        return; 
    }
    fac->removeDepartment(deptName);
    FileHandler::saveDepartments(*uni);
}

void Admin::addDegreeProgram(University* uni, string deptName, string progName, int duration) {
    Department* dept = uni->findDepartment(deptName);
    if (!dept) { 
        cout << "Department not found!" << endl; 
        return; 
    }
    dept->addDegreeProgram(DegreeProgram(progName, duration));
    FileHandler::saveDegreePrograms(*uni);
    cout << "Degree Program '" << progName << "' added successfully!" << endl;
}

void Admin::removeDegreeProgram(University* uni, string deptName, string progName) {
    Department* dept = uni->findDepartment(deptName);
    if (!dept) { 
        cout << "Department not found!" << endl; 
        return; 
    }
    dept->removeDegreeProgram(progName);
    FileHandler::saveDegreePrograms(*uni);
}

void Admin::addTeacher(University* uni, string deptName, string name, string email, string phone, string password, string employeeId) {
    Department* dept = uni->findDepartment(deptName);
    if (!dept) { 
        cout << "Department not found!" << endl; 
        return; 
    }
    Teacher* t = new Teacher(name, email, phone, password, employeeId);
    dept->addTeacher(t);
    t->setDepartment(dept);
    FileHandler::saveTeachers(*uni);
    cout << "Teacher '" << name << "' added successfully!" << endl;
}

void Admin::removeTeacher(University* uni, string deptName, string employeeId) {
    Department* dept = uni->findDepartment(deptName);
    if (!dept) { 
        cout << "Department not found!" << endl; 
        return; 
    }
    dept->removeTeacher(employeeId);
    FileHandler::saveTeachers(*uni);
}

void Admin::assignTeacherToCourse(University* uni, string employeeId, string courseCode) {
    Teacher* t = uni->findTeacher(employeeId);
    Course*  c = uni->findCourse(courseCode);
    if (!t) { 
        cout << "Teacher not found!" << endl; 
        return; 
    }
    if (!c) { 
        cout << "Course not found!"  << endl; 
        return; 
    }
    c->setTeacher(t);
    t->addCourse(c);
    FileHandler::saveCourses(*uni);
    FileHandler::saveTeachers(*uni);
    cout << "Teacher assigned to course successfully!" << endl;
}

void Admin::assignHOD(University* uni, string deptName, string employeeId) {
    Department* dept = uni->findDepartment(deptName);
    Teacher* t = uni->findTeacher(employeeId);
    if (!dept) { 
        cout << "Department not found!" << endl; 
        return; 
    }
    if (!t) { 
        cout << "Teacher not found!"    << endl; 
        return; 
    }
    t->setRole(TeacherRole::HOD);
    dept->setHOD(t);
    FileHandler::saveTeachers(*uni);
    cout << "HOD assigned successfully!" << endl;
}

void Admin::assignDean(University* uni, string facultyName, string employeeId) {
    Faculty* fac = uni->findFaculty(facultyName);
    Teacher* t   = uni->findTeacher(employeeId);
    if (!fac) { 
        cout << "Faculty not found!"  << endl; 
        return; 
    }
    if (!t) { 
        cout << "Teacher not found!" << endl; 
        return; 
    }
    t->setRole(TeacherRole::DEAN);
    fac->setDean(t);
    FileHandler::saveTeachers(*uni);
    cout << "Dean assigned successfully!" << endl;
}

void Admin::admitStudent(University* uni, vector<Student*>& students, string name, string email, string phone, string password, string regNo, string rollNo, string progName) {
    DegreeProgram* dp = uni->findDegreeProgram(progName);
    if (!dp) { 
        cout << "Degree Program not found!" << endl; 
        return; 
    }
    Student* s = new Student(name, email, phone, password, regNo, rollNo);
    s->setProgram(dp);
    students.push_back(s);
    // auto enroll in all courses
    for (Semester& sem : dp->getSemesters()) {
        for (Course& c : sem.getCourses()) {
            Enrollment* e = new Enrollment(s, &c);
            s->addEnrollment(e);
            c.addEnrollment(e);
        }
    }
    FileHandler::saveStudents(students);
    FileHandler::saveEnrollments(students);
    FileHandler::saveAssessments(students);
    cout << "Student '" << name << "' admitted successfully!" << endl;
}

void Admin::removeStudent(University* uni, vector<Student*>& students, string regNo) {
    for (int i=0;i<(int)students.size();i++) {
        if (students[i]->getRegNo()==regNo) {
            // remove enrollments from courses
            for (Enrollment* e : students[i]->getEnrollments()) {
                Course* c = e->getCourse();
                auto& enrs = c->getEnrollments(); // auto here is for vector<Enrollment*>&
                for (int j=0;j<(int)enrs.size();j++) {
                    if (enrs[j]==e) { 
                        enrs.erase(enrs.begin()+j); 
                        break; 
                    }
                }
                delete e;
            }
            delete students[i];
            students.erase(students.begin()+i);
            FileHandler::saveStudents(students);
            FileHandler::saveEnrollments(students);
            FileHandler::saveAssessments(students);
            cout << "Student removed successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void Admin::addCourse(University* uni, string progName, string semName, string courseCode, string title, int creditHours) {
    Semester* sem = uni->findSemester(progName, semName);
    if (!sem) { 
        cout << "Semester not found!" << endl; 
        return; 
    }
    sem->addCourse(Course(courseCode, title, creditHours));
    FileHandler::saveCourses(*uni);
    cout << "Course '" << title << "' added successfully!" << endl;
}

void Admin::removeCourse(University* uni, string progName, string semName, string courseCode) {
    Semester* sem = uni->findSemester(progName, semName);
    if (!sem) { 
        cout << "Semester not found!" << endl; 
        return; 
    }
    sem->removeCourse(courseCode);
    FileHandler::saveCourses(*uni);
}

void Admin::showMenu(University* uni, vector<Student*>& students) {
    int choice;
    do {
        cout << "Admin Menu: " << endl;
        cout << "1.  Add Faculty" << endl;
        cout << "2.  Remove Faculty" << endl;
        cout << "3.  Add Department" << endl;
        cout << "4.  Remove Department" << endl;
        cout << "5.  Add Degree Program" << endl;
        cout << "6.  Remove Degree Program" << endl;
        cout << "7.  Add Teacher" << endl;
        cout << "8.  Remove Teacher" << endl;
        cout << "9.  Assign Teacher to Course" << endl;
        cout << "10. Assign HOD" << endl;
        cout << "11. Assign Dean" << endl;
        cout << "12. Admit Student" << endl;
        cout << "13. Remove Student" << endl;
        cout << "14. Add Course" << endl;
        cout << "15. Remove Course" << endl;
        cout << "0.  Logout" << endl;
        cout << "Enter choice: ";
        cin  >> choice;

        switch(choice) {
            case 1: {
                string name;
                cout << "Enter Faculty Name: "; 
                cin.ignore(); 
                getline(cin, name);
                addFaculty(uni, name);
                break;
            }
            case 2: {
                string name;
                cout << "Enter Faculty Name: "; 
                cin.ignore(); 
                getline(cin, name);
                removeFaculty(uni, name);
                break;
            }
            case 3: {
                string facultyName, deptName;
                cout << "Enter Faculty Name: ";     
                cin.ignore(); 
                getline(cin, facultyName);
                cout << "Enter Department Name: ";  
                getline(cin, deptName);
                addDepartment(uni, facultyName, deptName);
                break;
            }
            case 4: {
                string facultyName, deptName;
                cout << "Enter Faculty Name: ";     
                cin.ignore(); 
                getline(cin, facultyName);
                cout << "Enter Department Name: ";  
                getline(cin, deptName);
                removeDepartment(uni, facultyName, deptName);
                break;
            }
            case 5: {
                string deptName, progName; int duration;
                cout << "Enter Department Name: ";      
                cin.ignore(); 
                getline(cin, deptName);
                cout << "Enter Program Name: ";         
                getline(cin, progName);
                cout << "Enter Duration (semesters): "; 
                cin >> duration;
                addDegreeProgram(uni, deptName, progName, duration);
                break;
            }
            case 6: {
                string deptName, progName;
                cout << "Enter Department Name: "; 
                cin.ignore(); 
                getline(cin, deptName);
                cout << "Enter Program Name: ";    
                getline(cin, progName);
                removeDegreeProgram(uni, deptName, progName);
                break;
            }
            case 7: {
                string deptName, name, email, phone, password, employeeId;
                cout << "Enter Department Name: "; 
                cin.ignore(); 
                getline(cin, deptName);
                cout << "Enter Name: ";            
                getline(cin, name);
                cout << "Enter Email: ";           
                cin >> email;
                cout << "Enter Phone: ";           
                cin >> phone;
                cout << "Enter Password: ";        
                cin >> password;
                cout << "Enter Employee ID: ";     
                cin >> employeeId;
                addTeacher(uni, deptName, name, email, phone, password, employeeId);
                break;
            }
            case 8: {
                string deptName, employeeId;
                cout << "Enter Department Name: "; 
                cin.ignore(); 
                getline(cin, deptName);
                cout << "Enter Employee ID: ";     
                cin >> employeeId;
                removeTeacher(uni, deptName, employeeId);
                break;
            }
            case 9: {
                string employeeId, courseCode;
                cout << "Enter Employee ID: ";  
                cin >> employeeId;
                cout << "Enter Course Code: ";  
                cin >> courseCode;
                assignTeacherToCourse(uni, employeeId, courseCode);
                break;
            }
            case 10: {
                string deptName, employeeId;
                cout << "Enter Department Name: "; 
                cin.ignore(); 
                getline(cin, deptName);
                cout << "Enter Employee ID: ";     
                cin >> employeeId;
                assignHOD(uni, deptName, employeeId);
                break;
            }
            case 11: {
                string facultyName, employeeId;
                cout << "Enter Faculty Name: "; 
                cin.ignore(); 
                getline(cin, facultyName);
                cout << "Enter Employee ID: ";  
                cin >> employeeId;
                assignDean(uni, facultyName, employeeId);
                break;
            }
            case 12: {
                string name, email, phone, password, regNo, rollNo, progName;
                cout << "Enter Name: ";         
                cin.ignore(); 
                getline(cin, name);
                cout << "Enter Email: ";        
                cin >> email;
                cout << "Enter Phone: ";        
                cin >> phone;
                cout << "Enter Password: ";     
                cin >> password;
                cout << "Enter Reg No: ";       
                cin >> regNo;
                cout << "Enter Roll No: ";      
                cin >> rollNo;
                cout << "Enter Program Name: "; 
                cin.ignore(); 
                getline(cin, progName);
                admitStudent(uni, students, name, email, phone, password, regNo, rollNo, progName);
                break;
            }
            case 13: {
                string regNo;
                cout << "Enter Reg No: "; 
                cin >> regNo;
                removeStudent(uni, students, regNo);
                break;
            }
            case 14: {
                string progName, semName, courseCode, title; 
                int creditHours;
                cout << "Enter Program Name: ";  
                cin.ignore(); 
                getline(cin, progName);
                cout << "Enter Semester Name: "; 
                getline(cin, semName);
                cout << "Enter Course Code: ";   
                cin >> courseCode;
                cout << "Enter Course Title: ";  
                cin.ignore(); 
                getline(cin, title);
                cout << "Enter Credit Hours: ";  
                cin >> creditHours;
                addCourse(uni, progName, semName, courseCode, title, creditHours);
                break;
            }
            case 15: {
                string progName, semName, courseCode;
                cout << "Enter Program Name: ";  
                cin.ignore(); 
                getline(cin, progName);
                cout << "Enter Semester Name: "; 
                getline(cin, semName);
                cout << "Enter Course Code: ";   
                cin >> courseCode;
                removeCourse(uni, progName, semName, courseCode);
                break;
            }
            case 0: 
                cout << "Logging out..." << endl; 
                break;
            default: 
                cout << "Invalid choice!" << endl;
        }
    } while(choice != 0);
}

//  -------------------------- MAIN FUNCTION --------------------------

int main() {
    University uni;
    vector<Student*> students;

    // ── Load all data from CSV files ──────────────────────────
    cout << "Loading data..." << endl;
    FileHandler::loadAll(uni, students);
    cout << "Data loaded successfully!" << endl;

    // ── Application Loop ──────────────────────────────────────
    int roleChoice;
    do {
        cout << "\nThe Superior University" << endl;
        cout << "University Management System: " << endl;
        cout << "1. Admin" << endl;
        cout << "2. Dean" << endl;
        cout << "3. HOD" << endl;
        cout << "4. Teacher" << endl;
        cout << "5. Student" << endl;
        cout << "0. Exit" << endl;
        cout << "Select Role: ";
        cin  >> roleChoice;

        if (roleChoice == 0) {
            cout << "Exiting system. Goodbye!" << endl;
            break;
        }

        if (roleChoice < 1 || roleChoice > 5) {
            cout << "Invalid choice!" << endl;
            continue;
        }

        // ── Login ─────────────────────────────────────────────
        string email, password;
        cout << "Enter Email: ";    
        cin >> email;
        cout << "Enter Password: "; 
        cin >> password;

        Person* loggedInUser = uni.findPerson(email, students);

        if (!loggedInUser) {
            cout << "Email not found!" << endl;
            continue;
        }
        if (loggedInUser->getPassword() != password) {
            cout << "Incorrect password!" << endl;
            continue;
        }

        // ── Role Verification & Menu ──────────────────────────
        if (roleChoice == 1) {
            Admin* a = dynamic_cast<Admin*>(loggedInUser);
            if (!a) { 
                cout << "Access denied!" << endl; 
                continue; 
            }
            cout << "\nWelcome, " << a->getName() << "!" << endl;
            a->showMenu(&uni, students);
        }
        else if (roleChoice == 2) {
            Teacher* t = dynamic_cast<Teacher*>(loggedInUser);
            if (!t || t->getRole() != TeacherRole::DEAN) {
                cout << "Access denied!" << endl; 
                continue;
            }
            cout << "\nWelcome, Dean " << t->getName() << "!" << endl;
            // find faculty of this dean
            for (Faculty& f : uni.getFaculties()) {
                if (f.getDean() == t) {
                    int choice;
                    do {
                        cout << "\nDean Menu: " << endl;
                        cout << "1. View Departments" << endl;
                        cout << "2. View Teachers" << endl;
                        cout << "3. View Students" << endl;
                        cout << "4. View Degree Programs" << endl;
                        cout << "5. View Faculty Performance" << endl;
                        cout << "0. Logout" << endl;
                        cout << "Enter choice: ";
                        cin  >> choice;
                        switch(choice) {
                            case 1: 
                                f.viewDepartments();        
                                break;
                            case 2: 
                                f.viewTeachers();           
                                break;
                            case 3: 
                                f.viewStudents();           
                                break;
                            case 4: 
                                f.viewDegreePrograms();     
                                break;
                            case 5: 
                                f.viewFacultyPerformance(); 
                                break;
                            case 0: 
                                cout << "Logging out..." << endl; 
                                break;
                            default: 
                                cout << "Invalid choice!" << endl;
                        }
                    } while(choice != 0);
                    break;
                }
            }
        }
        else if (roleChoice == 3) {
            Teacher* t = dynamic_cast<Teacher*>(loggedInUser);
            if (!t || t->getRole() != TeacherRole::HOD) {
                cout << "Access denied!" << endl; 
                continue;
            }
            cout << "\nWelcome, HOD " << t->getName() << "!" << endl;
            Department* dept = t->getDepartment();
            if (dept) {
                int choice;
                do {
                    cout << "\nHOD Menu: " << endl;
                    cout << "1. View Teachers" << endl;
                    cout << "2. View Students" << endl;
                    cout << "3. View Degree Programs" << endl;
                    cout << "4. View Courses" << endl;
                    cout << "5. View Department Performance" << endl;
                    cout << "6. View Student Performance" << endl;
                    cout << "0. Logout" << endl;
                    cout << "Enter choice: ";
                    cin  >> choice;
                    switch(choice) {
                        case 1: 
                            dept->viewTeachers();              
                            break;
                        case 2: 
                            dept->viewStudents();              
                            break;
                        case 3: 
                            dept->viewDegreePrograms();        
                            break;
                        case 4: 
                            dept->viewCourses();               
                            break;
                        case 5: 
                            dept->viewDepartmentPerformance(); 
                            break;
                        case 6: {
                            string regNo;
                            cout << "Enter Student Reg No: "; 
                            cin >> regNo;
                            for (Student* s : students) {
                                if (s->getRegNo()==regNo) {
                                    dept->viewStudentPerformance(s);
                                    break;
                                }
                            }
                            break;
                        }
                        case 0: 
                            cout << "Logging out..." << endl; 
                            break;
                        default: 
                            cout << "Invalid choice!" << endl;
                    }
                } while(choice != 0);
            }
        }
        else if (roleChoice == 4) {
            Teacher* t = dynamic_cast<Teacher*>(loggedInUser);
            if (!t) { 
                cout << "Access denied!" << endl; 
                continue; 
            }
            cout << "\nWelcome, " << t->getName() << "!" << endl;
            t->showMenu();
            // save assessments after teacher is done
            FileHandler::saveAssessments(students);
        }
        else if (roleChoice == 5) {
            Student* s = dynamic_cast<Student*>(loggedInUser);
            if (!s) { 
                cout << "Access denied!" << endl; 
                continue; 
            }
            cout << "\nWelcome, " << s->getName() << "!" << endl;
            s->showMenu();
        }

    } while(roleChoice != 0);

    // ── Cleanup ───────────────────────────────────────────────
    for (Student* s : students) {
        for (Enrollment* e : s->getEnrollments()) {
            delete e;
        }
        delete s;
    }
    return 0;
}