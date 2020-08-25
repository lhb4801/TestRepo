/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "ClippingScrollView.h"

#define ScreenX 1920
#define ScreenY 1080

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
    MenuItemImage* btn_1 = MenuItemImage::create("image/test1.png", "image/test2.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
    MenuItemImage* btn_2 = MenuItemImage::create("image/test3.png", "image/test4.png", CC_CALLBACK_1(HelloWorld::menuCallback2, this));
    Menu* menu = Menu::create(btn_1, btn_2, NULL);
    menu->alignItemsVertically();
    menu->setPosition(ScreenX * 0.9, ScreenY * 0.9);
    this->addChild(menu);

    clippingScrollView_ = ClippingScrollView::create(Direction::VERTICAL_DOWN, 10);
    clippingScrollView_->setPosition(Vec2(ScreenX * 0.5, ScreenY * 0.5));
    clippingScrollView_->setName("clippingScrollView");
    this->addChild(clippingScrollView_);
    
    
        
    return true;
}

void HelloWorld::menuCallback(Ref *sender)
{
    switch (random(0, 3))
    {
        case 0:
        {
            Sprite* spr = Sprite::create("image/test1.png");
            clippingScrollView_->insertItem(spr);
        }
            break;
        case 1:
        {
            Sprite* spr = Sprite::create("image/test2.png");
            clippingScrollView_->insertItem(spr);
        }
            break;
        case 2:
        {
            Sprite* spr = Sprite::create("image/test3.png");
            clippingScrollView_->insertItem(spr);
        }
            break;
        case 3:
        {
            Sprite* spr = Sprite::create("image/test4.png");
            clippingScrollView_->insertItem(spr);
        }
            break;
            
        default:
            break;
    }
    
}

void HelloWorld::menuCallback2(Ref *sender)
{
//    clippingScrollView->releaseItem(random(0, 0));
    clippingScrollView_->releaseItem(0);
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point location = touch->getLocation();
    
    auto cSV = (ClippingScrollView*)this->getChildByName("clippingScrollView");
    Rect rect = cSV->getSprite()->getBoundingBox();
    rect.origin += cSV->getPosition();
    
    if (rect.containsPoint(location))
    {
        CCLOG ("터치");
        cSV->setIsClicked(true);
    }
    else
    {
        CCLOG ("터치안됨");
        cSV->setIsClicked(false);
    }
    cSV->setOrigin(location);
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point location = touch->getLocation();
    auto cSV = (ClippingScrollView*)this->getChildByName("clippingScrollView");
    cSV->moveByMouse(location);
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto cSV = (ClippingScrollView*)this->getChildByName("clippingScrollView");
    cSV->setIsClicked(false);
    cSV->replace();
}

void HelloWorld::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
}

