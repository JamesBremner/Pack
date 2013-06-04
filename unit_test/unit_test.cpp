// unit_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

TEST( DimensionalUnits )
{
	BoxBindingsParser *parser = new BoxBindingsParser();

	char *bins = "0:in:1:5x5x5";
	char *items = "0:in:0:1:1x1x1";
	vector<Bin*> bins_v;
	vector<Item*> items_v;

	int dim;
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(5.0,bins_v[0]->side_1()->size(),0.1);
	CHECK_CLOSE(5.0,bins_v[0]->side_2()->size(),0.1);
	CHECK_CLOSE(1.0,items_v[0]->side_1()->size(),0.1);
	CHECK_CLOSE(1.0,items_v[0]->side_2()->size(),0.1);

	bins = "0:ft:1:5x5x5";
	items = "0:ft:0:1:1x1x1";
	bins_v.clear();
	items_v.clear();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(60.0,bins_v[0]->side_1()->size(),0.1);
	CHECK_CLOSE(60.0,bins_v[0]->side_2()->size(),0.1);
	CHECK_CLOSE(12.0,items_v[0]->side_1()->size(),0.1);
	CHECK_CLOSE(12.0,items_v[0]->side_2()->size(),0.1);

	bins = "0:cm:1:5x5x5";
	items = "0:cm:0:1:1x1x1";
	bins_v.clear();
	items_v.clear();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(1.97,bins_v[0]->side_1()->size(),0.01);
	CHECK_CLOSE(1.97,bins_v[0]->side_2()->size(),0.01);
	CHECK_CLOSE(0.39,items_v[0]->side_1()->size(),0.01);
	CHECK_CLOSE(0.39,items_v[0]->side_2()->size(),0.01);

	bins = "0:mm:1:5x5x5";
	items = "0:mm:0:1:1x1x1";
	bins_v.clear();
	items_v.clear();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(0.197,bins_v[0]->side_1()->size(),0.001);
	CHECK_CLOSE(0.197,bins_v[0]->side_2()->size(),0.001);
	CHECK_CLOSE(0.039,items_v[0]->side_1()->size(),0.001);
	CHECK_CLOSE(0.039,items_v[0]->side_2()->size(),0.001);

	bins = "0:m:1:5x5x5";
	items = "0:m:0:1:1x1x1";
	bins_v.clear();
	items_v.clear();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(197,bins_v[0]->side_1()->size(),1);
	CHECK_CLOSE(197,bins_v[0]->side_2()->size(),1);
	CHECK_CLOSE(39,items_v[0]->side_1()->size(),1);
	CHECK_CLOSE(39,items_v[0]->side_2()->size(),1);

}

TEST( ItemQuantity )
{
	BoxBindingsParser *parser = new BoxBindingsParser();

	char *bins = "0:ft:1:5x5x5";
	char *items = "0:ft:0:125:1x1x1";
	vector<Bin*> bins_v;
	vector<Item*> items_v;

	int dim;
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_EQUAL( 125, items_v.size() );

}

TEST( BinQuantity1 )
{
	BoxBindingsParser *parser = new BoxBindingsParser();

	char *bins = "0:ft:1:2x2x2";
	char *items = "0:ft:0:125:1x1x1";
	vector<Bin*> bins_v;
	vector<Item*> items_v;

	int dim;
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_EQUAL( 125, items_v.size() );

	BoxPacker3D *packer = new BoxPacker3D();
	packer->BoxPacker2D::packThem(bins_v, items_v);
	delete packer;

	CHECK_EQUAL( 1, bins_v.size() );
	int packed_item_count = 0;
	for( vector< Bin* >::iterator ibin = bins_v.begin();
		ibin != bins_v.end(); ibin++ )
	{
		packed_item_count += (*ibin)->itemsInBinCount();
	}
	CHECK_EQUAL( 8, packed_item_count );
}
TEST( BinQuantity2 )
{

	vector<Bin*> bins_v;
	vector<Item*> items_v;
	char* bins = "0:ft:2:2x2x2";
	char* items = "0:ft:0:125:1x1x1";

	int dim;
	BoxBindingsParser *parser = new BoxBindingsParser();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);
	delete parser;

	BoxPacker3D *packer = new BoxPacker3D();
	packer->BoxPacker2D::packThem(bins_v, items_v);
	delete packer;

	CHECK_EQUAL( 2, bins_v.size() );
	int packed_item_count = 0;
	for( vector< Bin* >::iterator ibin = bins_v.begin();
		ibin != bins_v.end(); ibin++ )
	{
		packed_item_count += (*ibin)->itemsInBinCount();
	}
	CHECK_EQUAL( 16, packed_item_count );

}
TEST( BinQuantityEndless )
{

	vector<Bin*> bins_v;
	vector<Item*> items_v;
	char* bins = "0:ft:-1:2x2x2";
	char* items = "0:ft:0:125:1x1x1";

	int dim;
	BoxBindingsParser *parser = new BoxBindingsParser();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);
	delete parser;

	BoxPacker3D *packer = new BoxPacker3D();
	packer->BoxPacker2D::packThem(bins_v, items_v);
	delete packer;

	CHECK_EQUAL( 16, bins_v.size() );
	int packed_item_count = 0;
	for( vector< Bin* >::iterator ibin = bins_v.begin();
		ibin != bins_v.end(); ibin++ )
	{
		packed_item_count += (*ibin)->itemsInBinCount();
	}
	CHECK_EQUAL( 125, packed_item_count );

}

int _tmain(int argc, _TCHAR* argv[])
{
	return raven::set::UnitTest::RunAllTests();

}

