
#include "GameLayer.h"
#include "GameConfig.h"
#include "Constants.h"
#include "StatIcon.h"
#include "QuoteCloud.h"

USING_NS_CC;

GameLayer::~GameLayer() {
    if(quest) {
        delete quest;
    }
}

GameLayer::GameLayer() {
    topMount = nullptr;
    
    kindnessIcon = nullptr;
    healthIcon = nullptr;
    moneyIcon = nullptr;
    socialsIcon = nullptr;
    iconsMenu = nullptr;
    
    questionMount = nullptr;
    questionLabel = nullptr;
    
    answerMessage = nullptr;
    
    leftBtn = nullptr;
    leftBtnLabel = nullptr;

    rightBtn = nullptr;
    rightBtnLabel = nullptr;

    decisionMenu = nullptr;
    
    quest = nullptr;
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
    
    srand((unsigned)time(0));
    
    Size designSize = GameConfig::sharedInstance()->getDesignLayoutSize();
    Point origin = GameConfig::sharedInstance()->getVisibleOrigin();

    Sprite *sprite = Sprite::create("mainBack.png");

    sprite->setPosition(Point(designSize.width/2 + origin.x, designSize.height/2 + origin.y));

    this->addChild(sprite, 0, zMainBack);
    
    // top mount
    topMount = Sprite::create("topMount.png");
    this->addChild(topMount);
    
    // icons
    kindnessIcon = StatIcon::create("kindnessIcon.png");
    healthIcon = StatIcon::create("healthIcon.png");
    moneyIcon = StatIcon::create("moneyIcon.png");
    socialsIcon = StatIcon::create("socialsIcon.png");
    
    iconsMenu = Node::create();
    iconsMenu->addChild(kindnessIcon);
    iconsMenu->addChild(healthIcon);
    iconsMenu->addChild(moneyIcon);
    iconsMenu->addChild(socialsIcon);
    
    this->addChild(iconsMenu);
    
    // question mount
    questionMount = Sprite::create("questionMount.png");
    this->addChild(questionMount);
    
    questionLabel = LabelBMFont::create("Hello there!\n Wanna play a game?", "questionLabels.fnt");
    questionLabel->setPosition(questionMount->getContentSize().width / 2, questionMount->getContentSize().height / 2);
    questionLabel->setAlignment(Label::HAlignment::CENTER);
    questionMount->addChild(questionLabel);
    
    // answer quote
    answerMessage = QuoteCloud::create();

    this->addChild(answerMessage);
    
    // decision menu;
    leftBtn = MenuItemImage::create("decisionButton.png", "decisionButtonOn.png",
                                    CC_CALLBACK_0(GameLayer::onLeftDecisionBtnPressed, this));
    
    leftBtnLabel = LabelBMFont::create("setMe", "decisionBtnLabels.fnt");
    leftBtnLabel->setPosition({leftBtn->getContentSize().width / 2, leftBtn->getContentSize().height / 2});
    leftBtn->addChild(leftBtnLabel);
    
    rightBtn = MenuItemImage::create("decisionButton.png", "decisionButtonOn.png",
                                    CC_CALLBACK_0(GameLayer::onRightDecisionBtnPressed, this));
    
    rightBtnLabel = LabelBMFont::create("setMe", "decisionBtnLabels.fnt");
    rightBtnLabel->setPosition({rightBtn->getContentSize().width / 2, rightBtn->getContentSize().height / 2});
    rightBtn->addChild(rightBtnLabel);

    decisionMenu = Menu::create(leftBtn, rightBtn, nullptr);
    decisionMenu->alignItemsHorizontallyWithPadding(30);
    this->addChild(decisionMenu);
    
    this->onDeviceOrientationChanged();
    
    
    ////////////////////////
    Sprite *baby = Sprite::create("baby.png");
    this->addChild(baby);
    baby->setPosition({designSize.width / 2, designSize.height / 2});
    
    //
    this->loadQuest();
    
    return true;
}

void GameLayer::loadQuest() {
    if(quest) {
        delete quest;
    }
    
    // block ui
    leftBtn->setEnabled(false);
    rightBtn->setEnabled(false);
    
    stats.clear();
    // do we have any unfinished quests?
    
    // otherwise, start a new one
    quest = new Quest();
    // fill in default stats
    //
    stats.addStat(ST_Age, 0);
    stats.addStat(ST_Health, 0);
    stats.addStat(ST_Kindness, 0);
    stats.addStat(ST_Money, 0);
    stats.addStat(ST_Socials, 0);
    //
    // get new file name
    string file = "quest.txt";
    quest->load(file);
    
    const QuestEntry& entry = quest->start();
    this->visitQuestEntry(entry);
}

void GameLayer::visitQuestEntry(const QuestEntry &entry) {
    questionLabel->setString(entry.getQuestion().c_str());
    
    QuestEntry::QuestAnswerIndicesPool answers = entry.get2RandomAnswers();

    leftBtnLabel->setString(answers[0].second.getGaption().c_str());
    leftBtn->setTag(answers[0].first);

    rightBtnLabel->setString(answers[1].second.getGaption().c_str());
    rightBtn->setTag(answers[1].first);
    
    // apply animations
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size designSize = GameConfig::sharedInstance()->getDesignLayoutSize();
    Point origin = GameConfig::sharedInstance()->getVisibleOrigin();

    questionMount->setPosition({visibleSize.width + questionMount->getContentSize().width, origin.y + designSize.height * 0.22});
    questionLabel->setOpacity(0);
    
    answerMessage->setScale(0);
    
    leftBtn->setScale(0);
    rightBtn->setScale(0);
    
    questionMount->runAction(EaseExponentialOut::create(MoveTo::create(0.2, {origin.x + designSize.width / 2, origin.y + designSize.height * 0.22})));
    questionLabel->runAction(Sequence::create(DelayTime::create(0.21),
                                              FadeIn::create(0.1),
                                              NULL));
    
    leftBtn->runAction(Sequence::create(DelayTime::create(0.15),
                                        EaseBackOut::create(ScaleTo::create(0.1, 1.05)),
                                        ScaleTo::create(0.01, 1),
                                        CallFunc::create([=]() {
                                            leftBtn->setEnabled(true);
                                        }),
                                        NULL));
    
    rightBtn->runAction(Sequence::create(DelayTime::create(0.2),
                                        EaseBackOut::create(ScaleTo::create(0.1, 1.05)),
                                        ScaleTo::create(0.01, 1),
                                        CallFunc::create([=]() {
                                            rightBtn->setEnabled(true);
                                        }),
                                        NULL));
}

//void GameLayer::transitTo(const QuestAnswerTransition& transition) {
//    
//}

void GameLayer::popUp() {
    
}

void GameLayer::popOut() {
    
}

void GameLayer::onDeviceOrientationChanged() {
    
    Size designSize = GameConfig::sharedInstance()->getDesignLayoutSize();
    Point origin = GameConfig::sharedInstance()->getVisibleOrigin();
    
    // top mount
    topMount->setAnchorPoint({0.5, 1});
    topMount->setPosition({origin.x + designSize.width / 2, origin.y + designSize.height});
    
    // question mount
    questionMount->setPosition({origin.x + designSize.width / 2, origin.y + designSize.height * 0.22});
    
    // answer message
    answerMessage->setPosition({origin.x + designSize.width / 2, origin.y + designSize.height * 0.65});
    
    // icons
    float iconsPadding = 0;
    float iconsWidth = -iconsPadding;
    Object *icon = NULL;
    CCARRAY_FOREACH(iconsMenu->getChildren(), icon) {
        Node *child = dynamic_cast<Node*>(icon);
        if(child) {
            iconsWidth += child->getContentSize().width * child->getScaleX() + iconsPadding;
        }
    }
    
    float startX = -iconsWidth / 2.0f;
    icon = NULL;
    CCARRAY_FOREACH(iconsMenu->getChildren(), icon) {
        Node *child = dynamic_cast<Node*>(icon);
        if(child) {
            child->setPosition(Point(startX + child->getContentSize().width * child->getScaleX() / 2.0f, 0));
            startX += child->getContentSize().width * child->getScaleX() + iconsPadding;
        }
    }

    iconsMenu->setPosition({origin.x + designSize.width / 2, origin.y + designSize.height * 0.92});

    // decision menu
    decisionMenu->setPosition({origin.x + designSize.width / 2, origin.y + designSize.height * 0.07});
}

#pragma mark - callbacks

void GameLayer::onLeftDecisionBtnPressed() {
    this->onDecisionMade(leftBtn->getTag());
}

void GameLayer::onRightDecisionBtnPressed() {
    this->onDecisionMade(rightBtn->getTag());
}

void GameLayer::onDecisionMade(int key) {
    // disable ui
    leftBtn->setEnabled(false);
    rightBtn->setEnabled(false);
    
    const QuestAnswerTransition &transition = quest->applyAnswer(key, stats);
    
    answerMessage->setString(transition.getMessage());
    
    answerMessage->setScale(0);
    answerMessage->runAction(Sequence::create(DelayTime::create(0.1),
                                              EaseBackOut::create(ScaleTo::create(0.2, 1)),
                                              DelayTime::create(2),
                                              EaseBackIn::create(ScaleTo::create(0.2, 0)),
                                              NULL));
    
    if(transition.getKey() == -1) {
        this->onPlayerDead();
    } else {
        this->visitQuestEntry(quest->visitEntryByKey(transition.getKey()));
    }
}

void GameLayer::onPlayerDead() {
    
}