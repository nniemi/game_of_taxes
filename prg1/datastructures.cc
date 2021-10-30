// Datastructures.cc
//
// Student name:  Niemi



#include "datastructures.hh"

#include <random>

#include <cmath>
#include <unordered_map>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)





Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::town_count()
{

    return database.size();

}

void Datastructures::clear_all()
{
    database.clear();
}

bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{

    if(database.find(id) != database.end())
        return false;

    Town* new_town = new Town;
    database.insert(std::make_pair(id, new_town));
    new_town->name = name;
    new_town->coord = coord;
    new_town->tax = tax;
    return true;

}

Name Datastructures::get_town_name(TownID id)
{
    if (database.find(id) == database.end())
        return NO_NAME;
    return database.at(id)->name;
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    if (database.find(id) == database.end())
        return NO_COORD;
    return database.at(id)->coord;
}

int Datastructures::get_town_tax(TownID id)
{
    if (database.find(id) == database.end())
        return NO_VALUE;
    return database.at(id)->tax;
}

std::vector<TownID> Datastructures::all_towns()
{
    std::vector<std::string> all;
    for (auto& i : database) {
        all.push_back(i.first);
    }
    return all;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    std::vector<TownID> towns;

    for (auto& i : database) {
        if(i.second->name == name)
            towns.push_back(name);
    }
    return towns;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{

    // Checking if the town exists.
    if(database.find(id) == database.end())
        return false;

    // Renaming the city.
    database.at(id)->name = newname;
    return true;
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    // Creating a vector
    std::vector<TownID> towns;

    // Reserving memoryspace for the vector.
    towns.reserve(database.size());

    // Going through the database and pushing TownIDs to the vector.
    for(auto& i : database) {
        towns.push_back(i.first);
    }

    // Sorting by names of the towns, using lambda function to
    // find the correct sorting.
    std::sort(towns.begin(), towns.end(),[this](TownID a, TownID b)
        {return database.at(a)->name < database.at(b)->name;});

    // Returning the vector.
    return towns;

}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    // Creating a vector
    std::vector<TownID> towns;

    // Reserving memoryspace for the vector.
    towns.reserve(database.size());

    // Going through the database and pushing TownIDs to the vector.
    for(auto& i : database) {
        towns.push_back(i.first);
    }

    // Sorting by the distance to origin (0,0), using lambda function to
    // find the correct sorting.
    std::sort(towns.begin(), towns.end(),[this](TownID a, TownID b)
        {return sqrt(pow((0 - database.at(a)->coord.x),2.0) +
                     pow((0 - database.at(a)->coord.y),2.0)) <
                sqrt(pow((0 - database.at(b)->coord.x),2.0) +
                     pow((0 - database.at(b)->coord.y),2.0));});

    // Returning the vector.
    return towns;
}

TownID Datastructures::min_distance()
{
    // Replace the line below with your implementation
    throw NotImplemented("min_distance()");
}

TownID Datastructures::max_distance()
{
    // Replace the line below with your implementation
    throw NotImplemented("max_distance()");
}

bool Datastructures::add_vassalship(TownID /*vassalid*/, TownID /*masterid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("add_vassalship()");
}

std::vector<TownID> Datastructures::get_town_vassals(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("get_town_vassals()");
}

std::vector<TownID> Datastructures::taxer_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("taxer_path()");
}

bool Datastructures::remove_town(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_town()");
}

std::vector<TownID> Datastructures::towns_nearest(Coord /*coord*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("towns_nearest()");
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("longest_vassal_path()");
}

int Datastructures::total_net_tax(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("total_net_tax()");
}
