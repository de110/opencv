#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void detectHScolor(const Mat&image, double minHue, double maxHue, double minSat, double maxSat, Mat&mask) {
	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);

	vector<Mat> channels;
	split(hsv, channels);

	Mat mask1;
	threshold(channels[0], mask1, maxHue, 255, THRESH_BINARY_INV);
	Mat mask2;
	threshold(channels[0], mask2, minHue, 255, THRESH_BINARY);
	Mat hueMask;
	if (minHue < maxHue) hueMask = mask1 & mask2;
	else hueMask = mask1 | mask2;

	threshold(channels[1], mask1, maxSat, 255, THRESH_BINARY_INV);
	threshold(channels[1], mask2, minSat, 255, THRESH_BINARY);

	Mat satMask;
	satMask = mask1 & mask2;

	mask = hueMask & satMask;
}

int main()
{
	Mat image = imread("D:\image.jpg");
	Mat mask;
	detectHScolor(image, 0, 15, 160, 255, mask);
	Mat detected(image.size(), CV_8UC3, Scalar(0, 0, 0));
	image.copyTo(detected, mask);
	namedWindow("Image");
	imshow("Image", image);
	namedWindow("Mask");
	imshow("Mask", mask);
	namedWindow("Detected");
	imshow("Detected", detected);

	waitKey(0);

}