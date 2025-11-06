#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <string>
#include <filesystem>
#include "IModule.h"
#include "DataInterface.h"

namespace fs = std::filesystem;

void loadModules(const std::string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".dll") {
            HMODULE handle = LoadLibraryW(entry.path().c_str());
            if (!handle) {
                std::cerr << "Failed to load module: " << GetLastError() << "\n";
                continue;
            }

            auto createModule = (CreateModuleFunc)GetProcAddress(handle, "createModule");
            auto destroyModule = (DestroyModuleFunc)GetProcAddress(handle, "destroyModule");

            if (!createModule || !destroyModule) {
                std::cerr << "Invalid module: " << GetLastError() << "\n";
                FreeLibrary(handle);
                continue;
            }

            IModule* module = createModule();
            std::cout << "Loaded module: " << module->getName() << "\n";
            module->execute();

            destroyModule(module);
            FreeLibrary(handle);
        }
    }
}

void foo(DataInterface& d)
{
    int* a = d.get<int>("a");
    std::string* s = d.get<std::string>("s");
    std::vector<int>* v = d.get<std::vector<int>>("v");
    for(int i = 0; i < v->size(); ++i)
        (*v)[i] += 12;
    *a = 0;
    std::reverse(s->begin(), s->end());
}   

int main() {
    DataInterface intrf;
    int a = 12;
    std::string s = "Hello, world!";
    std::vector<int> v{1, 2, 3, 4, 5};
    intrf.push("a", a);
    intrf.push("s", s);
    intrf.push("v", v);
    foo(intrf);
    std::cout << a << "\n";
    std::cout << s << "\n";
    for(auto i : v)
        std::cout << i << " ";
    //loadModules(".\\modules");
    return 0;
}
