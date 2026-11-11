#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// 다이아몬드 스탯 키 = "13"
static constexpr char const* DIAMOND_KEY = "13";

class $modify(DiamondMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // 오른쪽 아래 메뉴에 💎 버튼 추가
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
        int before = gsm->getStat(DIAMOND_KEY);
        gsm->setStat(DIAMOND_KEY, amount);

        FLAlertLayer::create(
            "Diamond Max",
            fmt::format("다이아: <cy>{}</c> → <cg>{}</c>", before, amount),
            "OK"
        )->show();
    }
};
