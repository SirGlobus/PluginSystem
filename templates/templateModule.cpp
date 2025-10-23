#include "IModule.h"
#include <iostream>

class TemplateModule : public IModule {
public:
    const char* getName() const override {
        return "templateModule";
    }

    void execute() override {
        //Your code here
    }
};


extern "C" IModule* createModule() {
    return new TemplateModule();
}

extern "C" void destroyModule(IModule* module) {
    delete module;
}
