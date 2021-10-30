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

struct Town
{
    Name name;
    Coord coord;
    int tax;

    Town* vessel;
};


std::unordered_map<TownID, Town*> database;



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

std::vector<TownID> Datastructures::find_towns(const Name &/*name*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("find_towns()");
}

bool Datastructures::change_town_name(TownID /*id*/, const Name &/*newname*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("change_town_name()");
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    // Replace the line below with your implementation
    throw NotImplemented("towns_alphabetically()");
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    // Replace the line below with your implementation
    throw NotImplemented("towns_distance_increasing()");
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
