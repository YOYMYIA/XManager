#ifndef __MUDUO_ATOMIC_H__
#define __MUDUO_ATOMIC_H__

#include "noncopyable.h"
#include <stdint.h>

namespace muduo
{

namespace detail
{

    template <typename T>
    class AtomicIntegerT : nocopyable
    {
    public:
        AtomicIntegerT() : _value(0)
        {
        }

        T get()
        {
            return __sync_val_compare_and_swap(&_value, 0, 0);
        }

        T getAndAdd(T x)
        {
            // in gcc >= 4.7: __atomic_fetch_add(&value_, x, __ATOMIC_SEQ_CST)
            return __sync_fetch_and_add(&_value, x);
        }

        T addAndGet(T x)
        {
            return getAndAdd(x) + x;
        }

        T incrementAndGet()
        {
            return addAndGet(1);
        }

        T decrementAndGet()
        {
            return addAndGet(-1);
        }

        void add(T x)
        {
            getAndAdd(x);
        }

        void increment()
        {
            incrementAndGet();
        }

        void decrement()
        {
            decrementAndGet();
        }

        T getAndSet(T newValue)
        {
            // in gcc >= 4.7: __atomic_exchange_n(&value_, newValue, __ATOMIC_SEQ_CST)
            return __sync_lock_test_and_set(&_value, newValue);
        }

    private:
        volatile T _value;
    };

} // detail

typedef detail::AtomicIntegerT<int32_t> AtomicInt32;
typedef detail::AtomicIntegerT<int64_t> AtomicInt64;

}

#endif