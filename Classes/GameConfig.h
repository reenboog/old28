//
//  GameConfig.h
//  solveMe
//
//  Created by Alex Gievsky on 11.11.13.
//
//

#ifndef __solveMe__GameConfig__
#define __solveMe__GameConfig__

#include "cocos2d.h"

USING_NS_CC;

#define kAppVersion         1

class GameConfig {
private:
    GameConfig();
    void setDesignLayoutSize(const Size &size);
    void setVisibleOrigin(const Point &point);
public:
    ~GameConfig();
    
    void load();
    void save();
    
    Size getDesignLayoutSize();
    Point getVisibleOrigin();
    
    void loadFilePaths();
    
    static GameConfig* sharedInstance();
private:
    static GameConfig *__sharedInstance;
    
    Point visibleOrigin;
    Size designLayoutSize;
};


#endif /* defined(__solveMe__GameConfig__) */
