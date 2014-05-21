#include <memory>

class cWorld
{

public:

    std::vector< bin_t > Bins;
    std::vector< item_t > Items;
    int Dimension;

    cWorld()
        : Dimension( 0 )
    {

    }

    int Build(
        const char* bin_input_description,
        const char* item_input_description );

    void Pack();

    string getJson();

    static float DimensionUnitScale( const string& unit_string );

private:
    int BuildBins(  vector<string>& bin_v );
    int BuildItems(  vector<string>& item_v );
    bool isDimError( int dim );
};
