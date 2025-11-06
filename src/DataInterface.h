
#ifndef DATA_INTERFACE_H
#define DATA_INTERFACE_H
#include <memory>
#include <map>
#include "DataInterfaceVariable.h"
#include "DataInterfacePair.h"

class DataInterface
{
public:
    DataInterface(){}

    template<typename T>
    void pushPair(DataInterfacePair<T> pair)
    {
        intrf[pair.getName()] = pair.getValue();
    }

    template<typename T>
    void push(std::string name, T* data)
    {
        pushPair(DataInterfacePair<T>(name, data));
    }
    template<typename T>
    void push(std::string name, T& data)
    {
        pushPair(DataInterfacePair<T>(name, &data));
    }
    template<typename T>
    void push(std::string name, T&& data)
    {
        pushPair(DataInterfacePair<T>(name, data));
    }
    
    template<typename T>
    T* get(std::string name)
    {
        auto it = intrf.find(name);
        if(it == intrf.end())
            return nullptr;
        
        auto* base = it->second.get();
        if(base->type() == typeid(T))
        {
            auto* d = static_cast<DataInterfaceVariable<T>*>(base);
            return d->ptr;  
        }
        return nullptr;
    }
private:
    std::map<std::string, std::unique_ptr<IDataInterfaceVariable>> intrf;
};

#endif //DATA_INTERFACE_H