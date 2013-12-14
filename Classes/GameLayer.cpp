
#include "GameLayer.h"
#include "GameConfig.h"

USING_NS_CC;

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
    
    Size visibleSize = GameConfig::sharedInstance()->getDesignLayoutSize();
    Point origin = GameConfig::sharedInstance()->getVisibleOrigin();

    Sprite *sprite = Sprite::create("HelloWorld.png");

    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);
    
    return true;
}