#ifndef DATA_INTERFACE_PAIR_H
#define DATA_INTERFACE_PAIR_H
#include <string>
#include <memory>
#include "DataInterfaceVariable.h"

template<typename T>
class DataInterfacePair
{
public:
    DataInterfacePair(std::string __name, T __data) : name(__name), ptr(new DataInterfaceVariable<T>(new T(__data))){}
    DataInterfacePair(std::string __name, T* __data) : name(__name), ptr(new DataInterfaceVariable<T>(__data)){}

    std::string getName()
    {
        return name;
    }
    std::unique_ptr<IDataInterfaceVariable>&& getValue()
    {
        return std::move(ptr);
    }
private:
    std::string name;
    std::unique_ptr<IDataInterfaceVariable> ptr;
};

#endif //DATA_INTERFACE_PAIR_H