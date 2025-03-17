#include <iostream>
#include "video2ascii.hpp"

using namespace std;
using namespace cv;

int main7() {
	cout << "Text2Art Generator - transformez vos videos en videos en textArt ! \n";

	string video ="";

	do
	{
		cout << "Saisissez la video choisie (ou deplacez - la dans la console) \n (Attention : pas d'espace autorise) : ";
		cin >> video;
	} while (video == "");
	

	String strBlack = "";

	do
	{
		cout << "Entrez le caractere pour les zones noires (1 caractere seulement) : ";
		cin >> strBlack;
	} while (strBlack.length() !=1);
	

	String strWhite = "";
	do
	{
		cout << "Entrez le caractere pour les zones blanches (1 caractere seulement) : ";
		cin >> strWhite;
	} while (strWhite.length()!=1);
	

	int thresholdBW = -1;
	do {
		cout << "Entrez le seuil pour la video (nombre entre 0 et 255) : ";
		cin >> thresholdBW;
	} while (thresholdBW < 0 || thresholdBW > 255);
	
	String withAudio = "";
	bool isMute;
	do {
		cout << "Souhaitez-vous ajouter l'audio original (tapez y ou n) : ";
		cin >> withAudio;
		if (withAudio == "y") isMute = false;
		else isMute = true;
	} while (withAudio.length() != 1);

	int success = videoToASCIIvideo(video, strBlack, strWhite, Scalar(255,0,0), Scalar(0, 0, 255), thresholdBW, isMute);

	//Mat img = imread("test.png");
	//vector<vector<String>> ascii = matToASCII(img, "0", "1", 127);
	//Mat mat2 = ASCIItoMat(ascii);
	//imwrite("output.png", mat2);
	system("pause");

	return 0;
}