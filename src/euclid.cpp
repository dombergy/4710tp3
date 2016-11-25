
#include "utils.hpp"

float euclid(cv::Mat matrix1, cv::Mat matrix2) {
	CV_Assert(matrix1.size() == matrix2.size());

	float distance = 0;

	for (int i = 0; i < matrix1.rows; ++i) {
		for (int j = 0; j < matrix1.cols; ++j) {
			distance += sqrt(pow(matrix1.at<float>(i, j) - matrix2.at<float>(i, j), 2));
		}
	}

	return distance;
}