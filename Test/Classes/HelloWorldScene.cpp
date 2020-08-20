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

#define ScreenX 1080
#define ScreenY 720

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
    
    for(int i = 0; i < 10; i++)
    {
        Sprite* slime = Sprite::create("image/slime/slime_normal.png");
        slime->setScale(0.25, 0.25);
        slime->setPosition(Vec2(ScreenX * 0.5, ScreenY * 0.5));
        slimes.push_back(slime);
        this->addChild(slime);
    }
    
    MenuItemImage* item_1 = MenuItemImage::create("image/slime/slime_normal.png", "image/slime/slime_snow.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
//    MenuItemImage* item_2 = MenuItemImage::create("image/slime/slime_leaf.png", "image/slime/slime_flower.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
//    item_2->setPosition(Vec2(0, -140));
    Menu* menu = Menu::create(item_1, NULL);
    this->addChild(menu);
    menu->setPosition(Vec2(ScreenX * 0.08, ScreenY * 0.9));
    
    
    Sprite* pSprite = Sprite::create("Image/Test2.png");
    pSprite->setPosition(Vec2(0, 0));
    pSprite->setVisible(true);
    pSprite->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(pSprite);
    
//    auto action =
//    pSprite->runAction(action);
    
    
    
//    auto btn_1 = MenuItemFont::create("메뉴1", CC_CALLBACK_1(HelloWorld::menuCallback, this));
//    auto btn_2 = MenuItemImage::create("image/btn2.png", "image/btn1.png", CC_CALLBACK_1(HelloWorld::menuCallback, this));
//    btn_2->setContentSize(Size(50, 50)); // 사이즈는 콜라이더와 연관있고, 이미지 크기와는 연관이 없다
//    btn_2->setScale(0.5);
//    auto menu = Menu::create(btn_1, btn_2, NULL); //메뉴의 마지막에는 NULL, 문자열처럼!
//    menu->alignItemsVertically(); //안의 구성 요소를 수직으로 정렬
////    menu->setPosition(Vec2(240, 160));
//    menu->setAnchorPoint(Vec2(0.5, 0.5));
//    this->addChild(menu);
//
//
    //this->reorderChild(pSprite, 0);

    
    return true;
}
void HelloWorld::menuCallback(Ref *sender)
{
    
    CCLOG("menuCallback");
    for (Sprite* slime : slimes)
    {
        auto action = JumpBy::create(0.6, Vec2(random(-50, 50), random(-50, 50)), 20, 3);
        slime->runAction(action);
    }
    //이벤트 발생
    
}
