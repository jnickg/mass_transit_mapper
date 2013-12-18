#include <iostream>
#include <cstring>

#include "MassTransit.h"
#include "jnickgio.h"

using namespace std;

int main(void)
{
	char m; // menu input, used in main loop
	char* cinpt_1 = NULL; // line inputs, used to interact with Mass Transit
	char* cinpt_2 = NULL; // used to add connections in Mass Transit (second stop)
	int iinpt; // int input, used to add connections in Mass Transit
	char* con = NULL; // used to get info for connections, below
	
	cout << "\nNick Giampietro | giampiet@pdx.edu\n5 Dec 2013\nCS 163 | Data Structures\nProgram 5" << endl;	
	
	cout << "\n\nWelcome to the Mass Transit Manager." << endl;
	
	jnickg::io::getStr(cinpt_1, 256, "Please enter the name of your mass transit system.");
	MassTransit mt(cinpt_1);
	
	do // while (m != "Q")
	{
		cout << "\n\nAvailable commands are:"
			<< "\n(A)dd a stop"
			<< "\n(C)onnect two stops"
			<< "\n(G)et connections for a stop"
			<< "\n(P)rint the whole system"
			<< "\n(S)how all routes from a stop"
			<< "\n(Q)uit"
			<< endl;
		jnickg::io::getChar(m, "Please enter a command");
		
		if(m == 'A') // Add new stop
		{
			jnickg::io::getStr(cinpt_1, 256, "Enter the name of the new stop");
			cout << mt.addStop(cinpt_1) << " stops entered into the system" << endl;
		}
		
		else if(m == 'C') // Connect two stops
		{
			jnickg::io::getStr(cinpt_1, 256, "Enter the name of the first stop");
			jnickg::io::getStr(cinpt_2, 256, "Enter the name of the second stop");
			jnickg::io::getInt(iinpt, "How many minutes does it take to get from the\nfirst to second stop?");
			int rtn = mt.putConnection(cinpt_1, cinpt_2, iinpt);
			switch(rtn)
			{
				case -1: cout << "Both connections existed; updated time to " << iinpt << " minutes." << endl;
					break;
				case 0: cout << "Made new " << iinpt << "-minute connection between " << cinpt_1 << " and " << cinpt_2 << "." << endl;
					break;
				case 1: cout << "Added stop " << cinpt_1 << " with " << iinpt << "-minute connection to " << cinpt_2 << "." << endl;
					break;
				case 2: cout << "Added stop " << cinpt_2 << " with " << iinpt << "-minute connection from " << cinpt_1 << "." << endl;
					break;
				case 3: cout << "Added stop " << cinpt_1 << " with " << iinpt << "-minute connection to also-new stop " << cinpt_2 << "." << endl;
					break;
				}
		}
		
		else if(m == 'G') // Get connections for a stop
		{
			jnickg::io::getStr(cinpt_1, 256, "For which stop would you like to get connections?");
			cout << "Getting connections for " << cinpt_1 << ": ";
			cout << mt.getConnections(cinpt_1, con) << " stops" << endl;
			cout << "Connections are:\n";
			cout << con << endl;
		}
		
		else if(m == 'P') // Print whole mass-transit system
		{
			mt.print(cout);
		}
		
		else if(m == 'S') // Show routes from a stop
		{
			jnickg::io::getStr(cinpt_1, 256, "For which stop would you like to get routes?");
			mt.printRoutesDF(cout, cinpt_1);
		}
		
		else if(m == 'Q') cout << "\n\nOkay then, goodbye.\n" << endl;
		
		else cout << "\n\nUnrecognized command.\n" << endl;
		
	} while(m != 'Q');
	
	// Below is my inadequate unit test that definitely doesn't
	// demonstrate the efficacy of my data structure
	// 
	// cout << trimet.addStop("Salmon") << endl;
	// cout << trimet.putConnection("Salmon", "10th", 5) << endl;
	// cout << trimet.putConnection("Salmon", "9th", 8) << endl;
	// cout << trimet.putConnection("Salmon", "11th", 7) << endl;
	// cout << trimet.putConnection("Salmon", "12th", 6) << endl;
	// cout << trimet.putConnection("12th", "9th", 1) << endl;
	// cout << trimet.putConnection("12th", "13th", 4) << endl;
	// cout << trimet.putConnection("13th", "Main", 6) << endl;
	// cout << trimet.putConnection("9th", "10th", 2) << endl;
	// cout << trimet.putConnection("10th", "11th", 2) << endl;
	// cout << trimet.putConnection("10th", "21st", 2) << endl;
	// cout << trimet.putConnection("21st", "24th", 7) << endl;
	// cout << trimet.putConnection("24th", "9th", 9) << endl;
	// cout << trimet.putConnection("24th", "37th", 11) << endl;
	// cout << trimet.putConnection("11th", "14th", 1) << endl;
	// cout << trimet.putConnection("14th", "17th", 2) << endl;
	// cout << trimet.putConnection("17th", "Salmon", 6) << endl;
	// cout << trimet.putConnection("Main", "17th", 9) << endl;
	// cout << trimet.putConnection("Main", "12th", 12) << endl;
	// cout << trimet.putConnection("Main", "9th", 8) << endl;
	// cout << trimet.putConnection("Main", "37th", 17) << endl;
	
	// cout << "Getting connections for Salmon: ";
	// cout << trimet.getConnections("Salmon", con) << endl;
	// cout << "Connections are:\n";
	// cout << con << endl;
	
	// cout << "Getting connections for 12th: ";
	// cout << trimet.getConnections("12th", con) << endl;
	// cout << "Connections are:\n";
	// cout << con << endl;
	
	// cout << "Getting connections for Main: ";
	// cout << trimet.getConnections("Main", con) << endl;
	// cout << "Connections are:\n";
	// cout << con << endl;
	
	// trimet.print(cout);
	
	// trimet.printRoutesDF(cout, "777th");
	// cout << endl;
	// trimet.printRoutesDF(cout, "Salmon");
	// cout << endl;
	// trimet.printRoutesDF(cout, "Salmon");
	// cout << endl;
	// trimet.printRoutesDF(cout, "10th");
	// cout << endl;
	
	cout << "\n\nTERMINATING PROGRAM\n" << endl;
	
	delete cinpt_1;
	delete cinpt_2;
	delete con;
	
	return 0;
}
