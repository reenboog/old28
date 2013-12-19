//
//  StatIcon.h
//  old28
//
//  Created by reenboog on 16.12.13.
//
//

#ifndef __old28__StatIcon__
#define __old28__StatIcon__

#include <string>

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class StatIcon: public Node {
public:
    virtual bool initWithFileName(string file);
    
    ~StatIcon();
    StatIcon();
    
    CREATE_FUNC(StatIcon);
    static StatIcon* create(string file);

    // animations
    void popUp();
    void popOut();
    
    // set&get
    void setValue(int value);
    void setValueFrom(int value, int from);
private:
    Sprite *icon;
    Sprite *mount;
    LabelBMFont *label;
};

#endif /* defined(__old28__StatIcon__) */
