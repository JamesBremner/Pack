#include <memory>

/**  A world of items and bins into which they can be packed
*/
class cWorld
{

public:

    /// the bins into which items can be packed
    std::vector< bin_t > Bins;

    /// the items which can be packed into bins
    std::vector< item_t > Items;

    /// The dimensionality of the world
    int Dimension;

    /// Construct a new empty world
    cWorld()
        : Dimension( 0 )
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

    /// Convert feet, cm or m into inches
    static float DimensionUnitScale( const string& unit_string );

    void Clear();

private:
    int BuildBins(  vector<string>& bin_v );
    int BuildItems(  vector<string>& item_v );
    bool isDimError( int dim );
};
