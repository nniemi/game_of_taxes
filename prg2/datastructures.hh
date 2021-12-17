// Datastructures.hh
//
// Student name:  Niemi



#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <unordered_set>


// Types for IDs
using TownID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    unsigned int town_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_town_name(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_town_coordinates(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int get_town_tax(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> all_towns();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID min_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID max_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_town(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);


    // Phase 2 operations

    // Estimate of performance: O(N)
    // Short rationale for estimate: Complexity is linear since algorithm
    // Goes through all the elements in the unordered_map
    void clear_roads();

    // Estimate of performance: O(N)
    // Short rationale for estimate: Looping through the road database so
    // the complexity is linear.
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance: O(N)
    // Short rationale for estimate: Since the find-algorithm for std::vector is O(N), the whole
    // function is linear despite most of the elements in this function are O(1)
    // for example push_back.
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance: O(N)
    // Short rationale for estimate: The find-algorith for unordered_map is O(1)
    // on average, but O(N) at the worst. For-loop is linear so the complexity
    // for the whole function is O(N).
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance: O(N+K)
    // Short rationale for estimate: Calls for the least towns route which uses
    // BFS-algorithm. BFS graph algorithm is O(N+K) which means
    // N as towns and K as roads. This is O(N²) at worst.
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory phase 2 operations

    // Estimate of performance: O(N²)
    // Short rationale for estimate: The function contains erasing from vector
    // and removing from vector (to find the correct road) so the
    // complexity adds to O(N²). The for loop in the end doesn't affect the
    // complexity due to rounding -> O(N²+N) = O(N²). All of these are in
    // the worst case.
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance: O(N+K)
    // Short rationale for estimate: Just as described on any_route function
    // BFS-algorithm is O(N+K) where N is towns and K is roads, which means
    // the function is O(N²) at worst.
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_road_network();

private:


    enum Color {white,grey,black};


    struct Town
    {
        TownID id = NO_TOWNID;
        Name name = NO_NAME;
        Coord coord = NO_COORD;
        int tax = NO_VALUE;

        Town* parent = nullptr;
        std::vector<Town*> neighbour = {};
        std::vector<std::pair<Town*,int>> road;
        Town* road_parent = nullptr;
        Color current_color = white;
        std::vector<TownID> route;

    };

    int distance_from_point(const Coord& coord, const Coord& point) const;
    std::vector<TownID> recursive_longest_path(Town* current_town, std::vector<TownID> current, std::vector<TownID>& longest);
    int recursive_total_tax(Town* current_town);

    std::unordered_map<TownID, Town*> database;

    struct Road {

        Town* town1;
        Town* town2;
        int distance;


    };

    std::vector<Road*> roads;
    std::vector<std::string> road_string;


};

#endif // DATASTRUCTURES_HH
