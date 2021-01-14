#ifndef __BOX_H__
#define __BOX_H__

#include <cstdlib>
#include <fstream>



/*
 * \class Box
 * \brief this class describes a point in UTM32
 * \author Yves Jordan NJAMEN
 * \date 2020
 */

class Box
{
    /*
     * \brief Creates a box
     * \param x  abscisse in UMT32 projection
     * \param y  ordonnée in UMT32 projection
     * \param h  cote in UMT32 projection
     */
  public:
    Box(float x, float y, float h);
    ~Box();

    /*
     * \brief Overloads the operator >> to read an UTM32 point
     * \note For create an instance of Box
     */
    friend std::istream& operator>>(std::istream& stream, Box &b);

    float coord_x;
    float coord_y;
    float cote;
};

bool compar_x(Box *b1, Box *b2);
/*
 * \brief compares the y-parameter of two boxes
 * \param b1 pointer to a box
 * \param b2 pointer to a box
 */
bool compar_y(Box *b1, Box *b2);
/*
 * \brief compares the cote of two boxes
 * \param b1 pointer to a box
 * \param b2 pointer to a box
 */
bool compar_z(Box *b1, Box *b2);

#endif
