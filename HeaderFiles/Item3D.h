/* 
 * File:   Item3D.h
 * Author: arash
 *
 * Created on June 14, 2012, 1:17 PM
 */

#ifndef ITEM3D_H
#define	ITEM3D_H
using namespace std;
#pragma warning( disable : 4250 )

class Item3D : public Shape3D, public Item {
	public:

		static const int NO_CONSTRAINTS = 0;
		static const int CONSTRAINT_WIDTH = 1;
		static const int CONSTRAINT_HEIGHT = 2;
		static const int CONSTRAINT_LENGTH = 3;
		static const int CONSTRAINT_WIDTH_HEIGHT = 4;
		static const int CONSTRAINT_WIDTH_LENGTH = 5;
		static const int CONSTRAINT_HEIGHT_LENGTH = 6;
		Item3D();
		Item3D(const Item3D& orig);
		virtual ~Item3D();

		virtual void ScaleSize( float f );

		void encodeAsJSON(stringstream &jsonStr);

	private:

};

#endif	/* ITEM3D_H */

