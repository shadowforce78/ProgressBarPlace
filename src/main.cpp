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
		// auto btnSprite = CCSprite::createWithSpriteFrameName("GJ_editModeBtn_001.png");
		auto btnSprite = CCSprite::create("iconload.png"_spr);
		auto menu = this->getChildByID("center-button-menu");
		auto btn = CCMenuItemSpriteExtra::create(btnSprite, this, menu_selector(EditBtn::EditFunction));
		btn->setPosition(ccp(-245, 148));
		btn->setID("edit-button"_spr);
		// btn->setScale(1.f);
		menu->addChild(btn);
		menu->updateLayout();
	};
};
#include <chrono>

using namespace std::chrono;

void HSVtoRGB(float &fR, float &fG, float &fB, float &fH, float &fS, float &fV)
{
	float fC = fV * fS; // Chroma
	float fHPrime = fmod(fH / 60.0, 6);
	float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
	float fM = fV - fC;

	if (0 <= fHPrime && fHPrime < 1)
	{
		fR = fC;
		fG = fX;
		fB = 0;
	}
	else if (1 <= fHPrime && fHPrime < 2)
	{
		fR = fX;
		fG = fC;
		fB = 0;
	}
	else if (2 <= fHPrime && fHPrime < 3)
	{
		fR = 0;
		fG = fC;
		fB = fX;
	}
	else if (3 <= fHPrime && fHPrime < 4)
	{
		fR = 0;
		fG = fX;
		fB = fC;
	}
	else if (4 <= fHPrime && fHPrime < 5)
	{
		fR = fX;
		fG = 0;
		fB = fC;
	}
	else if (5 <= fHPrime && fHPrime < 6)
	{
		fR = fC;
		fG = 0;
		fB = fX;
	}
	else
	{
		fR = 0;
		fG = 0;
		fB = 0;
	}

	fR += fM;
	fG += fM;
	fB += fM;
}
float g = 0;
cocos2d::_ccColor3B getRainbow(float offset)
{
	float R;
	float G;
	float B;

	float hue = fmod(g + offset, 360);
	// geode::log << hue;
	float sat = 1;
	float vc = 1;
	HSVtoRGB(R, G, B, hue, sat, vc);

	cocos2d::_ccColor3B out;
	out.r = R * 255;
	out.g = G * 255;
	out.b = B * 255;
	return out;
}

#include <Geode/modify/PlayLayer.hpp>
#include "Utils.hpp"

class $modify(PlayLayer)
{

	CCSprite *progressBar;
	CCLabelBMFont *percentLabel;

	void postUpdate(float p0)
	{

				PlayLayer::postUpdate(p0);

		if (g >= 360)
		{
			g = 0;
		}
		else
		{
			g += 0.5;
		}

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
			bool ignorePalteformerPosition = Mod::get()->getSettingValue<bool>("plateformerLabelPos");
			bool rainbowBar = Mod::get()->getSettingValue<bool>("progressBarRainbow");
			bool rainbowLabel = Mod::get()->getSettingValue<bool>("percentLabelRainbow");

			auto rainbow = getRainbow(0);
			ccColor3B barColor = ccColor3B{progressBarColor.r, progressBarColor.g, progressBarColor.b};
			ccColor3B labelColor = ccColor3B{percentLabelColor.r, percentLabelColor.g, percentLabelColor.b};

			if (m_level->isPlatformer())
			{
				m_fields->progressBar->setVisible(false);

				if (ignorePalteformerPosition == true)
				{
					m_fields->percentLabel->setPositionX(264.500f);
					m_fields->percentLabel->setPositionY(312.f);

					// Rainbow

					if (rainbowLabel == true)
					{
						m_fields->percentLabel->setColor(rainbow);
					}
					else
					{
						m_fields->percentLabel->setColor(labelColor);
					}
				}
				else
				{
					m_fields->percentLabel->setPosition(ccp(progressLabelPositionX, progressLabelPositionY));
					// Rainbow
					if (rainbowLabel == true)
					{
						m_fields->percentLabel->setColor(rainbow);
					}
					else
					{
						m_fields->percentLabel->setColor(labelColor);
					}
				}

				if (m_fields->percentLabel->getFntFile() != "bigFont.fnt")
				{
					m_fields->percentLabel->setFntFile("bigFont.fnt");

					// Label Percent
					if (rainbowLabel == true)
					{
						m_fields->percentLabel->setColor(rainbow);
					}
					else
					{
						m_fields->percentLabel->setColor(labelColor);
					}
				}
			}
			else
			{
				// 	if (m_fields->percentLabel->getFntFile() != "bigFont.fnt")
				// 	{
				// 		m_fields->percentLabel->setFntFile("bigFont.fnt");
				// 		// Progress Bar
				// 		m_fields->progressBar->setPosition(ccp(progressBarPositionX, progressBarPositionY));
				// 		m_fields->progressBar->setVisible(progressBarState);
				// 		m_fields->progressBar->setChildColor(ccColor3B{progressBarColor.r, progressBarColor.g, progressBarColor.b});
				// 		// Label Percent
				// 		m_fields->percentLabel->setPosition(ccp(progressLabelPositionX, progressLabelPositionY));
				// 		m_fields->percentLabel->setVisible(percentLabelState);
				// 		m_fields->percentLabel->setColor(ccColor3B{percentLabelColor.r, percentLabelColor.g, percentLabelColor.b});
				// 	}
				// 	else
				{
					// Progress Bar
					m_fields->progressBar->setPosition(ccp(progressBarPositionX, progressBarPositionY));
					m_fields->progressBar->setVisible(progressBarState);
					if (rainbowBar == true)
					{
						m_fields->progressBar->setChildColor(rainbow);
					}
					else
					{
						m_fields->progressBar->setChildColor(barColor);
					}
					// Label Percent
					m_fields->percentLabel->setPosition(ccp(progressLabelPositionX, progressLabelPositionY));
					m_fields->percentLabel->setVisible(percentLabelState);
					if (rainbowLabel == true)
					{
						m_fields->percentLabel->setColor(rainbow);
					}
					else
					{
						m_fields->percentLabel->setColor(labelColor);
					}
				}
			}
		}
	}
};