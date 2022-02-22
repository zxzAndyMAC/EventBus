//
//  Event.h
//  EventBus
//
//  Created by AndyZheng on 2022/2/21.
//

#ifndef Event_h
#define Event_h

#include "EObject.h"

namespace EB {

class Event: public EObject {
public:
    virtual ~Event(){}
    
    explicit Event(EObject& sender):_sender(sender){}
    
    /**
     *获取事件发送者
     *@return 事件发送者
     */
    EObject& getSender() {
        return this->_sender;
    }
    
    /**
     *终止传递事件
     */
    void suspendEvent() {
        this->_suspend = true;
    }
    
    /**
     *事件是否终止传递
     */
    bool isSuspend() {
        return this->_suspend;
    }
    
private:
    /**
     *是否终止事件的传递
     */
    bool _suspend = false;
    
    EObject& _sender;
};

}

#endif /* Event_h */
