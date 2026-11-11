#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// 바꿀 스탯 목록 (번호, 이름)
struct StatInfo {
    char const* key;
    char const* name;
};

static constexpr StatInfo STATS[] = {
    { "13", "Diamonds" },       // 다이아
    { "14", "Orbs" },           // 오브
    { "29", "Diamond Shards" }, // 다이아 조각
};

class $modify(DiamondMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto spr = CircleButtonSprite::createWithSpriteFrameName(
            "GJ_diamondsIcon_001.png", 1.2f,
            CircleBaseColor::Cyan, CircleBaseSize::MediumAlt
        );
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(DiamondMenuLayer::onDiamond)
        );
        btn->setID("diamond-max-button"_spr);

        if (auto menu = this->getChildByID("bottom-menu")) {
            menu->addChild(btn);
            menu->updateLayout();
        }
        return true;
    }

    void onDiamond(CCObject*) {
        int amount = static_cast<int>(Mod::get()->getSettingValue<int64_t>("amount"));
        auto gsm = GameStatsManager::sharedState();

        std::string msg;
        for (auto const& s : STATS) {
            int before = gsm->getStat(s.key);
            gsm->setStat(s.key, amount);
            msg += fmt::format("{}: <cy>{}</c> -> <cg>{}</c>\n", s.name, before, amount);
        }

        FLAlertLayer::create("Diamond Max", msg, "OK")->show();
    }
};
