#include "CrazyArcadeData.h"

//critical section
int clientNumber;
bool wait = true;
std::mutex mtx;



void echo(TCPSocketPtr servsock, TCPSocketPtr clientsocket)
{
	clientNumber++;
	std::cout << clientNumber << "�� Ŭ���̾�Ʈ�� �����Ͽ����ϴ�!!" << std::endl;
	int thisclientnumber = clientNumber;

	while (true) {
		MoveData moveData;

		char* buffer = static_cast<char*>(malloc(1470));
		int size = clientsocket->Receive(buffer, 1470);
		if (moveData.clientID == -1) // ó�� ������ �� ���̵�ѹ� �ο�
			moveData.clientID = thisclientnumber;
		if (size < 0) {			// ����� ����
			break;
		}
		
		InputMemoryStream in(buffer, size);
		moveData.Read(in);
		print(moveData, thisclientnumber);
		clientsocket->Send(buffer, size);
	}
	std::cout << thisclientnumber << "�� Ŭ���̾�Ʈ ���� ����" << '\n' << std::endl;
}











int main()
{
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SocketAddressFactory fac;
	SocketAddress servAddr(INADDR_ANY, 9190);//�߿�!
	SocketAddress clientAddr;

	TCPSocketPtr ServSock = SocketUtil::CreateTCPSocket(INET);

	ServSock->Bind(servAddr);
	std::cout << "������ �����մϴ�!" << std::endl;
	std::cout << "Ŭ���̾�Ʈ ���� �����..." << std::endl;

	srand(time(NULL));

	ServSock->Listen(5);

	while (true)
	{
		TCPSocketPtr ClientSocket;
		ClientSocket = ServSock->Accept(clientAddr);

		std::thread t1(echo, ServSock, ClientSocket);
		t1.detach();
	}

	WSACleanup();
}