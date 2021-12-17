// Datastructures.cc
//
// Student name:  Niemi



#include "datastructures.hh"

#include <random>

#include <cmath>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <list>

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
    // Calls for clear function
    clear_all();
}

unsigned int Datastructures::town_count()
{
    // Returns the size of the database.
    return database.size();
}

void Datastructures::clear_all()
{
    // Clears roads
    clear_roads();

    // Deletes the pointers
    for(auto& town_pointer : database) {
        delete town_pointer.second;
    }

    // Clears the database
    database.clear();
}

bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{

    const auto town = database.find(id);

    // Checks if the town exists.
    if(town != database.end())
        return false;

    // Factors the variables to the Town struct.
    Town* new_town = new Town;
    database.insert(std::make_pair(id, new_town));
    new_town->id = id;
    new_town->name = name;
    new_town->coord = coord;
    new_town->tax = tax;
    return true;

}

Name Datastructures::get_town_name(TownID id)
{

    const auto town = database.find(id);

    // Checks if the town exists.
    if (town == database.end())
        return NO_NAME;
    return town->second->name;
}

Coord Datastructures::get_town_coordinates(TownID id)
{


    const auto town = database.find(id);

    // Checks if the town exists.
    if (town == database.end())
        return NO_COORD;
    return town->second->coord;
}

int Datastructures::get_town_tax(TownID id)
{
    const auto town = database.find(id);
    if (town == database.end())
        return NO_VALUE;
    return town->second->tax;
}


std::vector<TownID> Datastructures::all_towns()
{
    std::vector<TownID> all = {};

    // Reserving the vector
    all.reserve(database.size());

    // Loops through and stores the TownIDs to the vector
    for (auto& i : database) {
        all.push_back(i.first);
    }
    return all;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    // Creating a vector to store names
    std::vector<TownID> towns;

    // Looping through the database and storing the names.
    for (auto& i : database) {
        if(i.second->name == name)
            towns.push_back(i.first);
    }
    return towns;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{
    const auto town = database.find(id);

    // Checking if the town exists.
    if(town == database.end())
        return false;

    // Renaming the city.
    town->second->name = newname;
    return true;
}

std::vector<TownID> Datastructures::towns_alphabetically() {

    // Creating a vector and a multimap
    std::vector<Town*> towns;

    // Reserving the vector
    towns.reserve(database.size());


    for(auto& town : database) {
        towns.push_back(town.second);
    }

    // Sorting the vector by town name.
    std::sort(towns.begin(), towns.end(),[](Town* a, Town* b)
    {return a->name < b->name;});


    std::vector<TownID> towns_ordered;

    for(auto& town : towns) {
        towns_ordered.push_back(town->id);
    }


    // Returning the vector.
    return towns_ordered;



}

std::vector<TownID> Datastructures::towns_distance_increasing()
{

    // Creating a vector
    std::vector<TownID> towns_ordered;
    std::multimap<int,TownID> towns;

    // Reserving the vector
    towns_ordered.reserve(database.size());

    // Constant for coordinates
    const Coord origin = {0,0};

    // Going through the database and pushing TownIDs to the vector.
    for(auto& i : database) {
        towns.insert({distance_from_point(origin,(i.second->coord)),i.first});
    }

    // Sorting by the distance to origin (0,0), using lambda function to
    // find the correct sorting.

    for (auto& i : towns) {
        towns_ordered.push_back(i.second);
    }


    // Returning the vector.
    return towns_ordered;

}

TownID Datastructures::min_distance()
{

    // Factoring the origin
    const Coord origin = {0,0};

    // Sorts the database and finds the smallest element.
    return  std::min_element(database.begin(),database.end(),[this,origin] (const auto& a, const auto& b)
    {return distance_from_point(origin,(a.second->coord)) < distance_from_point(origin,(b.second->coord));})->first;


}

TownID Datastructures::max_distance()
{
    // Factoring the origin
    const Coord origin = {0,0};


    // Sorts the database and finds the biggest element.
    return  std::max_element(database.begin(),database.end(),[this,origin] (const auto& a, const auto& b)
    {return distance_from_point(origin,(a.second->coord)) < distance_from_point(origin,(b.second->coord));})->first;
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{


    const auto vassal = database.find(vassalid);
    const auto master = database.find(masterid);

    // Checks if either IDs are missing and if the vassal doesn't have a parent town.
    if (vassal == database.end() || master == database.end() || vassal->second->parent != nullptr) {
        return false;
    }

    // Sets the vassalships
    vassal->second->parent = master->second;
    master->second->neighbour.push_back(vassal->second);

    return true;
}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{


    std::vector<TownID> towns;
    const auto town = database.find(id);


    // Checks if the town exists.
    if(town == database.end()) {
        towns.push_back(NO_TOWNID);
        return towns;
    }
    // Reserving the vector.
    towns.reserve(town->second->neighbour.size());

    // Checks if the town doesn't have any neighbours.
    if (town->second->neighbour.empty()) {

        return towns;
    }

    // Pushbacks if a town was found.
    for (auto& i : town->second->neighbour) {
        towns.push_back(i->id);
    }
    return towns;

}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{

    std::vector<TownID> towns = {};
    auto town = database.find(id);

    if(town == database.end()) {
        towns.push_back(NO_TOWNID);
        return towns;
    }

    // Adds the city to the vector.
    towns.push_back(id);

    // Loops through the parents and stores them to the vector;
    while(town->second->parent != nullptr) {
        towns.push_back(town->second->parent->id);
        id = town->second->parent->id;
        town = database.find(id);
    }

    return towns;

}

bool Datastructures::remove_town(TownID id)
{


    const auto town = database.find(id);

    // Checking if the id exists in the database.
    if(town == database.end())
        return false;


    // Checks if the id has a parent, if so, adds the vassals to the parents
    // neighbour. If the id doesn't have a parent, clears the neighbour vector
    if (town->second->parent != nullptr) {
        for (auto& i : town->second->neighbour) {
            town->second->parent->neighbour.push_back(i);
        }
    } else {
        for(auto& i : town->second->neighbour) {
            delete i;

        }
        town->second->neighbour.clear();
    }

    // Erases the element from the database
    database.erase(database.find(id));
    return true;
}

std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{

    // Creating a vector
    std::vector<TownID> towns_ordered;
    std::multimap<int,TownID> towns;

    towns_ordered.reserve(database.size());

    // Going through the database and pushing TownIDs to the vector.
    for(auto& i : database) {
        towns.insert({distance_from_point(coord, i.second->coord),i.first});
    }

    // Sorting by the distance to origin (0,0), using lambda function to
    // find the correct sorting.
    for (auto& i : towns) {
        towns_ordered.push_back(i.second);
    }

    // Returning the vector.
    return towns_ordered;

}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{

    std::vector<TownID> longest_towns;
    std::vector<TownID> current_towns;

    const auto town = database.find(id);

    // Checks if the town exists in the database
    if(town == database.end()) {
        longest_towns.push_back(NO_TOWNID);
        return longest_towns;
    }

    // Checks the towns neighbours.
    if (town->second->neighbour.empty()) {
        longest_towns.push_back(town->second->id);
        return longest_towns;
    }

    // Starts the recursive fuction.
    recursive_longest_path(town->second,current_towns, longest_towns);

    return longest_towns;



}

int Datastructures::total_net_tax(TownID id)
{
    const auto town = database.find(id);
    if(town == database.end())
        return NO_VALUE;

    // Starts the recursive loop.
    auto tax = recursive_total_tax(town->second);

    // Checks if the town has a parent.
    if(town->second->parent != nullptr)

        // If so, subtracts their own tax.
        tax -= std::floor(0.1*tax);

    return tax;
}



int Datastructures::distance_from_point(const Coord &coord, const Coord& point) const
{
    return sqrt(((point.x - coord.x)*(point.x - coord.x)) + ((point.y - coord.y)*(point.y - coord.y)));
}

std::vector<TownID> Datastructures::recursive_longest_path(Town* current_town, std::vector<TownID> current, std::vector<TownID>& longest)
{

    // If the town doesn't have any vassals, returns the vector.
    if(current_town->neighbour.empty())
        return current;

    // If the current vector is empty, inserts the id of the current town.
    if(current.empty())
        current.push_back(current_town->id);


    // Goes through the neighbours.
    for (auto& town : current_town->neighbour) {

        // First the current town id is inserted.
        current.push_back(town->id);

        // Calls the fuction again.
        auto recursive = recursive_longest_path(town, current, longest);

        // If the new size is bigger than current longest, inserts the current one as longest.
        if(recursive.size() > longest.size())
            longest = current;

        // Pops back the last element to prevent duplicates.
        current.pop_back();
    }
    return current;
}

int Datastructures::recursive_total_tax(Town *current_town)
{
    int tax = 0;

    // Checking does the town have neighbours.
    if(current_town->neighbour.empty()) {
        return current_town->tax;
    }

    // Loops through towns in neighbours
    for(auto& town : current_town->neighbour) {

        // Calls the function again and calculates the tax.
        // std::floor is used to round the numbers.
        auto recursive = recursive_total_tax(town);
        tax += std::floor(0.1 * recursive);
    }

    // Returns the tax + current town tax.
    return tax + current_town->tax;
}



//
// Phase 2 operations
//


void Datastructures::clear_roads()
{

    // Deleting the road pointers to allocate memory
    for(auto& road_pointer : roads) {
        delete road_pointer;
    }

    // Clears all roads
    roads.clear();


}

std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    std::vector<std::pair<TownID,TownID>> all_roads = {};

    // Reserving the vector
    all_roads.reserve(database.size());


    // Looping through the roads.
    for(auto& town : roads) {

        // If the town1 is "smaller" than town2, pushes town1 first to the vector
        if(town->town1->id < town->town2->id) {
            all_roads.push_back(std::make_pair(town->town1->id,town->town2->id));

        } else {

            // This means town2 is smaller here
            all_roads.push_back(std::make_pair(town->town2->id,town->town1->id));
        }

    }


    // Returning the vector
    return all_roads;
}

bool Datastructures::add_road(TownID town1, TownID town2)
{

    // Formating the towns for easier use
    const auto id1 = database.find(town1);
    const auto id2 = database.find(town2);

    // Checks if the towns are in the database
    if(id1 == database.end() || id2 == database.end())
        return false;



    // Creates a new road pointer
    Road* new_road = new Road;

    // Inserts the pointer to a database which is keeping track of all roads
    roads.push_back(new_road);

    // Determines the end points of the road
    new_road->town1 = id1->second;
    new_road->town2 = id2->second;

    // Determines the distance between towns
    new_road->distance = distance_from_point(id1->second->coord,id2->second->coord);

    // Adds the information to each town
    id1->second->road.push_back(std::make_pair(new_road->town2,new_road->distance));
    id2->second->road.push_back(std::make_pair(new_road->town1,new_road->distance));
    return true;



}

std::vector<TownID> Datastructures::get_roads_from(TownID id)
{

    // Formatting the town vector
    std::vector<TownID> town_vector;

    // Formating the town
    const auto town = database.find(id);

    // Checking if the town exists
    if(town == database.end()) {
        town_vector.push_back(NO_TOWNID);
        return town_vector;
    }

    // Appending the ids from the towns road vector
    for (auto town : town->second->road) {
        town_vector.push_back(town.first->id);
    }

    // Returns the town vector
    return town_vector;



}

std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{

    // Since any route is wanted, why not use the least towns one
    return least_towns_route(fromid,toid);
}

bool Datastructures::remove_road(TownID town1, TownID town2)
{


    // Formating the towns
    auto id1 = database.find(town1);
    auto id2 = database.find(town2);

    // Checking that the towns exist
    if(id1 == database.end() || id2 == database.end())
        return false;

    // Removing the road from the town struct
    id1->second->road.erase(std::remove_if(id1->second->road.begin(), id1->second->road.end(),
                               [&](const std::pair<Town*,int> i) { return i.first->id == town2;}),id1->second->road.end());

    id2->second->road.erase(std::remove_if(id2->second->road.begin(), id2->second->road.end(),
                               [&](const std::pair<Town*,int> i) { return i.first->id == town1;}),id2->second->road.end());



    // Checking the index for the road
    unsigned int iterator = 0;
    for(auto& it : roads) {
        if((it->town1->id == town1 || it->town1->id == town2) && (it->town2->id == town1 || it->town2->id == town2)) {
            break;
        }
        iterator++;
    }

    // Erasing the road from the vector
    if (iterator != roads.size()) {
        roads.erase(roads.begin() + iterator);
    }



    return true;
}

std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{

    // Formating the BFS queue
    std::list<Town*> queue;

    // Fromating the route_vector
    std::vector<TownID> route_vector;

    // Formating the town pointers for easier use
    const auto from_town = database.find(fromid);
    const auto to_town = database.find((toid));

    // Checking if the towns are found from the database
    if(from_town == database.end() || to_town == database.end()) {
        route_vector.push_back(NO_TOWNID);
        return route_vector;
    }

    // Reseting the nodes which are towns
    for(auto town : database) {
        town.second->current_color = white;
        town.second->road_parent = nullptr;
    }


    // Changing the starting node to grey
    from_town->second->current_color = grey;

    // Pushing the starting node to first
    queue.push_back(from_town->second);

    // Starting BFS loop
    while (!queue.empty()) {

        // Determing the first node
        auto u  = queue.front();
        queue.pop_front();

        for(auto v : u->road) {

            // If the current node color is whit aka. it hasn't been visited yet
            if(v.first->current_color == white) {

                // Changes the current color to grey
                v.first->current_color = grey;

                // Determinates the node predecessor
                v.first->road_parent = u;

                // Adding the current node to the queue
                queue.push_front(v.first);

                // Checks if the node is the wanted destination town.
                if(v.first->id == toid) {
                    break;

                }
                // Sets the u node to black aka. completely gone through
                u->current_color = black;
            }


        }

    }

    // Determing the current town
    auto current_town = to_town->second;

    // Appending the destination id to the route_vector
    route_vector.push_back(toid);


    // Looping until hitting nullptr aka the starting node
    while(current_town->road_parent != nullptr) {
        route_vector.push_back(current_town->road_parent->id);
        current_town = current_town->road_parent;
    }

    // Reserving the route_vector since it is wrong way around
    std::reverse(route_vector.begin(), route_vector.end());

    // Returning the route_vector
    return route_vector;

}

std::vector<TownID> Datastructures::road_cycle_route(TownID /*startid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("road_cycle_route()");
}

std::vector<TownID> Datastructures::shortest_route(TownID /*fromid*/, TownID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("shortest_route()");
}

Distance Datastructures::trim_road_network()
{
    // Replace the line below with your implementation
    throw NotImplemented("trim_road_network()");
}
