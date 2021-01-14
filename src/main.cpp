#define ACCEPT_USE_OF_DEPRECATED_PROJ_API_H
#include "proj.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include "Box.h"
#include "Pixel.h"

using namespace std;
// Proj variables
PJ_CONTEXT *C;
PJ *P;
PJ* P_for_GIS;
PJ_COORD a, b;

int const N(4);



// Deserialisation of the .txt file
vector<Box *> deserialize_txt(const string& file_name)
{    /*
     * \brief initialise a box with parameters long lat and cote then put it in a vector
     * \param file_name the name of data file
     */
    vector<Box *> donnee;
    ifstream f(file_name);
    if(!f.is_open())
        cout << "Cannot read the file" << endl;
    else
    {
        while(!f.eof())
        {
            Box *b = new Box(0,0,0);
            f >> *b;
            donnee.push_back(b); // puts the new box in line
        }
    }
    f.close();
    cout << "End of deserialisation" << endl;
    return donnee;
}


// Conversion of points to UTM32
vector<Box *> conversion(vector<Box *> donnee) //UTM32
{
    /*
     * \brief convert boxes long lat into UTM32 equivalent
     * \param donnees vector of boxes
     */
    C = proj_context_create();
    P = proj_create_crs_to_crs (C, "EPSG:4326", "+proj=utm +zone=32 +datum=WGS84",NULL);
    P_for_GIS = proj_normalize_for_visualization(C, P);
    if (0==P)
    {
        cout << " ----- Proj: Error ----" << endl;
    }
    proj_destroy(P);
    P = P_for_GIS;
    for (long unsigned int i=0; i<donnee.size(); i++)
    {
        a = proj_coord (donnee[i]->coord_y, donnee[i]->coord_x, 0, 0);
        b = proj_trans (P, PJ_FWD, a);
        donnee[i]->coord_x = b.enu.e;
        donnee[i]->coord_y = b.enu.n;
    }
    return donnee;
}


// Extraction min. squares containing all UTM32 points
float* grille_pix(vector<Box *> & b, int mode) // mode = 1 to get a PPM image & 255 for a PGM one
    {
    /*
     * \brief Determine the relative coordinate of boxes and also adjuste the cote for PPM/PGM images
     * \param b vector for pointer box
     * \param mode equal 1 to get a PPM image and 255 a PGM one
     */
        float* borne_pixel = new float[N];
        float max_x = (*max_element(b.begin(), b.end(), compar_x))->coord_x;
        float min_x = (*min_element(b.begin(), b.end(), compar_x))->coord_x;
        float max_y = (*max_element(b.begin(), b.end(), compar_y))->coord_y;
        float min_y = (*min_element(b.begin(), b.end(), compar_y))->coord_y;
        float max_z = (*max_element(b.begin(), b.end(), compar_z))->cote;
        float min_z = (*min_element(b.begin(), b.end(), compar_z))->cote;
        borne_pixel[0] = max_x;
        borne_pixel[1] = min_x;
        borne_pixel[2] = max_y;
        borne_pixel[3] = min_y;

// Calculation of relative coordinates
        for(size_t i = 0; i < b.size(); ++i)
        {
            b[i]->coord_x = b[i]->coord_x - min_x;
            b[i]->coord_y = b[i]->coord_y - min_y;
            b[i]->cote = abs(((b[i]->cote-min_z)*mode / (max_z-min_z)));
        }

    return borne_pixel;
    }

// Main
int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        cout << "You don't have the right number of parameters to enter" << endl;
    }
    cout << "Program start" << endl;
    float a, b, c, d;
    float dist_x, dist_y;
    Pixel** mat;
    Pixel** mat1;
    cout << argv[1] << endl;
    vector<Box *> data;
    vector<Box *> data_conv;
    cout << "Deserialisation and  conversion... " << endl;
    data =  deserialize_txt(argv[1]);
    data_conv = conversion(data);
    cout << "Deserialisation and  conversion done " << endl;

    float* tab;
    // float* tab_PGM;
    tab = grille_pix(data_conv, 1); // 255 PGM, 1 PPM

    a = tab[0];
    b = tab[1];
    c = tab[2];
    d = tab[3];


    dist_x = a - b;
    dist_y = c - d;


    mat = matrix_P(data_conv, dist_x, dist_y, argv[2]);

    cout << "Write PPM file..." << endl;
    ecriture_PPM(mat, "../src/Rendu_Guerledan.PPM");
    cout << "PPM Ready " << endl;

    grille_pix(data_conv, 255); // 255 PGM, 1 PPM
    mat1 = matrix_P(data_conv, dist_x, dist_y, argv[2]);

    cout << "Write PGM file..." << endl;
    ecriture_PGM(mat1, "../src/Rendu_Guerledan.PGM");
    cout << "PPM Ready" << endl;
    cout << "Program end" << endl;


    return EXIT_SUCCESS;
}
