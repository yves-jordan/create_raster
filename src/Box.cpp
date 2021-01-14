#include "Box.h"
#include <iostream>

using namespace std;

/*
 * \brief constructor of Box
 */
Box::Box(float x, float y, float h): coord_x(x), coord_y(y), cote(h)
{

}

/*
 * \brief compares the x's of two box
 */
bool compar_x(Box *b1, Box *b2)
{
    return b1->coord_x < b2->coord_x;
}


/*
 * \brief compares the y's of two box
 */
bool compar_y(Box *b1, Box *b2)
{
    return b1->coord_y < b2->coord_y;
}

/*
 * \brief compares the cotes of two box
 */
bool compar_z(Box *b1, Box *b2)
{
    return b1->cote < b2->cote;
}
/*
 * \brief destructor
 */
Box::~Box()
{
}

/*
 * \brief operator overload >>
 */
istream& operator>>(istream& stream, Box &b)
{
    string s;
    getline(stream, s) >> b.coord_x;
    cout << s <<endl;
    getline(stream, s, ' ') >> b.coord_y;
    cout << s <<endl;
    getline(stream, s, ' ') >> b.cote;
    cout << s <<endl;
    return stream;
}
