#ifndef __MUDUO_NOCOPYABLE_H__
#define __MUDUO_NOCOPYABLE_H__


namespace muduo
{

class nocopyable
{
public:
    nocopyable(const nocopyable &) = delete;
    void operator=(const nocopyable &) = delete;

protected:
    nocopyable() = default;
    ~nocopyable() = default;

};

}
#endif