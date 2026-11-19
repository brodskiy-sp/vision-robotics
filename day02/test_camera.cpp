
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>

int main()
{
    const int width = 704;
    const int height = 576;
    const int frameSize = width * height * 3 / 2;

    std::ifstream file(
        "C:/platform-tools/day05.nv12",
        std::ios::binary
    );

    if (!file) {
        std::cerr << "Cannot open camera file\n";
        return 1;
    }

    std::vector<unsigned char> data(frameSize);
    file.read(
        reinterpret_cast<char*>(data.data()),
        frameSize
    );

    if (file.gcount() != frameSize) {
        std::cerr << "Not enough data for one frame\n";
        return 1;
    }

    cv::Mat nv12(height * 3 / 2, width, CV_8UC1,
                 data.data());

    cv::Mat bgr;
    cv::cvtColor(nv12, bgr, cv::COLOR_YUV2BGR_NV12);

    if (cv::imwrite("camera_test.png", bgr))
        std::cout << "Saved camera_test.png\n";

    return 0;
}
