
The code is based on Arash Sharif's 2012 packit4me, which is no longer supported.
I have modified the modified Sharif's code to:

- build on windows using codeblocks
- utilize C++11 features, particularly shared pointers
- merge fragmented unused space in the bins
- record locations of items in bins
- output 2D cutting list
- output 3D packing visualization display
- optional limit to exactly one bin
- positional constraints


An approximation algorithmis used, called first-fit decreasing
(FFD). The elements are sorted in decreasing order of
size, and the bins are kept in a fixed order. Each element
is placed into the first bin that it fits into, without exceeding
the bin capacity. How good is the approximation?  The algorithm is guaranteed
to return a solution that uses no more than 11/9 of the optimal number of bins
(Johnson 1973).  For example, on problems of 90 items, where
the items are uniformly distributed from zero to one million,
and the bin capacity is one million, the algorith uses an average
of 47.732 bins. On these same problem instances, the optimal solution
averages 47.680 bins. The FFD solution is optimal 94.694%
of the time on these problem instances. (Korf 2002 http://www.aaai.org/Papers/AAAI/2002/AAAI02-110.pdf)
------------------------------------------------------------------------------------------------


This project is a library for best-fit bin packing.  It is designed to be one
native call and it will figure out the best way to pack 1d, 2d or 3d bin(s) with item(s).

The bins should be passed in the following format:

"id:dim_unit:quantity:size1xsize2xsize3:weight"

The items passed like so:

"id:dim_unit:constraints:quantity:size1xsize2xsize3:weight"

id could be a stock or order number.

example:

53443:5x5x5

constraints are for each item and if the item can be rotated:

constraint = position_constraint + rotation_constraint

position constraint

0     :  anywhere
100   :  bottom only
200   :  top only

rotation constraint

0     :  Any
1     :  Length axis only
2     :  Width axis only
3     :  Height axis only
7     :  No rotation allowed


Dependencies:
1.  To compile the algorithm you need to make sure you have boost for c++ installed

run ./packit4me or ./packit4me -help for options

<hr>

This code can handle both 2D and 3D packing problems, but it is focussed on 3D problems.  Pack2 ( https://github.com/JamesBremner/pack2 ) is optimized for 2D problems.


