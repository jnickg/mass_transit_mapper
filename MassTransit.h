#include <cstring>
#include <ostream>

/* PROGRAM DESCRIPTION
MassTransit.h

This class manages a graph of mass transit stops, and allows
the user to find every possible route between two stops.

END PROGRAM DESCRIPTION */

struct mt_vrtx;

// Edges between MassTransit stops
struct mt_edge 
{
	mt_vrtx*	dest; // The adjacent stop's index
	int			time; // Minutes taken to reach dest
	mt_edge*	next; // Points to next edge
};

// Contains information about the stop itself
struct mt_vrtx
{
	char*		name; // Name of the stop
	mt_edge*	edges; // Head pointer to edge list
	mt_vrtx*	next; // Points to the next vertex
	bool		visited; // Whether this stop has been visited
};

class MassTransit
{
public:
	// Creates a MassTransit system with name n
	MassTransit(const char* const n);
	
	// Default delete
	~MassTransit();
	
	// Adds a new stop with name n
	// Returns new size (1 or greater) if added
	// Note: this size can be used to address the stop
	// by its index, which is equivalent to return - 1
	// Returns 0 if a stop by that name already exists
	int addStop(const char* const n);
	
	// Adds a directional connection from n1 to n2 with specified time, creating
	// stops for n1 and n2 if necessary.
	// Returns -1 if both stops and the connection already exist, now with updated time
	// Returns 0 if both stops exist and the connection was made
	// Returns 1 if n1 was made before making connection
	// Returns 2 if n2 was made before making connection
	// Returns 3 if both n1 and n2 were made before making connection
	int putConnection(const char* const n1, const char* const n2, int time);

	// Checks if stop with name n exists
	// Returns 1 if it exists (later: returns its index)
	// Returns -1 if it does not
	int checkStop(const char* const n);
	
	// Gets all the connections for the stop with name n
	// Returns the number of connections, or 0 if n was not found
	// Sets rtn to a string containing all connection names
	int getConnections(const char* const n, char* & rtn);
	
	// Prints all stops and their connections with times
	std::ostream& print(std::ostream& out);
	
	// Prints all possible routes starting at the stop of name n
	// If a stop of this name does not exist, it will be made. Careful!
	std::ostream& printRoutesDF(std::ostream& out, const char* const n);
private:
	char*		mt_name; // The name of the mass transit system
	mt_vrtx*	head; // holds onto the most recently-made vertex for fingers
	int			size; // Size of the array
	
	// Adds a new stop with name n
	// Returns new size (1 or greater) if added
	// Returns 0 if a stop of that name already exists
	// Regardless, rtn is set to the stop with name n
	int addStop(const char* const n, mt_vrtx *& head, mt_vrtx *& rtn);
	
	// Adds edge from v1 to v2 with stated time
	// If edge already exists, this overrides the time
	int putConnection(mt_vrtx* /*&*/ v1, mt_vrtx* v2, int time);
	
	// Checks if stop with name n exists
	// Returns 1 if it exists
	// Returns 0 if it does not
	int checkStop(const char* const n, mt_vrtx * head);
	
	int getConnections(const char* const n, char* & rtn, mt_vrtx* head);
	
	void reinitialize(mt_vrtx* head);
	
	
	std::ostream& printRoutesDF(std::ostream& out, mt_vrtx* head);
};

