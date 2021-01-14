#include "Pixel.h"
#include "Box.h"
#include <vector>
#include <cstdlib>
#include <math.h>
#include <iostream>


using namespace std;
int largeur, longueur; // global variable length and width of the final image

/*
 * \brief default constructor of Class Pixel
 */
Pixel::Pixel(){

}


/*
 * \brief constructor of Class Pixel
 */
Pixel::Pixel(float val, int nb) : val_p(val), nb_p(nb)
{

}

/*
 * \brief destructor of Class Pixel
 */

Pixel::~Pixel()
{
  // Nothing to destroy.
}

/*
 * \brief Create a matrix of pixel
 */
Pixel** matrix_P(vector <Box *> donnee, float cote_x, float cote_y, char* larg)
{
    float l_eps, L_eps; // minimum square dimension containing any utm32 point to form a pixel
    float res; //resolution of our image
    int m, n;
    largeur = atoi(larg);
    res = largeur/cote_x;
    longueur = cote_y*res;

    l_eps = cote_x/ largeur;
    L_eps = cote_y/ longueur;


// An empty matrix is created at the right size.
    Pixel** mat=nullptr;
    mat = new Pixel*[longueur];
    for(int i =0; i<longueur; i++)
    {
        mat[i] = new Pixel[largeur];
    }


// Initialization of the matrix
    for(int i = 0; i<longueur; i++)
    {
        for(int j = 0; j<largeur; j++)
        {
            mat[i][j].val_p = 0.0;
            mat[i][j].nb_p = 0.0;
        }
    }

    cout << "Matrix initialisation OK" << endl;

//    Filling of the matrix

    for(size_t i = 0; i < donnee.size(); ++i) {
        n = floor(donnee[i]->coord_x/L_eps);
        m = floor(donnee[i]->coord_y/l_eps);

        if(n >= largeur)
        {
           n = largeur-1;
        }
        if (m >= longueur)
        {
            m = longueur-1;
        }
        mat[m][n].val_p = (donnee[i]->cote + mat[m][n].val_p * mat[m][n].nb_p)/(mat[m][n].nb_p + 1);
        mat[m][n].nb_p = mat[m][n].nb_p + 1;

    }
    cout << "Matrix filling OK" << endl;
    return mat;
}

/*
 * \brief writing the PGM file
 */
// Ecriture du fichier PGM
void ecriture_PGM(Pixel** mat, const string& file_name)
{
  ofstream f(file_name);

  if(!f.is_open()){
    cout << " Cannot open the file for writing " << endl;
    }
  else
  {

// standard header of a PGM file

    f << "P5" << endl;
    f << "800 753" << endl;
    f << "255" << endl;

// Writing the file in binary
    for(int i=longueur-1; i>= 0; i--)
    {
        for(int j=0; j< largeur; j++)
        {

            f << char(mat[i][j].val_p);
        }
    }
  }

  f.close();
}

/*
 * \brief writing the PPM file
 */
// Ecriture du fichier PPM
void ecriture_PPM(Pixel** mat, const string& file_name)
{
  float a, t;
  int X, Y, r, g, b;

  ofstream f(file_name);

  if(!f.is_open()){
    cout << " Cannot open the file for writing " << endl;
    }
  else
  {

// standard header of a PPM file
    f << "P6" << endl;
    f << "800 753" << endl;
    f << "255"<< endl;

    for(int i=longueur-1; i>= 0; i--)
    {
        for(int j=0; j< largeur; j++)
        {
            t = mat[i][j].val_p;
            a=t/0.25;
            X=floor(a);
            Y=floor(255*(a-X));

            switch(X)
            {
                case 0: r=255;g=Y;b=0;break;
                case 1: r=255-Y;g=255;b=0;break;
                case 2: r=0;g=255;b=Y;break;
                case 3: r=0;g=255-Y;b=255;break;
                case 4: r=0;g=0;b=255;break;
            }
            if (X == 0 and t == 0)
            {
                r = 0;
                g = 0;
                b = 0;
            }
            // Writing the file in binary
            f << char(r) << char(g) << char(b);
        }
    }

  }

  f.close();
}
