#include "Etc/stdafx.h"
#include "CharacterManager.h"
#include "CrazyArcadeClass/Obj/Character/Player.h"
#include "CrazyArcadeClass/Obj/Character/Player2.h"
#include "CrazyArcadeClass/Obj/Character/NetPlayer.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/SoundManager.h"

DEFINITION_SINGLE(CharacterManager)

CharacterManager::CharacterManager()
{
}
CharacterManager::~CharacterManager()
{
	release();
}

bool CharacterManager::init()
{
	//TODO : add other
	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();

	int p1x;
	int p1y;
	while (1) {
		p1x = RND->getInt(NUM_BLOCK_X);
		p1y = RND->getInt(NUM_BLOCK_Y);
		if (blocks[p1y][p1x].getType() == BlockType::BlockNone) {
			auto player = make_shared<Player>(p1x, p1y);
			player->init(CharacterType::Bazzi);
			characters.push_back(player);
			break;
		}
	}
	int p2x;
	int p2y;
	while (1) {
		p2x = RND->getInt(NUM_BLOCK_X);
		p2y = RND->getInt(NUM_BLOCK_Y);
		if (blocks[p2y][p2x].getType() == BlockType::BlockNone &&
			(p1x != p2x || p1y != p2y)) {
			int dist = abs(p1x - p2x) + abs(p1y - p2y);
			if (dist > 12) {
				auto player = make_shared<Player2>(p2x, p2y);
				player->init(CharacterType::Dao);
				characters.push_back(player);
				break;
			}			
		}
	}
	return true;
}
bool CharacterManager::init(std::vector<netCharacterInitData> _initDatas)
{
	for (auto _initData : _initDatas){
		if (_initData.netID == GET_SINGLE(NetworkManager)->getNetID()) {
			auto player = make_shared<Player>(_initData.posX, _initData.posY);
			player->init(_initData.type);
			characters.push_back(player);
		}
		else {
			auto player = make_shared<NetPlayer>(_initData.posX, _initData.posY, _initData.netID);
			player->init(_initData.type);
			characters.push_back(player);
		}		
	}
	return true;
}
void CharacterManager::update(float deltaTime)
{
	if (!charactersAllDead) {
		for (auto&e : characters)
			e->update(deltaTime);
		collision();
		int deadCount = 0;
		for (auto&e : characters) {
			if (e->isPlayerDead())
				deadCount++;
		}
		if (deadCount + 1 == characters.size()) {
			charactersAllDead = true;
		}
		if (deadCount == characters.size()) {
			charactersAllDead = true;
			draw = true;
		}
	}

}
void CharacterManager::render(HDC hdc)
{
	for (auto&e : characters)
		e->render(hdc);
}
void CharacterManager::debugRender(HDC hdc)
{
	for (auto&e : characters)
		e->debugRender(hdc);
}
void CharacterManager::afterRender(HDC hdc)
{
	for (auto&e : characters)
		e->afterRender(hdc);
}

void CharacterManager::release()
{
	characters.clear();
}

void CharacterManager::collision()
{
	collisionItem();
	collisionCharacter();
}
void CharacterManager::collisionItem()
{
	auto& items = GET_SINGLE(ItemManager)->GetItems();
	for (auto character = characters.begin(); character != characters.end(); ++character) {
		for (auto item = items.begin(); item != items.end(); ) {
			if (isRectRectCollision((*item)->getCollisionRect(), (*character)->getOtherCollisionRect())) {
				GET_SINGLE(SoundManager)->playSound("�����۾��", 4);
				switch ((*item)->getType())
				{
				case ItemType::ItemRangeUp:
					(*character)->bombRangeUp();
					break;
				case ItemType::ItemSpeedUp:
					(*character)->speedUp();
					break;
				case ItemType::ItemBombLimitUp:
					(*character)->bombLimitUp();
					break;
				/*case ItemType::ItemKick:
					(*character)->getUsableItem(ItemType::ItemKick);
					break;
				case ItemType::ItemDart:
					(*character)->getUsableItem(ItemType::ItemDart);
					break;*/
				case ItemType::ItemNone:
					break;
				}
				item = items.erase(item);
			}
			else item++;
		}
	}
}
void CharacterManager::collisionCharacter()
{
	for (int i = 0; i < characters.size(); ++i) {
		for (int j = 0; j < characters.size(); ++j) {
			if (characters[j]->getState() == CharacterState::CharacterInBalloon && 
				characters[i]->getState() != CharacterState::CharacterInBalloon) {
				if (characters[i] == characters[j]) continue;
				if (isRectRectCollision(characters[i]->getBlockCollisionRect(), characters[j]->getOtherCollisionRect())) {
					characters[j]->die();
				}
			}
		}
	}
}