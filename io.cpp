#include "io.hpp"

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string srcFilename;

Mat imgRead(char *filename) {
    Mat image = imread(filename);
    if (!image.data) {
        return Mat();
    }
    return image;
}

Mat imgCreate(Mat &srcImg, double factorN) {
    int imgRow = srcImg.rows;
    int imgCol = srcImg.cols;
    Mat outImg = Mat();
    outImg.create((int) (imgRow * factorN), (int) (imgCol * factorN), srcImg.type());
    return outImg;
}

int imgSave(const Mat &image, const string &filename) {
    int i = srcFilename.rfind('.');
    int j = srcFilename.rfind('/');
    string name = srcFilename.substr(0, j) + "/output/" + filename + srcFilename.substr(i);
    imwrite(name, image);
    return 0;
}

int imgShow(const string &winname, Mat &img) {
    namedWindow(winname);
    imshow(winname, img);
    waitKey(1000);
    return 0;
}

int pixelSaturation(double value) {
    if (value < 0) {
        return 0;
    } else if (value > 255) {
        return 255;
    } else {
        return (int) round(value);
    }
}

int pixelSaturation(int value) {
    if (value < 0) {
        return 0;
    } else if (value > 255) {
        return 255;
    } else {
        return value;
    }
}

double bicubic_sw(double x) {
    const double a = -0.5;
    double x_abs = abs(x);
    double sw = 0;
    if (x_abs <= 1) {
        sw = (a + 2) * pow(x_abs, 3) - (a + 3) * pow(x_abs, 2) + 1;
    } else if (x_abs < 2) {
        sw = a * pow(x_abs, 3) - 5 * a * pow(x_abs, 2) + 8 * a * x_abs - 4 * a;
    } else {
        sw = 0;
    }
    return sw;
}