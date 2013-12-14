#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameLayer: public Layer {
public:
    // init
    virtual bool init();
    static Scene* scene();
    
    CREATE_FUNC(GameLayer);
    
    
};

#endif // __HELLOWORLD_SCENE_H__
