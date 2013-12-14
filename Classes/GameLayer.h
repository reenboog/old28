#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

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
private:
    // top mount
    Sprite *topMount;
    // icons
    MenuItemImage *kindnessIcon;
    MenuItemImage *healthIcon;
    MenuItemImage *moneyIcon;
    MenuItemImage *socialsIcon;
    
    // decision menu
    MenuItemImage *leftBtn;
    MenuItemImage *rightBtn;
    Menu *decisionMenu;
    
    Menu *iconsMenu;
};

#endif // __HELLOWORLD_SCENE_H__
