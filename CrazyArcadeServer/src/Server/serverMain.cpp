#include "packet.h"

//critical section
int clientNumber;
bool wait = true;
std::mutex mtx;



void echo(TCPSocketPtr servsock, TCPSocketPtr clientSocket)
{
	//critical section
	mtx.lock();
	std::cout << clientNumber++ << "�� Ŭ���̾�Ʈ�� �����Ͽ����ϴ�!!" << std::endl;
	mtx.unlock();
	//end

	//Send initPacket
	InitiationPacket initPacket;
	int thisclientnumber = clientNumber;
	for (int i = 0; i < 2; ++i) {
		initPacket.clientCharacter[i] = i;
		initPacket.clientCharacterPosX[i] = i;
		initPacket.clientCharacterPosY[i] = i;
		initPacket.clientID[i] = i;
	}
	initPacket.blocks = createVillageBlocksData();

	OutputMemoryStream out;
	initPacket.Write(out);
	char* initBuffer = static_cast<char*>(malloc(1470));
	memcpy(initBuffer, out.GetBufferPtr(), out.GetLength());
	clientSocket->Send(initBuffer, out.GetLength());

	//send end

	std::cout << clientNumber << "�� Ŭ���̾�Ʈ�� �̴���Ŷ�� ���½��ϴ�.\n";


	while (true) {
		MoveData moveData;

		char* buffer = static_cast<char*>(malloc(1470));
		int size = clientSocket->Receive(buffer, 1470);
		if (moveData.clientID == -1) // ó�� ������ �� ���̵�ѹ� �ο�
			moveData.clientID = thisclientnumber;
		if (size < 0) {			// ����� ����
			break;
		}
		
		InputMemoryStream in(buffer, size);
		moveData.Read(in);
		moveData.show();
	}
	std::cout << thisclientnumber << "�� Ŭ���̾�Ʈ ���� ����" << '\n' << std::endl;
}




int main()
{
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SocketAddressFactory fac;
	SocketAddress servAddr(INADDR_ANY, 9190);
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