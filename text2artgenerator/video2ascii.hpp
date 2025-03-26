#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include "img2textart.hpp"

using namespace cv;
using namespace std;

//Conversion de videos en videos en textart

#ifndef VIDEO2ASCII
#define VIDEO2ASCII


/// <summary>
/// Recupere le nom d'un fichier a partir du chemin menant a lui
/// </summary>
/// <param name="path"> : Chaine de caractere representant le chemin du fichier (absolu ou relatif)</param>
/// <returns>fileName : Chaine de caractere avec le nom du fichier et l'extension</returns>
string fileFindName(string path);

/// <summary>
/// Creer une video en textArt a partir d'une video specifiee
/// </summary>
/// <param name="inPath"> : Chaine de caractere portant le chemin de la video specifie</param>
/// <param name="strBlack"> :  Caractere utilise pour representer les zones clairs dans la video </param>
/// <param name="strWhite"> :  Caractere utilise pour representer les zones clairs dans la video</param>
/// <param name="txtBGR"> : Tableau de 3 entiers (Blue, Green, Red) utilise pour determiner la couleur des caracteres</param>
/// <param name="bgBGR"> : Tableau de 3 entiers (Blue, Green, Red) utilise pour determiner la couleur du fond</param>
/// <param name="thresholdBW"> : Nombre entier pour le seuillage de la video</param>
/// <param name="isMute"> : Entier representant l'absence ou non d'une piste audio dans la video de sortie (1 si abscence d'audio)</param>
/// <returns>Nombre entier indicateur de la reussite de l'exportation (1 si oui, 0 sinon) </returns>
int videoToASCIIvideo(String inPath, String outPath, String strBlack, String strWhite, Scalar txtBGR, Scalar bgBGR, int thresholdBW, int isMute);



#endif // !VIDEO2ASCII

