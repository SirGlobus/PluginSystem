#ifndef IMODULE_H
#define IMODULE_H

class IModule {
public:
    virtual ~IModule() {}
    virtual const char* getName() const = 0;
    virtual void execute() = 0;
};

typedef IModule* (*CreateModuleFunc)();
typedef void (*DestroyModuleFunc)(IModule*); 

#endif // IMODULE_H
