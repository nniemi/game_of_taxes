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

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    // Gets the amount of towns from the hash. Size() is constant so performance
    // is O(1).
    unsigned int town_count();

    // Estimate of performance: O(N)
    // Short rationale for estimate:
    // Complexity is linear since the algorithm goes through all the elements
    // in the unordered_map.
    void clear_all();

    // Estimate of performance: O(N)
    // Short rationale for estimate: The complexity for find-algorithm in unordered_map
    // is O(N) in the worst case, O(1) in average cases.
    // and the complexity for insert is O(N) in the worst case and O(1) on average.
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance: O(N)
    // Short rationale for estimate: The complexity for find-algorithm in unordered_map
    // is O(N) in the worst case, O(1) in average cases.
    // The best case is where the first element is the searched id. In this case
    // the performance is constant.
    Name get_town_name(TownID id);

    // Estimate of performance: O(N)
    // Short rationale for estimate: The complexity for find-algorithm in unordered_map
    // is O(N) in the worst case, O(1) in average cases.
    // The best case is where the first element is the searched id. In this case
    // the performance is constant.
    Coord get_town_coordinates(TownID id);

    // Estimate of performance: O(N)
    // Short rationale for estimate: TThe complexity for find-algorithm in unordered_map
    // is O(N) in the worst case, O(1) in average cases.
    // The best case is where the first element is the searched id. In this case
    // the performance is constant.
    int get_town_tax(TownID id);

    // Estimate of performance: O(N)
    // Short rationale for estimate: For-loop is looping through the whole
    // database so it is O(N).
    std::vector<TownID> all_towns();

    // Estimate of performance: O(N)
    // Short rationale for estimate: For-loop is looping through the whole
    // database so it is O(N).
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance: O(N)
    // Short rationale for estimate: The complexity for find-algorithm in unordered_map
    // is O(N) in the worst case, O(1) in average cases.??
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance: O(NlogN)
    // Short rationale for estimate: For-loop loops through the database to store
    // Town-poninters to a vector => O(N), std::sort has complexity of NlogN
    // this means that the whole function is O(N). In this function std::sort is
    // faster than inserting to a map which is used in the next function.
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: O(NlogN)
    // Short rationale for estimate: For-loop loops through the database to store
    // Town-pointers to a vector => O(N). In this function map inserting is much
    // more faster. This was decided by running a lot of tests with std::sort and
    // map inserting. Map sorts the elements when inserted.
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: O(N)
    // Short rationale for estimate: Min_element-algorithm has complexity of O(N)
    // except when the vector is empty.
    TownID min_distance();

    // Estimate of performance: O(N)
    // Short rationale for estimate: Max_element-algorithm has complexity of O(N)
    // except when the vector is empty.
    TownID max_distance();

    // Estimate of performance: O(N)
    // Short rationale for estimate: The complexity for find-algorithm in unordered_map
    // is O(N) in the worst case, O(1) in average cases.
    // due to rounding it doesn't matter if there is multiple find-algorithms in
    // row. Push_back has complexity of O(1) so the function is O(N)
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(N)
    // Short rationale for estimate: Find-algorithm has a complexity of O(N)
    // and for-loop also is O(N), so the function is O(N).
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance: O(N)
    // Short rationale for estimate: The complexity for find-algorithm in unordered_map
    // is O(N) in the worst case, O(1) in average cases
    // and while loop loops until it will find a element, whose parent is nullptr
    // so in the worst program has to go through the whole database.
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance: O(N)
    // Short rationale for estimate: This function will first check if the element'
    // is in the database which is O(N), after this the function will either have
    // a for-loop or another for-loop and a clear function. All of these are O(N)
    // so the whole function is O(N). The best case is O(1) where all of the elements
    // are found in the beginning of vectors.
    bool remove_town(TownID id);

    // Estimate of performance: O(NlogN)
    // Short rationale for estimate: This function will first go through the database
    // and insert the distances and IDs to a map and the map will sort the IDs
    // according to distance. After this The function will go through another
    // loop, but it doesn't change the performance.
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance: O(N)
    // Short rationale for estimate: The worst case is O(N) since there is a find
    // function, then the function will go through the whole database which is
    // linear => O(N).
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance: O(N)
    // Short rationale for estimate: In the worst case the function will have to
    // go through the whole database, which is linear. The function also uses find function which
    // is O(N). The best case is constant O(1) where the wanted town is first
    // in the database and their neighbours are nullptr.
    int total_net_tax(TownID id);

private:


    struct Town
    {
        TownID id = NO_TOWNID;
        Name name = NO_NAME;
        Coord coord = NO_COORD;
        int tax = NO_VALUE;

        Town* parent = nullptr;
        std::vector<Town*> neighbour = {};
    };

    int distance_from_point(const Coord& coord, const Coord& point) const;
    std::vector<TownID> recursive_longest_path(Town* current_town, std::vector<TownID> current, std::vector<TownID>& longest);
    int recursive_total_tax(Town* current_town);

    std::unordered_map<TownID, Town*> database;


};

#endif // DATASTRUCTURES_HH
