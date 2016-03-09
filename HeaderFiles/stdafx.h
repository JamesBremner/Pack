
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <map>
#include <cstring>
#include <stdlib.h>
#include <exception>
#include <algorithm>
#include <functional>
#include <sstream>
#include <memory>
#include <random>
#include <chrono>

class Bin;
   using bin_t = std::shared_ptr< Bin >;
    using bin_v_t = std::vector< bin_t >;

#include "cCut.h"
#include "Side.h"
#include "Shape.h"
#include "Shape2D.h"
#include "Shape3D.h"
#include "Item.h"
#include "Item2D.h"
#include "Item3D.h"
    using item_t = std::shared_ptr< Item >;
        using item_v_t = std::vector< item_t >;
#include "Bin.h"
#include "Bin1D.h"
#include "Bin2D.h"
#include "Bin3D.h"


#include "Packer.h"
#include "BoxPacker2D.h"
#include "BoxPacker3D.h"
#include "TubePacker.h"
#include "Bindings.h"
#include "BoxBindingsParser.h"
#include "TubeBindingsParser.h"
#include "Utils.h"
#include "cWorld.h"


using namespace std;

