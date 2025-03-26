#include <iostream>
#include <cctype>
#include <map>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_PNG_Image.H>
#include "video2ascii.hpp"
using namespace std;

#ifndef UI
#define UI

/// <summary>
/// Fonction callback generant une fenetre de selection de fichiers .avi, .vmv, .mp4 ou .mkv  et affiche le chemin du fichier selectionne dans un champ de texte
/// </summary>
/// <param name=""> : Fl_Widget* reference a l'element dans la fenetre qui declenchera l'appel de fonction</param>
/// <param name="txtfield"> : void* reference a l'element dans la fenetre qui affichera le chemin du fichier selectionne</param>
void loadFile(Fl_Widget*, void* txtfield);

/// <summary>
/// Fonction callback generant une fenetre de sauvegarde d'un fichier .mkv et affiche le chemin du fichier cree dans un champ de texte
/// </summary>
/// <param name=""> : Fl_Widget* reference a l'element dans la fenetre qui declenchera l'appel de fonction</param>
/// <param name="txtfield"> : void* reference a l'element dans la fenetre qui affichera le chemin du fichier cree</param>
void saveFile(Fl_Widget*, void* txtfield);

/// <summary>
/// Fonction callback generant une fenetre de selection de couleur et affichant la couleur selectionne dans une boite
/// </summary>
/// <param name=""> : Fl_Widget* reference a l'element dans la fenetre qui declenchera l'appel de fonction</param>
/// <param name="box"> : void* reference a l'element dans la fenetre qui affichera la couleur selectionnee</param>
void colorWindow(Fl_Widget*, void* box);

/// <summary>
/// Fonction callback permettant de stocker les valeurs ecrites dans un champ de texte (ici les caracteres pour les zones sombres et claires)
/// </summary>
/// <param name=""> : Fl_Widget* reference a l'element dans la fenetre qui declenchera l'appel de fonction</param>
/// <param name="strfield"> : void* reference a l'element dans la fenetre ou les valeurs a stocker proviennent</param>
void textStr(Fl_Widget*, void* strfield);

/// <summary>
/// Fonction callback permettant de stocker les valeurs generes (ici un nombre entier pour le seuillage de la video) 
/// </summary>
/// <param name=""> : Fl_Widget* reference a l'element dans la fenetre qui declenchera l'appel de fonction</param>
/// <param name="slider"> : void* reference a l'element dans la fenetre ou les valeurs a stocker proviennent</param>
void threshold(Fl_Widget*, void* slider);

/// <summary>
/// Fonction callback permettant de stocker les valeurs generes (ici un nombre entier pour la presence ou non de l'audio original dans le fichier de sortie) 
/// </summary>
/// <param name=""> : Fl_Widget* reference a l'element dans la fenetre qui declenchera l'appel de fonction</param>
/// <param name="check"> : void* reference a l'element dans la fenetre ou les valeurs a stocker proviennent</param>
void audio(Fl_Widget*, void* check);

/// <summary>
/// Fonction callback generant une image textART a partir des valeurs des couleurs de texte et de fond, des caracteres pour les zones sombres et claires et du seuillage
/// et affichant l'image generee dans une boite 
/// </summary>
/// <param name=""> : Fl_Widget* reference a l'element dans la fenetre qui declenchera l'appel de fonction</param>
/// <param name="box"> : void* reference a l'element dans la fenetre ou l'image generee sera affichee</param>
void display(Fl_Widget*, void* box);

/// <summary>
/// Fonction callback generant une video textART a partir du fichier importe, des valeurs des couleurs de texte et de fond, des caracteres pour les zones sombres et claires, du seuillage
/// et de la presence ou non de l'audio original et l'exporte dans le fichier de sortie
/// </summary>
/// <param name=""> : Fl_Widget* reference a l'element dans la fenetre qui declenchera l'appel de fonction</param>
void exportVideo(Fl_Widget*);

/// <summary>
/// Creer une fenetre offrant une interface pour generer des video textART
/// </summary>
/// <param name="window"> : Fl_Window* reference a la fenetre contenant tous les elements de l'application</param>
void UIWindow(Fl_Window* window);

#endif // !UI


