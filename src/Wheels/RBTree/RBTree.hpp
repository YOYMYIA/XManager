#ifndef WHEEL_RBTREE_HPP
#define WHEEL_RBTREE_HPP

#include <iostream>
#include <iomanip>
#include "../../Log/include/DebugLog.h"

namespace my_wheel
{

template<class T>
class RBTNode
{
public:
    enum RBTColor
    {
        RED,
        BLACK
    };

public:
    
    T key;
    RBTColor color;
    RBTNode<T> *parent;
    RBTNode<T> *left;
    RBTNode<T> *right;

    RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r)
    : key(value), color(c), parent(p), left(l), right(r)
    {
        DBG_LOGI("create one RBTNode");
    }
};

#define rb_parent(r) ((r)->parent)
#define rb_color (r) ((r)->color )
#define rb_is_red(r) ((r)->color == RBTColor::RED)
#define rb_is_black(r) ((r)->color == RBTColor::BLACK)
#define rb_set_black(r)  do { (r)->color = RBTColor::BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RBTColor::RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

template <class T>
class RBTree
{
private:
    RBTNode<T> *_mRoot;  //root node



};


}//my_wheel


#endif