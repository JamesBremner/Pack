Copyright (C) 2012 by Arash Sharif

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Copyright (c) 2013 by James Bremner

Windows build mods

------------------------------------------------------------------------------------------------


This project is a library for best-fit bin packing.  It is designed to be one
native call and it will figure out the best way to pack 1d, 2d or 3d bin(s) with item(s).

The bins should be passed in the following format:

"id:size1xsize2xsize3"

The items passed like so:

"id:constraints:size1xsize2xsize3"

id could be a stock or order number.

example: 

53443:5x5x5

constraints are for each item and if the item can be rotated:

0=NO_CONSTRAINTS
1=CONSTRAINT_WIDTH
2=CONSTRAINT_HEIGHT
3=CONSTRAINT_LENGTH
4=CONSTRAINT_WIDTH_HEIGHT
5=CONSTRAINT_WIDTH_LENGTH
6=CONSTRAINT_HEIGHT_LENGTH

Dependencies:
1.  To compile the algorithm you need to make sure you have boost for c++ installed



run ./packit4me or ./packit4me -help for options


