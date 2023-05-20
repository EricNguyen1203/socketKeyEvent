// #include <iostream>
// using namespace std;
// #include <conio.h>
// #include <windows.h>
// #include <WinUser.h>
 
// void f1(){
//     cout << "I'm F1'\n";
// }
 
// void f2(){
//     cout << "I'm F2'\n";
// }
 
// int main(){
//     bool flag = true;
//     char ch;
//     while(true){
//         if(kbhit()){
//             ch = getch();
//             if(ch == 20){
//                 flag = !flag;
//             }
//         }
//         if(flag) f1();
//         else f2();
//         Sleep(500);
//     }
// }

#include <Windows.h>
#include <iostream>

bool IsCapitalized(short int shift, short int caps)
{
    bool s = shift < 0;
    bool c = (caps & 1) != 0;
    return s != c;
}

int main()
{
    unsigned char c;

    while (true)
    {
        for (c = 1; c <= 222; c++)
        {
            if (GetAsyncKeyState(c) & 1)
            {
                short int shift = GetAsyncKeyState(VK_SHIFT);
                short int caps = GetKeyState(VK_CAPITAL);

                switch (c)
                {
                case 65:
                {
                    if (IsCapitalized(shift, caps))
                    {
                        std::cout << "A\n";
                    }
                    else
                    {
                        std::cout << "a\n";
                    }
                }
                }
            }
        }
    }
}