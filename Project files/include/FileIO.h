#pragma once
#include <string>
#include "controller.h"
#include <fstream>

class FileIO {
private:

public:
    FileIO() {};
    static void readPrimitive(const std::string& filename, Controller& controller);
    static void writePrimitive(const std::string& filename,Controller& controller);
};
