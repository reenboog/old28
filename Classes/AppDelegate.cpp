#include "AppDelegate.h"
#include "GameLayer.h"

#include "GameConfig.h"

USING_NS_CC;

AppDelegate::~AppDelegate() {
    GameConfig::sharedInstance()->save();
    
    delete GameConfig::sharedInstance();
    
    //CC_SAFE_RELEASE(AppiraterManager::sharedInstance());
}

AppDelegate::AppDelegate() {

}

bool AppDelegate::applicationDidFinishLaunching() {
    Director* director = Director::getInstance();
    EGLView* eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);
    //director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    
    GameConfig::sharedInstance()->loadFilePaths();
    GameConfig::sharedInstance()->load();

    // create a scene. it's an autorelease object
    Scene *scene = GameLayer::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
