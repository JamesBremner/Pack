#include <iostream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include "cPackEngine.h"

using namespace std;

cPackEngine thePackEngine;

bool ParseOriginalOptions( vector< string >& argv,
                           string& bin,
                           string& item,
                           string& shape,
                           string& out_file)
{
    for( int i=1; i < (int)argv.size() ; ++i )
    {
        cout << argv[i] << "\n";

        if( strcmp(argv[i].c_str(), "-b") == 0 )
        {

            bin = argv[i+1];

        }

        if( strcmp(argv[i].c_str(), "-i") == 0 )
        {
            item = argv[i+1];
        }


        if( strcmp(argv[i].c_str(), "-s") == 0 )
        {
            shape = argv[i+1];
        }

        if( strcmp(argv[i].c_str(), "-o") == 0 )
        {
            out_file = argv[i+1];
        }

    }

    if( ! bin.length() )
    {

        cout << "did not get bin in args. pass in using -b" << endl;
        return false;
    }

    if( ! item.length()  )
    {

        cout << "did not get item in args. pass in using -i" << endl;
        return false;
    }


    if( ! shape.length() )
    {

        cout << "did not get bin shape. pass in using -s" << endl;
        return false;

    }
    else if ( shape != "b" && shape != "t" )
    {
        cout << "-s switch can only be used with 'b' or 't'" << endl;
        return false;


    }

    return true;

}


// parse user options

bool ParseNewOptions( int argc, char *argv[],
                      string& bin,
                      string& item,
                      string& shape,
                      string& out_file)
{
//    for( int k = 1; k < argc; k++ )
//        cout << argv[k] << endl;

    namespace po = boost::program_options;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "produce help message")
    ("original",po::value<std::string>(),"Using original command line options\n")
    ("bins", po::value<std::string>(),"bin specification. Comma separate multiple bins. format:\n"
        "{id}:{unit}:{quantity}:{size1}x{size2}x{size3}:{weight}\n"
        "unit can be in, ft, or cm\n"
        "A quantity of -1 indicates an endless supply of bins\n"
        "A weight of 0 indicates ignore weight constraints\n")
    ("items",po::value<std::string>(),"item specification. Comma separate multiple items. format:\n"
        "{id}:{unit}:{constraints}:{quantity}:{size1}x{size2}x{size3}:{weight}\n" )
    ("o", po::value<std::string>(), "output file. the output (json) are written to this file.  prints to stdout if left out")
    ("onebin",po::bool_switch( &thePackEngine.myfOneBin ),"Pack all items into one bin")
    ("random",po::bool_switch( &thePackEngine.myfRandom ),"Disable heuristics, use random pack")
    ;

    // parse the command line
    po::variables_map vm;
    try {

    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    }
    catch ( std::exception& e )
    {
        cout <<"\n" << e.what() << endl;
        cout <<"\n" << desc << "\n";
        Utils::displayHelp();
        exit(1);

    }
    if( vm.count("original"))
    {
        vector< string > av;
        boost::split( av,
                      vm["original"].as<std::string>(),
                      boost::is_any_of(" ") );
        return ParseOriginalOptions(
                   av,
                   bin, item, shape, out_file );
    }

    // extract the parameter values
    if (vm.count("help"))
    {
        cout << desc << "\n";
        Utils::displayHelp();
        exit(1);
    }

    if( vm.count("bins") )
    {
        bin = vm["bins"].as<std::string>();
    }
    else
    {
        cout << "did not get bin in args. pass in using --bins" << endl;
        return false;
    }
    if( vm.count("items") )
    {
        item = vm["items"].as<std::string>();
    }
    else
    {
        cout << "did not get items in args. pass in using --items" << endl;
        return false;
    }
    if( vm.count("o") )
    {
        out_file = vm["o"].as<std::string>();
    }



    return true;
}


int main(int argc, char *argv[])
{


    if ( argc == 1 )
    {
        Utils::displayHelp();
        return 0;
    }

    string bin;
    string item;
    string shape;
    string out_file;

    if( ! ParseNewOptions(
                argc, argv,
                bin, item, shape, out_file ) )
        return 1;

    try
    {

        if( thePackEngine.Build( bin.c_str(), item.c_str() ) != 0 )
        {
            throw std::runtime_error( "ERROR: could not build bins and items" );
        }

        thePackEngine.Pack();

    }
    catch ( std::runtime_error& e )
    {
        cout << e.what() << endl;
        if ( out_file.length() )
        {
            fstream file;
            file.open(out_file, fstream::out);
            file << "{\"error\":\"" << e.what() << "\"}" << endl;
            file.close();
        }
        return 1;
    }

    string json_s = thePackEngine.getJson();
    string cutlist_s = thePackEngine.getCutList();
    string drawlist_s = thePackEngine.DrawList();
    string csv = thePackEngine.getCSV();

//    if 	( json_s.find("error") != string::npos )
//    {
//        if( myError != "No bin capable of holding all items" )
//        {
//            cout << json_s << endl;
//            return 1;
//        }
//    }


    if ( ! out_file.length() )
    {
        cout << json_s << endl;
        //cout << cutlist_s;
        cout << drawlist_s;
        cout << csv;
    }
    else
    {

        fstream file;

        file.open(out_file, fstream::out);
        file << json_s;
        file << endl;
        file << cutlist_s;
        file << drawlist_s;
        file.close();

    }

//    ofstream filecsv("packit4me2.csv");
//    filecsv << csv;
//    filecsv.close();


    thePackEngine.getSTL();

    return 0;
}

const char *PACKIT4ME_packThemTube( const char *bins, const char *items)
{

//	TubeBindingsParser *parser = new TubeBindingsParser();
//
//	vector<Bin*> bins_v;
//	vector<Item*> items_v;
//
//	int dim;
//	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);
//
//	if ( dim == BoxBindingsParser::BIN_PARSE_ERROR )
//	{
//
//		Utils::cleanUpBindingCall( bins_v, items_v, parser );
//		return "error, could not parse bin.  please confirm bin string format id:v1[xv2xv3]";
//	}
//
//	if ( dim == BoxBindingsParser::ITEM_PARSE_ERROR )
//	{
//
//		Utils::cleanUpBindingCall( bins_v, items_v, parser );
//		return "error, could not parse item.  please confirm item string format id:constraints:v1[xv2xv3]";
//	}
//
//	if ( dim == BoxBindingsParser::PACKER_ERROR )
//	{
//
//		Utils::cleanUpBindingCall( bins_v, items_v, parser );
//		return "error, check input strings";
//
//	}
//
//	TubePacker *packer = new TubePacker();
//	packer->packThem(bins_v, items_v);
//	delete packer;
//
//
//	stringstream jsonStr;
//	jsonStr << "[";
//	for( unsigned i=0; i < bins_v.size(); ++i )
//	{
//		bins_v[i]->encodeAsJSON(jsonStr, false);
//		if ( i != bins_v.size() - 1)
//			jsonStr << ",";
//	}
//
//	jsonStr << "]";
//
//
//
//	string json = jsonStr.str();
//
//	char *s_buffer =  new char[json.size()+1];
//	copy(json.begin(), json.end(), s_buffer);
//	s_buffer[json.size()] = '\0';
//
//	Utils::cleanUpBindingCall( bins_v, items_v, parser );
//
//
//	return s_buffer;
    return "error, tube packing not implemented";
}
