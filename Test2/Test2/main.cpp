//
//  main.cpp
//  Test2
//
//  Created by ace-22 on 2020/08/20.
//  Copyright © 2020 ace-22. All rights reserved.
//

#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class SPtr
{
private:
    T* obj_;
    int* count_;
    
public:
    template<typename... Ts>
    void make_SPtr(Ts&&... params)
    {
        this->obj_ = new T(params...);
    }
    inline void getCount() { std::cout << "참조 카운트 : " << *count_ << std::endl; }
    
public:
    SPtr operator=(SPtr param)
    {
        obj_ = param.obj_;
        count_ = param.count_;
        ++*param.count_;
        return *this;
    }
    inline T* operator->() { return obj_; }
    inline T& operator*() { return *obj_; }
    
public:
    inline SPtr(T* p = nullptr) : obj_(p) { count_ = new int(1); }
    SPtr(const SPtr& copy)
    {
        obj_ = copy.obj_;
        count_ = copy.count_;
        ++(*count_);
    }
    ~SPtr()
    {
        if (--(*count_) == 0)
        {
            delete obj_;
            delete count_;
        }
    }
};

class Object
{
private:
    std::string name_;
public:
    inline std::string getName() { return name_; }
public:
    inline Object(std::string name = "null") : name_(name) { std::cout << name_ << "생성" << std::endl; }
    inline ~Object() {}
};

class Box
{
private:
    std::vector<SPtr<Object>> contents_;
public:
    void push(std::string name)
    {
        std::cout << name << "을 Box에 Push" << std::endl;
        SPtr<Object> obj;
        obj.make_SPtr<Object>(name);
        contents_.push_back(obj);
    }
    
    void check()
    {
        for (auto obj : contents_)
        {
            std::cout << "Box 안에 " << obj->getName() << "가 있다." << std::endl;
        }
    }
    
    void test()
    {
        contents_[1] = contents_[0];
        contents_[2] = contents_[0];
        
        contents_[0].getCount();
        contents_[1].getCount();
        contents_[2].getCount();
    }
};


int main(int argc, const char * argv[]) {
    Box box;
    
    box.push("Apple");
    box.push("Orange");
    box.push("Grape");
    box.check();
    return 0;
}
