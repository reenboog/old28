//
//  QuoteCloud.h
//  old28
//
//  Created by reenboog on 20.12.13.
//
//

#ifndef __old28__QuoteCloud__
#define __old28__QuoteCloud__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

class QuoteCloud: public Node {
public:
    ~QuoteCloud();
    QuoteCloud();
    
    bool init();
    static QuoteCloud* create();
    
    void popUp();
    void popOut();
    
    void setString(string str);
private:
    Scale9Sprite *mount;
    Sprite *arrow;
    LabelBMFont *textLabel;
};

USING_NS_CC;
USING_NS_CC_EXT;

#endif /* defined(__old28__QuoteCloud__) */
