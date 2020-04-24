#include "FileIO.h"


void FileIO::read(const std::string& filename, Controller& controller)
{
	std::ifstream file;

	file.open(filename);

	if (!file.is_open())
	{
		return;
	}


	while (!file.eof())
	{
		std::string typeName;
		file >> typeName;

		if (typeName == "Point")
		{
			std::string temp;
			double x;
			double y;
			char buf[1024];
			file >> temp >> temp >> x >> temp >> y >> temp >> temp >> buf >> temp;
			ID* id = new ID(buf);
			Storage<double> args;
			args.add(x);
			args.add(y);
			controller.addPrimitive(P_Point, args, id);
		}
		else if (typeName == "Segment")
		{
			std::string temp;
			double x1;
			double y1;
			double x2;
			double y2;
			char buf[1024];
			// Segment { start { x 15 y 10 } end { x 16 y 17 } }
			file >> temp >> temp >> temp >> temp >> x1 >> temp >> y1
				>> temp >> temp >> temp >> temp >> x2 >> temp >> y2 >> temp >> temp >> temp >> buf >> temp;
			ID* id = new ID(buf);
			Storage<double> args;
			args.add(x1);
			args.add(y1);
			args.add(x2);
			args.add(y2);

			controller.addPrimitive(P_Segment, args, id);
		}
		else if (typeName == "Circle")
		{
			std::string temp;
			double xCenter;
			double yCenter;
			double radius;
			char buf[1024];
			// Circle { center { x 16 y 17 } radius 4 }
			file >> temp >> temp >> temp >> temp >> xCenter >> temp >> yCenter
				>> temp >> temp >> radius >> temp >> temp >> buf >> temp;
			ID* id = new ID(buf);
			Storage<double> args;
			args.add(xCenter);
			args.add(yCenter);
			args.add(radius);

			controller.addPrimitive(P_Circle, args, id);
		}
		else
		{
			if (file.eof())
				break;
			file.close();
			throw Error();
		}
	}

	file.close();
}

void FileIO::write(const std::string& filename, PrimitiveType type, const Pair<ID, Storage<double>>& params)
{
	std::ofstream file(filename, std::ios_base::app);


	if (!file.is_open())
	{
		return;
	}
	switch (type)
	{
	case P_Point:
		if (params.value.size() == 2)
			file << "Point { x " << params.value[0] << " y " << params.value[1] << " } [ " << params.key << " ]"
			<< std::endl;
		else throw BadArgument();
		break;
	case P_Segment:
		if (params.value.size() == 4)
			file << "Segment { start { x " << params.value[0] << " y " << params.value[1] << " } end { x "
			<< params.value[2] << " y " << params.value[3] << " } } [ " << params.key << " ]" << std::endl;
		else throw BadArgument();
		break;
	case P_Circle:
		if (params.value.size() == 3)
			file << "Circle { center { x " << params.value[0] << " y " << params.value[1] << " } radius "
			<< params.value[2] << " } [ " << params.key << " ]" << std::endl;
		else throw BadArgument();
		break;
	default:
		break;
	}

	file.close();
}


//Ожидает реализации метода addRequirement()

//void FileIO::writeRequirement(const std::string& filename, Controller& controller);

//void FileIO::readRequirement(const std::string& filename, Controller& controller);

