#ifndef GRAPH_NODE_HPP
#define GRAPH_NODE_HPP

#include "GraphException.hpp"
#include <unordered_map>
#include <string>

namespace graph
{

typedef unsigned long int Distance;
typedef unsigned long int CityID;
    
class Node
{
public:
    std::string city_name;
    std::unordered_map<CityID, Distance> reachable;

    CityID previous;
    Distance distance;
};

}

#endif
