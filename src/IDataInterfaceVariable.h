#ifndef I_DATA_INTER_FACE_VARIABLE_H
#define I_DATA_INTER_FACE_VARIABLE_H
#include <typeindex>

class IDataInterfaceVariable
{
public:
    virtual void* get() = 0;
    virtual std::type_index type() const = 0;
    virtual ~IDataInterfaceVariable() = default;
};

#endif //I_DATA_INTER_FACE_VARIABLE_H