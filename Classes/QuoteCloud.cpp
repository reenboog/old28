//
//  QuoteCloud.cpp
//  old28
//
//  Created by reenboog on 20.12.13.
//
//

#include "QuoteCloud.h"

QuoteCloud::~QuoteCloud() {
    
}

QuoteCloud::QuoteCloud() {
    mount = nullptr;
    arrow = nullptr;
    textLabel = nullptr;
}

bool QuoteCloud::init() {
    if(!Node::init()) {
        return false;
    }
    
    Size minSize =  Sprite::create("quoteCloud.png")->getContentSize();
    
    arrow = Sprite::create("quoteCloudArrow.png");
    arrow->setAnchorPoint({0.5, 1.0});
    arrow->setPosition({0, arrow->getContentSize().height});
    this->addChild(arrow);
    
    mount = Scale9Sprite::create("quoteCloud.png");
    mount->setAnchorPoint({0.5, 0.0});
    mount->setPosition({0, arrow->getContentSize().height});
    this->addChild(mount);
    
    textLabel = LabelBMFont::create("", "messagesLabels.fnt");
    textLabel->setPosition({mount->getContentSize().width / 2.0, mount->getContentSize().height / 2.0});

    mount->addChild(textLabel);
    
    return true;
}

QuoteCloud* QuoteCloud::create() {
    QuoteCloud *cloud = new QuoteCloud();
    if(cloud && cloud->init()) {
        cloud->autorelease();
        return cloud;
    } else {
        delete cloud;
        return nullptr;
    }
}

void QuoteCloud::setString(string str) {
    textLabel->setString(str.c_str());
    mount->setContentSize({textLabel->getContentSize().width * 1.2, textLabel->getContentSize().height * 1.4});
    
    this->setContentSize({mount->getContentSize().width, mount->getContentSize().height + arrow->getContentSize().height});
    textLabel->setPosition({mount->getContentSize().width / 2.0, mount->getContentSize().height / 2.0});
}

void QuoteCloud::popUp() {
    
}

void QuoteCloud::popOut() {
    
}