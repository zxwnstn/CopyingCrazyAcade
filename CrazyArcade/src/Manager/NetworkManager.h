#include "Network/packet.h"



class NetworkManager
{
public:
	//Scene�ܿ��� ������ ip�� �Ѱܹ޾� init�Ѵ�. 
	void init(string _ip);
	void recvID();
	InitiationPacket recvInitData();
	void sendMoveData(char _clientID, char _playerMoveDir);
	MovePacket recvMoveData();

public:
	int getNetID();

private:
	string server_ip;
	TCPSocketPtr clientSock;
	int netID;

private:
	DECLARE_SINGLE(NetworkManager)
};

