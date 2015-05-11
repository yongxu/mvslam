#include "opencv2/opencv.hpp"

cv::Mat K, cam_matrix;
cv::Mat Kinv;
cv::Mat distortion_coeff;

void readCamCali(){

	cv::FileStorage fs;
	fs.open("./camera.yml", cv::FileStorage::READ);
	fs["camera_matrix"] >> cam_matrix;
	fs["distortion_coefficients"] >> distortion_coeff;

	K = cam_matrix;
	cv::invert(K, Kinv);
}