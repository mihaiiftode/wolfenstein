//
// Created by Morten Nobel-Jørgensen on 22/09/2017.
//

#include "WorldMap.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

using namespace std;

void WorldMap::loadMap(std::string filename)
{
    // todo implement json loading this instead following
    //values.push_back({0, 0, 0,0}); // -------> x
    //values.push_back({0,-1,-1,2}); // |
    //values.push_back({0,-1,-1,9}); // |
    //values.push_back({0, 0, 0,0}); // v z

    using namespace rapidjson;
    ifstream fis(filename);
    IStreamWrapper isw(fis);
    Document d;
    d.ParseStream(isw);

    const Value& a = d["tileMap"];
    assert(a.IsArray());
    for (SizeType i = 0; i<a.Size(); i++)
    {
        std::vector<int> row;
        for (SizeType j = 0; j<a[i].Size(); ++j)
        {
            row.push_back(a[i][j].GetInt());
        }
        values.push_back(row);
    }

    startingPosition.x = d["spawn"]["x"].GetFloat();
    startingPosition.y = d["spawn"]["y"].GetFloat();
    startingRotation = d["spawn"]["angle"].GetFloat();

}

int WorldMap::getTile(int x, int y)
{
    return values.at(y).at(x);
}

int WorldMap::getWidth()
{
    return values[0].size();
}

int WorldMap::getHeight()
{
    return values.size();
}

glm::vec2 WorldMap::getStartingPosition()
{
    return startingPosition;
}

float WorldMap::getStartingRotation()
{
    return startingRotation;
}

glm::vec4 WorldMap::getFloorColor()
{
    return floorColor;
}

glm::vec4 WorldMap::getCeilColor()
{
    return ceilColor;
}
