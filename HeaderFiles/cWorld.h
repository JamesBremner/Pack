#include <memory>

/**  A world of items and bins into which they can be packed
*/
class cWorld
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
    cWorld()
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

    string getCSV();

    /** STL format packing results

    This is a 3D graphics format read by many 3D viewers

    http://www.fabbers.com/tech/STL_Format

    */
    string getSTL();

    /// Convert feet, cm or m into inches
    static float DimensionUnitScale( const string& unit_string );

    void Clear();

    /// True if user wants all items packed into one bin
    bool myfOneBin;

    /// True if user wants to disable heuristics and do a random pack
    bool myfRandom;

private:
    int BuildBins(  vector<string>& bin_v );
    int BuildItems(  vector<string>& item_v );
    bool isDimError( int dim );
    void RemoveBinsTooSmallForAllItems();
    void RemoveSmallestBin();
    void RemoveBinsTooLightForAllItems();
    bin_t SmallestBinForAllItems();
    int CountBinsUsed();
};

extern cWorld theWorld;
