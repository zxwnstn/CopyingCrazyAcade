#include "Etc/stdafx.h"
#include "InGameScene.h"
#include "Manager/SoundManager.h"

InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

HRESULT InGameScene::init()
{
	//=============== inGameScene image settup ======================//

	//map
	IMAGEMANAGER->addImage		("�ΰ��Ӿ����", L"images/map.bmp",					WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//character
	IMAGEMANAGER->addImage		("�÷��̾�",	L"images/bazziReadyCharacter.bmp",	54, 63, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("��1������",	L"images/1p.bmp",					24, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("��2������",	L"images/2p.bmp",					24, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("�����̵�",	L"images/BazziMove.bmp",			560, 320, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("����ǳ����",	L"images/bazziBubble.bmp",			960, 65, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("��������",	L"images/bazziDie.bmp",				770, 110, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("�ٿ��̵�",	L"images/DaoMove.bmp",				560, 320, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("�ٿ�ǳ����",	L"images/DaoBubble.bmp",			960, 65, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("�ٿ�����",	L"images/DaoDie.bmp",				770, 110, 11, 1, true, RGB(255, 0, 255));

	//block
	IMAGEMANAGER->addImage		("�ϵ���",	L"images/house.bmp",				180, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("����Ʈ���",	L"images/box.bmp",					180, 67, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("Ÿ��",		L"images/Tile.bmp",					300, 60);
	IMAGEMANAGER->addImage		("�׸���",		L"images/shadow.bmp",				62,  62, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("����",		L"images/tree.bmp",					60,  95, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("�ν�",		L"images/bush.bmp",					60, 84, true,RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("�ν��׸���",	L"images/bushShadow.bmp",			60, 84, true,RGB(255, 0, 255));

	//bomb
	IMAGEMANAGER->addFrameImage	("����ź",		L"images/bomb_already.bmp",			222, 75, 4, 1, true, RGB(255, 0, 255));

	//boom
	IMAGEMANAGER->addFrameImage	("�������ʳ�",	L"images/bomb_top.bmp",				540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("��������",	L"images/bomb_top_ex.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߾Ʒ��ʳ�",L"images/bomb_bottom.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߾Ʒ���",	L"images/bomb_bottom_ex.bmp",		540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߿����ʳ�",L"images/bomb_right.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߿�����",	L"images/bomb_right_ex.bmp",		540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߿��ʳ�",	L"images/bomb_left.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߿���",	L"images/bomb_left_ex.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("���߼���",	L"images/bomb_center.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	//item
	IMAGEMANAGER->addFrameImage	("������",		L"images/item.bmp", 160, 234, 3, 4, true, RGB(255, 0, 255));

	//============================================================//
	//===================== sound settup =========================//

	GET_SINGLE(SoundManager)->addStream("����",				"music/Boomhill.mp3", true);
	GET_SINGLE(SoundManager)->addStream("ũ��������",		"music/Xmas.mp3", true);
															
	GET_SINGLE(SoundManager)->addSound("������",			"music/boom.mp3");
	GET_SINGLE(SoundManager)->addSound("��ź����",			"music/dropBomb.mp3");
	GET_SINGLE(SoundManager)->addSound("���ӽ�ŸƮ",		"music/game_start.mp3");
	GET_SINGLE(SoundManager)->addSound("�ν�����",		"music/bushIn.mp3");
	GET_SINGLE(SoundManager)->addSound("�����ۻ���",		"music/ItemGen.mp3");
	GET_SINGLE(SoundManager)->addSound("�����۾��",		"music/ItemGet.mp3");
	GET_SINGLE(SoundManager)->addSound("�й�",				"music/defeat.mp3");
	GET_SINGLE(SoundManager)->addSound("��ο�",			"music/draw.mp3");
	GET_SINGLE(SoundManager)->addSound("�����۾��",		"music/ItemGet.mp3");
	GET_SINGLE(SoundManager)->addSound("����",				"music/select.mp3");
															
	GET_SINGLE(SoundManager)->addSound("ǳ��������",		"music/inBalloon.mp3");
	GET_SINGLE(SoundManager)->addSound("ǳ������",			"music/ballon_explosion.mp3");
	

	//InGameScene manager init
	GET_SINGLE(BlockManager)->init();
	GET_SINGLE(CharacterManager)->init();
	GET_SINGLE(BombManager)->init();
	GET_SINGLE(ItemManager)->init();

	//for debugMode
	_stprintf(str, L"DEBUG ENABLED A : speed up S : limit up D : range up");
	len = _tcslen(str);

	gameEnd = false;
	gameStart = true;
	gameStartEnd = 1.5f;
	pastStart = 0.f;
	SceneFinal = false;

	mouseDis = false;
	mouseDisApearDelay = 1.0f;
	mousePastTime = 0.f;
	lastMousePos = m_ptMouse;
	bgmSelector = RND->getInt(100);
	exitMouseSetted = false;

	GET_SINGLE(SoundManager)->playSound("���ӽ�ŸƮ", 2);

	if (bgmSelector > 70)
		GET_SINGLE(SoundManager)->playSound("����", 0);
	else
		GET_SINGLE(SoundManager)->playSound("ũ��������", 0);

	return S_OK;
}

void InGameScene::release()
{
	RELEASE_SINGLE(BlockManager);
	RELEASE_SINGLE(CharacterManager);
	RELEASE_SINGLE(BombManager);
	RELEASE_SINGLE(ItemManager);
}

void InGameScene::update(float deltaTime)
{
	uiUpdate(deltaTime);
	if (!SceneFinal) {
		GET_SINGLE(BlockManager)->update(deltaTime);
		GET_SINGLE(BombManager)->update(deltaTime);
		GET_SINGLE(CharacterManager)->update(deltaTime);
		GET_SINGLE(ItemManager)->update(deltaTime);

		if (GET_SINGLE(CharacterManager)->charactersAllDead) {
			if (GET_SINGLE(CharacterManager)->draw)
				gameDraw = true;
			if (!gameEnd) {
				gameEnd = true;
				pastStart = 0.f;
			}		
		}		
	}
}

void InGameScene::render()
{
	DrawColorRect(getMemDC(), IRECT(0, 0, WINSIZEX, WINSIZEY), RGB(95, 95, 95));
	IMAGEMANAGER->render("�ΰ��Ӿ����", getMemDC(), 0, 0);

	GET_SINGLE(BlockManager)->render(getMemDC());
	GET_SINGLE(BombManager)->render(getMemDC());
	GET_SINGLE(ItemManager)->render(getMemDC());
	GET_SINGLE(CharacterManager)->render(getMemDC());

	if (m_debugMode) {
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 100, 20, str, len);
	}
}

void InGameScene::afterRender()
{
	GET_SINGLE(BlockManager)->afterRender(getMemDC());
	if(!mouseDis)
		IMAGEMANAGER->render("���콺", getMemDC(), m_ptMouse.x, m_ptMouse.y);
	GET_SINGLE(CharacterManager)->afterRender(getMemDC());
}

void InGameScene::debugRender()
{
	GET_SINGLE(BlockManager)->debugRender(getMemDC());
	GET_SINGLE(CharacterManager)->debugRender(getMemDC());
	GET_SINGLE(BombManager)->debugRender(getMemDC());
	GET_SINGLE(ItemManager)->debugRender(getMemDC());
	DrawColorRect(getMemDC(), exitButtonRect, RGB(255, 255, 255));
}

void InGameScene::uiUpdate(float deltaTime)
{
	if (KEYMANAGER->isOnceKeyDown(GAME_DEBUGMODE))
		m_debugMode = !m_debugMode;


	if (KEYMANAGER->isOnceKeyDown(GAME_RECTMODE))
		m_showRect = !m_showRect;

	if (m_debugMode) {
		/*if (KEYMANAGER->isOnceKeyDown(VK_TAB))
			state = CharacterState::CharacterOnIdle;
		if (KEYMANAGER->isOnceKeyDown('A'))
			speedUp();
		if (KEYMANAGER->isOnceKeyDown('S'))
			bombLimitUp();
		if (KEYMANAGER->isOnceKeyDown('D'))
			bombRangeUp();*/
	}

	if (!mouseDis) {
		mousePastTime += deltaTime;
		if (mouseDisApearDelay < mousePastTime) {
			mouseDis = true;
		}
	}

	if ((lastMousePos.x != m_ptMouse.x) || (lastMousePos.y != m_ptMouse.y)) {
		lastMousePos = m_ptMouse;
		mouseDis = false;
		mousePastTime = 0.f;
	}

	if (isPointRectCollision(m_ptMouse, exitButtonRect)) {
		if (!exitMouseSetted) {
			exitMouseSetted = true;
			GET_SINGLE(SoundManager)->playSound("���콺Ȱ��", 7);
		}
	}
	else {
		exitMouseSetted = false;
	}

	if (exitMouseSetted) {
		if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE)) {
			for (int i = 0; i < 10; ++i)
				GET_SINGLE(SoundManager)->stopChannel(i);
			SCENEMANAGER->changeScene("���θ޴�");
			SceneFinal = true;
		}
	}
		

	if (gameEnd && !SceneFinal) {
		pastStart += deltaTime;
		if (pastStart > 0.3f) {
			GET_SINGLE(SoundManager)->stopChannel(0);
			if(gameDraw)
				GET_SINGLE(SoundManager)->playSound("��ο�", 0);
			else
				GET_SINGLE(SoundManager)->playSound("�й�", 0);
			pastStart = 0.f;
			SceneFinal = true;
		}
	}
	if (SceneFinal) {
		pastStart += deltaTime;
		if (pastStart > 3.f){
			for (int i = 0; i < 10; ++i)
				GET_SINGLE(SoundManager)->stopChannel(i);
			SCENEMANAGER->changeScene("���θ޴�");
		}
	}
	
}
