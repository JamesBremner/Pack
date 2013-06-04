// unit_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

TEST( DimensionalUnits )
{
	BoxBindingsParser *parser = new BoxBindingsParser();

	char *bins = "0:in:5x5x5";
	char *items = "0:in:0:1:1x1x1";
	vector<Bin*> bins_v;
	vector<Item*> items_v;

	int dim;
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(5.0,bins_v[0]->side_1()->size(),0.1);
	CHECK_CLOSE(5.0,bins_v[0]->side_2()->size(),0.1);
	CHECK_CLOSE(1.0,items_v[0]->side_1()->size(),0.1);
	CHECK_CLOSE(1.0,items_v[0]->side_2()->size(),0.1);

	bins = "0:ft:5x5x5";
	items = "0:ft:0:1:1x1x1";
	bins_v.clear();
	items_v.clear();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(60.0,bins_v[0]->side_1()->size(),0.1);
	CHECK_CLOSE(60.0,bins_v[0]->side_2()->size(),0.1);
	CHECK_CLOSE(12.0,items_v[0]->side_1()->size(),0.1);
	CHECK_CLOSE(12.0,items_v[0]->side_2()->size(),0.1);

	bins = "0:cm:5x5x5";
	items = "0:cm:0:1:1x1x1";
	bins_v.clear();
	items_v.clear();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(1.97,bins_v[0]->side_1()->size(),0.01);
	CHECK_CLOSE(1.97,bins_v[0]->side_2()->size(),0.01);
	CHECK_CLOSE(0.39,items_v[0]->side_1()->size(),0.01);
	CHECK_CLOSE(0.39,items_v[0]->side_2()->size(),0.01);

	bins = "0:mm:5x5x5";
	items = "0:mm:0:1:1x1x1";
	bins_v.clear();
	items_v.clear();
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_CLOSE(0.197,bins_v[0]->side_1()->size(),0.001);
	CHECK_CLOSE(0.197,bins_v[0]->side_2()->size(),0.001);
	CHECK_CLOSE(0.039,items_v[0]->side_1()->size(),0.001);
	CHECK_CLOSE(0.039,items_v[0]->side_2()->size(),0.001);

	bins = "0:m:5x5x5";
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

	char *bins = "0:ft:5x5x5";
	char *items = "0:ft:0:125:1x1x1";
	vector<Bin*> bins_v;
	vector<Item*> items_v;

	int dim;
	parser->parseBinsAndItems( bins, items, bins_v, items_v, dim);

	CHECK_EQUAL( 125, items_v.size() );

}

int _tmain(int argc, _TCHAR* argv[])
{
	return raven::set::UnitTest::RunAllTests();

}

