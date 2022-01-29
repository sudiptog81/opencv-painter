#include <bits/stdc++.h>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

void findColor(Mat img,
               int hmin, int smin, int vmin,
               int hmax, int smax, int vmax)
{
  Mat _img, _masked;

  cvtColor(img, _img, COLOR_BGR2HSV);

  Scalar lower(hmin, smin, vmin);
  Scalar upper(hmax, smax, vmax);

  inRange(_img, lower, upper, _masked);

  cout << hmin << "," << smin << "," << vmin << ","
       << hmax << "," << smax << "," << vmax << endl;

  imshow("Image", img);
  imshow("Mask", _masked);
}

int main()
{
  Mat img;
  VideoCapture cap(0);
  vector<vector<int>> drawnPoints;
  int hmin = 0, smin = 0, vmin = 0;
  int hmax = 179, smax = 255, vmax = 255;

  namedWindow("Trackbars", (640, 200));
  createTrackbar("Hue Min", "Trackbars", &hmin, 179);
  createTrackbar("Hue Max", "Trackbars", &hmax, 179);
  createTrackbar("Sat Min", "Trackbars", &smin, 255);
  createTrackbar("Sat Max", "Trackbars", &smax, 255);
  createTrackbar("Val Min", "Trackbars", &vmin, 255);
  createTrackbar("Val Max", "Trackbars", &vmax, 255);

  while (true)
  {
    cap.read(img);
    findColor(img, hmin, smin, vmin, hmax, smax, vmax);
    waitKey(1);
  }
}
