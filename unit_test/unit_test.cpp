// unit_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cutest.h"

cWorld theWorld;

TEST( DimensionalUnits2 )
{
    char* bins = "0:ft:1:1x1:100";
    char* items = "0:in:0:1250:1x1:1";

    cWorld W;
    W.Build( bins, items );
    W.Pack();
    CHECK_EQUAL( 1, W.Bins.size() );
    CHECK_EQUAL( 144, W.Bins[0]->itemsInBinCount() );
    CHECK_CLOSE( 1, W.Items[0]->side_1()->size(),0.001);
    CHECK_CLOSE( 1, W.Items[0]->side_2()->size(),0.001);
    CHECK_CLOSE( 12, W.Bins[0]->side_1()->size(),0.001);
    CHECK_CLOSE( 12, W.Bins[0]->side_2()->size(),0.001);

    bins = "0:in:1:1x1:100";
    items = "0:ft:0:1250:1x1:1";

    W.Build( bins, items );
    CHECK_EQUAL( 1, W.Bins.size() );
    CHECK_CLOSE( 12, W.Items[0]->side_1()->size(),0.001);
    CHECK_CLOSE( 12, W.Items[0]->side_2()->size(),0.001);
    CHECK_CLOSE( 1, W.Bins[0]->side_1()->size(),0.001);
    CHECK_CLOSE( 1, W.Bins[0]->side_2()->size(),0.001);

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

    char *bins = "0:ft:1:2x2:100";
    char *items = "0:ft:0:125:1x1:1";

    cWorld W;
    W.Build( bins, items );
    W.Pack();
    CHECK_EQUAL( 1, W.Bins.size() );
    CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );


}
TEST( Bin3DQuantity1 )
{

    char *bins = "0:ft:1:2x2x1:100";
    char *items = "0:ft:0:4:1x1x1:1";

    cWorld W;
    W.Build( bins, items );
    W.Pack();
    CHECK_EQUAL( 1, W.Bins.size() );
    CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );

    bins = "0:ft:1:2x2x2:100";
    items = "0:ft:0:8:1x1x1:1";

    W.Clear();
    W.Build( bins, items );
    W.Pack();
    CHECK_EQUAL( 1, W.Bins.size() );
    CHECK_EQUAL( 8, W.Bins[0]->itemsInBinCount() );



}
TEST( BinQuantity2 )
{

    char* bins = "0:ft:2:2x2:100";
    char* items = "0:ft:0:125:1x1:1";

    cWorld W;
    W.Build( bins, items );
    W.Pack();
    CHECK_EQUAL( 2, W.Bins.size() );
    CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );
    CHECK_EQUAL( 4, W.Bins[1]->itemsInBinCount() );


}
TEST( BinQuantityEndless )
{

    char* bins = "0:ft:-1:2x2x2:100";
    char* items = "0:ft:0:125:1x1x1:1";

    cWorld W;
    W.myfOneBin = false;
    W.Build( bins, items );
    W.Pack();
    CHECK_EQUAL( 16, W.Bins.size() );
    CHECK_EQUAL( 8, W.Bins[0]->itemsInBinCount() );
    CHECK_EQUAL( 8, W.Bins[1]->itemsInBinCount() );

}

TEST( weight )
{

    char* bins = "0:ft:1:2x2x2:7";
    char* items = "0:ft:0:125:1x1x1:1";

    cWorld W;
    W.myfOneBin = false;
    W.Build( bins, items );
    W.Pack();
    CHECK_EQUAL( 1, W.Bins.size() );
    CHECK_EQUAL( 7, W.Bins[0]->itemsInBinCount() );

}

//
//TEST( Defragment )
//{
//    char* bins = "0:ft:0:3x3:100";
//    char* items = "0:ft:0:125:1x2:1";
//
//    cWorld W;
//    W.Build( bins, items );
//    W.Pack();
//    CHECK_EQUAL( 1, W.Bins.size() );
//    CHECK_EQUAL( 4, W.Bins[0]->itemsInBinCount() );
//
//}

TEST( CutList )
{
    cCutList L;
    L.Add( cCut( 1,1,1,2));
    L.Add( cCut( 2,1,2,2));
    CHECK_EQUAL( 2, L.size());

    L.Add( cCut( 1,2,1,1));
    CHECK_EQUAL( 2, L.size());

    L.Add( cCut( 1,2,1,3));
    CHECK_EQUAL( 3, L.size());
    L.Join();
    CHECK_EQUAL( 2, L.size());


}

TEST( BinCutList )
{
    char *bins = "0:ft:1:2x2:100";
    char *items = "0:ft:0:1:1x1:1";

    cWorld W;
    W.Build( bins, items );
    W.Pack();
    cCutList L;
    W.Bins[0]->CreateCutList( L );
    CHECK_EQUAL( 4, L.size());

   // cout << L.get();

}
TEST( BinCutList2 )
{
    char *bins = "0:ft:1:2x2:100";
    char *items = "0:ft:0:2:1x1:1";

    cWorld W;
    W.Build( bins, items );
    W.Pack();
    cCutList L;
    W.Bins[0]->CreateCutList( L );
    CHECK_EQUAL( 5, L.size());

    //cout << L.get();

}

TEST( AboveBelow )
{
    std::shared_ptr<Item> i1( new Item3D() );
    i1->set_side_1( new Side( 1, 'w' ));
    i1->set_side_2( new Side( 2, 'h'  ) );
    i1->set_side_3( new Side( 3, 'l'  ) );
    i1->setWLocation(0);
    i1->setHLocation(0);
    i1->setLLocation(0);
    std::shared_ptr<Item> i2( new Item3D() );
    i2->set_side_1( new Side( 1, 'w' ));
    i2->set_side_2( new Side( 2, 'h'  ) );
    i2->set_side_3( new Side( 3, 'l'  ) );
    i2->setWLocation(0);
    i2->setHLocation(200);
    i2->setLLocation(0);
    std::shared_ptr<Item> i3( new Item3D() );
    i3->set_side_1( new Side( 1, 'w' ));
    i3->set_side_2( new Side( 2, 'h'  ) );
    i3->set_side_3( new Side( 3, 'l'  ) );
    i3->setWLocation(220);
    i3->setHLocation(0);
    i3->setLLocation(0);

    std::shared_ptr<Bin> bin( new Bin3D );
    i1->setBin( bin->Root( bin )->progid() );
    i2->setBin( bin->Root( bin )->progid() );
    i3->setBin( bin->Root( bin )->progid() );

    CHECK( i1->IsAboveBelow( i2 ) );
    CHECK( ! i3->IsAboveBelow( i2 ) );
}

TEST( AreaWidthLength )
{
    Shape3D s1;
    s1.set_side_1( new Side( 1, 'w' ));
    s1.set_side_2( new Side( 2, 'h'  ) );
    s1.set_side_3( new Side( 3, 'l'  ) );

    CHECK_CLOSE( s1.AreaWidthLength(), 3, 0.1 );

}

TEST( OverlapArea )
{
    std::shared_ptr<Shape3D> i1( new Shape3D() );
    i1->set_side_1( new Side( 1, 'w' ));
    i1->set_side_2( new Side( 2, 'h'  ) );
    i1->set_side_3( new Side( 3, 'l'  ) );
    i1->setWLocation(0);
    i1->setHLocation(0);
    i1->setLLocation(0);
    std::shared_ptr<Shape3D> i2( new Shape3D() );
    i2->set_side_1( new Side( 1, 'w' ));
    i2->set_side_2( new Side( 2, 'h'  ) );
    i2->set_side_3( new Side( 3, 'l'  ) );
    i2->setWLocation(0);
    i2->setHLocation(200);
    i2->setLLocation(0);

    CHECK_CLOSE( i1->AreaWidthLength(), i1->OverlapArea( i2 ), 0.1 );

    std::shared_ptr<Shape3D> i3( new Shape3D() );
    i3->set_side_1( new Side( 1, 'w' ));
    i3->set_side_2( new Side( 2, 'h'  ) );
    i3->set_side_3( new Side( 3, 'l'  ) );
    i3->setWLocation(0.5);
    i3->setHLocation(0);
    i3->setLLocation(0);
     CHECK_CLOSE( i3->AreaWidthLength() / 2, i3->OverlapArea( i2 ), 0.1 );

}

TEST(AboveBelowBug)
{
	std::shared_ptr<Item> i1(new Item3D());
	i1->set_side_1(new Side(1, 'w'));
	i1->set_side_2(new Side(2, 'h'));
	i1->set_side_3(new Side(3, 'l'));
	i1->setWLocation(0);
	i1->setHLocation(0);
	i1->setLLocation(7);
	std::shared_ptr<Item> i2(new Item3D());
	i2->set_side_1(new Side(1, 'w'));
	i2->set_side_2(new Side(2, 'h'));
	i2->set_side_3(new Side(3, 'l'));
	i2->setWLocation(0);
	i2->setHLocation(200);
	i2->setLLocation(5);

	CHECK(i1->IsAboveBelow(i2));
}

int main(int argc, char *argv[])
{
    return raven::set::UnitTest::RunAllTests();

}

