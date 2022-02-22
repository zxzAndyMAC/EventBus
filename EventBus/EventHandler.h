//
//  EventHandler.h
//  EventBus
//
//  Created by AndyZheng on 2022/2/21.
//

#ifndef EventHandler_h
#define EventHandler_h

namespace EB {

/**
 *前置声明
 */
class Event;

template<class T>
class EventHandler {
public:
    EventHandler(){
        static_assert(std::is_base_of<Event, T>::value, "Constructor Error: EventHandler<T> T must be a class derived from Event");
    }
    
    virtual ~EventHandler(){}
    
    /**
     *纯虚函数，事件接收处理
     *@param event实例
     */
    virtual void onEvent(T&) = 0;
    
    /**
     *此方法被EvenBus掉用并且动态转化为T类型Event
     *@param e 需要下发的event
     */
    void dispatch(Event& e) {
        onEvent(dynamic_cast<T&>(e));
    }
};

}

#endif /* EventHandler_h */
