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
class $modify(EditedBar, PlayLayer){};