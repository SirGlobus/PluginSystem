#ifndef DATA_INTER_FACE_VARIABLE_H
#define DATA_INTER_FACE_VARIABLE_H
#include "IDataInterfaceVariable.h"

template<typename T>
class DataInterfaceVariable : public IDataInterfaceVariable
{
public:
    T* ptr;
    DataInterfaceVariable(T* p) : ptr(p) {}

    void* get() override
    {
        return static_cast<void*>(ptr);
    }
    std::type_index type() const override
    {
        return typeid(T);
    }

};

#endif //DATA_INTER_FACE_VARIABLE_H