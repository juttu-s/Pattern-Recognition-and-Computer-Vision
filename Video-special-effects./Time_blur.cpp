/*
  Saikiran Juttu & Suriya Kasiyalan Siva
  Spring 2024
  01/27/2024
  CS 5330 Computer Vision
*/
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

double getTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = currentTime.time_since_epoch();

    // Extract seconds and microseconds
    long seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count() % 1000000;

    return seconds + microseconds / 1000000.0;
}
static int blur5x5_1(cv::Mat& src, cv::Mat& dst) {
    if (src.empty()) {
        return -1;  // Return error code if source image is empty
    }

    // Copy the source image to the destination image
    dst = src.clone();

    // Get image dimensions
    int rows = src.rows;
    int cols = src.cols;

    // Gaussian kernel
    int kernel[5][5] = { {1, 2, 4, 2, 1},
                        {2, 4, 8, 4, 2},
                        {4, 8, 16, 8, 4},
                        {2, 4, 8, 4, 2},
                        {1, 2, 4, 2, 1} };

    // Apply the blur filter to each color channel separately
    for (int i = 2; i < rows - 2; ++i) {
        for (int j = 2; j < cols - 2; ++j) {
            for (int c = 0; c < src.channels(); ++c) {
                int sum = 0;
                // Convolution with the 5x5 kernel
                for (int m = -2; m <= 2; ++m) {
                    for (int n = -2; n <= 2; ++n) {
                        sum += src.at<cv::Vec3b>(i + m, j + n)[c] * kernel[m + 2][n + 2];
                    }
                }
                // Update the destination pixel
                dst.at<cv::Vec3b>(i, j)[c] = sum / 100;  // Integer approximation of Gaussian
            }
        }
    }

    return 0;  // Return success code
}
static int blur5x5_2(cv::Mat& src, cv::Mat& dst) {
    if (src.empty()) {
        return -1;  // Return error code if source image is empty
    }

    // Copy the source image to the destination image
    dst = src.clone();

    // Get image dimensions
    int rows = src.rows;
    int cols = src.cols;

    // Separable 1x5 filters for vertical and horizontal blur
    int kernel[5] = { 1, 2, 4, 2, 1 };

    // Apply the horizontal blur filter
    for (int i = 0; i < rows; ++i) {
        for (int j = 2; j < cols - 2; ++j) {
            for (int c = 0; c < src.channels(); ++c) {
                int sum = 0;
                // Convolution with the 1x5 kernel horizontally
                for (int n = -2; n <= 2; ++n) {
                    sum += src.ptr<cv::Vec3b>(i)[j + n][c] * kernel[n + 2];
                }
                // Update the destination pixel
                dst.ptr<cv::Vec3b>(i)[j][c] = sum / 10;  // Integer approximation of Gaussian
            }
        }
    }

    // Apply the vertical blur filter
    for (int i = 2; i < rows - 2; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int c = 0; c < src.channels(); ++c) {
                int sum = 0;
                // Convolution with the 1x5 kernel vertically
                for (int m = -2; m <= 2; ++m) {
                    sum += dst.ptr<cv::Vec3b>(i + m)[j][c] * kernel[m + 2];
                }
                // Update the destination pixel
                dst.ptr<cv::Vec3b>(i)[j][c] = sum / 10;  // Integer approximation of Gaussian
            }
        }
    }

    return 0;  // Return success code
}


int main() {
    // Replace "your_image.jpg" with the path to your input image
    cv::Mat src = cv::imread("cathedral.jpeg");
    std::cout << "Width : " << src.cols << std::endl;
    std::cout << "Height: " << src.rows << std::endl;
    cv::Mat dst;
    if (src.empty()) {
        std::cerr << "Error loading image." << std::endl;
        return -1;
    }
    const int Ntimes = 25;
    double startTime1 = getTime();
    for (int i = 0; i < Ntimes; i++) {
        blur5x5_1(src, dst);
    }
    // end the timing
    double endTime1 = getTime();

    // compute the time per image
    double difference1 = (endTime1 - startTime1) / Ntimes;

    // print the results
    printf("Time per image (1): %.4lf seconds\n", difference1);
    // Save the result
    std::cout << "Width : " << dst.cols << std::endl;
    std::cout << "Height: " << dst.rows << std::endl;
    cv::imwrite("2D_blur_result.jpg", dst);
    cv::imshow("2D_blur_result.jpg", dst);
    
    double startTime2 = getTime();
    for (int i = 0; i < Ntimes; i++) {
      
        blur5x5_2(src, dst);
        
    }
    //end the timing
    double endTime2 = getTime();

    //compute the time per image
    double difference2 = (endTime2 - startTime2) / Ntimes;

    //print the results
    printf("Time per image (1): %.4lf seconds\n", difference2);
    //Save the result
    std::cout << "Width : " << dst.cols << std::endl;
    std::cout << "Height: " << dst.rows << std::endl;
    cv::imwrite("separable_blur_result.jpg", dst);
    cv::imshow("separable_blur_result.jpg", dst);
    cv::waitKey(0);
    return 0;
    
}
