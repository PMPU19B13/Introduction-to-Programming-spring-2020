#pragma once

#include <string>
#include <fstream>
#include "controller.h"

class Controller;

enum PrimitiveType;

class FileIO
{
private:

public:

	static void read(const std::string& filename, Controller& controller);

	static void write(const std::string& filename, PrimitiveType type, const Pair<ID, Storage<double>>& params);
};
