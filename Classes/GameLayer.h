#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Quest;
class StatIcon;

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
    
    void loadQuest();
    
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
    
    // decision menu
    MenuItemImage *leftBtn;
    MenuItemImage *rightBtn;
    Menu *decisionMenu;
    
    Node *iconsMenu;
    
    // quest
    Quest *quest;
};

#endif // __HELLOWORLD_SCENE_H__
