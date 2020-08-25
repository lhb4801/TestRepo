//
//  ClippingScrollView.h
//  Test
//
//  Created by ace-22 on 2020/08/21.
//

#ifndef ClippingScrollView_h
#define ClippingScrollView_h

class ClippingLayer;

enum Direction
{
    VERTICAL_DOWN = 0,
    VERTICAL_UP,
    HORIZONTAL_LEFT,
    HORIZONTAL_RIGHT
};

USING_NS_CC;

class ClippingScrollView : public ClippingNode
{
public:
    static ClippingScrollView* create(Direction dir = (Direction)0, float padding = 0.0);
    bool init(Direction dir = (Direction)0, float padding = 0.0);
    
private:
    Direction dir_;
    float padding_;
    
    bool isClicked_;
    Vec2 offset;
    Point origin_;
    
    float viewSize_; // 추가된 아이템들의 총 길이
    Vector<Node*> itemList_; //아이템 벡터
    
    Node* touchLayer_;
    Node* itemGroup_;
    Sprite* sprite_;
    
public:
    void insertItem(Node* node);
    void releaseItem(int value);
    void refresh();
    
    void moveByMouse(Point location);
    void replace();

public:
    inline float getPadding() { return padding_; }
    inline Node* getTouchLayer() { return touchLayer_; }
    inline Sprite* getSprite() { return sprite_; }
    inline Point getOrigin() { return origin_; }
    inline Direction getDirection() { return dir_; }
    inline bool getIsClick() { return isClicked_; }
    
public:
    inline void setOrigin(Point value) { origin_ = { value.x, value.y }; }
    inline void setOrigin(float x, float y) { origin_ = {x, y}; }
    inline void setIsClicked(bool value) { isClicked_ = value; }
    
};

#endif /* ClippingScrollView_h */
