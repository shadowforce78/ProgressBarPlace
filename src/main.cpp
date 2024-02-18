/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 */
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer){
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	 */
	bool init(){
		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init()){
			return false;
}

/**
 * See this page for more info about buttons
 * https://docs.geode-sdk.org/tutorials/buttons
 */
auto myButton = CCMenuItemSpriteExtra::create(
	CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
	this,
	/**
	 * Here we use the name we set earlier for our modify class.
	 */
	menu_selector(MyMenuLayer::onMyButton));

/**
 * Here we access the `bottom-menu` node by its ID, and add our button to it.
 * Node IDs are a Geode feature, see this page for more info about it:
 * https://docs.geode-sdk.org/tutorials/nodetree
 */
auto menu = this->getChildByID("bottom-menu");
menu->addChild(myButton);

/**
 * The `_spr` string literal operator just prefixes the string with
 * your mod id followed by a slash. This is good practice for setting your own node ids.
 */
myButton->setID("my-button"_spr);

/**
 * We update the layout of the menu to ensure that our button is properly placed.
 * This is yet another Geode feature, see this page for more info about it:
 * https://docs.geode-sdk.org/tutorials/layouts
 */
menu->updateLayout();

/**
 * We return `true` to indicate that the class was properly initialized.
 */
return true;
}

/**
 * This is the callback function for the button we created earlier.
 * The signature for button callbacks must always be the same,
 * return type `void` and taking a `CCObject*`.
 */
void onMyButton(CCObject *)
{
	FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
}
}
;
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
class $modify(EditedBar, PlayLayer){

};