#include <iostream>

using namespace std;

class Person {
protected:
    string name;
    string surname;
public:
    Person(const string &name, const string &surname) : name(name), surname(surname) {}

    friend ostream &operator<<(ostream &output, const Person &obj) {
        output << obj.name << " " << obj.surname;
        return output;
    }

    void speak(){
        cout << name << " says \"Hello\"" << endl;
    }
};

class Employee : public Person {
public:
    string job;
public:
    Employee(const string &name, const string &surname, const string &job) : Person(name, surname) {
        this->job = job;
    }

    friend ostream &operator<<(ostream &output, const Employee &obj) {
        output << obj.job << " " << obj.name << " " << obj.surname;
        return output;
    }

    void speak(){
        cout << job << " " << name << " says \"Morning\"" << endl;
    }
};

class Professor : public Employee {
public:
    string university;
public:
    Professor(const string &name, const string &surname, const string &university) : Employee(name,
                                                                                              surname,
                                                                                              "Professor") {
        this->university = university;
    }
    friend ostream &operator<<(ostream &output, const Professor &obj) {
        output << obj.job << " " << obj.name << " " << obj.surname << ". " << obj.university;
        return output;
    }

    void speak(){
        cout << job << " " << name << " says \"Good morning\"" << " at the " << university << endl;
    }
};

class Student : public Person {
public:
    string university;
public:
    Student(const string &name, const string &surname, const string &university) : Person(name, surname) {
        this->university = university;
    }

    friend ostream &operator<<(ostream &output, const Student &obj) {
        output << obj.name << " " << obj.surname << ". " << obj.university;
        return output;
    }

    void speak(){
        cout << name << " says \"What's up\"" << " at the " << university << endl;
    }
};

int main() {
    Person random = Person("Ivan", "Ivanov");
    Employee randomEmployer = Employee("NeIvan", "Ivanov", "Developer");
    Professor professor = Professor("Ivan", "NeIvanov", "University of San Andreas in Los Santos");
    Student student = Student("NeIvan", "NeIvanov", "University of San Andreas in Los Santos");
    cout << random << "\n" << randomEmployer << "\n" << professor << "\n" << student << "\n";
    random.speak();
    randomEmployer.speak();
    professor.speak();
    student.speak();
    return 0;
}