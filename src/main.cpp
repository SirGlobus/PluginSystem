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

int main() {
    loadModules(".\\modules");
    return 0;
}
