#pragma once
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
	MainGame *game;
	String^ IP;
	String^ err_msg;
	String^ msg;
	array <IPAddress^> ^myip;
	TcpListener^ tcpListener;
	Thread^ listenThread;
	Thread^ gameThread;
	
	//List<Socket^>^ socketList;
	int connection_count;
	void gameStart(void);
	void ListenForClients(void);
	void HandleClientComm(Object^);
	void MarshalString(String ^, string&);
public:
	TCPServer();
	~TCPServer();
	int Start(int);
	void Stop();
	void setIP(String ^);
	String^ serverIP();
	String^ serverCount();
	String^ getIParray();
	String^ getError();
	String^ getMessage();
};

