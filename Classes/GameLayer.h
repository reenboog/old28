#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Quest.h"

class StatIcon;
class QuoteCloud;

USING_NS_CC;

class GameLayer: public Layer {
public:
    // init
    virtual bool init();
    static Scene* scene();
    
    ~GameLayer();
    GameLayer();
    
    CREATE_FUNC(GameLayer);
    
    void onDeviceOrientationChanged();
    
    // callbacks
    void onLeftDecisionBtnPressed();
    void onRightDecisionBtnPressed();
    void onDecisionMade(int key);
    
    void onPlayerDead();
    
    void loadQuest();
    void visitQuestEntry(const QuestEntry &entry);
    //void transitToQuestEntry(const QuestAnswerTransition& transition);
    
    // animations
    void popUp();
    void popOut();
private:
    // top mount
    Sprite *topMount;
    // icons
    StatIcon *kindnessIcon;
    StatIcon *healthIcon;
    StatIcon *moneyIcon;
    StatIcon *socialsIcon;
    
    // quesiton mount
    Sprite *questionMount;
    LabelBMFont *questionLabel;
    
    QuoteCloud *answerMessage;
    
    StatGroup stats;
    
    // decision menu
    MenuItemImage *leftBtn;
    LabelBMFont *leftBtnLabel;
    MenuItemImage *rightBtn;
    LabelBMFont *rightBtnLabel;
    Menu *decisionMenu;
    
    Node *iconsMenu;
    
    // quest
    Quest *quest;
};

#endif // __HELLOWORLD_SCENE_H__
