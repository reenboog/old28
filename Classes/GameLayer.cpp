
#include "GameLayer.h"
#include "GameConfig.h"
#include "Constants.h"

USING_NS_CC;

GameLayer::~GameLayer() {
    
}

GameLayer::GameLayer() {
    topMount = nullptr;
    
    kindnessIcon = nullptr;
    healthIcon = nullptr;
    moneyIcon = nullptr;
    socialsIcon = nullptr;
    iconsMenu = nullptr;
    
    leftBtn = nullptr;
    rightBtn = nullptr;
    decisionMenu = nullptr;
}

Scene* GameLayer::scene() {
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    Size designSize = GameConfig::sharedInstance()->getDesignLayoutSize();
    Point origin = GameConfig::sharedInstance()->getVisibleOrigin();

    Sprite *sprite = Sprite::create("mainBack.png");

    sprite->setPosition(Point(designSize.width/2 + origin.x, designSize.height/2 + origin.y));

    this->addChild(sprite, 0, zMainBack);
    
    // top mount
    topMount = Sprite::create("topMount.png");
    this->addChild(topMount);
    
    // icons
    kindnessIcon = MenuItemImage::create("kindnessIcon.png", "kindnessIcon.png");
    healthIcon = MenuItemImage::create("healthIcon.png", "healthIcon.png");
    moneyIcon = MenuItemImage::create("moneyIcon.png", "moneyIcon.png");
    socialsIcon = MenuItemImage::create("socialsIcon.png", "socialsIcon.png");
    
    iconsMenu = Menu::create(kindnessIcon, healthIcon, moneyIcon, socialsIcon, nullptr);
    iconsMenu->alignItemsHorizontally();
    
    this->addChild(iconsMenu);
    
    // decision menu;
    
    leftBtn = MenuItemImage::create("decisionButton.png", "decisionButtonOn.png",
                                    CC_CALLBACK_0(GameLayer::onLeftDecisionBtnPressed, this));
    
    LabelBMFont *leftBtnLabel = LabelBMFont::create("убить", "decisionBtnLabels.fnt");
    leftBtnLabel->setTag(kDecisionBtnLabelKey);
    leftBtnLabel->setPosition({leftBtn->getContentSize().width / 2, leftBtn->getContentSize().height / 2});
    leftBtn->addChild(leftBtnLabel);
    
    rightBtn = MenuItemImage::create("decisionButton.png", "decisionButtonOn.png",
                                    CC_CALLBACK_0(GameLayer::onLeftDecisionBtnPressed, this));
    
    LabelBMFont *rightBtnLabel = LabelBMFont::create("помиловать", "decisionBtnLabels.fnt");
    rightBtnLabel->setTag(kDecisionBtnLabelKey);
    rightBtnLabel->setPosition({rightBtn->getContentSize().width / 2, rightBtn->getContentSize().height / 2});
    rightBtn->addChild(rightBtnLabel);

    decisionMenu = Menu::create(leftBtn, rightBtn, nullptr);
    decisionMenu->alignItemsHorizontallyWithPadding(30);
    this->addChild(decisionMenu);
    
    this->onDeviceOrientationChanged();
    
    return true;
}

void GameLayer::onDeviceOrientationChanged() {
    
    Size designSize = GameConfig::sharedInstance()->getDesignLayoutSize();
    Point origin = GameConfig::sharedInstance()->getVisibleOrigin();
    
    // top mount
    topMount->setAnchorPoint({0.5, 1});
    topMount->setPosition({origin.x + designSize.width / 2, origin.y + designSize.height});
    
    // icons
    iconsMenu->setPosition({origin.x + designSize.width / 2, origin.y + designSize.height * 0.9});

    // decision menu
    decisionMenu->setPosition({origin.x + designSize.width / 2, origin.y + designSize.height * 0.1});
}

#pragma mark - callbacks

void GameLayer::onLeftDecisionBtnPressed() {
}

void GameLayer::onRightDecisionBtnPressed() {
    
}