/* 
 * File:   Item.h
 * Author: arash
 *
 * Created on June 14, 2012, 1:16 PM
 */

#ifndef ITEM_H
#define	ITEM_H
using namespace std;

class Item : public virtual Shape2D {
	public:
		Item();
		Item(const Item& orig);
		virtual ~Item();

		int constraints();
		void set_constraints( int value );

	virtual void ScaleSize( float f ) { }

		virtual void encodeAsJSON(stringstream &jsonStr) = 0;
	private:

		int constraints_;
};

#endif	/* ITEM_H */

