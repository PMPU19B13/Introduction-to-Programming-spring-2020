#pragma once

#include <string>
#include <fstream>

#include "controller.h"

class FileIO
{
private:

public:
	static void readPrimitive(const std::string& filename, Controller& controller);
	static void writePrimitive(const std::string& filename, Controller& controller);
	static void writeRequirement(const std::string& filename, Controller& controller);
	static void readRequirement(const std::string& filename, Controller& controller);
};

