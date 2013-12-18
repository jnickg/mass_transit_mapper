#include "MassTransit.h"

/* PROGRAM DESCRIPTION
MassTransit.cpp

Implementation of the functions defined in MassTransit.h

END PROGRAM DESCRIPTION */

//

MassTransit::MassTransit(const char* const n)
{
	mt_name = new char[strlen(n)+1];
	strcpy(mt_name, n);
	
	head = NULL;
	size = 0;
}

MassTransit::~MassTransit()
{
	//clear(true);
}

int MassTransit::addStop(const char* const n)
{
	mt_vrtx * tmp; // Unused, to properly call recursive call that allows return pointer
	return addStop(n, head, tmp);
}

int MassTransit::addStop(const char* const n, mt_vrtx *& head, mt_vrtx *& rtn)
{
	// Case 1: there is no head; size is 0
	if(NULL == head)
	{
		mt_vrtx* tmp = new mt_vrtx;

		// Initialize new stop data
		tmp->name = new char[strlen(n)+1];
		strcpy(tmp->name, n);
		tmp->edges = NULL;
		tmp->next = NULL;
		tmp->visited = false;
		
		head = tmp;
		rtn = tmp;
		
		return ++size;
	}
	
	// Case 2: this vertex is currently last
	else if(NULL == head->next)
	{
		// Double check that only existing vertex is not this one
		if(strcmp(n, head->name) == 0)
		{
			rtn = head;
			return 0;
		}
		// If not, free to add it.
		else
		{
			mt_vrtx* tmp = new mt_vrtx;

			// Initialize new stop data
			tmp->name = new char[strlen(n)+1];
			strcpy(tmp->name, n);
			tmp->edges = NULL;
			tmp->next = NULL;
			tmp->visited = false;
			
			head->next = tmp; // Append to the end of the array
			rtn = tmp; // Point rtn to the new stop
			return ++size;
		}
	}
	
	// Case 3: There is a list and we're currently not at the last vertex
	else
	{
		if(strcmp(n, head->name) == 0)
		{
			rtn = head; // Point rtn to the match
			return 0; // Disallow duplicate stops
		}
		else return addStop(n, head->next, rtn); // Recursive call
	}
}

int MassTransit::putConnection(const char* const n1, const char* const n2, int time)
{
	mt_vrtx* t1 = NULL; // Winds up pointing to stop with name n1
	mt_vrtx* t2 = NULL; // Winds up pointing to stop with name n2
	int r1, r2, r3; // Used to generate the return flag; r3 is the connection
	
	// Add the new stops if necessary; store return to check if they were made
	r1 = addStop(n1, head, t1);
	r2 = addStop(n2, head, t2);
	
	// Initiate call to add connection
	r3 = putConnection(t1, t2, time);
	
	if((r1==0) && (r2==0)) // Both existed already
	{
		// Connection already existed
		if(0==r3) return -1;
		// Connection newly-made
		else return 0;
	}
	else if((0 < r1) && (0 < r2)) return 3; // Both were made
	else if(0 < r1) return 1; // Just n1 was made
	else if(0 < r2) return 2; // just n2 was made
	else return -999; // Something went horribly wrong
}

int MassTransit::putConnection(mt_vrtx* /*&*/ v1, mt_vrtx* v2, int time)
{
	mt_edge* tmp = v1->edges;
	while(tmp != NULL)
	{
		if(tmp->dest == v2) // This edge points to the stop
		{
			tmp->time = time; // Update time
			return 0;
		}
		else tmp = tmp->next; // Otherwise check next one
	}
	
	// Checked whole list w/o finding edge; make it
	tmp = new mt_edge;
	tmp->dest = v2;
	tmp->time = time;
	tmp->next = v1->edges;
	v1->edges = tmp;
	return 1;
}

int MassTransit::checkStop(const char* const n)
{
	return checkStop(n, head);
}

int MassTransit::checkStop(const char* const n, mt_vrtx * head)
{
	if(NULL == head) return -1;
	else
	{
		if(0==strcmp(n, head->name)) return 1;
		else return checkStop(n, head->next);
	}
}

int MassTransit::getConnections(const char* const n, char* & rtn)
{
	return getConnections(n, rtn, head);
}

int MassTransit::getConnections(const char* const n, char* & rtn, mt_vrtx* head)
{
	// Case 1: At an empty vertex
	if(NULL == head) return 0;
	// If the vertex is not empty, check if n matches its name and, if it does,
	// add its edges to rtn
	else
	{
		// If names match, this is the vertex whose connections must be returned
		if(0 == strcmp(n, head->name))
		{
			int r = 0; // to return the number of edges
			int l = 0; // to find the total length of all edge names
			if(rtn) delete rtn;
			
			// JUST BECAUSE WE CAN'T USE STRINGS, WE SHALL ITERATE THROUGH
			// THE ENTIRE LIST IN ORDER TO GET THE TOTAL SIZE. WHAT A SHAME.
			mt_edge* tmp = head->edges;
			while(tmp) 
			{
				l += strlen(tmp->dest->name + 1); // add 1 to make space for newlines
				tmp = tmp->next;
			}
			
			rtn = new char[l+1]; // Make return string.
			
			// Go through list again and copy each name into rtn
			tmp = head->edges; // reset to head
			while(tmp)
			{
				strcat(rtn, tmp->dest->name);
				strcat(rtn, "\n");
				++r;
				tmp = tmp->next;
			}
			return r;
		}
		// If names don't match, recursive call
		else return getConnections(n, rtn, head->next);
	}
}

void MassTransit::reinitialize(mt_vrtx* head)
{
	// Can't reinitialize a null vertex
	if(NULL == head) return;
	else
	{
		head->visited = false;
		reinitialize(head->next); // Recursive call
	}
}

std::ostream& MassTransit::print(std::ostream& out)
{
	mt_vrtx* tmp = head;
	out << "\n\nPrinting all stops for " << mt_name << ":";
	while(tmp)
	{
		out << "\n" << tmp->name;
		
		// Count the number of stops by iterating through adjacency list
		int stops = 0;
		mt_edge* tmpe = tmp->edges;
		while(tmpe)
		{
			++stops;
			tmpe = tmpe->next;
		}
		
		
		out << " (" << stops << " adjacent stops)";
		
		// Iterate through again to print all stops
		tmpe = tmp->edges;
		while(tmpe)
		{
			out << "\n\t" << tmpe->dest->name << "\t(" << tmpe->time << " min)";
			tmpe = tmpe->next;
		}
		tmp = tmp->next;
	}
	return out;
}

std::ostream& MassTransit::printRoutesDF(std::ostream& out, const char* const n)
{
	reinitialize(head);
	
	mt_vrtx* tmp;
	
	// If this stop already existed
	if(0 == addStop(n, head, tmp))
	{
		out << "\n\nPrinting all routes from: " << tmp->name << "\nNote:\t(eol) indicates End of Line\n\t(v) indicates an already-visited stop\n\n";
		return printRoutesDF(out, tmp);
	}
	// If it didn't there are no routes to print.
	else
	{
		out << "\n\nThere are no routes from new stop: " << tmp->name << "\n";
		return out;
	}
	

}

std::ostream& MassTransit::printRoutesDF(std::ostream& out, mt_vrtx* head)
{
	// Case 1: This vertex has been visited
	if(head->visited)
	{
		out << head->name << "(v)\n";
		return out;
	}
	// Case 2: This head has not been visited but terminates
	else if(NULL == head->edges)
	{
		head->visited = true; // Mark as visited
		out << head->name << "(eol)\n";
		return out;
	}
	// Case 3: This head has edges and has not been visisted
	else
	{	
		head->visited = true; // Mark this stop as visited
		
		mt_edge* tmpe = head->edges;
		while(!(NULL == tmpe))
		{
			out << head->name << "\t---> ";
			printRoutesDF(out, tmpe->dest); // Recursive call
			//if(tmpe->next) out << "\n";
			tmpe = tmpe->next;
		}
		return out;
	}
}

