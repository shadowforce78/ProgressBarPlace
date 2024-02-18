#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

#include <Geode/modify/PauseLayer.hpp>
class $modify(EditBtn, PauseLayer)
{

	void EditFunction(CCObject *)
	{

		geode::openSettingsPopup(Mod::get());
	};

	void customSetup()
	{
		PauseLayer::customSetup();
		auto btnSprite = CCSprite::createWithSpriteFrameName("GJ_editModeBtn_001.png");
		auto menu = this->getChildByID("center-button-menu");
		auto btn = CCMenuItemSpriteExtra::create(btnSprite, this, menu_selector(EditBtn::EditFunction));
		btn->setID("edit-button"_spr);
		menu->addChild(btn);
		menu->updateLayout();
	};
};

#include <Geode/modify/PlayLayer.hpp>
class $modify(PlayLayer){
	CCSprite* progressBar;

	bool progressBarState = Mod::get()->getSettingValue<bool>("progressBarState");

	// if (m_fields->progressBar == nullptr)
	// {
	// 	// https://github.com/FireMario211/Prism-Menu/blob/ab66db14115703bc6710a41c4aeb5be1979070e1/src/main.cpp#L378
	// }
};