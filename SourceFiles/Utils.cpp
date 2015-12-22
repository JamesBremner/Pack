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


bool Utils::compareAscShape(std::shared_ptr<Shape> a, std::shared_ptr<Shape> b)
{
	return (*a) < (*b);


}

bool Utils::compareDescShape(std::shared_ptr<Shape> a, std::shared_ptr<Shape> b)
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
	cout << "Copyright (C) 2012 by Arash Sharif under MIT license" << endl;
	cout << "Copyright (C) 2015 by James Bremner under MIT license" << endl << endl;
	cout << "use: packit4me [options] " << "example: packit4me -b 0:ft:1:5x5x5 -i 0:ft:0:1:1x1x1 -s b -o result" << endl << endl;
	cout << "\t-b\t- bin or bins size (format: {id}::{dim_unit}:{quantity}:{size1}x{size2}x{size3}). comma dil multiple" << endl;
	cout << "\t\t A quantity of -1 indicates an endless supply of bins" << endl << endl;
	cout << "\t-i\t- item or items size (format: {id}:{dim_unit}:{constraints}:{quantity}:{size1}x{size2}x{size3}) comma dil multiple" << endl << endl;
	cout << "\t-s\t- shape. Either 'b' for box or 't' for any tube or round" << endl << endl;
	cout << "\t-o\t- output file. the output (json) are written to this file.  prints to stdo if left out" << endl << endl;
	cout << "find source @ https://github.com/JamesBremner/packit4me2" << endl << endl;

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
