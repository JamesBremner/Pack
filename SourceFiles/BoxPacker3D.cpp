#include "stdafx.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif

using namespace std;

BoxPacker3D::BoxPacker3D() {
}

BoxPacker3D::BoxPacker3D(const BoxPacker3D& orig) {
}

BoxPacker3D::~BoxPacker3D() {
}


bool BoxPacker3D::packIt(Bin *bin, Item *item, vector<Bin*> &bins) {

	int constraints = item->constraints();

    if (constraints == Item3D::CONSTRAINT_WIDTH)
        return checkFitsConstrWidth(bin, item, bins);
    else if (constraints == Item3D::CONSTRAINT_HEIGHT)
        return checkFitsConstrHeight(bin, item, bins);
    else if (constraints == Item3D::CONSTRAINT_LENGTH)
        return checkFitsConstrLength(bin, item, bins);
    else if (constraints == Item3D::CONSTRAINT_WIDTH_HEIGHT)
        return checkFitsConstrWidthHeight(bin, item, bins);
    else if (constraints == Item3D::CONSTRAINT_WIDTH_LENGTH)
        return checkFitsConstrWidthLength(bin, item, bins);
    else if (constraints == Item3D::CONSTRAINT_HEIGHT_LENGTH)
        return checkFitsConstrHeightLength(bin, item, bins);
    else
        return checkFitsNoConstr(bin, item, bins);

}

void BoxPacker3D::splitBinWidth(Bin *bin, Item *item) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);

    map<string, double> sides = findSubBinSizes( bin, item );
    double dx_w = sides["dx_w"];
    double dx_h = sides["dx_h"];
    double dx_l = sides["dx_l"];


    if (dx_w <= 0)
        bin3d->set_x_sub_bin(NULL);
    else {

        Bin3D *sub_binX = new Bin3D();
        sub_binX->set_side_1(bin3d->side_1()->size_side_to(dx_w));
        sub_binX->set_side_2(bin3d->side_2()->size_side_to(dx_h));
        sub_binX->set_side_3(bin3d->side_3()->size_side_to(dx_l));
        sub_binX->set_parent_bin(bin);
        sub_binX->set_id(bin->id());
        bin3d->set_x_sub_bin(sub_binX);


    }


}

void BoxPacker3D::splitBinHeight(Bin *bin, Item *item) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);

    map<string, double> sides = findSubBinSizes( bin, item );
    double dy_w = sides["dy_w"];
    double dy_h = sides["dy_h"];
    double dy_l = sides["dy_l"];


    if (dy_h <= 0)
        bin3d->set_y_sub_bin(NULL);
    else {

        Bin3D *sub_binY = new Bin3D();
        sub_binY->set_side_1(bin3d->side_1()->size_side_to(dy_w));
        sub_binY->set_side_2(bin3d->side_2()->size_side_to(dy_h));
        sub_binY->set_side_3(bin3d->side_3()->size_side_to(dy_l));
        sub_binY->set_parent_bin(bin);
        sub_binY->set_id(bin->id());
        bin3d->set_y_sub_bin(sub_binY);


    }

}

void BoxPacker3D::splitBinLength(Bin *bin, Item *item) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);

    map<string, double> sides = findSubBinSizes( bin, item );
    double dz_w = sides["dz_w"];
    double dz_h = sides["dz_h"];
    double dz_l = sides["dz_l"];


    if (dz_l <= 0)
        bin3d->set_z_sub_bin(NULL);
    else {

        Bin3D *sub_binZ = new Bin3D();
        sub_binZ->set_side_1(bin3d->side_1()->size_side_to(dz_w));
        sub_binZ->set_side_2(bin3d->side_2()->size_side_to(dz_h));
        sub_binZ->set_side_3(bin3d->side_3()->size_side_to(dz_l));
        sub_binZ->set_parent_bin(bin);
        sub_binZ->set_id(bin->id());
        bin3d->set_z_sub_bin(sub_binZ);


    }

}

bool BoxPacker3D::checkFitsConstrWidth(Bin *bin, Item *item, vector<Bin*> &bins) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
    Item3D *item3d = (Item3D*) item;


    if (bin3d->side_2()->size() < bin3d->side_3()->size()) {

        Side *tmps;
        tmps = bin3d->side_2();
        bin3d->set_side_2(bin3d->side_3());
        bin3d->set_side_3(tmps);
    }


    if (item3d->side_2()->size() < item3d->side_3()->size()) {

        Side *tmps;
        tmps = item3d->side_2();
        item3d->set_side_2(item3d->side_3());
        item3d->set_side_3(tmps);
    }

    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
            item3d->side_2()->size() <= bin3d->side_2()->size() &&
            item3d->side_3()->size() <= bin3d->side_3()->size()) {

        bin->set_item(item);

        //if it fits split item and recurse
        splitBinWidth(bin, item);
        splitBinHeight(bin, item);
        splitBinLength(bin, item);



        if (bin3d->x_sub_bin() != NULL) {

            bins.push_back(bin3d->x_sub_bin());

        }
        if (bin3d->y_sub_bin() != NULL) {

            bins.push_back(bin3d->y_sub_bin());
        }
        if (bin3d->z_sub_bin() != NULL) {

            bins.push_back(bin3d->z_sub_bin());
        }

        return true;

    }

    return false;

}

bool BoxPacker3D::checkFitsConstrHeight(Bin *bin, Item *item, vector<Bin*> &bins) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
    Item3D *item3d = (Item3D*) item;


    if (bin3d->side_1()->size() < bin3d->side_3()->size()) {

        Side *tmps;
        tmps = bin3d->side_1();
        bin3d->set_side_1(bin3d->side_3());
        bin3d->set_side_3(tmps);
    }



    if (item3d->side_1()->size() < item3d->side_3()->size()) {

        Side *tmps;
        tmps = item3d->side_1();
        item3d->set_side_1(item3d->side_3());
        item3d->set_side_3(tmps);
    }



    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
            item3d->side_2()->size() <= bin3d->side_2()->size() &&
            item3d->side_3()->size() <= bin3d->side_3()->size()) {

        bin->set_item(item);

        //if it fits split item and recurse
        splitBinWidth(bin, item);
        splitBinHeight(bin, item);
        splitBinLength(bin, item);

        //Bin2D * bin2d = dynamic_cast<Bin2D*> (bin);

        if (bin3d->x_sub_bin() != NULL) {

            bins.push_back(bin3d->x_sub_bin());

        }
        if (bin3d->y_sub_bin() != NULL) {

            bins.push_back(bin3d->y_sub_bin());
        }
        if (bin3d->z_sub_bin() != NULL) {

            bins.push_back(bin3d->z_sub_bin());
        }

        return true;

    }

    return false;

}

bool BoxPacker3D::checkFitsConstrLength(Bin *bin, Item *item, vector<Bin*> &bins) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
    Item3D *item3d = (Item3D*) item;

    //sort both bin and item
    if (bin3d->side_1()->size() < bin3d->side_2()->size()) {

        Side *tmps;
        tmps = bin3d->side_1();
        bin3d->set_side_1(bin3d->side_2());
        bin3d->set_side_2(tmps);
    }


    if (item3d->side_1()->size() < item3d->side_2()->size()) {

        Side *tmps;
        tmps = item3d->side_1();
        item3d->set_side_1(item3d->side_2());
        item3d->set_side_2(tmps);
    }


    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
            item3d->side_2()->size() <= bin3d->side_2()->size() &&
            item3d->side_3()->size() <= bin3d->side_3()->size()) {

        bin->set_item(item);

        //if it fits split item and recurse
        splitBinWidth(bin, item);
        splitBinHeight(bin, item);
        splitBinLength(bin, item);

        //Bin2D * bin2d = dynamic_cast<Bin2D*> (bin);

        if (bin3d->x_sub_bin() != NULL) {

            bins.push_back(bin3d->x_sub_bin());

        }
        if (bin3d->y_sub_bin() != NULL) {

            bins.push_back(bin3d->y_sub_bin());
        }
        if (bin3d->z_sub_bin() != NULL) {

            bins.push_back(bin3d->z_sub_bin());
        }


        return true;

    }

    return false;

}

bool BoxPacker3D::checkFitsNoConstr(Bin *bin, Item *item, vector<Bin*> &bins) {

    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
    Item3D *item3d = (Item3D*) item;

    //sort both bin and item
    if (bin3d->side_1()->size() < bin3d->side_2()->size()) {

        Side *tmps;
        tmps = bin3d->side_1();
        bin3d->set_side_1(bin3d->side_2());
        bin3d->set_side_2(tmps);
    }


    if (bin3d->side_1()->size() < bin3d->side_3()->size()) {

        Side *tmps;
        tmps = bin3d->side_1();
        bin3d->set_side_1(bin3d->side_3());
        bin3d->set_side_3(tmps);
    }

    if (bin3d->side_2()->size() < bin3d->side_3()->size()) {

        Side *tmps;
        tmps = bin3d->side_2();
        bin3d->set_side_2(bin3d->side_3());
        bin3d->set_side_3(tmps);
    }



    if (item3d->side_1()->size() < item3d->side_2()->size()) {

        Side *tmps;
        tmps = item3d->side_1();
        item3d->set_side_1(item3d->side_2());
        item3d->set_side_2(tmps);
    }

    if (item3d->side_1()->size() < item3d->side_3()->size()) {

        Side *tmps;
        tmps = item3d->side_1();
        item3d->set_side_1(item3d->side_3());
        item3d->set_side_3(tmps);
    }

    if (item3d->side_2()->size() < item3d->side_3()->size()) {

        Side *tmps;
        tmps = item3d->side_2();
        item3d->set_side_2(item3d->side_3());
        item3d->set_side_3(tmps);
    }

    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
            item3d->side_2()->size() <= bin3d->side_2()->size() &&
            item3d->side_3()->size() <= bin3d->side_3()->size()) {

        bin->set_item(item);

        //if it fits split item and recurse
        splitBinWidth(bin, item);
        splitBinHeight(bin, item);
        splitBinLength(bin, item);

        Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
        if (bin3d->x_sub_bin() != NULL) {

            bins.push_back(bin3d->x_sub_bin());

        }
        if (bin3d->y_sub_bin() != NULL) {

            bins.push_back(bin3d->y_sub_bin());
        }
        if (bin3d->z_sub_bin() != NULL) {

            bins.push_back(bin3d->z_sub_bin());
        }

        return true;

    }


    return false;

}

bool BoxPacker3D::checkFitsConstrWidthHeight(Bin *bin, Item *item, vector<Bin*> &bins) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
    Item3D *item3d = (Item3D*) item;

    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
            item3d->side_2()->size() <= bin3d->side_2()->size() &&
            item3d->side_3()->size() <= bin3d->side_3()->size()) {

        bin->set_item(item);

        //if it fits split item and recurse
        splitBinWidth(bin, item);
        splitBinHeight(bin, item);
        splitBinLength(bin, item);


        if (bin3d->z_sub_bin() != NULL) {

            bins.push_back(bin3d->z_sub_bin());
        }

        return true;

    }

    return false;

}

bool BoxPacker3D::checkFitsConstrWidthLength(Bin *bin, Item *item, vector<Bin*> &bins) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
    Item3D *item3d = (Item3D*) item;

    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
            item3d->side_2()->size() <= bin3d->side_2()->size() &&
            item3d->side_3()->size() <= bin3d->side_3()->size()) {

        bin->set_item(item);

        //if it fits split item and recurse
        splitBinWidth(bin, item);
        splitBinHeight(bin, item);
        splitBinLength(bin, item);


        if (bin3d->y_sub_bin() != NULL) {

            bins.push_back(bin3d->y_sub_bin());
        }

        return true;

    }

    return false;

}

bool BoxPacker3D::checkFitsConstrHeightLength(Bin *bin, Item *item, vector<Bin*> &bins) {
    Bin3D * bin3d = dynamic_cast<Bin3D*> (bin);
    Item3D *item3d = (Item3D*) item;

    if (item3d->side_1()->size() <= bin3d->side_1()->size() &&
            item3d->side_2()->size() <= bin3d->side_2()->size() &&
            item3d->side_3()->size() <= bin3d->side_3()->size()) {

        bin->set_item(item);

        //if it fits split item and recurse
        splitBinWidth(bin, item);
        splitBinHeight(bin, item);
        splitBinLength(bin, item);


        if (bin3d->x_sub_bin() != NULL) {

            bins.push_back(bin3d->x_sub_bin());
        }

        return true;

    }

    return false;

}

map<string, double> BoxPacker3D::findSubBinSizes(Bin *bin, Item *item) {

    Bin3D *bin3d = dynamic_cast<Bin3D*> (bin);
    Item3D *item3d = (Item3D*) item;


    double w_diff = bin3d->side_1()->size() - item3d->side_1()->size();
    double h_diff = bin3d->side_2()->size() - item3d->side_2()->size();
    double l_diff = bin3d->side_3()->size() - item3d->side_3()->size();


    double dx_w, dx_h, dx_l;
    double dy_w, dy_h, dy_l;
    double dz_w, dz_h, dz_l;

    if (l_diff >= w_diff && w_diff >= h_diff) {

        dx_w = bin3d->side_1()->size() - item3d->side_1()->size();
        dx_h = item3d->side_2()->size();
        dx_l = bin3d->side_3()->size();

        dy_w = bin3d->side_1()->size();
        dy_h = bin3d->side_2()->size() - item3d->side_2()->size();
        dy_l = bin3d->side_3()->size();

        dz_w = item3d->side_1()->size();
        dz_h = item3d->side_2()->size();
        dz_l = bin3d->side_3()->size() - item3d->side_3()->size();

    }
    else if (l_diff >= h_diff && h_diff >= w_diff) {

        dx_w = bin3d->side_1()->size() - item3d->side_1()->size();
        dx_h = bin3d->side_2()->size();
        dx_l = bin3d->side_3()->size();

        dy_w = item3d->side_1()->size();
        dy_h = bin3d->side_2()->size() - item3d->side_2()->size();
        dy_l = bin3d->side_3()->size();

        dz_w = item3d->side_1()->size();
        dz_h = item3d->side_2()->size();
        dz_l = bin3d->side_3()->size() - item3d->side_3()->size();

    } else if (w_diff >= h_diff && h_diff >= l_diff) {

        dx_w = bin3d->side_1()->size() - item3d->side_1()->size();
        dx_h = item3d->side_2()->size();
        dx_l = item3d->side_3()->size();

        dy_w = bin3d->side_1()->size();
        dy_h = bin3d->side_2()->size() - item3d->side_2()->size();
        dy_l = item3d->side_3()->size();

        dz_w = bin3d->side_1()->size();
        dz_h = bin3d->side_2()->size();
        dz_l = bin3d->side_3()->size() - item3d->side_3()->size();

    } else if (w_diff >= l_diff && l_diff >= h_diff)
    {
        dx_w = bin3d->side_1()->size() - item3d->side_1()->size();
        dx_h = item3d->side_2()->size();
        dx_l = item3d->side_3()->size();

        dy_w = bin3d->side_1()->size();
        dy_h = bin3d->side_2()->size() - item3d->side_2()->size();
        dy_l = bin3d->side_3()->size();

        dz_w = bin3d->side_1()->size();
        dz_h = item3d->side_2()->size();
        dz_l = bin3d->side_3()->size() - item3d->side_3()->size();

    } else if (h_diff >= w_diff && w_diff >= l_diff) {
        dx_w = bin3d->side_1()->size() - item3d->side_1()->size();
        dx_h = bin3d->side_2()->size();
        dx_l = item3d->side_3()->size();

        dy_w = item3d->side_1()->size();
        dy_h = bin3d->side_2()->size() - item3d->side_2()->size();
        dy_l = item3d->side_3()->size();

        dz_w = bin3d->side_1()->size();
        dz_h = bin3d->side_2()->size();
        dz_l = bin3d->side_3()->size() - item3d->side_3()->size();

    } else if (h_diff >= l_diff && l_diff >= w_diff) {

        dx_w = bin3d->side_1()->size() - item3d->side_1()->size();
        dx_h = bin3d->side_2()->size();
        dx_l = bin3d->side_3()->size();

        dy_w = item3d->side_1()->size();
        dy_h = bin3d->side_2()->size() - item3d->side_2()->size();
        dy_l = item3d->side_3()->size();

        dz_w = item3d->side_1()->size();
        dz_h = bin3d->side_2()->size();
        dz_l = bin3d->side_3()->size() - item3d->side_3()->size();

    }

    map<string, double> sides;
    sides["dx_w"] = dx_w;
    sides["dx_h"] = dx_h;
    sides["dx_l"] = dx_l;

    sides["dy_w"] = dy_w;
    sides["dy_h"] = dy_h;
    sides["dy_l"] = dy_l;

    sides["dz_w"] = dz_w;
    sides["dz_h"] = dz_h;
    sides["dz_l"] = dz_l;

    return sides;


}
