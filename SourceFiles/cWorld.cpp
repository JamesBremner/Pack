#include "stdafx.h"
#include <boost/algorithm/string.hpp>


struct item_build_instructions
{
    string id;
    vector<string> size_v;
    string dimension_units;
    int constraints;
    float weight;
};

int   cWorld::Build(
    const char* bin_input_description,
    const char* item_input_description )
{
    Clear();
    vector<string> bin_v;
    boost::split(bin_v, bin_input_description, boost::is_any_of(","));
    vector<string> item_v;
    boost::split(item_v, item_input_description, boost::is_any_of(","));

    int error = BuildBins( bin_v );
    if ( error )
    {
        return error;
    }

    return BuildItems( item_v );
}

void cWorld::Clear()
{
    Bins.clear();
    Items.clear();
    myUnpackedItems.clear();
    Dimension = 0;
}

void cWorld::Pack()
{
    if( Dimension == 2 )
    {
        BoxPacker2D packer;
        packer.packThem( Bins, Items );
    }

    else if( Dimension == 3 )
    {
        /*
        Save the bins
        in case we need to try again with the original list
        */
        BinsOriginal = Bins;

        bool fOneBin_saved = myfOneBin;
        bool packOK = false;

        if( ! myfOneBin )
        {
            // the one bin option was not selected
            // but lets try packing just one bin anyway
            myfOneBin = true;
        }
        /*
            if one bin is requested
            there is no need to look at bins that are too small to hold every item
        */
        RemoveBinsTooSmallForAllItems();

        /*
          need not look at bins that are not strong enough
          to hold the weight of all the items
        */
        RemoveBinsTooLightForAllItems();

        /*
          check that requested one bin pack is feasible
        */
        if( ( ! Bins.size() ) && fOneBin_saved )
        {
            myError = "No bin capable of holding all items";

            // Do the best we can
            // by packing as much as possible into the largest bin
            Bins = BinsOriginal;
            RemoveAllButLargestBin();
        }

        if( Bins.size() )
        {


            // sort bins into increasing size
            sort( Bins.begin(), Bins.end(),
                  []( bin_t a, bin_t b )
            {
                return a->volume() < b->volume();
            });

            bin_v_t Bins_saved( Bins );

            if( myfOneBin )
            {
                // try smallest
                bin_t smallest_bin = Bins[0];
                Bins.clear();
                Bins.push_back( smallest_bin );
            }
            else
            {
                bin_t smallest_bin = SmallestBinForAllItems();
                Bins.clear();
                Bins.push_back( smallest_bin );
            }

            /*
                Pack
            */
            BoxPacker3D packer;
            packer.packThem( Bins, Items );

            while ( myUnpackedItems.size() )
            {
                // there were some unpacked items

                if( Bins_saved.size() <= 1 )
                    break;

                /*
                    try again with saved bins
                    without the smallest
                */
                myUnpackedItems.clear();
                Bins = Bins_saved;

                // reset items to unpacked status
                for( auto i : Items )
                    i->setBin( -1 );

                RemoveSmallestBin();
                Bins_saved = Bins;
                bin_t smallest_bin = Bins[0];
                Bins.clear();
                Bins.push_back( smallest_bin );

                packer.packThem( Bins, Items );

            }
            Bins[0]->Ground();
            Bins[0]->Support();

            if( ! myUnpackedItems.size() )
                packOK = true;
        }

        if( ( ! packOK ) && ( ! fOneBin_saved ) )
        {

            // one bin packing failed
            // but it was not explicitly requested
            // so try packing into multiple bins
            //cout << "Trying multiple bins\n";
            myfOneBin = false;
            Bins = BinsOriginal;
            myUnpackedItems.clear();
            // reset items to unpacked status
            for( auto i : Items )
                i->setBin( -1 );

            BoxPacker3D packer;
            packer.packThem( Bins, Items );

            // Slide unsupported bins downwards
            for( auto b : Bins )
                b->Ground();
        }
    }

    // delete unused  bins

    Bins.erase(
        remove_if(
            Bins.begin(),
            Bins.end(),
            [ ] ( bin_t b )
    {
        return b->itemsInBinCount() == 0 ;
    } ),
    Bins.end() );
}

string cWorld::getJson()
{
    stringstream jsonStr;
    if( myError.length() )
    {
        jsonStr << "{\"error\":\"" << myError << "\",\n";
    }
    else
    {
        jsonStr << "{";
    }
    jsonStr << "\"packed\":[";
    for( unsigned i=0; i < Bins.size(); ++i )
    {
        Bins[i]->encodeAsJSON(jsonStr, false);
        if ( i != Bins.size() - 1)
            jsonStr << ",";
    }

    jsonStr << "],\n";

    jsonStr << "\"unpacked\":[\n";
    bool first = true;
    for( auto unpacked_item : myUnpackedItems )
    {
        if( ! first )
            jsonStr << ",";
        first = false;
        unpacked_item->encodeAsJSON( jsonStr );
    }
    jsonStr << "]}";


    string json = jsonStr.str();

    char *s_buffer =  new char[json.size()+1];
    copy(json.begin(), json.end(), s_buffer);
    s_buffer[json.size()] = '\0';

//    for( auto i : Items )
//    {
//        i->Print();
//    }

    return string( s_buffer );
}

string cWorld::getCutList()
{
    cCutList L;
    for( auto b : Bins )
    {
        b->AddToCutList( L );
    }

    return L.get();
}

string cWorld::DrawList()
{
    stringstream ss;
    for( auto b : Bins )
    {
        b->DrawList( ss );
    }
    return ss.str();
}


string cWorld::getCSV()
{
    stringstream ss;

    for( auto& b : Bins )
    {
        ss << b->getCSV();
    }
    return ss.str();
}

void cWorld::getSTL()
{
    if( myfRandom )
        return;

    string s;
    int offset = 0;
    for( auto& b : Bins )
    {
        s += b->getSTL( offset );
        offset += b->side_1()->size() * 1.5;
    }

    ofstream filestl("packit4me2.stl");
    filestl << s;
    filestl.close();
}

int cWorld::BuildBins( vector<string>& bin_v )
{

    for(unsigned i= 0; i < bin_v.size(); i++)
    {
        string bin_str = bin_v[i];
        vector<string> id_bin;
        boost::split(id_bin, bin_str, boost::is_any_of(":"));

        const int expected_field_count = 5;

        if( id_bin.size() != expected_field_count )
        {
            throw std::runtime_error("Unexpected bin field count");
        }
        Bin::bin_build_instructions instructions;
        instructions.bin_id = id_bin[0];
        instructions.dimension_units = id_bin[1];
        int quantity = (int) atof( id_bin[2].c_str() );
        if( quantity == -1 )
            instructions.can_copy = true;
        else
            instructions.can_copy = false;
        string bin_size = id_bin[3];
        instructions.maxWeight = atof( id_bin[4].c_str() );

        id_bin.clear();


        vector<string> bin_size_v;
        boost::split(bin_size_v, bin_size, boost::is_any_of("x"));

        if ( isDimError( (int)bin_size_v.size() ) == true )
        {
            return 2;
        }



        instructions.size_v = bin_size_v;

        // Build the bin and store it
        if( quantity <= 0 )
            quantity = 1;

        for( int k = 0; k < quantity; k++ )
        {
            Bins.push_back( bin_t( Bin::Build ( instructions ) ) );
        }

    }
    return 0;
}
int cWorld::BuildItems( vector<string>& item_v )
{
    //cout << "Building " << item_v.size() << " items" << "\n";

    for(unsigned i= 0; i < item_v.size(); i++)
    {
        item_build_instructions instructions;
        string item_str = item_v[i];
        vector<string> id_item;
        boost::split(id_item, item_str, boost::is_any_of(":"));

        const int expected_field_count = 6;

        if( id_item.size() < expected_field_count || id_item.size() > expected_field_count )
        {
            throw std::runtime_error("Unexpected item field count "+item_str);
        }

        //string item_id = id_item[0];
        instructions.id = id_item[0];
        instructions.dimension_units = id_item[1];
        instructions.constraints = (int) atof( id_item[2].c_str() );
        int quantity = (int) atof( id_item[3].c_str() );
        string item_size = id_item[4];
        instructions.weight = atof( id_item[5].c_str() );

        id_item.clear();

        vector<string> item_size_v;
        boost::split(item_size_v, item_size, boost::is_any_of("x"));

        if ( isDimError( (int)item_size_v.size() ) == true )
        {
            return 2;
        }

        instructions.size_v =  item_size_v;


        for( int k = 0; k < quantity; k++ )
        {
            Items.push_back( item_t( Item::Build( instructions  ) ) );
        }
    }
    return 0;
}
bool cWorld::isDimError( int dim )
{
    if ( dim < 2 || dim > 3 )
        return true;

    if( Dimension == 0)
    {
        Dimension = dim;
        return false;
    }
    else
    {
        if ( Dimension != dim )
            return true;
        else
            return false;
    }
}

/**
cWorld
  Scale according to input dimension units into inches

	param[in] unit_string  The dimensional unit string input e.g. ft, in

	@return Scale required, 1.0 if not recognized

*/
float cWorld::DimensionUnitScale( const string& unit_string )
{
    if ( unit_string == "ft" )
    {
        return 12.0f;
    }
    else if ( unit_string == "mm" )
    {
        return  0.0393701f;
    }
    else if ( unit_string == "cm" )
    {
        return 0.393701f;
    }
    else if ( unit_string == "m" )
    {
        return 39.3701f;
    }
    return 1.0f;
}

void cWorld::RemoveBinsTooSmallForAllItems()
{
    // check that this is wanted
    if( ! myfOneBin )
        return;

    // calculate total volume of all items
    double totalVolumeAllItems = 0;
    for( auto& i : Items )
    {
        totalVolumeAllItems += i->volume();
    }

    // remove bins that are too small
    Bins.erase(
        remove_if(
            Bins.begin(),
            Bins.end(),
            [ totalVolumeAllItems ] ( bin_t b )
    {
        return b->volume() < totalVolumeAllItems;
    } ),
    Bins.end() );

}

bin_t cWorld::SmallestBinForAllItems()
{
    // calculate total volume of all items
    double totalVolumeAllItems = 0;
    double totalWeightAllItems = 0;
    for( auto& i : Items )
    {
        totalVolumeAllItems += i->volume();
        totalWeightAllItems += i->Weight();
    }
    for( auto b : Bins )
    {
        if( b->volume() >= totalVolumeAllItems &&
                b->MaxWeight() >= totalWeightAllItems )
            return b;
    }
    return Bins.back();
}

void cWorld::RemoveBinsTooLightForAllItems()
{
    // check that this is wanted
    if( ! myfOneBin )
        return;

    // calculate total weight of all items
    double totalWeightAllItems = 0;
    for( auto& i : Items )
    {
        totalWeightAllItems += i->Weight();
    }


    // remove bins that cannot carry the total weight
    Bins.erase(
        remove_if(
            Bins.begin(),
            Bins.end(),
            [ totalWeightAllItems ] ( bin_t b )
    {
        return b->MaxWeight() < totalWeightAllItems;
    } ),
    Bins.end() );

}

void cWorld::RemoveSmallestBin()
{
    if( Bins.size() <= 1 )
    {
        throw std::runtime_error("No bins big enough to contain all items");
    }

    sort(Bins.begin(), Bins.end(), Utils::compareAscShape);

    Bins.erase( Bins.begin() );
}

void cWorld::RemoveAllButLargestBin()
{
    if( Bins.size() <= 1 )
        return;
    sort( Bins.begin(), Bins.end(), Utils::compareAscShape);
    auto iter_last_but_one = Bins.end();
    iter_last_but_one--;
    iter_last_but_one--;
    Bins.erase( Bins.begin(), iter_last_but_one );
}

int cWorld::CountBinsUsed()
{
    int count = 0;
    for( auto b : Bins )
    {
        if( b->itemsInBinCount() )
            count++;
    }
    return count;
}

void cWorld::PrintAllBins()
{
    if( ! Bins.size() )
    {
        cout << "the world has zero bins!\n";
        return;
    }
    cout << "All " << Bins.size() << " Bins\n";
    for( auto b : Bins )
    {
        cout << "Bin " << b->id() <<" contains " << b->itemsInBinCount() << "\n";
    }
    cout << "===All Bins\n";
}


Bin* Bin::Build(  bin_build_instructions& instructions )
{
    Bin *bin;
    switch( instructions.size_v.size() )
    {
    case 1:
        bin = new Bin1D();
        bin->set_id( instructions.bin_id );
        bin->set_side_1( new Side(atof(instructions.size_v[0].c_str()), 'w') );
        bin->set_side_2( new Side(atof(instructions.size_v[1].c_str()), 'h') );

        break;

    case 2:
        bin = new Bin2D();
        bin->set_id( instructions.bin_id );
        bin->set_side_1( new Side(atof(instructions.size_v[0].c_str()), 'w') );
        bin->set_side_2( new Side(atof(instructions.size_v[1].c_str()), 'h') );

        break;

    case 3:
        bin = new Bin3D();
        bin->set_id( instructions.bin_id );
        bin->set_side_1( new Side(atof(instructions.size_v[0].c_str()), 'w') );
        bin->set_side_2( new Side(atof(instructions.size_v[1].c_str()), 'h') );
        bin->set_side_3( new Side(atof(instructions.size_v[2].c_str()), 'l') );

        break;

    default:
        break;


    }

    // Convert from input dimensional units
    // to internal units, assumed to be inches ( the default )

    bin->ScaleSize( cWorld::DimensionUnitScale( instructions.dimension_units ) );

    bin->setCanCopy( instructions.can_copy );

    bin->MaxWeight( instructions.maxWeight );

    return bin;

}

Item* Item::Build(  item_build_instructions& instructions )
{
    Item* item;

    switch( instructions.size_v.size() )
    {
    case 1:
        item = new Item2D();

        item->set_id( instructions.id );
        item->set_side_1( new Side( atof(instructions.size_v[0].c_str()), 'w' ) );
        item->set_side_2( new Side( atof(instructions.size_v[1].c_str()), 'h' ) );
        break;

    case 2:
        item = new Item2D();
        item->set_id( instructions.id );
        item->set_side_1( new Side( atof(instructions.size_v[0].c_str()), 'w' ) );
        item->set_side_2( new Side( atof(instructions.size_v[1].c_str()), 'h' ) );
        break;

    case 3:
        item = new Item3D();
        item->set_id( instructions.id );
        item->set_side_1( new Side( atof(instructions.size_v[0].c_str()), 'w' ));
        item->set_side_2( new Side( atof(instructions.size_v[1].c_str()), 'h'  ) );
        item->set_side_3( new Side( atof(instructions.size_v[2].c_str()), 'l'  ) );
        break;

    default:
        break;


    }

    item->set_constraints( instructions.constraints );

    item->ScaleSize( cWorld::DimensionUnitScale( instructions.dimension_units ) );

    item->Weight( instructions.weight );

    return item;
}
