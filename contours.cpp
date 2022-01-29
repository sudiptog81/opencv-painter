#include <bits/stdc++.h>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

void drawBoundingBox(Mat img, Mat masked)
{
  vector<Vec4i> hierarchy;
  vector<vector<Point>> contours;

  findContours(masked, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

  for (int i = 0; i < contours.size(); i++)
  {
    double _area = contourArea(contours.at(i));

    if (_area > 20)
    {
      vector<vector<Point>> conPoly(contours.size());
      vector<Rect> boundingBox(contours.size());

      double _peri = arcLength(contours.at(i), true);
      approxPolyDP(contours.at(i), conPoly.at(i), .02 * _peri, true);
      boundingBox.at(i) = boundingRect(conPoly.at(i));

      drawContours(img, contours, i, Scalar(0, 255, 0), 2, LINE_AA);
    }
  }
}

Mat getMaskedImage(Mat img, vector<int> color)
{
  Mat _img, _masked;

  cvtColor(img, _img, COLOR_BGR2HSV);

  Scalar lower(color[0], color[1], color[2]);
  Scalar upper(color[3], color[4], color[5]);

  inRange(_img, lower, upper, _masked);

  return _masked;
}

int main()
{
  Mat img;
  VideoCapture cap(0);
  vector<vector<int>> drawnPoints;
  vector<int> color = {158, 132, 50, 179, 255, 255};

  while (true)
  {
    cap.read(img);
    Mat _img = getMaskedImage(img, color);
    drawBoundingBox(img, _img);
    imshow("Image", img);
    waitKey(1);
  }
}
