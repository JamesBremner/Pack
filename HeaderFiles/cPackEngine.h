#pragma once
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
class Bin;
class Item;
using bin_t = std::shared_ptr< Bin >;
using bin_v_t = std::vector< bin_t >;
using item_t = std::shared_ptr< Item >;
using item_v_t = std::vector< item_t >;
#include "cCut.h"
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
#include "BoxPacker2D.h"
#include "BoxPacker3D.h"
#include "TubePacker.h"
#include "Bindings.h"
#include "BoxBindingsParser.h"
#include "TubeBindingsParser.h"
#include "Utils.h"



/**  A world of items and bins into which they can be packed
*/
class cPackEngine
{

public:

    /// the bins into which items can be packed
    bin_v_t Bins;

    /// the original bins into which items can be packed, used to reset if pack fails
    bin_v_t BinsOriginal;

    /// the items which can be packed into bins
    item_v_t Items;

    /// the items that could not find a place in a bin
    item_v_t myUnpackedItems;

    /// The dimensionality of the world
    int Dimension;

    /// Construct a new empty world
    cPackEngine()
        : Dimension( 0 )
        , myfRandom( false )
    {
    }
    /**  Build world from input strings

    @param[in] bin_input_description
    @param[in] item_input_description

    @return 0 if no problems building the world
    */
    int Build(
        const char* bin_input_description,
        const char* item_input_description );

    /// Pack items into bins
    void Pack();

    /// JSON format world description and packing results
    string getJson();

    string getCutList();

    /// windex format instructions to display 2D packing arrangement
    string DrawList();

    /// CSV item ids that could not be fittted
    string Unpacked();

    string getCSV();

    /** STL format packing results

    This is a 3D graphics format read by many 3D viewers

    http://www.fabbers.com/tech/STL_Format

    There is a specialized STL-Viewer ( https://github.com/JamesBremner/STL-Viewer )
    which animates the packing when the mousewheel is rotated
    in addition to the usual pan, zoom, etc viewing optiions.

    */
    void getSTL();

    /// Convert feet, cm or m into inches
    static float DimensionUnitScale( const string& unit_string );

    void Clear();

    /// True if user wants all items packed into one bin
    bool myfOneBin;

    /// True if user wants to disable heuristics and do a random pack
    bool myfRandom;

    void PrintAllBins();

    int CountBinsUsed();

    bin_v_t& bins()
    {
        return Bins;
    }

private:
    std::string myError;

    int BuildBins(  vector<string>& bin_v );
    int BuildItems(  vector<string>& item_v );
    bool isDimError( int dim );
    void RemoveBinsTooSmallForAllItems();
    void RemoveSmallestBin();
    void RemoveBinsTooLightForAllItems();
    void RemoveAllButLargestBin();
    bin_t SmallestBinForAllItems();
};

extern cPackEngine thePackEngine;

namespace pack
{
void RemoveUnusedBins( cPackEngine& packer );

}
