#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/GameManager.hpp>
class $modify(MyGameManager, GameManager) {

	bool init() {

		if (!GameManager::init()) {
			return false;
		}

    	const char* GameManager::getBGTexture(int index) {
        	index = std::clamp(index, 0, 191);
        	this->loadBackground(index);
        	return cocos2d::CCString::createWithFormat("game_bg_%02d_001.png", index)->getCString();
    	}

    	const char* GameManager::getFontFile(int index) {
        	index = std::clamp(index, 0, 72);
        	this->loadFont(index);
        	if (index != 0) {
            	return cocos2d::CCString::createWithFormat("gjFont%02d.fnt", index)->getCString();
        	}
       		return "bigFont.fnt";
    	}

    	const char* GameManager::getFontTexture(int index) {
        	index = std::clamp(index, 0, 72);
        	this->loadFont(index);
        	if (index != 0) {
            	return cocos2d::CCString::createWithFormat("gjFont%02d.png", index)->getCString();
        	}
        	return "bigFont.png";
    	}

    	const char* GameManager::getGTexture(int index) {
        	index = std::clamp(index, 0, 41);
        	this->loadGround(index);
        	return cocos2d::CCString::createWithFormat("groundSquare_%02d_001.png", index)->getCString();
    	}

    	const char* GameManager::getMGTexture(int index) {
        	index = std::clamp(index, 0, 6);
        	this->loadMiddleground(index);
        	return cocos2d::CCString::createWithFormat("fg_%02d_001.png", index)->getCString();
    	}

    	void GameManager::loadBackgroundAsync(int index) {
        	index = std::clamp(index, 0, 191);
        	if (m_loadingBG || m_loadedBgID == index) return;
        	m_loadingBG = true;
        	cocos2d::CCTextureCache::sharedTextureCache()->addImageAsync(
            	cocos2d::CCString::createWithFormat("game_bg_%02d_001.png", index)->getCString(),
            	this,
            	callfuncO_selector(GameManager::finishedLoadingBGAsync),
            	index,
            	cocos2d::kCCTexture2DPixelFormat_RGBA8888
        	);
    	}

    	void GameManager::loadGroundAsync(int index) {
        	index = std::clamp(index, 0, 41);
        	if (m_loadingG || m_loadedGroundID == index) return;
        	m_loadingG = true;
        	auto hasSecondary = this->groundHasSecondaryColor(index);
        	m_finishedLoadingG1 = false;
        	m_finishedLoadingG2 = !hasSecondary;
        	cocos2d::CCTextureCache::sharedTextureCache()->addImageAsync(
            	cocos2d::CCString::createWithFormat("groundSquare_%02d_001.png", index)->getCString(),
            	this,
            	callfuncO_selector(GameManager::finishedLoadingGAsync1),
            	index,
            	cocos2d::kCCTexture2DPixelFormat_RGBA8888
        	);
        	if (!hasSecondary) return;
        	cocos2d::CCTextureCache::sharedTextureCache()->addImageAsync(
            	cocos2d::CCString::createWithFormat("groundSquare_%02d_2_001.png", index)->getCString(),
            	this,
            	callfuncO_selector(GameManager::finishedLoadingGAsync2),
            	index,
            	cocos2d::kCCTexture2DPixelFormat_RGBA8888
        	);
    	}

    	void GameManager::loadMiddlegroundAsync(int index) {
        	index = std::clamp(index, 0, 6);
        	if (m_loadingG1 || m_loadedMG == index) return;
        	m_loadingG1 = true;
        	m_finishedLoadingMG1 = false;
        	m_finishedLoadingMG2 = false;
        	cocos2d::CCTextureCache::sharedTextureCache()->addImageAsync(
            	cocos2d::CCString::createWithFormat("fg_%02d_001.png", index)->getCString(),
            	this,
            	callfuncO_selector(GameManager::finishedLoadingMGAsync1),
            	index,
            	cocos2d::kCCTexture2DPixelFormat_RGBA8888
        	);
        	cocos2d::CCTextureCache::sharedTextureCache()->addImageAsync(
            	cocos2d::CCString::createWithFormat("fg_%02d_2_001.png", index)->getCString(),
            	this,
            	callfuncO_selector(GameManager::finishedLoadingMGAsync2),
            	index,
            	cocos2d::kCCTexture2DPixelFormat_RGBA8888
        	);
    	}
	}
};
