#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat src, gray;
	src = imread("D:\\1.png");
	resize(src, src, Size(600, 400));
	cvtColor(src, gray, CV_BGR2GRAY);

	GaussianBlur(gray, gray, Size(9, 9), 2, 2);

	vector<Vec3f>circles;

	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 100, 50, 30, 0, 0);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		cout << "center:" << center << "\nradius" << radius << endl;
	}

	namedWindow("show", CV_WINDOW_AUTOSIZE);
	imshow("show", src);

	waitKey(0);
	return 0;
}