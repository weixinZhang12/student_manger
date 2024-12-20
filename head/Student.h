#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
using namespace std;
// 学生类
class Student
{
public:
    string name;
    long id;
    int age;
    int grade;
    Student(string name, long id, int age, int grade);
};
Student::Student(string name, long id, int age, int grade)
{
    this->name = name;
    this->id = id;
    this->age = age;
    this->grade = grade;
}

#endif // STUDENT_H