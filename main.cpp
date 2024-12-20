#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include "./head/my_cout.h"
#include "./head/Student.h"
#include "./head/StudentManger.h"
using namespace std;

// 正常输出信息,使用原始字符串
const string PRINT_INFO = R"(
--------------------------------
欢迎进入学生信息管理系统
--------------------------------
系统支以下功能:
    1.添加学生信息
    2.删除学生信息
    3.修改学生信息
    4.查询学生信息
    5.输出所有学生信息
    6.导出信息到csv文件 
    7.从本目录temp.csv导入数据
    8.语句模式（实验功能，暂时废弃）
--------------------------------
    0.退出系统
--------------------------------
你也可以使用命令行工具
help    提示帮助信息
)";
// 命令行工具输出信息
const string TERMUNAL_HELP_INFO = R"(
---------------------------------
欢迎使用命令行工具
---------------------------------
help               提示有关帮助信息
import <文件路径>   导入学生信息,支持csv文件
---------------------------------

)";

// 处理命令行参数,使用完毕后程序退出
void argc_deal(int argc, char const *argv[], StudentManger *manger)
{
    // 当参数小于2时,不使用
    if (argc < 2)
    {
        return;
    }
    string commond = argv[1];
    // 导入文件
    if (commond == "import")
    {
        if (argv[2] == nullptr)
        {
            cerr_red_bold("缺少第二个参数");
            exit(1);
        }

        manger->add_student_info_from_csv(argv[2]);
    }
    // 导出文件
    if (commond == "export")
    {
        if (argv[2] == nullptr)
        {
            cerr_red_bold("缺少第二个参数");
            exit(1);
        }

        manger->save_student_info_to_csv(argv[2]);
    }
    // 帮助命令
    if (commond == "help")
    {
        cout << TERMUNAL_HELP_INFO << endl;
    }
    exit(0);
}
// 词法分析函数，用于分析语句
void command_parse()
{
    // 放置用户输入后的被拆分的文本
    vector<string> command_list;
    string user_input_string;
    // 这个方法不适用于读取整行的数据，cin遇到空格就会停止
    // cin >> user_input_string;
    cin.ignore();

    getline(cin, user_input_string);
    stringstream ss(user_input_string);
    string s;
    while (getline(ss, s, ' '))
    {
        command_list.push_back(s);
    }
    for (const auto &entry : command_list)
    {
        cout << entry << endl;
    }
}

void exit_application(bool &flag)
{
    string input;
    cout_yellow("你确定要退出吗？(输入任意字符取消退出)");
    getline(cin, input);
    if (input.empty())
    {
        flag = false;
    }
    else
    {
        cout_yellow("你已经取消了退出");
    }
}
int main(int argc, char const *argv[])
{

    StudentManger *manger = new StudentManger;
    argc_deal(argc, argv, manger);
    cout_green(PRINT_INFO);
    // 如果用户没有使用命令行参数,下面命令将被执行
    // manger->add_student_info_from_csv("./temp.csv");
    // manger->print_info();
    int input;
    bool running = true;
    while (running)
    {
        cout << "请输入代码:";
        cin >> input;
        // 检查输入是否有效
        if (cin.fail())
        {
            cin.clear();                                         // 清除错误状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清理缓冲区
            cerr_red_bold("输入无效");
            continue; // 继续循环
        }
        // 清理掉缓冲区中的换行符，否则getline将直接读取换行符结束执行
        switch (input)
        {
        case 1:
            manger->add_stundet_from_terminal();
            break;
        case 2:
            manger->delete_student_info();
            break;
        case 3:
            manger->modify_student_info_from_terminal();
            break;
        case 5:
            manger->print_info();
            break;
        case 6:
            manger->export_studnet_info();
            break;
        case 7:
            manger->add_student_info_from_csv("temp.csv");
            break;
        case 8:
            command_parse();
            manger->print_student_info_by_id();
            break;
        case 0:
            // running = false;
            exit_application(running);
            break;
        default:
            cout_green(PRINT_INFO);
            break;
        }
    }

    return 0;
}
