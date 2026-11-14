#include <iostream>
#include <windows.h>
using namespace std;
void typePrint(string text,int delay){
    for (char ch : text){
        cout<<ch;
        cout.flush();
        Sleep(delay);
    }
}
int main(){
    typePrint("\033[0;95m#include \033[0;94m<iostream>\n\033[95musing \033[38;5;172mnamespace \033[0;92mstd;\n\033[38;5;208mint \033[95mmain\033[0m(){\n    \033[0mcout<<\033[38;5;111m\"Hello World\"\033[0m;\n    \033[95mreturn \033[0m0;\n}",10);
    Sleep(2000);
    return 0;
}
