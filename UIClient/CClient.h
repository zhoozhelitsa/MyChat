#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <functional>

#pragma warning(disable: 4996)

delegate System::Void myEvent();
using MyEvent = std::function<System::Void()>;

ref class CClient : public System::Object
{
public:
	CClient();
	~CClient();

	BOOL CtrlHandler(DWORD fdwCtrlType);
	void reciveMessage();
	static void messageHandler();
	bool connectClient();
	std::vector<std::string>* getMessageArrayPtr();
	void disconnectClient();

	void sendMessage(System::String^ messageText);
	static event myEvent^ mEv;
	static void emitEvent() {
		mEv();
	}
private:
	SOCKADDR_IN* addr;
	int addr_size;
};


