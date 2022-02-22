//
//  EObject.h
//  EventBus
//
//  Created by AndyZheng on 2022/2/21.
//

#ifndef EObject_h
#define EObject_h

namespace EB {

/**
 * EventBus 基类
 */
class EObject {
public:
    virtual ~EObject() {};
    
    EObject() = default;
    
    EObject(const EObject&) = delete;
    EObject& operator = (const EObject&) = delete;
};

}
#endif /* EObject_h */
