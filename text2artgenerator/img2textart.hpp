#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;
//Conversion d'image en image Textart

#ifndef IMG2TEXTART
#define IMG2TEXTART

/// <summary>
/// Coller une matrice "tuile" dans une matrice "toile" (comme pour une mosaique) selon des coordonnees
/// </summary>
/// <param name="canvas"> : Matrice "toile"</param>
/// <param name="tile"> : Matrice "tuile"</param>
/// <param name="posx"> : Nombre entier de la position ou coller la tuile </param>
/// <param name="posy"> : Nombre entier de la position ou coller la tuile</param>
void matCopy(Mat& canvas, Mat& tile, int posx, int posy);

/// <summary>
/// Convertir une matrice conteant une image en tableau 2D contenant le textArt de celui-ci
/// </summary>
/// <param name="img"> : Matrice contenant une image</param>
/// <param name="strWhite"> : Caractere utilise pour representer les zones clairs dans le tableau</param>
/// <param name="strBlack"> : Caractere utilise pour representer les zones sombres dans le tableau</param>
/// <param name="thresholdBW"> : Nombre entier pour le seuillage de l'image</param>
/// <returns>ASCII : Tableau dynamique 2D contenant le textArt de img</returns>
vector<vector<String>> matToASCII(Mat img, String strWhite, String strBlack, int thresholdBW);

/// <summary>
/// Conversion d'un tableau 2D contenant des caracteres en Matrice
/// </summary>
/// <param name="ASCII"> : tableau dynamique 2D contenant des caracteres</param>
/// <param name="txtBGR"> : Tableau de 3 entiers (Blue, Green, Red) utilise pour determiner la couleur des caracteres</param>
/// <param name="bgBGR"> : Tableau de 3 entiers (Blue, Green, Red) utilise pour determiner la couleur du fond</param>
/// <param name="strBlack"> : Caractere utilise pour representer les zones sombres dans le tableau</param>
/// <returns>matASCII : Matrice representant le tableau 2D</returns>
Mat ASCIItoMat(vector<vector<String>> ASCII, Scalar txtBGR, Scalar bgBGR);

#endif // !IMG2TEXTART

