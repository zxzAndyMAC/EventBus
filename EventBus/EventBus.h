//
//  EventBus.h
//  EventBus
//
//  Created by AndyZheng on 2022/2/22.
//

#ifndef EventBus_h
#define EventBus_h

#include "Event.h"
#include "EventHandler.h"

#include <list>
#include <typeinfo>
#include <unordered_map>
#include <typeindex>
#include <iostream>

namespace EB {

class EventBus {
public:
    /**
     *获取EventBus单例
     */
    static EventBus& getInstance(){
        static EventBus instance;
        return instance;
    }
    
    /**
     * 注册事件监听，指定具体事件发送者
     *
     * @param handler 事件接收处理者
     * @param sender 事件发送者 指定处理具体事件发送者
     */
    template <class T>
    void addHandler(EventHandler<T> & handler, EObject & sender) {
        EventBus& instance = getInstance();

        // 根据事件类型获取事件处理map
        Registrations* registrations = instance.handlers[typeid(T)];

        // 创建新的map，如果不存在此事件类型集合
        if (registrations == nullptr) {
            registrations = new Registrations();
            instance.handlers[typeid(T)] = registrations;
        }

        // 添加事件处理者
        registrations->insert(std::pair(static_cast<void*>(&handler), &sender));
    }

    /**
     * 注册事件监听，不明确指定发送者
     *
     * @param handler 事件接收处理者
     */
    template <class T>
    void addHandler(EventHandler<T> & handler) {
        EventBus& instance = getInstance();

        // 根据事件类型获取事件处理map
        Registrations* registrations = instance.handlers[typeid(T)];

        // 创建新的map，如果不存在此事件类型集合
        if (registrations == nullptr) {
            registrations = new Registrations();
            instance.handlers[typeid(T)] = registrations;
        }

        // 添加事件处理者
        registrations->insert(std::pair(static_cast<void*>(&handler), nullptr));
    }
    
    /**
     * 注销事件监听
     *
     * @param handler 事件接收处理者
     */
    template <class T>
    bool removeHandler(EventHandler<T> & handler){
        EventBus& instance = getInstance();

        // 根据事件类型获取事件处理map
        Registrations* registrations = instance.handlers[typeid(T)];

        // 创建新的map，如果不存在此事件类型集合
        if (registrations == nullptr) {
            return false;
        }
        
        registrations->erase(static_cast<void*>(&handler));
        
        return true;
    }

    /**
     * 事件发射
     *
     * @param e 需要派发的事件
     */
    void fireEvent(Event & e) {
        EventBus& instance = getInstance();

        Registrations* registrations = instance.handlers[typeid(e)];

        //如果不存在指定事件处理集合则返回
        if (registrations == nullptr) {
            return;
        }

        //遍历集合发射事件
        for (auto & reg : *registrations) {
            if (e.isSuspend()) {
                break;
            }
            if ( (reg.second == nullptr) || (reg.second == &e.getSender()) ) {
                static_cast<EventHandler<Event>*>(reg.first)->dispatch(e);
            }
        }
    }
    
    virtual ~EventBus() {
        std::cout << "===== destructor EventBus =====" << std::endl;
        for (auto & reg : handlers) {
            delete reg.second;
        }
    }
private:
    /**
     *私有化构造函数
     */
    EventBus() {}
    
    /**
     *去除默认拷贝构造和赋值函数
     */
    EventBus(const EventBus&) = delete;
    EventBus& operator = (const EventBus&) = delete;
    
private:
    typedef std::unordered_map<void*, EObject*> Registrations;
    typedef std::unordered_map<std::type_index, Registrations*> TypeMap;

    TypeMap handlers;
};

}

#endif /* EventBus_h */
