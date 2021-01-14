#ifndef PIXEL_H
#define PIXEL_H
#include "Box.h"
#include <vector>
#include <cstdlib>

/*
 * \class Pixel
 * \brief this class describes a pixel on our final image
 * \author Yves Jordan NJAMEN
 * \date 2020
 */

using namespace std;
class Pixel
{

    /*
     * \brief Create a Pixel and write it in a .ppm/ .Pgm file
     * \param val matrix of values for each pixel
     * \param nb matrix of number of pixels averaged to obtain the value of a pixel
     */

  public:
    Pixel();
    Pixel(float val, int nb);
    ~Pixel();


   int nb_p;
   float val_p;
};
/*
 * \brief Create a matrix of pixel
 * \param donnee a vector of all UMT32 points
 * \param cote_x the width of the minimum square contains all our stitches
 * \param cote_y the length of the minimum square contains all our stitches
 * \param larg  argv[2] width of the final image
 */
Pixel** matrix_P(vector <Box *> donnee, float cote_x, float cote_y, char* larg);
/*
 * \brief Writes our points in a PGM file
 * \param mat matrix of all our pixels
 * \param filename name of the PGM file
 */
void ecriture_PGM(Pixel** mat, const string& file_name);
/*
 * \brief Writes our points in a PPM file
 * \param mat matrix of all our pixels
 * \param filename name of the PPM file
 */
void ecriture_PPM(Pixel** mat, const string& file_name);
#endif // PIXEL_H
