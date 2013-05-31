
#include "stdafx.h"

#ifndef WIN32
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <exception>
#include <algorithm>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/unordered_set.hpp>
#include "Side.h"
#include "Shape.h"
#include "Shape2D.h"
#include "Shape3D.h"
#include "Item.h"
#include "Item2D.h"
#include "Item3D.h"
#include "Bin.h"
#include "Bin1D.h"
#include "Bin2D.h"
#include "Bin3D.h"
#include "Packer.h"
#include "BoxPacker2D.h"
#include "BoxPacker3D.h"
#include "TubePacker.h"
#include "Bindings.h"
#include "BoxBindingsParser.h"
#include "TubeBindingsParser.h"
#include "Utils.h"
#include "Side.cpp"
#include "Shape.cpp"
#include "Shape2D.cpp"
#include "Shape3D.cpp"
#include "Bin.cpp"
#include "Bin1D.cpp"
#include "Bin2D.cpp"
#include "Bin3D.cpp"
#include "Packer.cpp"
#include "Item.cpp"
#include "Item2D.cpp"
#include "Item3D.cpp"
#include "Utils.cpp"
#include "BoxPacker2D.cpp"
#include "BoxPacker3D.cpp"
#include "TubePacker.cpp"
#include "BoxBindingsParser.cpp"
#include "TubeBindingsParser.cpp"
using namespace std;
#endif

int main(int argc, char *argv[]) 
{ 


	if ( argc == 1 )
	{
		Utils::displayHelp();
		return 0;
	}

	char *bin = NULL;
	char *item = NULL;
	char *shape = NULL;
	char *out_file = NULL;

	for( int i=1; i < argc ; ++i )
	{

		if( strcmp(argv[i], "-help") == 0 )
		{
			Utils::displayHelp();
			return 0;
		}

		if( strcmp(argv[i], "-b") == 0 )
		{
			if ( ( i+1 ) <= ( argc -1 ) )
				bin = argv[i+1];
			else
			{
				cout << "no bin found with -b" << endl;
				return 1;
			}

		}

		if( strcmp(argv[i], "-i") == 0 )
		{
			if ( ( i+1 ) <= ( argc -1 ) )
				item = argv[i+1];
			else
			{
				cout << "no item found with -i" << endl;
				return 1;
			}
		}


		if( strcmp(argv[i], "-s") == 0 )
		{
			if ( ( i+1 ) <= ( argc -1 ) )
				shape = argv[i+1];
			else
			{
				cout << "no shape found with -s" << endl;
				return 1;
			}
		}

		if( strcmp(argv[i], "-o") == 0 )
		{
			if ( ( i+1 ) <= ( argc -1 ) )
				out_file = argv[i+1];
			else
			{
				cout << "no output file found with -o" << endl;
				return 1;
			}
		}

	}

	if( bin == NULL )
	{

		cout << "did not get bin in args. pass in using -b" << endl;
		return 1;
	}

	if( item == NULL )
	{

		cout << "did not get item in args. pass in using -i" << endl;
		return 1;
	}


	if( shape == NULL )
	{

		cout << "did not get bin shape. pass in using -s" << endl;
		return 1;

	}
	else if ( (strcmp(shape, "b") != 0) && (strcmp(shape, "t") != 0) )
	{
		cout << "-s switch can only be used with 'b' or 't'" << endl;
		return 1;


	}


	const char *json = NULL;
	if( strcmp(shape, "t") == 0 )
		json = PACKIT4ME_packThemTube( bin, item);
	else
		json = PACKIT4ME_packThem( bin, item );

	string json_s(json);
	if 	( json_s.find("error") != string::npos )
	{
		cout << json << endl;
		return 1;
	}


	if ( out_file == NULL )
	{
		cout << json << endl;
	} 
	else
	{

		fstream file;

		file.open(out_file, fstream::out);
		file << json;
		file.close();

	}

	delete[] json;

	return 0;
}

/**

  Pack items in bins

  @param[in] bins  The bin specifications
  @param[in] items The item specifications

*/
const char *PACKIT4ME_packThem( const char *bins, const char *items )
{

	BoxBindingsParser *parser = new BoxBindingsParser();

	vector<Bin*> bins_v;
	vector<Item*> items_v;


	int dim;
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	if ( dim == BoxBindingsParser::BIN_PARSE_ERROR )
	{
		Utils::cleanUpBindingCall( bins_v, items_v, parser );
		return "error, could not parse bin.  please confirm bin string format id::v1[xv2xv3]";
	}

	if ( dim == BoxBindingsParser::ITEM_PARSE_ERROR )
	{
		Utils::cleanUpBindingCall( bins_v, items_v, parser );
		return "error, could not parse item.  please confirm item string format id:constraints:v1[xv2xv3]";
	}

	if ( dim == BoxBindingsParser::PACKER_ERROR )
	{
		Utils::cleanUpBindingCall( bins_v, items_v, parser );
		return "error, check input strings";
	}


	if( dim == BoxBindingsParser::PACKER_2D )
	{
		BoxPacker2D *packer = new BoxPacker2D();
		packer->packThem(bins_v, items_v);
		delete packer;
	}

	if( dim == BoxBindingsParser::PACKER_3D )
	{
		BoxPacker3D *packer = new BoxPacker3D();
		packer->BoxPacker2D::packThem(bins_v, items_v);
		delete packer;
	}

	stringstream jsonStr;
	jsonStr << "[";
	for( unsigned i=0; i < bins_v.size(); ++i )
	{
		bins_v[i]->encodeAsJSON(jsonStr, false);
		if ( i != bins_v.size() - 1)
			jsonStr << ",";
	}

	jsonStr << "]";



	string json = jsonStr.str();

	char *s_buffer =  new char[json.size()+1];
	copy(json.begin(), json.end(), s_buffer);
	s_buffer[json.size()] = '\0';        


	Utils::cleanUpBindingCall( bins_v, items_v, parser );

	return s_buffer;

}


const char *PACKIT4ME_packThemTube( const char *bins, const char *items)
{

	TubeBindingsParser *parser = new TubeBindingsParser();

	vector<Bin*> bins_v;
	vector<Item*> items_v;

	int dim;
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	if ( dim == BoxBindingsParser::BIN_PARSE_ERROR )
	{

		Utils::cleanUpBindingCall( bins_v, items_v, parser );
		return "error, could not parse bin.  please confirm bin string format id:v1[xv2xv3]";
	}

	if ( dim == BoxBindingsParser::ITEM_PARSE_ERROR )
	{

		Utils::cleanUpBindingCall( bins_v, items_v, parser );
		return "error, could not parse item.  please confirm item string format id:constraints:v1[xv2xv3]";
	}

	if ( dim == BoxBindingsParser::PACKER_ERROR )
	{

		Utils::cleanUpBindingCall( bins_v, items_v, parser );
		return "error, check input strings";

	}

	TubePacker *packer = new TubePacker();
	packer->packThem(bins_v, items_v);
	delete packer;


	stringstream jsonStr;
	jsonStr << "[";
	for( unsigned i=0; i < bins_v.size(); ++i )
	{
		bins_v[i]->encodeAsJSON(jsonStr, false);
		if ( i != bins_v.size() - 1)
			jsonStr << ",";
	}

	jsonStr << "]";



	string json = jsonStr.str();

	char *s_buffer =  new char[json.size()+1];
	copy(json.begin(), json.end(), s_buffer);
	s_buffer[json.size()] = '\0';        

	Utils::cleanUpBindingCall( bins_v, items_v, parser );


	return s_buffer;

}
