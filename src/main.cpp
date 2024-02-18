#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;
class PopupMenu : public geode::Popup<std::string const &>
{

protected:
	bool setup(std::string const &value) override
	{

		auto winSize = CCDirector::sharedDirector()->getWinSize();

		// convenience function provided by Popup
		// for adding/setting a title to the popup
		this->setTitle("Hi mom!");

		auto label = CCLabelBMFont::create(value.c_str(), "bigFont.fnt");
		label->setPosition(winSize / 2);
		this->addChild(label);

		// Settings for the popup
		auto settingsSprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
		settingsSprite->setScale(0.5f);
		settingsSprite->setID("settings-sprite"_spr);
		auto settingsBtn = CCMenuItemSpriteExtra::create(settingsSprite, this, menu_selector(PopupMenu::openSettingsMenu));
		auto menu = CCMenu::create(settingsBtn, nullptr);
		menu->setPositionX(winSize.width - 387.f);
		menu->setPositionY(winSize.height - (222.f - 13.5f));
		menu->setID("settings-menu"_spr);
		this->addChild(menu);

		// Toggable bar
		// [6] cocos2d::CCSprite == Progress bar
		// [9] cocos2d::CCLabelBMFont == Label

		// Progress Bar button + label
		auto barIsHidden = false;
		auto superSpriteToUse = barIsHidden ? "GJ_checkOn_001.png" : "GJ_checkOff_001.png";
		auto checkOffBtnSpr = CCSprite::createWithSpriteFrameName(superSpriteToUse);

		auto toggleBarBTN = CCMenuItemSpriteExtra::create(
			checkOffBtnSpr, this, menu_selector(PopupMenu::hideProgressBar));
		toggleBarBTN->setPositionX(winSize.width - 350.f);
		toggleBarBTN->setPositionY(winSize.height - 101.f);
		toggleBarBTN->setID("toggle-bar-btn"_spr);
		this->addChild(toggleBarBTN);

		return true;
	}

public:
	void openSettingsMenu(CCObject *)
	{
		geode::openSettingsPopup(Mod::get());
	};

	void hideProgressBar(CCObject *)
	{
		auto btn = this->getChildByID("toggle-bar-btn");
		auto bar = this->getChildByID("toggle-bar");
		auto label = this->getChildByID("toggle-bar-label");

		auto barIsHidden = !bar->isVisible();
		auto superSpriteToUse = barIsHidden ? "GJ_checkOn_001.png" : "GJ_checkOff_001.png";
		auto checkOffBtnSpr = CCSprite::createWithSpriteFrameName(superSpriteToUse);
		barIsHidden ? bar->setVisible(true) : bar->setVisible(false);
	};

	static PopupMenu *create(std::string const &text)
	{
		auto ret = new PopupMenu();
		if (ret && ret->init(240.f, 160.f, text))
		{
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
};

#include <Geode/modify/PauseLayer.hpp>
class $modify(EditBtn, PauseLayer)
{

	void EditFunction(CCObject *)
	{
		PopupMenu::create("Hello, world!")->show();
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