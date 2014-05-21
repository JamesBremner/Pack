/*
 * File:   Utils.h
 * Author: arash
 *
 * Created on June 7, 2012, 6:13 PM
 */

#ifndef UTILS_H
#define	UTILS_H



using namespace std;

class Utils {
public:
    Utils();
    Utils(const Utils& orig);
    virtual ~Utils();


    static bool compareAscShape(std::shared_ptr<Shape> a, std::shared_ptr<Shape> b);
    static bool compareDescInt( int a, int b );
	static bool compareDescShape(std::shared_ptr<Shape> a, std::shared_ptr<Shape> b);
	static void cleanUpBindingCall( vector<Bin*> &bins_v, vector<Item*> &items_v, BoxBindingsParser *parser );
	static void displayHelp();


};

#endif	/* UTILS_H */

