#pragma once
/**

  A 2D line

*/
class cCut
{
public:
    bool myIsVertical;
    double myIntercept;     // axis intercept, y for horizontal, x for vertical
    double myStart;
    double myStop;

    /// default ctor ( not sane )
    cCut() {}

    /// ctor from end points (x0,y0) to (x1,y1)
    cCut( double x0, double y0, double x1, double y1 );

    /** true if two cuts can be joined together
    @param[out] the joined cut
    @param[in] cut1
    @param[in] cut2
    @return true if cuts can be joined
    */
    static bool CanJoin( cCut& joined, const cCut& cut1, const cCut& cut2 );

    /// descriptive string (x0,y0) to (x1,y1)
    std::string get() const;

    /// identity operator
    bool operator==( const cCut& other ) const;

};

/**

  The cuts that will create the items out of a bin

*/
class cCutList
{
    std::vector < cCut >  myCut;
    bin_t myBin;
public:

    /** Add a cut
    @param[in] cut to be added

    Ignored if identical cut already present
    */
    void Add( const cCut& cut );

    /** Join all possible cuts
    */
    void Join();

    /** Number of cuts in list
    */
    int size() { return (int) myCut.size(); }

    /**  Clear list
    */
    void clear() { myCut.clear(); }

    /**  Descriptive string
    */
    std::string get() const;

    void set( bin_t bin ) { myBin = bin; }
};
