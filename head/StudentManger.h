#ifndef STUDENTMANGER_H
#define STUDENTMANGER_H
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include "./my_cout.h"
#include "./Student.h"
// 学生管理了类
class StudentManger
{
public:
    unordered_map<long, Student *> map;
    unsigned int length;
    StudentManger()
    {
        // printf("1");
    }
    // 判断这个数是否是偶数,用于高亮某些行
    bool is_even(int num)
    {
        return (num & 1) == 0;
    }
    // 添加学生信息
    void add_student(string name, long id, int age, int grade)
    {
        Student *s = new Student(name, id, age, grade);
        map.insert({s->id, s});
        length += 1;
    }
    void add_stundet_from_terminal()
    {
        string name;
        long id;
        int age;
        int grade;
        cout << "请输入姓名：" << endl;
        cin >> name;
        cout << "请输入学生号" << endl;
        cin >> id;
        cout << "请输入年龄" << endl;
        cin >> age;
        cout << "请输入成绩" << endl;
        cin >> grade;
        this->add_student(name, id, age, grade);
    }
    void delete_student_info_by_id(long id, unordered_map<long, Student *> map)
    {
        auto it = map.find(id);
        // 如果没有找到元素返回map.end()
        if (it != map.end())
        {
            delete it->second;
            map.erase(id);
        }
    }
    void delete_student_info()
    {
        long id;
        cout << "请输入需要删除的学生的id" << endl;
        cin >> id;
        delete_student_info_by_id(id, map);
    }

    // 从csv文件中添加学生信息,该操作不会覆盖信息
    void add_student_info_from_csv(string path)
    {
        // 临时存储结结果
        vector<string> result;
        // 打开文件
        ifstream file(path);
        if (!file.is_open())
        {
            cerr << "\e[1;31m文件无法正常打开\e[0m" << endl;
            return;
        }
        int t = 0;
        // 用于存储行的内容
        string line;
        // 用于记录当前是哪一行
        unsigned int lines = 1;

        // 读取字符串
        while (getline(file, line))
        {
            // 此时并非最优性能
            vector<string> temp;
            // 声明一个需要切割的字符串
            stringstream ss(line);
            string s;
            // 分割字符串
            while (getline(ss, s, ','))
            {
                temp.push_back(s);
            }
            // 如果发现不满足条件的行,直接退出本次循环,跳过该行
            if (temp.size() != 4)
            {
                cerr << "\e[1;31m" << lines << "行出现问题\e[0m" << endl;
                // temp.clear();
                // lines+=1;
                continue;
                ;
            }
            try
            {
                this->add_student(temp[0], stol(temp[1]), stoi(temp[2]), stol(temp[3]));
                temp.clear();
                lines += 1;
            }
            // 数据类型错误
            catch (const invalid_argument &e)
            {
                cerr << "\e[1;31m" << lines << "行含有无效的数据\e[0m\n"
                     << e.what() << endl;
                continue;
            }
        }
        cout_green_bold("数据导入成功");
        // this->save_student_info_to_csv("temp.csv");
    }
    // 将数据导出到文件
    void export_studnet_info()
    {
        this->save_student_info_to_csv("./temp.csv");
    }
    // 将学生信息保存到csv文件
    void save_student_info_to_csv(string path)
    {
        ofstream file(path, ios::trunc);
        if (!file.is_open())
        {
            cerr_red_bold("文件无法正常打开");
        }
        for (const auto &entry : map)
        {
            file << entry.second->name << "," << entry.second->id << "," << entry.second->age << "," << entry.second->grade << endl;
        }
        file.close();
        cout_green_bold("文件写入成功");
    }
    // id升序比较函数
    static bool compare_by_id_raise(const Student *a, const Student *b)
    {
        return a->id < b->id;
    }
    static bool compare_by_grade_down(const Student *a, const Student *b)
    {
        return a->grade > b->grade;
    }
    // 按照id顺序升序打印
    void print_student_info_by_id()
    {
        vector<Student *> temp_v;
        for (const auto &entry : map)
        {
            temp_v.push_back(entry.second);
        }
        sort(temp_v.begin(), temp_v.end(), compare_by_id_raise);
        print_student_info(temp_v);
    }
    void print_student_info_by_grade()
    {
        vector<Student *> temp_v;
        for (const auto &entry : map)
        {
            temp_v.push_back(entry.second);
        }
        sort(temp_v.begin(), temp_v.end(), compare_by_grade_down);
        print_student_info(temp_v);
    }

    // 通用打印函数
    void print_student_info(const vector<Student *> vec)
    {

        unsigned int lines = 1;
        unsigned int index = 1;
        cout << "---------------------------------------------\n";
        // 输出字段部分
        cout << left << setw(7) << "INDEX"
             << "|" << setw(12) << "NAME"
             << "|" << setw(12) << "ID"
             << "|" << setw(5) << "AGE"
             << "|" << setw(5) << "GRADE"
             << "\n";
        cout << "---------------------------------------------\n";
        // 输出学生的信息部分
        for (const auto &entry : vec)
        {
            // 如果是奇数,高亮该行
            if (!is_even(lines))
            {
                cout << "\e[7m" << left << setw(7) << index
                     << "|" << setw(12) << entry->name
                     << "|" << setw(12) << entry->id
                     << "|" << setw(5) << entry->age
                     << "|" << setw(5) << entry->grade
                     << "\e[0m\n";
                lines += 1;
                index += 1;
                continue;
            }

            cout << left << setw(7) << index
                 << "|" << setw(12) << entry->name
                 << "|" << setw(12) << entry->id
                 << "|" << setw(5) << entry->age
                 << "|" << setw(5) << entry->grade
                 << "\n";
            index += 1;
            lines += 1;
        }
        cout << "---------------------------------------------\n";
    }
    // 修改学生信息
    void modify_student_info(long id)
    {
        auto it = this->map.find(id);
        // 如果找到了
        if (it != this->map.end())
        {
            string name;
            long id;
            int age;
            int grade;
            cout << "请输入姓名：" << endl;
            cin >> name;
            cout << "请输入学生号" << endl;
            cin >> id;
            cout << "请输入年龄" << endl;
            cin >> age;
            cout << "请输入成绩" << endl;
            cin >> grade;
            it->second->name = name;
            it->second->id = id;
            it->second->age = age;
            it->second->grade = grade;
        }
        else
        {
            cerr_red_bold("没有找到数据");
        }
    }
    // 在终端修改学生信息
    void modify_student_info_from_terminal()
    {
        long id;
        cout << "请输入需要修改的id" << endl;
        cin >> id;
        this->modify_student_info(id);
    }
    // 打印信息，无序打印
    void print_info()
    {
        vector<Student *> temp_vec;
        for (const auto &entry : this->map)
        {
            temp_vec.push_back(entry.second);
        }
        print_student_info(temp_vec);
    }
    // 释放StudentManger的相关的内存
    ~StudentManger()
    {
        for (auto &entry : map)
        {
            delete entry.second;
        }
    }
};

#endif // STUDENTMANGER_H
