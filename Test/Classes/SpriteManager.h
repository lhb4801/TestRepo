//
//  SpriteManager.h
//  Test
//
//  Created by ace-22 on 2020/08/14.
//

#ifndef SpriteManager_h
#define SpriteManager_h


#endif /* SpriteManager_h */


class SpriteManager
{
private:
    SpriteManager();
    ~SpriteManager();
    static SpriteManager* instance_;
    
    std::map<std::string, cocos2d::Sprite> spriteList;
public:
    static SpriteManager* Instance()
    {
        if (instance_ == nullptr) instance_ = new SpriteManager();
        return instance_;
    }
    
    
};

SpriteManager* SpriteManager::instance_ = nullptr;
