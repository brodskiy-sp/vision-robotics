
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>

int main()
{
    const int width = 704;
    const int height = 576;
    const int frameSize = width * height * 4;

    std::ifstream file(
        "C:/platform-tools/test.xr24",
        std::ios::binary
    );

    if (!file) {
        std::cerr << "Cannot open test.xr24\n";
        return 1;
    }

    std::vector<unsigned char> data(frameSize);
    file.read(
        reinterpret_cast<char*>(data.data()),
        frameSize
    );

    if (file.gcount() != frameSize) {
        std::cerr << "Incorrect frame size\n";
        return 1;
    }

    cv::Mat bgrx(height, width, CV_8UC4, data.data());
    cv::Mat bgr;

    cv::cvtColor(bgrx, bgr, cv::COLOR_BGRA2BGR);

    if (cv::imwrite("camera_xr24.png", bgr))
        std::cout << "Saved camera_xr24.png\n";

    return 0;
}
