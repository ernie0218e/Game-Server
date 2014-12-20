#pragma once
#include <vector>
using namespace System;
using namespace System::Text;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Collections::Generic;
using namespace std;

ref class TCPServer
{
private:
	String^ IP;
	TcpListener^ tcpListener;
	Thread^ listenThread;
	/*List<String^>^ recieveData;
	List<String^>^ sendData;*/
	List<Socket^>^ socketList;
	int connection_count;
	void ListenForClients(void);
	void HandleClientComm(Object^);
public:
	TCPServer(void);
	~TCPServer();
	String^ serverIP();
	String^ serverCount();
};

