#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include "img2textart.hpp"
#include "video2ascii.hpp"

using namespace cv;
using namespace std;


string fileFindName(string path) {
    string fileName = "";

    //Decoupage du nom du chemin en fonction des anti-slashs et des points :
    int fileNameStart = path.find_last_of('\\');
    if (fileNameStart != -1)
        fileName += path.substr(fileNameStart+1, path.length());
    else
        fileName += path.substr(0, path.length());

    fileName = fileName.substr(0, fileName.find_last_of('.'));

    return fileName;
}


int videoToASCIIvideo(string fileName, String strBlack, String strWhite, int thresholdBW, bool audio = true) {
    //Importation de la video :
    VideoCapture videoImport(fileName);

    string name = fileFindName(fileName);
    if (!videoImport.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    //Creation de la video textArt (avec des proprietes que la video importee) : 
    double videoProperties[3] = { videoImport.get(CAP_PROP_FRAME_WIDTH), videoImport.get(CAP_PROP_FRAME_HEIGHT), videoImport.get(CAP_PROP_FPS)};
    VideoWriter videoExport("out/" + name + "_textaRT.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), videoProperties[2], Size(videoProperties[0], videoProperties[1]), false);
    
    int count = 0;

    //Conversion de chaque frame en image textArt et ecriture dans la video d'export :
    while (1) {
        Mat frame;
        videoImport >> frame;
        count++;
        if (!frame.empty()) {
            cout << count << "\n";
            vector<vector<String>> ASCII = matToASCII(frame, strWhite, strBlack, thresholdBW);
            Mat frameASCII = ASCIItoMat(ASCII);
            
            videoExport.write(frameASCII);
        }
        else break;
    }
    videoExport.release();
    videoImport.release();
    
	return 0;
}