#ifndef MY_COUT_H
#define MY_COUT_H

#include <iostream>
using namespace std;

// 输出红色加粗
void cout_red_bold(string s){
    cout << "\e[1;31m" << s << "\e[0m" << endl;
}

// 输出绿色加粗
void cout_green_bold(string s){
    cout << "\e[1;32m" << s << "\e[0m" << endl;
}

// 输出黄色
void cout_yellow(string s){
    cout << "\e[33m" << s << "\e[0m" << endl;
}

// 输出蓝色
void cout_blue(string s){
    cout << "\e[34m" << s << "\e[0m" << endl;
}

// 输出紫色
void cout_purple(string s){
    cout << "\e[35m" << s << "\e[0m" << endl;
}

// 输出天蓝色
void cout_cyan(string s){
    cout << "\e[36m" << s << "\e[0m" << endl;
}

// 输出白色
void cout_white(string s){
    cout << "\e[37m" << s << "\e[0m" << endl;
}

// 输出黑色
void cout_black(string s){
    cout << "\e[30m" << s << "\e[0m" << endl;
}

// 输出亮红色
void cout_bright_red(string s){
    cout << "\e[1;31m" << s << "\e[0m" << endl;
}

// 输出亮绿色
void cout_bright_green(string s){
    cout << "\e[1;32m" << s << "\e[0m" << endl;
}

// 输出亮黄色
void cout_bright_yellow(string s){
    cout << "\e[1;33m" << s << "\e[0m" << endl;
}

// 输出亮蓝色
void cout_bright_blue(string s){
    cout << "\e[1;34m" << s << "\e[0m" << endl;
}

// 输出亮紫色
void cout_bright_purple(string s){
    cout << "\e[1;35m" << s << "\e[0m" << endl;
}

// 输出亮天蓝色
void cout_bright_cyan(string s){
    cout << "\e[1;36m" << s << "\e[0m" << endl;
}

// 输出亮白色
void cout_bright_white(string s){
    cout << "\e[1;37m" << s << "\e[0m" << endl;
}

// 输出加粗
void cout_bold(string s){
    cout << "\e[1m" << s << "\e[0m" << endl;
}

// 输出下划线
void cout_underline(string s){
    cout << "\e[4m" << s << "\e[0m" << endl;
}

// 输出反显（反色）
void cout_reverse(string s){
    cout << "\e[7m" << s << "\e[0m" << endl;
}

// 重置为默认颜色和样式
void cout_reset(string s){
    cout << "\e[0m" << s << "\e[0m" << endl;
}

// 输出红色
void cout_red(string s){
    cout << "\e[31m" << s << "\e[0m" << endl;
}

// 输出绿色
void cout_green(string s){
    cout << "\e[32m" << s << "\e[0m" << endl;
}

// 输出红色加粗错误信息
void cerr_red_bold(string s){
    cerr << "\e[1;31m" << s << "\e[0m" << endl;
}

#endif // MY_COUT_H
