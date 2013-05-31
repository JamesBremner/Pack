/* 
 * File:   BindingParser.h
 * Author: arash
 *
 * Created on June 20, 2012, 11:25 PM
 */

#ifndef BINDINGPARSER_H
#define	BINDINGPARSER_H
using namespace std;

class BoxBindingsParser {
public:
    
    static const int PACKER_1D = 1;
    static const int PACKER_2D = 2;
    static const int PACKER_3D = 3;
    static const int PACKER_ERROR = 4;
    static const int BIN_PARSE_ERROR = 5;
    static const int ITEM_PARSE_ERROR = 6;
    
    
    BoxBindingsParser();
    BoxBindingsParser(const BoxBindingsParser& orig);
    virtual ~BoxBindingsParser();
    
    void parseBinsAndItems( const char *bins, const char *items,
                              vector<Bin*> &bins_v, vector<Item*> &items_v, int &dim );
    
    
protected:
    
    int dim_;
    
    void parseBins( vector<Bin*> &bins, vector<string> bin_v, int &dim );
    void parseItems( vector<Item*> &items, vector<string> item_v, int &dim );
    
    virtual bool isDimError( int dim );
    virtual Bin *buildBin( string bin_id, vector<string> bin_size_v );
    virtual Item *buildItem( string item_id, vector<string> item_size_v, int constraints);

private:
	float DimensionUnitScale( const string& unit_string );
};

#endif	/* BINDINGPARSER_H */

