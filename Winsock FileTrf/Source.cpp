#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")


string GetRequest(string reqType, string request);
void _recv(SOCKET Socket, char* fileToRcv);

int main(void) {


	string response = GetRequest("GET http://", "www.w3.org/Protocols/rfc2616/rfc2616-sec5.html");
	// Display HTML source 
	cout << response;
	system("PAUSE");
	return 0;
}


string GetRequest(string reqType, string request)
{
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int lineCount = 0;
	int rowCount = 0;
	struct hostent *host;
	locale local;
	char buffer[80000];
	int i = 0;
	int nDataLength;
	string website_HTML;

	//HTTP GET
	string get_http = reqType + request + "\r\nConnection: close\r\n\r\n";


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		system("pause");
		return NULL;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	host = gethostbyname(request.c_str());
	if (host == nullptr)
	{
		cout << "Cant resolve host\n";
		return "NULL\n";
	}
	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		cout << "Could not connect";
		system("pause");
		//return 1;
	}

	// send GET / HTTP
	send(Socket, get_http.c_str(), strlen(get_http.c_str()), 0);

	// recieve html
	/*	while ((nDataLength = recv(Socket, buffer, 80000, 0)) > 0) {
	int i = 0;
	while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {

	website_HTML += buffer[i];
	i += 1;
	}
	}*/
	char* file = NULL;
	_recv(Socket, file);
	std::string str(file);


	closesocket(Socket);
	WSACleanup();
	return file;
}


void _recv(SOCKET Socket, char* fileToRcv)
{
	int dwSize;
	char* buffer = new char[1024];

	if (recv(Socket, (char*)buffer, 1024, 0)) //receive file size
	{
		dwSize = atoi((const char *)buffer);
		printf("File Size: %i\r\n", dwSize);
	}
	char* ibuffer = new char[dwSize];

	if (recv(Socket, (char*)ibuffer, dwSize, 0))//recv binary
	{
		FILE* pfile;
		pfile = fopen(fileToRcv, "wb");
		fwrite((const char*)ibuffer, 1, dwSize, pfile);
		fclose(pfile);
	}
}