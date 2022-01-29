#include <bits/stdc++.h>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

Point getTrackpoint(Mat img)
{
  Point poi(0, 0);
  double area = 0;
  vector<Vec4i> hierarchy;
  vector<vector<Point>> contours;

  findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

  for (int i = 0; i < contours.size(); i++)
  {
    double _area = contourArea(contours.at(i));

    if (_area > 10 && _area > area)
    {
      vector<vector<Point>> conPoly(contours.size());
      vector<Rect> boundingBox(contours.size());

      double _peri = arcLength(contours.at(i), true);
      approxPolyDP(contours.at(i), conPoly.at(i), .02 * _peri, true);
      boundingBox.at(i) = boundingRect(conPoly.at(i));

      poi.x = boundingBox.at(i).x + boundingBox.at(i).width / 2;
      poi.y = boundingBox.at(i).y;
    }
  }

  return poi;
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

void drawOnCanvas(Mat img, vector<vector<int>> points)
{
  for (int i = 0; i < points.size(); i++)
  {
    circle(img, Point(points.at(i)[0], points.at(i)[1]), 5, Scalar(0, 255, 0), FILLED);
  }
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
    Point _poi = getTrackpoint(_img);

    if (_poi.x != 0 && _poi.y != 0)
      drawnPoints.push_back({_poi.x, _poi.y});

    drawOnCanvas(img, drawnPoints);

    imshow("Image", img);
    waitKey(1);
  }
}
