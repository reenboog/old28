//
//  StatIcon.cpp
//  old28
//
//  Created by reenboog on 16.12.13.
//
//

#include "StatIcon.h"

StatIcon::~StatIcon() {
    
}

StatIcon::StatIcon() {
    icon = nullptr;
    mount = nullptr;
    label = nullptr;
}

StatIcon* StatIcon::create(string file) {
    StatIcon *icon = new StatIcon();
    if(icon && icon->initWithFileName(file)) {
        icon->autorelease();
        return icon;
    } else {
        delete icon;
        return nullptr;
    }
    
    return nullptr;
}

bool StatIcon::initWithFileName(string file) {
    if(!Node::init()) {
        return false;
    }
    
    icon = Sprite::create(file.c_str());
    icon->setPosition({0, 0});
    
    this->addChild(icon);
    
    mount = Sprite::create("iconMount.png");
    mount->setPosition({icon->getContentSize().width / 2, 0});
    
    icon->addChild(mount);
    
    label = LabelBMFont::create("99", "questionLabels.fnt");
    //label->setAnchorPoint({});
    label->setPosition({mount->getContentSize().width / 2, mount->getContentSize().height / 2});
    
    mount->addChild(label);
    
    this->setContentSize(icon->getContentSize());
    
    return true;
}

#pragma mark - animations

void StatIcon::popUp() {
    
}

void StatIcon::popOut() {
    
}

#pragma mark - set/get

void StatIcon::setValue(int value) {
    label->setString(String::createWithFormat("%i", value)->getCString());
}

void StatIcon::setValueFrom(int value, int from) {
    //label->setString(String::createWithFormat("%i", value)->getCString());
}