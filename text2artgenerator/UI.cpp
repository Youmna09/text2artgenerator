#include <iostream>
#include <string>
#include <map>
#include <FL/x.H>
#include "UI.hpp"
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_PNG_Image.H>
#include <Fl/Fl_ask.H>
#include <Fl/Fl_Group.H>
#include "video2ascii.hpp"

using namespace cv;
using namespace std;

//Tableaux associatifs pour stocker les valeurs entrees et les reutiliser au sein des fonction callbacks :
map<string, string> strData = { {"InputFile", ""}, {"ExportFile", ""}, {"StrBlack", ""}, {"StrWhite", ""} };
map<string, Scalar> doubleData = { {"TextBGR", Scalar(0,0,0)}, {"bgBGR", Scalar(255,255,255)}, {"Threshold", 0}, {"WithAudio",  0} };


#define DEFAULT_COLOR (FL_FREE_COLOR)
#define OUTPUT_FILE (".mkv")
#define IDI_ICON1 101


//Fonctions callback :
void loadFile(Fl_Widget*, void* txtfield) {
	//Generer une fenetre de selection de fichiers :
	char* filePath = fl_file_chooser("Ouvrir un fichier", "*{.avi,.vmv,.mp4,.mkv}", "");
	if (!filePath == NULL) {
		//Afficher le chemin du fichier selectionne dans un champ de texte :
		Fl_Output* field = (Fl_Output*)txtfield;
		field->static_value(filePath);
		field->redraw();

		//Stockage des valeurs :
		strData["InputFile"] = field->value();
	}
}

void saveFile(Fl_Widget*, void* txtfield) {
	//Generer une fenetre de sauvegarde dans un fichier :
	char* f = fl_file_chooser("Sauvegarder dans un dossier", "*{.mkv}", "");
	if (!f == NULL) {
		//Afficher le chemin du fichier cree dans un champ de texte (ajouter l'extension .mkv si besoin) :
		string path = (string)f;
		if (path.substr(path.size()-4, path.size() - 1) != ".mkv") {
			path += OUTPUT_FILE;
		}
		const char* filePath = path.c_str();
		Fl_Output* field = (Fl_Output*)txtfield;
		field->static_value(filePath);
		field->redraw();

		//Stockage des valeurs :
		strData["ExportFile"] = field->value();
	}
}

void colorWindow(Fl_Widget*, void *box) {
	//Variables pour stocker les valeurs des caneaux r, g, b et pour affecter la couleur choisie dans la boite :
	uchar r, g, b;
	Fl_Color color = DEFAULT_COLOR;

	//Generer une fenetre de selection de couleurs :
	if (!fl_color_chooser("Couleur", r, g, b, 0)) return;
	
	//Affectation de la couleur choisie dans les variables et affichage celle-ci dans la boite :
	Fl::set_color(color, r, g, b);
	Fl_Box* bx = (Fl_Box*)box;
	bx->color(color);
	bx->redraw();

	//Stockage des valeurs (en fonction de quelle boite a ete affectee) :
	double R = (double)r; 
	double G = (double)g; 
	double B = (double)b;
	if (bx->y() == 200) doubleData["TextBGR"] = Scalar(B, G, R);
	else doubleData["bgBGR"] = Scalar(B, G, R);
}

void textStr(Fl_Widget*, void* strfield) {
	//Stockage des valeurs (en fonction de quel champ de texte est concerne) : 
	Fl_Input* txt = (Fl_Input*)strfield;
	if (txt->y() == 120) {
		strData["StrBlack"] = txt->value();
	}
	else {
		strData["StrWhite"] = txt->value();
	}
}

void threshold(Fl_Widget*, void* slider) {
	//Stockage des valeurs :
	Fl_Value_Slider* sl = (Fl_Value_Slider*)slider;
	doubleData["Threshold"] = sl->value();
}

void audio(Fl_Widget*, void* check) {
	//Stockage des valeurs :
	Fl_Check_Button* c = (Fl_Check_Button*)check;
	doubleData["WithAudio"] = c->value();
}

void display(Fl_Widget*, void *box) {
	//Image utilisee pour l'apercu :
	Mat img = imread("../../text2artgenerator/imgs/example.png");

	//Creation de l'image textART a partir des valeurs stockes : 
	vector<vector<String>> ASCII = matToASCII(img, strData["StrBlack"], strData["StrWhite"], doubleData["Threshold"][0]);
	Mat display = ASCIItoMat(ASCII, doubleData["bgBGR"], doubleData["TextBGR"]);
	imwrite("../../text2artgenerator/imgs/display.png", display);
	
	//Affichage de l'image dans une boite (aux memes dimensions que l'image) :
	Fl_Box* bx = (Fl_Box*)box;
	Fl_PNG_Image* example = new Fl_PNG_Image("../../text2artgenerator/imgs/display.png");
	bx->image(example);
	bx->redraw();
}

void exportVideo(Fl_Widget*, void* group) {
	//Verification de la presence du fichier d'entree et de sortie :
	if (strData["InputFile"] == "" || strData["ExportFile"] == "") fl_alert("Erreur : le fichier importe ou a exporter n'existe pas");

	else {
		//Verification de la presence de doublon entre un fichier existant et le fichier de sortie :
		int exportFile;
		string c = "cd " + strData["ExportFile"].substr(0, strData["ExportFile"].size() - fileFindName(strData["ExportFile"]).size() - 1);
		c += " && dir " + fileFindName(strData["ExportFile"]);
		if (system(c.c_str()) == 0) {
			string m = fileFindName(strData["ExportFile"]) + " existe deja. Voulez-vous le remplacer ?";

			//Supression du fichier existant (si demandee par l'utilisateur) :
			if (fl_choice(m.c_str(), "OK", "Annuler", 0) == 0) {
				c += "&& del " + fileFindName(strData["ExportFile"]);
				system(c.c_str());
				exportFile = 1;
			}
			else exportFile = 0; //Sinon : exportation annulee

		}

		//Conversion du fichier d'entree en video textART puis exportation dans le fichier de sortie : 
		else exportFile = 1;
		while (exportFile == 1) {
			int choice = fl_choice("L'exportation va bientot commencer. Vous pouvez suivre la progression via la console d'execution.", "OK", "Annuler", 0);
			if (choice != 0) exportFile = 2; //Sinon : exportation annulee
			else exportFile = videoToASCIIvideo(strData["InputFile"], strData["ExportFile"], strData["StrBlack"], strData["StrWhite"], doubleData["TextBGR"], doubleData["bgBGR"], doubleData["Threshold"][0], doubleData["WithAudio"][0]);

			//Reecriture des valeurs dans le champs de texte et les boites de couleurs
			// (pour eviter les bugs d'affichage apres l'exportation) :
			Fl_Group* grp = (Fl_Group*)group;
			Fl_Output* inPath = (Fl_Output*)grp->child(0);
			Fl_Output* outPath = (Fl_Output*)grp->child(1);
			Fl_Box* txtColor = (Fl_Box*)grp->child(2);
			Fl_Box* bgColor = (Fl_Box*)grp->child(3);

			Fl_Color txtRGB = DEFAULT_COLOR;
			Fl::set_color(txtRGB,(uchar)doubleData["TextBGR"][2], (uchar)doubleData["TextBGR"][1], (uchar)doubleData["TextBGR"][0]);

			inPath->static_value(strData["InputFile"].c_str());
			outPath->static_value(strData["ExportFile"].c_str());
			txtColor->color(txtRGB);

			inPath->redraw();
			outPath->redraw();
			txtColor->redraw();

			//Affichage de message en fonction de la reussite ou non de l'exportation :
			if (exportFile == 0) fl_alert("Exportation reussie");
			if (exportFile == -1) fl_alert("Erreur : video source introuvable");
			if (exportFile == -2) fl_alert("Erreur : encodage impossible");
		}
	}
}

void UIWindow(Fl_Window* window) {
	//Ajout d'une icone sur la fenetre : 
	window->icon((char*)LoadIcon(fl_display, MAKEINTRESOURCE(IDI_ICON1)));

	//Champ de texte affichant le chemin du fichier d'entree et bouton pour selectionner un fichier :
	Fl_Output* openFilePath = new Fl_Output(10, 27, 420, 20);
	Fl_Button* openButton = new Fl_Button(440, 20, 50, 30, "Ouvrir");
	openButton->callback(loadFile, openFilePath);

	//Champ de texte affichant le chemin du fichier de sortie et bouton pour creer le fichier :
	Fl_Output* saveFilePath = new Fl_Output(10, 67, 350, 20);
	Fl_Button* saveButton = new Fl_Button(370, 60, 120, 30, "Sauvegarder sous");
	saveButton->callback(saveFile, saveFilePath);

	//Bouton check pour autoriser la presence de l'audio du fichier d'entree dans le fichir de sortie :
	Fl_Check_Button* audioButton = new Fl_Check_Button(10, 95, 15, 15, "Audio original");
	audioButton->align(FL_ALIGN_RIGHT);
	audioButton->callback(audio, audioButton);

	//Champs de texte pour entrer les caracters pour les zones sombres et claires : 
	Fl_Input* strBlack = new Fl_Input(10, 120, 30, 30, "Caractere pour les zones sombres");
	strBlack->align(FL_ALIGN_RIGHT);
	strBlack->maximum_size(1);
	strBlack->callback(textStr, strBlack);

	Fl_Input* strWhite = new Fl_Input(10, 160, 30, 30, "Caractere pour les zones claires");
	strWhite->align(FL_ALIGN_RIGHT);
	strWhite->maximum_size(1);
	strWhite->callback(textStr, strWhite);

	//Boutons pour selectioner les couleurs pour le texte et le fond et boites pour afficher les couleurs selectionnees :
	Fl_Button* textColor = new Fl_Button(10, 200, 140, 30, "Couleur de texte");
	Fl_Box* textColorDisplay = new Fl_Box(160, 200, 100, 30);
	textColorDisplay->box(FL_UP_BOX);
	textColorDisplay->color(0);
	textColor->callback(colorWindow, textColorDisplay);

	Fl_Button* bgColor = new Fl_Button(10, 240, 140, 30, "Couleur de fond");
	Fl_Box* bgColorDisplay = new Fl_Box(160, 240, 100, 30);
	bgColorDisplay->box(FL_UP_BOX);
	bgColorDisplay->color(255);
	bgColor->callback(colorWindow, bgColorDisplay);

	//Slider pour regler le seuillage de couleurs : 
	Fl_Value_Slider* thresholdSlider = new Fl_Value_Slider(10, 300, 250, 30, "Seuillage");
	thresholdSlider->type(FL_HOR_NICE_SLIDER);
	thresholdSlider->align(FL_ALIGN_TOP);
	thresholdSlider->bounds(0, 255);
	thresholdSlider->precision(0);
	thresholdSlider->callback(threshold, thresholdSlider);

	//Boite pour afficher l'apercu du textART qui sera genere dans le fichier de sortie et bouton pour le generer :
	Fl_Box* preview = new Fl_Box(290, 150, 200, 200);
	preview->box(FL_UP_BOX);
	Fl_Button* displayButton = new Fl_Button(10, 350, 120, 30, "Charger l'apercu");
	displayButton->callback(display, preview);

	//Regroupement de certaines donnees dans un groupe : 
	Fl_Group* dataGroup = new Fl_Group(0, 0, 500, 400, "");
	dataGroup->add(openFilePath);
	dataGroup->add(saveFilePath);
	dataGroup->add(textColorDisplay);

	//Bouton pour lancer la conversion et l'exportation du fichier d'entree en video textART dans le fichier de sortie :
	Fl_Button* generateButton = new Fl_Button(140, 350, 70, 30, "Exporter");
	generateButton->callback(exportVideo, dataGroup);

	window->end();
}
