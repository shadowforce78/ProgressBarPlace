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
#include "Utils.hpp"

class $modify(PlayLayer)
{

	CCSprite *progressBar;
	CCLabelBMFont *percentLabel;

	void postUpdate(float p0)
	{
		PlayLayer::postUpdate(p0);
		if (m_fields->progressBar == nullptr || m_fields->percentLabel == nullptr)
		{
			for (size_t i = 0; i < this->getChildrenCount(); i++)
			{
				auto obj = this->getChildren()->objectAtIndex(i);
				if (Utils::getNodeName(obj) == "cocos2d::CCLabelBMFont" && m_fields->percentLabel == nullptr)
				{
					auto labelTest = static_cast<CCLabelBMFont *>(obj);
					if (strlen(labelTest->getString()) < 6)
					{
						m_fields->percentLabel = labelTest;
					}
				}
				else if (Utils::getNodeName(obj) == "cocos2d::CCSprite" && m_fields->progressBar == nullptr)
				{
					m_fields->progressBar = static_cast<CCSprite *>(obj);
				}
			}
		}
		else
		{

			auto progressBarColor = Mod::get()->getSettingValue<ccColor3B>("progressBarColor");
			auto percentLabelColor = Mod::get()->getSettingValue<ccColor3B>("percentLabelColor");
			auto progressBarState = Mod::get()->getSettingValue<bool>("progressBarState");
			auto percentLabelState = Mod::get()->getSettingValue<bool>("percentLabelState");
			float progressBarPositionX = Mod::get()->getSettingValue<double>("xPositionBar");
			float progressBarPositionY = Mod::get()->getSettingValue<double>("yPositionBar");
			float progressLabelPositionX = Mod::get()->getSettingValue<double>("xPositionLabel");
			float progressLabelPositionY = Mod::get()->getSettingValue<double>("yPositionLabel");


			// Progress Bar
			m_fields->progressBar->setPosition(ccp(progressBarPositionX, progressBarPositionY));
			m_fields->progressBar->setVisible(progressBarState);
			m_fields->progressBar->setChildColor(ccColor3B{progressBarColor.r, progressBarColor.g, progressBarColor.b});
			// Label Percent
			m_fields->percentLabel->setPosition(ccp(progressLabelPositionX, progressLabelPositionY));
			m_fields->percentLabel->setVisible(percentLabelState);
			m_fields->percentLabel->setColor(ccColor3B{percentLabelColor.r, percentLabelColor.g, percentLabelColor.b});

		}
	}
};