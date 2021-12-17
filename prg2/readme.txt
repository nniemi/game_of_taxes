--------------------------Connecting towns-----------------------------------

This program introduces a road system which is connected to the earlier town
database. These roads implify the connections between towns.
The Town* pointers are seen as nodes and the Road* pointers as graphs 
between the nodes. This allows the usage of graph algorithms for example
BFS. This also makes the efficiency of these functions downgrade from the
stage 1 program due to the algorithms.  


This program version contains 8 functions, which one of them -> clear_all
has to be changed a bit due to clearing the whole database with the roads.

In this implementation there are seven new functions:

- clear_roads
	Clears all the roads which have been introduced in the road system.
	For-loop is used to delete pointers to allocate memory. This way
	there won't be memory issues due to roads.

- all_roads
	First reserves a vector with a fixed size, since all current roads
	are wanted. Then loops through the road database and pushes the roads
	to a correct order. This check is done by comparing the TownIDs.
	After all the wanted roads have been checked and pushed to the vector,
	the function will return a vector which contains pairs.

 - add_road
	Creates a new Road* pointer which is stored to the road database.
	Then determinates the connections between towns by inserting
	roads to a vector inside of Town* pointers.

- get_roads_from

	Using pointers makes the function efficient, so the town is formated
	with database.find(). Then the function does a routine check where 
	the town existance will be checked. After this the function loops
	through the roads which start from the selected town. Returns
	a vector with TownIDs.

- any_route

	No reason to create a duplicate function to BFS so this
	function calls for least_towns_route, more info on that section.

- remove_road

	Removes a town from the database and from each connected town.
	Chose erase-remove_if idiom since it is the easiest way to find
	correct roads from the Town* pointer and remove them. Also deletes
	the corresponging road from the road database.

- least_town_route

	This function uses BFS search algorithm, since it can find the route 
	with least towns. Overall the search algorithms aren't too efficient
	because they use loops which have loops inside. This can't be evaded
	so it isn't the fastest algorithm out there. Implemented pretty much
	by the book with the change of inserting the values to a vector. 
	This function relies on Town* pointers and their attributes such as
	current_color which implicates if the node has been visited.

	Since the node storing is done from the bottom-up, the vector has to 
	be reserved before returning. In the end returns a vector which
	contains TownIDs.

-----------------------------------------------------------------------------


