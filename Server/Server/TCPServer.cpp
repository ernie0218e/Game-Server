#include "StdAfx.h"
#include "TCPServer.h"

MainGame *game;

TCPServer::TCPServer(void){
	
}

TCPServer::~TCPServer()
{
	tcpListener->Stop();
	listenThread->Abort();
	gameThread->Abort();
	socketList->Clear();
}

void TCPServer::Start()
{
	//******Game Initial************
	game = new MainGame();
	game->Init();
	//******End Game Initial********
	//******new	a game thread*******
	this->gameThread = gcnew Thread(gcnew ThreadStart(this, &TCPServer::gameStart));
	//******End*********************
	array <IPAddress^> ^myip = Dns::GetHostAddresses(Dns::GetHostName());
	IP= Convert::ToString(myip[4]);
	System::Diagnostics::Debug::WriteLine(IP);
	this->serverIP();
	this->socketList = gcnew List<Socket^>();
	connection_count = 0;
	this->tcpListener = gcnew TcpListener(IPAddress::Parse(IP), 3000);
	this->listenThread = gcnew Thread(gcnew ThreadStart(this, &TCPServer::ListenForClients));
	this->listenThread->Start();
}

void TCPServer::gameStart(void){
	for(;;){
		game->Update();
	}
}

void TCPServer::ListenForClients(void){
	//start the tcpListener
	this->tcpListener->Start();

	while(true){
		//blocks until a client has connected to the server
		Socket ^client = this->tcpListener->AcceptSocket();

		//create a thread to handle communication
		//with connected client
		Thread ^clientThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &TCPServer::HandleClientComm));
		clientThread->Start(client);
		connection_count++;
		socketList->Add(client);
	}
}

String^ TCPServer::serverIP(){
	return gcnew String(IP);
}

String^ TCPServer::serverCount()
{
	return Convert::ToString(connection_count);
}

void TCPServer::HandleClientComm(Object ^client){
	Socket ^tcpClient = (Socket^ )client;
	array <unsigned char> ^myBytes;
	String ^receivedata = nullptr;
	if(tcpClient->Connected == true){
		myBytes = Encoding::Unicode->GetBytes("Welcome to My Server !!!!!\n");
		tcpClient->Send(myBytes);
		while(true){
			try{
				do{
					array <unsigned char> ^myBufferBytes=gcnew array <unsigned char>(1024);
					int dataLength  = tcpClient->Receive(myBufferBytes);
					
					if (dataLength > 0){
						receivedata += Encoding::Unicode->GetString(myBufferBytes, 0, dataLength);
					}
				}while(tcpClient->Available);
				//do some work
				if (receivedata != nullptr){
					myBytes = Encoding::Unicode->GetBytes(receivedata);
					for(int i = 0;i < socketList->Count;i++){
						if(tcpClient != socketList[i]){
							try{
								socketList[i]->Send(myBytes);
							}
							catch(Exception ^send_err){

							}
						}
					}
				}
				receivedata = nullptr;
			}
			catch(Exception ^ee){
				break;
			}
		}
	}
	tcpClient->Close();
	socketList->Remove(tcpClient);
	connection_count--;
}


