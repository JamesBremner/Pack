#include "stdafx.h"
#ifndef NULL
#define NULL   ((void *) 0)
#endif

using namespace std;

Utils::Utils() {
}

Utils::Utils(const Utils& orig) {
}

Utils::~Utils() {
}


bool Utils::compareAscShape(Shape *a, Shape *b)
{
	return (*a) < (*b);


}

bool Utils::compareDescShape(Shape *a, Shape *b)
{

	return (*a) > (*b);


}

bool Utils::compareDescInt( int a, int b)
{

	return a > b;

}

void Utils::displayHelp()
{

	cout << endl;
	cout << "packit4me v1.0.0, open source bin packing algorithm based on classic bin packing best fit" << endl;
	cout << "Copyright (C) 2012 by Arash Sharif under MIT license" << endl << endl;
	cout << "use: packit4me [options] " << "example: packit4me -m 0:5x5x5 -i 0:0:1x1x1 -s b -o result" << endl << endl;
	cout << "\t-b\t- bin or bins size (format: {id}:{size1}x{size2}x{size3}). comma dil multiple" << endl;
	cout << "\t-i\t- item or items size (format: {id}:{constraints}:{size1}x{size2}x{size3}) comma dil multiple" << endl;
	cout << "\t-s\t- shape. Either 'b' for box or 't' for any tube or round" << endl;
	cout << "\t-o\t- output file. the output (json) are written to this file.  prints to stdo if left out" << endl << endl;
	cout << "find source @ https://github.com/asharif/packit4.me" << endl << endl;

}

void Utils::cleanUpBindingCall( vector<Bin*> &bins_v, vector<Item*> &items_v, BoxBindingsParser *parser )
{

	for( vector<Bin*>::iterator member = bins_v.begin(); member != bins_v.end(); member++ )
		delete *member;

	bins_v.clear();


	for( vector<Item*>::iterator member = items_v.begin(); member != items_v.end(); member++ )
		delete *member;

	items_v.clear();

	delete parser; 
	

}
