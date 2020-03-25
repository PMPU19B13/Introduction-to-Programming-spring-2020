#include "FileIO.h"


void FileIO::readPrimitive(const std::string& filename, Controller& controller)
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

            file >> temp >> temp >> x >> temp >> y >> temp;

            Storage<double> args;
            args.add(x);
            args.add(y);
            std::cout << "first: " << args[0] << "\t second: " << args[1] << std::endl;
            controller.addPrimitive(P_Point, args);
        }
        else if (typeName == "Segment")
        {
            std::string temp;
            double x1;
            double y1;
            double x2;
            double y2;

            // Segment { start { x 15 y 10 } end { x 16 y 17 } }
            file >> temp >> temp >> temp >> temp >> x1 >> temp >> y1
                >> temp >> temp >> temp >> temp >> x2 >> temp >> y2 >> temp >> temp;

            Storage<double> args;
            args.add(x1);
            args.add(y1);
            args.add(x2);
            args.add(y2);

            controller.addPrimitive(P_Segment, args);
        }
        else if (typeName == "Circle")
        {
            std::string temp;
            double xCenter;
            double yCenter;
            double radius;

            // Circle { center { x 16 y 17 } radius 4 }
            file >> temp >> temp >> temp >> temp >> xCenter >> temp >> yCenter
                >> temp >> temp >> radius >> temp;

            Storage<double> args;
            args.add(xCenter);
            args.add(yCenter);
            args.add(radius);

            controller.addPrimitive(P_Circle, args);
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



void FileIO::writePrimitive(const std::string& filename, Controller& controller)
{
    std::ofstream file;

    file.open(filename);

    if (!file.is_open())
    {
        return;
    }

    List<Pair<ID, Point>>::Marker pointMarker = controller.m_points.createMarker();
    while (pointMarker.isValid())
    {
        Storage<double> args = pointMarker.getValue().value.getParams();

        file << "Point { x " << args[0] << " y " << args[1] << " }" << std::endl;
        pointMarker.next();
    }

    List<Pair<ID, Segment>>::Marker segmentMarker = controller.m_segments.createMarker();
    while (segmentMarker.isValid())
    {
        Storage<double> args = segmentMarker.getValue().value.getParams();
        file << "Segment { start { x " << args[0] << " y " << args[1] << " } end { x "
            << args[2] << " y " << args[3] << " } }" << std::endl;
        segmentMarker.next();
    }

    List<Pair<ID, Circle>>::Marker circleMarker = controller.m_circles.createMarker();
    while (circleMarker.isValid())
    {
        Storage<double> args = circleMarker.getValue().value.getParams();
        file << "Circle { center { x " << args[0] << " y " << args[1] << " } radius "
            << args[2] << " }" << std::endl;
        circleMarker.next();
    }

    file.close();
}
