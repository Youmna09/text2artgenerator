#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <FL/Fl_Window.H>
#include <FL/Fl_Output.H>
#include "img2textart.hpp"
#include "video2ascii.hpp"


using namespace cv;
using namespace std;

string fileFindName(string path) {
    string fileName = "";
    //Decoupage du nom du chemin en fonction des anti-slashs  :
    int fileNameStart = path.find_last_of('/');
    if (fileNameStart != -1)
        fileName += path.substr(fileNameStart+1, path.length());
    else
        fileName += path.substr(0, path.length());
    return fileName;
}


int videoToASCIIvideo(String inFile, String outFile, String strBlack, String strWhite, Scalar txtBGR, Scalar bgBGR, int thresholdBW, int isMute) {
    //Importation de la video : 
    VideoCapture videoImport(inFile);
    if (!videoImport.isOpened()) return -1;

    string inName = fileFindName(inFile);
    string inPath = inFile.substr(0, inPath.size()-inName.size());

    //Creation de la video textArt (avec des proprietes que la video importee) : 
    string outName = fileFindName(outFile);
    string outPath = outFile.substr(0, outFile.size()-outName.size());
    double videoProperties[3] = { videoImport.get(CAP_PROP_FRAME_WIDTH), videoImport.get(CAP_PROP_FRAME_HEIGHT), videoImport.get(CAP_PROP_FPS)};
    VideoWriter videoExport(outFile + "video.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), videoProperties[2], Size(videoProperties[0], videoProperties[1]), true);

    //Conversion de chaque frame en image textArt et ecriture dans la video d'export :
    int count = 0;
    cout << "Conversion des images de la video : \n";
    while (1) {
        Mat frame;
        videoImport >> frame;
       
        if (!frame.empty()) {
            count++;
            vector<vector<String>> ASCII = matToASCII(frame, strWhite, strBlack, thresholdBW);
            Mat frameASCII = ASCIItoMat(ASCII, bgBGR, txtBGR);
            videoExport.write(frameASCII);
            cout << "Image " << count << "/" << videoImport.get(CAP_PROP_FRAME_COUNT) << "  : convertie\n";
        }
        else break;
    }
    videoExport.release();
    videoImport.release();

    
    string c;
    if (isMute == 1) {
        cout << "Ajout de l'audio et conversion de la video : \n";
        //Ajout de l'audio (audio de la video original ou piste vide generee par ffmpeg) :
        c = "ffmpeg -i " + inFile + " -vn " + outFile + "audio.wav && ffmpeg -i " + outFile + "video.avi" + " -i " + outFile + "audio.wav -map 0 -map 1:a -c:v copy -shortest " + outFile; 
    }
    else c = "ffmpeg -i " + outFile + "video.avi -f lavfi -i anullsrc=channel_layout=stereo:sample_rate=44100 -c:v copy -shortest " + outFile;
    const char* command = c.c_str();
    if (system(command) != 0) {
        cout << "Conversion de la video :\n";
        c = "cd " + outPath + " && del " + outName + "video.avi; del " + outName + "audio.wav";
        system(c.c_str());
        return -2;
    }
    c = "cd " + outPath + " && del " + outName + "video.avi; del " + outName + "audio.wav";
    system(c.c_str());
	return 0;
}