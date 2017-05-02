
#include <string>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


char rgbOrHsv(string prompt){
    char option = ' ';
    bool choosing = true;
    
    do{
        cout << prompt << endl;
        cin >> option;
        switch(option){
            case 'r':
            case 'R':
                option = 'r';
                choosing = false;
                break;
            case 'h':
            case 'H':
                option = 'h';
                choosing = false;
                break;
            default:
                break;
        }
    }while(choosing);
    
    return option;
}

char chooseRGBN(string prompt){
    char option = ' ';
    bool choosing = true;
    
    do{
        cout << prompt << endl;
        cin >> option;
        switch(option){
            case 'r':
            case 'R':
                option = 'x';
                choosing = false;
                break;
            case 'g':
            case 'G':
                option = 'y';
                choosing = false;
                break;
            case 'b':
            case 'B':
                option = 'z';
                choosing = false;
                break;
            case '0':
                option = '0';
                choosing = false;
                break;
            case '1':
                option = '1';
                choosing = false;
                break;
            default:
                break;
        }
    }while(choosing);
    
    return option;
}

char chooseHSVN(string prompt){
    char option = ' ';
    bool choosing = true;
    
    do{
        cout << prompt << endl;
        cin >> option;
        switch(option){
            case 'h':
            case 'H':
                option = 'x';
                choosing = false;
                break;
            case 's':
            case 'S':
                option = 'y';
                choosing = false;
                break;
            case 'v':
            case 'V':
                option = 'z';
                choosing = false;
                break;
            case '0':
                option = '0';
                choosing = false;
                break;
            case '1':
                option = '1';
                choosing = false;
                break;
            default:
                break;
        }
    }while(choosing);
    
    return option;
}


int main(int argc, const char * argv[]){
    
    string imagePath;
    
    if(argc == 2){
        imagePath = argv[1];
    }else{
        cout << "Enter filename: ";
        getline(cin, imagePath);
    }
    
    Mat inputImage;
    inputImage = imread(imagePath.c_str(), CV_LOAD_IMAGE_COLOR);
    
    if(!inputImage.data){
        cout << "No image data." << endl;
        return -1;
    }
    
    cout << "Loaded Image: " << imagePath << endl;
    
    //imshow("Input", inputImage);
    
    //waitKey(10);
    
    //destroyWindow("Input");
    
    char fromOption = rgbOrHsv("From RGB or HSV? (r,h)");
    char toOption = rgbOrHsv("To RGB or HSV? (r,h)");
    
    char XshouldBeFrom, YshouldBeFrom, ZshouldBeFrom;
    
    string toStr;
    
    Mat fromImage;
    
    if(fromOption == 'r'){
        toStr = "RGB";
        cvtColor(inputImage, fromImage, COLOR_BGR2RGB);
    }else{
        toStr = "HSV";
        cvtColor(inputImage, fromImage, COLOR_BGR2HSV);
    }

    if(toOption == 'r'){
        toStr = "RGB";
    }else{
        toStr = "HSV";
    }
    
    if(fromOption == 'r'){
        XshouldBeFrom = chooseRGBN(toStr.substr(0,1)+" from (r,g,b,0,1)");
        YshouldBeFrom = chooseRGBN(toStr.substr(1,1)+" from (r,g,b,0,1)");
        ZshouldBeFrom = chooseRGBN(toStr.substr(2,1)+" from (r,g,b,0,1)");
    }else{
        XshouldBeFrom = chooseHSVN(toStr.substr(0,1)+" from (h,s,v,0,1)");
        YshouldBeFrom = chooseHSVN(toStr.substr(1,1)+" from (h,s,v,0,1)");
        ZshouldBeFrom = chooseHSVN(toStr.substr(2,1)+" from (h,s,v,0,1)");
    }
    
    cout << "Processing..." << endl;
    
    Mat result(fromImage.rows, fromImage.cols, CV_8UC3);
    
    for(int i = 0; i < fromImage.rows; i++){
        for(int j = 0; j < fromImage.cols; j++){
            Vec3b fromXYZ = fromImage.at<Vec3b>(i, j);
            Vec3b toXYZ(0, 0, 0);
            if(fromOption == 'h'){
                fromXYZ[0] = (unsigned char)(fromXYZ[0] * (255/180.0));
            }
            switch (XshouldBeFrom) {
                case 'x': toXYZ[0] = fromXYZ[0]; break;
                case 'y': toXYZ[0] = fromXYZ[1]; break;
                case 'z': toXYZ[0] = fromXYZ[2]; break;
                case '0': toXYZ[0] = 0; break;
                case '1': toXYZ[0] = 255; break;
                default: break;
            }
            switch (YshouldBeFrom) {
                case 'x': toXYZ[1] = fromXYZ[0]; break;
                case 'y': toXYZ[1] = fromXYZ[1]; break;
                case 'z': toXYZ[1] = fromXYZ[2]; break;
                case '0': toXYZ[1] = 0; break;
                case '1': toXYZ[1] = 255; break;
                default: break;
            }
            switch (ZshouldBeFrom) {
                case 'x': toXYZ[2] = fromXYZ[0]; break;
                case 'y': toXYZ[2] = fromXYZ[1]; break;
                case 'z': toXYZ[2] = fromXYZ[2]; break;
                case '0': toXYZ[2] = 0; break;
                case '1': toXYZ[2] = 255; break;
                default: break;
            }
            if(toOption == 'h'){
                fromXYZ[0] = (unsigned char)(toXYZ[0] * (180/255.0));
            }
            result.at<Vec3b>(i, j) = toXYZ;
        }
    }
    
    Mat outputImage;
    
    if(toOption == 'r'){
        cvtColor(result, outputImage, COLOR_RGB2BGR);
    }else{
        cvtColor(result, outputImage, COLOR_HSV2BGR);
    }
    
    imwrite("converted.png", outputImage);

    
}
