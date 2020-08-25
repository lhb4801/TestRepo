//
//  ClippingScrollView.cpp
//  Test
//
//  Created by ace-22 on 2020/08/21.
//

#include "ClippingScrollView.h"

bool ClippingScrollView::init(Direction dir, float padding)
{
    if(false == ClippingNode::init())
        return false;
    
    touchLayer_ = Layer::create();
    
    dir_ = dir;
    padding_ = padding;
    
    sprite_ = Sprite::create("image/test6.png");
    sprite_->setPosition(Vec2(0, 0));
    sprite_->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(sprite_);
    this->reorderChild(sprite_, -1);
    this->setContentSize(sprite_->getContentSize());
    
    touchLayer_->setAnchorPoint(Vec2(0.5, 0.5));
    touchLayer_->setContentSize(sprite_->getContentSize());
    
    itemGroup_ = Node::create();
    itemGroup_->setPosition(0, 0);
    itemGroup_->setAnchorPoint(Vec2(0.5, 0.5));
    itemGroup_->setContentSize(sprite_->getContentSize());
    touchLayer_->addChild(itemGroup_);
    
    this->setStencil(sprite_);
    
    
    switch (dir_)
    {
        case VERTICAL_UP:
        case VERTICAL_DOWN:
        {
            touchLayer_->setPositionX(sprite_->getContentSize().width * 0.5);
            itemGroup_->setPositionX(sprite_->getContentSize().width * 0.5);
            break;
        }
        case HORIZONTAL_LEFT:
        case HORIZONTAL_RIGHT:
        {
            touchLayer_->setPositionY(sprite_->getContentSize().height * 0.5);
            itemGroup_->setPositionY(sprite_->getContentSize().height * 0.5);
            break;
        }
        default:
            break;
    }
    this->addChild(touchLayer_);
    
    refresh();
    replace();
    
    return true;
}

ClippingScrollView* ClippingScrollView::create(Direction dir, float padding)
{
    ClippingScrollView* ret = new ClippingScrollView();
    if (ret && ret->init(dir, padding))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void ClippingScrollView::insertItem(Node *node)
{
    switch (dir_)
    {
        case VERTICAL_UP:
        {
            node->setPosition(0, viewSize_ + (node->getContentSize().height + padding_) * 0.5);
            break;
        }
           
        case VERTICAL_DOWN:
        {
            node->setPosition(0, viewSize_ - (node->getContentSize().height + padding_) * 0.5);
        }
            break;
        case HORIZONTAL_LEFT:
        {
            node->setPosition(viewSize_ - (node->getContentSize().width + padding_) * 0.5, 0);
        }
            break;
        case HORIZONTAL_RIGHT:
        {
            node->setPosition(viewSize_ + (node->getContentSize().width + padding_) * 0.5, 0);
        }
            break;
        default:
            break;
    }
    
    auto scaleByAct = ScaleBy::create(0.1, 1.1);
    auto sequenceAct = Sequence::create(scaleByAct, scaleByAct->reverse(), NULL);
    
//    node->setAnchorPoint(Vec2(0.5, 0.5));
    node->runAction(sequenceAct);
    itemGroup_->addChild(node);
    itemList_.pushBack(node);
    refresh();
    
    
}

void ClippingScrollView::releaseItem(int value)
{
    if (value > itemList_.size() - 1 || itemList_.empty()) // 예외 처리 (삭제하려는 번호가 아이템 갯수보다 많은 경우 || 아이템 리스트 벡터가 비어있는 경우)
        return;
        
    Vector<Node*>::iterator it = itemList_.find(itemList_.at(value));
    if (it != itemList_.end())
    {
        itemGroup_->removeChild(itemList_.at(value), false);
        itemList_.erase(it);
    }
    refresh();
}

void ClippingScrollView::refresh()
{
    viewSize_ = 0;
    
    if (itemList_.size() == 0)
        return;
    
    
    switch (dir_)
    {
        case VERTICAL_UP:
        {
            for (auto item : itemList_)
            {
                float itemSize = (item->getContentSize().height + padding_) * 0.5;
                viewSize_ += itemSize;
                auto moveToAct = MoveTo::create(0.1, Vec2(0, viewSize_));
                auto easeOutAct = EaseOut::create(moveToAct, 3);
                item->runAction(easeOutAct);
                viewSize_ += itemSize;
            }
            break;
        }
            
        case VERTICAL_DOWN:
        {
            for (auto item : itemList_)
            {
                float itemSize = (item->getContentSize().height + padding_) * 0.5;
                viewSize_ -= itemSize;
                auto moveToAct = MoveTo::create(0.1, Vec2(0, viewSize_));
                auto easeOutAct = EaseOut::create(moveToAct, 3);
                item->runAction(easeOutAct);
                viewSize_ -= itemSize;
            }
            break;
        }
            
        case HORIZONTAL_LEFT:
        {
            for (auto item : itemList_)
            {
                float itemSize = (item->getContentSize().width + padding_) * 0.5;
                viewSize_ -= itemSize;
                auto moveToAct = MoveTo::create(0.1, Vec2(viewSize_, 0));
                auto easeOutAct = EaseOut::create(moveToAct, 3);
                item->runAction(easeOutAct);
                viewSize_ -= itemSize;
            }
            break;
        }
            
        case HORIZONTAL_RIGHT:
        {
            for (auto item : itemList_)
            {
                float itemSize = (item->getContentSize().width + padding_) * 0.5;
                viewSize_ += itemSize;
                auto moveToAct = MoveTo::create(0.1, Vec2(viewSize_, 0));
                auto easeOutAct = EaseOut::create(moveToAct, 3);
                item->runAction(easeOutAct);
                viewSize_ += itemSize;
            }
            break;
        }
            
        default:
            break;
    }
    replace();
}

void ClippingScrollView::moveByMouse(Point location)
{
    if (false == isClicked_)
        return;
    
    Point distance = origin_ - location;
    switch (dir_) {
        case Direction::VERTICAL_UP :
        case Direction::VERTICAL_DOWN :
            distance.x = 0;
            break;
        case Direction::HORIZONTAL_LEFT :
        case Direction::HORIZONTAL_RIGHT :
            distance.y = 0;
            break;
        default:
            break;
    }
    
    origin_ = location;
    auto moveAct = MoveBy::create(0.1, Vec2(-distance));
    itemGroup_->runAction(moveAct);
}

void ClippingScrollView::replace()
{
    itemGroup_->stopAllActions();
    offset = this->getPosition();
    bool isChanged = false;
    Point position;
    
    switch (dir_) // 재배치 시에는 양 끝의 인자가 레이어를 넘었는 지 확인
    {
        case HORIZONTAL_RIGHT:
        {
            if (itemGroup_->getPositionX() + viewSize_ < itemGroup_->getContentSize().width)
            {
                isChanged = true;
                position.x = itemGroup_->getContentSize().width - viewSize_;
            }
            if (itemGroup_->getPositionX() > 0 || viewSize_ < itemGroup_->getContentSize().width)
            {
                position.x = 0;
                isChanged = true;
            }
            break;
        }
        case HORIZONTAL_LEFT:
        {
            if (itemGroup_->getPositionX() < itemGroup_->getContentSize().width || -viewSize_ < itemGroup_->getContentSize().width)
            {
                isChanged = true;
                position.x = itemGroup_->getContentSize().width;
            }
            if (itemGroup_->getPositionX() > -viewSize_ && -viewSize_ > itemGroup_->getContentSize().width)
            {
                isChanged = true;
                position.x = -viewSize_;
            }
            CCLOG ("%f", itemGroup_->getPositionX());
            CCLOG ("%f", itemGroup_->getContentSize().width);
            CCLOG ("%f", viewSize_);
            break;
        }
        case VERTICAL_DOWN:
        {
            if (itemGroup_->getPositionY() < itemGroup_->getContentSize().height || -viewSize_ < itemGroup_->getContentSize().height)
            {
                isChanged = true;
                position.y = itemGroup_->getContentSize().height;
            }
            if (itemGroup_->getPositionY() > -viewSize_ && -viewSize_ > itemGroup_->getContentSize().height)
            {
                isChanged = true;
                position.y = -viewSize_;
            }
            break;
        }
        case VERTICAL_UP:
        {
            if (itemGroup_->getPositionY() + viewSize_ < itemGroup_->getContentSize().height)
            {
                isChanged = true;
                position.y = itemGroup_->getContentSize().height - viewSize_;
            }
            if (itemGroup_->getPositionY() > 0 || viewSize_ < itemGroup_->getContentSize().height)
            {
                isChanged = true;
                position.y = 0;
            }
            break;
        }
        default:
            break;
    }
    
    if (false == isChanged)
        return;
    
    auto moveAct = MoveTo::create(0.02, position);
    itemGroup_->runAction(moveAct);
}
