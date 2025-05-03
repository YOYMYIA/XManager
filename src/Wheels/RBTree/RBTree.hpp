#ifndef WHEEL_RBTREE_HPP
#define WHEEL_RBTREE_HPP

#include <iostream>
#include <iomanip>
#include "../../Log/include/DebugLog.h"

namespace my_wheel
{

template<class T>
class RBNode
{
public:
    enum RBColor
    {
        RED,
        BLACK
    };

public:
    
    T key;
    RBColor color;
    RBNode<T> *parent;
    RBNode<T> *left;
    RBNode<T> *right;

    RBNode(T value, RBColor c, RBNode *p, RBNode *l, RBNode *r)
    : key(value), color(c), parent(p), left(l), right(r)
    {
        DBG_LOGI("create one RBNode");
    }
};

#define rb_parent(r) ((r)->parent)
#define rb_color (r) ((r)->color )
#define rb_is_red(r) ((r)->color == RBColor::RED)
#define rb_is_black(r) ((r)->color == RBColor::BLACK)
#define rb_set_black(r)  do { (r)->color = RBColor::BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RBColor::RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

template <class T>
class RBTree
{
private:
    RBNode<T> *_mRoot;  //root node



};


}//my_wheel


#endif