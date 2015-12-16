
#include "stdafx.h"

cWorld theWorld;

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

    if( theWorld.Build( bin, item ) != 0 )
    {
        cout << "ERROR: could not build bins and items" << endl;
        return 1;
    }

    theWorld.Pack();

    string json_s = theWorld.getJson();
    string cutlist_s = theWorld.getCutList();

    if 	( json_s.find("error") != string::npos )
    {
        cout << json_s << endl;
        return 1;
    }


    if ( out_file == NULL )
    {
        cout << json_s << endl;
        cout << cutlist_s;
    }
    else
    {

        fstream file;

        file.open(out_file, fstream::out);
        file << json_s;
        file << endl;
        file << cutlist_s;
        file.close();

    }

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
