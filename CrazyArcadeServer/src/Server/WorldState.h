#pragma once
#include "packet.h"
#include <map>
#include <vector>

class WorldState
{


public:
	// Ŭ���̾�Ʈ�� WorldPacket�� �����°��̾ƴ϶� Packet�� ������. 
	void Write(OutputMemoryStream& out);
	void Read(InputMemoryStream& in);

private:
	void PacketClassify(CrazyPacket* packet);

private:
	size_t Header;
	std::map<int, std::vector<float>> WorldData; 
	// ���⿡ �÷��̾���� ������ ��ǳ�������� ����
	// �÷��̾��� Ű���� 1����(NetID)�� �Ҵ�
	// ��ǳ���� 1000������� ����(�ִ� 21�ﰳ ��������)
	// value�� �� Ű���� x y��ǥ�� ��. 
	// �̰Ÿ� Write�ؼ� ��Ŷ���κ������.
	// �÷��̾��� ��� value�� NetID, x, y �� ��. (�����ؾ��ҵ�)
};