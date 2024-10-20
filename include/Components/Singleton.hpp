#pragma once
#include "vex.h"

template<typename T>
class Singleton {
public:
    static T* GetInstance() {
        if(m_instance == nullptr) {
            vex::mutex m_mutex;
            m_mutex.lock();
            if(m_instance == nullptr)
                m_instance = new Singleton();
            m_mutex.unlock();
        }
        return m_instance;
    }

private:
    Singleton<T> () = default;
    Singleton<T> (const Singleton<T>&) = delete;
	Singleton<T>& operator=(const Singleton<T>&) = delete;

private:
    static T* m_instance;
    static vex::mutex m_mutex;
};
