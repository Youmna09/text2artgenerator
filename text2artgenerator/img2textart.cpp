#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include "img2textart.hpp"


using namespace cv;
using namespace std;



void matCopy(Mat &canvas, Mat &tile, int posx, int posy) {
	//Copier la tuile dans une zone delimite dans l'image :
	tile.copyTo(canvas({Range(posy, posy + tile.rows), Range(posx, posx + tile.cols)}));
}


vector<vector<String>> matToASCII(Mat img, String strWhite, String strBlack, int thresholdBW) {
		//Conversion de l'image en noir et blanc :
		cvtColor(img, img, COLOR_RGB2GRAY);

		//Redimensionner l'image a un dixieme de sa taille :
		int width = img.cols / 10;
		int height = img.rows / 10;
		resize(img, img, Size(width, height));

		//Creation et remplissage du tableau 2D :
		vector<vector<String>> ASCII;
		vector<String> row;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x <width ; x++) {
				//Determiner le caractere utilise en fonction de la valeur du pixel par rapport au seuillage :
				if (img.at<uchar>(Point(x, y)) < thresholdBW) row.push_back(strBlack);
				else row.push_back(strWhite);
			}
			ASCII.push_back(row);
			row = {};
		}
		return ASCII;
}


Mat ASCIItoMat(vector<vector<String>> ASCII, Scalar bgBGR, Scalar txtBGR) {
	//Creation de la matrice "toile" representant le tableau :
	int width = ASCII[0].size();
	int height = ASCII.size();
	Mat matASCII = Mat::zeros(Size(width*10, height  * 10), CV_8UC3);
	
	//Creation de la matrice "tuile" : 
	Mat tile = Mat::zeros(Size(10, 10), CV_8UC3);

	Scalar txtColor;
	Scalar bgColor;

	//Collage des matrices "tuile" representant chaque lettre du tableau 2D dans la "toile" :
	for (int y = 0; y < matASCII.rows; y+=10) {
		for (int x = 0; x < matASCII.cols; x+=10) {
			//Choix des couleurs de police et de fond :
			tile.setTo(bgBGR);
			putText(tile, ASCII[y/10][x/10], Point(1, 8), FONT_HERSHEY_COMPLEX, 0.4, txtBGR);
			matCopy(matASCII, tile, x, y);
		}
	}
	return matASCII;

}

