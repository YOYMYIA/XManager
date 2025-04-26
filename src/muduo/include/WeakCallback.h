#ifndef __MUDUO_WEAKCALLBACK_H__
#define __MUDUO_WEAKCALLBACK_H__

#include <functional>
#include <memory>

namespace muduo
{

template<typename CLASS, typename ...ARGS>
class WeakCallback
{
public:

    WeakCallback(const std::weak_ptr<CLASS>& object, 
                 const std::function<void (CLASS*, ARGS...)> &function)
        :_object(object), _function(function)
        {

        }

    void operator()(ARGS&&... args) const
    {
        //create the shared_ptr of this objest
        std::shared_ptr<CLASS> ptr(_object.lock());
        if(ptr)
        {
            _function(ptr.get(), std::forward<ARGS>(args) ...);
        }
    }

private:
    std::weak_ptr<CLASS> _object;
    std::function<void(CLASS*, ARGS...)> _function;
};

template<typename CLASS, typename ...ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::shared_ptr<CLASS> &object, void(CLASS::*function)(ARGS...))
{
    return WeakCallback<CLASS, ARGS...> (object, function);
}

template<typename CLASS, typename ...ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::shared_ptr<CLASS> &object, void(CLASS::*function)(ARGS...) const)
{
    return WeakCallback<CLASS, ARGS...> (object, function);
}

}//muduo

#endif