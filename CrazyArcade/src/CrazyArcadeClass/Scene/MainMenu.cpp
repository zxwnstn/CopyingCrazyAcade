#include "MainMenu.h"
#include "Etc/stdafx.h"
#include "Manager/SoundManager.h"



HRESULT MainMenu::init()
{
	IMAGEMANAGER->addImage("���콺",			L"images/mouse.bmp", 33, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ȭ����",		L"images/MainImg.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("��ŸƮ��ư",		L"images/play2p.bmp", 225, 75);
	IMAGEMANAGER->addImage("�������ư",		L"images/exit.bmp", 225, 75);
	IMAGEMANAGER->addImage("������ư",			L"images/tcp_ip.bmp", 225, 75);

	startButtonRect = RectMake(900, 625, 225, 75);
	tcpButtonRect = RectMake(900, 700, 225, 75);
	exitButtonRect = RectMake(900, 775, 225, 75);

	startButtonImage = IMAGEMANAGER->findImage("��ŸƮ��ư");
	exitButtonImage = IMAGEMANAGER->findImage("�������ư");
	tcpButtonImage = IMAGEMANAGER->findImage("������ư");

	GET_SINGLE(SoundManager)->addSound("���콺Ȱ��", "music/mouse_position_up.mp3");
	GET_SINGLE(SoundManager)->addStream("���κ��", "music/MainMenu.mp3", 1);

	GET_SINGLE(SoundManager)->playSound("���κ��", 0);

	return S_OK;
}

void MainMenu::release()
{
}

void MainMenu::update(float deltaTime)
{
	if (isPointRectCollision(m_ptMouse, startButtonRect)) {
		if (!mouseSettedStart) {
			mouseSettedStart = true;
			GET_SINGLE(SoundManager)->playSound("���콺Ȱ��", 1);
		}	
	}
	else {
		mouseSettedStart = false;
	}

	if (isPointRectCollision(m_ptMouse, exitButtonRect)) {
		if (!mouseSettedExit) {
			mouseSettedExit = true;
			GET_SINGLE(SoundManager)->playSound("���콺Ȱ��", 1);
		}
	}
	else {
		mouseSettedExit = false;
	}

	if (isPointRectCollision(m_ptMouse, tcpButtonRect)) {
		if (!mouseSettedTcp) {
			mouseSettedTcp = true;
			GET_SINGLE(SoundManager)->playSound("���콺Ȱ��", 1);
		}
	}
	else {
		mouseSettedTcp = false;
	}

	if (mouseSettedStart) {
		if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE)) {
			GET_SINGLE(SoundManager)->stopChannel(0);
			SCENEMANAGER->changeScene("�ΰ���");
		}
	}
	if (mouseSettedExit) {
		if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE)) {
			m_bLoop = false;
		}
	}
}

void MainMenu::render()
{
	IMAGEMANAGER->render("����ȭ����", getMemDC());
	startButtonImage->render(getMemDC(), startButtonRect.left, startButtonRect.top);
	tcpButtonImage->render(getMemDC(), tcpButtonRect.left, tcpButtonRect.top);
	exitButtonImage->render(getMemDC(), exitButtonRect.left, exitButtonRect.top);
	IMAGEMANAGER->render("���콺", getMemDC(), m_ptMouse.x, m_ptMouse.y);

}