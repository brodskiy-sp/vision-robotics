#include <opencv2/opencv.hpp>
#include <conio.h>
#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
    std::cout << "Program started" << std::endl;

    if (argc < 2)
{
    std::cerr << "Usage: rtsp_test <RTSP_URL>" << std::endl;
    return 1;
}

const std::string url = argv[1];

    cv::VideoCapture cap(url, cv::CAP_FFMPEG);

    if (!cap.isOpened())
    {
        std::cerr << "ERROR: Cannot open RTSP stream" << std::endl;
        return 1;
    }

    std::cout << "RTSP connected!" << std::endl;
    cv::Mat frame;
    cv::Mat hsv;
    cv::Mat mask;
    cv::Mat greenOnly;
double processingTime = 0.0;
int framesProcessed = 0;
auto start = std::chrono::steady_clock::now();
bool maskSaved = false;
while (cap.read(frame))
{

    if (frame.empty())
    {
        std::cerr << "Empty frame!" << std::endl;
        break;
    }
    auto processStart = std::chrono::steady_clock::now();

cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
cv::inRange(hsv, cv::Scalar(35,50,50), cv::Scalar(85, 255, 255),mask);
cv::bitwise_and(frame, frame, greenOnly, mask);
if (!maskSaved)
{
    cv::imwrite("green_only.png", greenOnly);
    cv::imwrite("original_frame.png", frame);
    cv::imwrite("green_mask.png", mask);
    maskSaved = true;
    std::cout << "Mask saved!" << std::endl;
}


auto processEnd = std::chrono::steady_clock::now();
processingTime +=
    std::chrono::duration<double>(
        processEnd - processStart
    ).count();
    std::cout << "Frame received!" << std::endl;
    framesProcessed++;
    if (_kbhit())
{
    char key = _getch();

    if (key == 'q' || key == 'Q')
    {
        break;
    }
}

}
auto end = std::chrono::steady_clock::now();

double elapsedSeconds =
    std::chrono::duration<double>(end - start).count();

double fps = framesProcessed / elapsedSeconds;

double averageProcessingMs =
    processingTime * 1000.0 / framesProcessed;

std::cout << "Average processing time: "
          << averageProcessingMs << " ms" << std::endl;

std::cout << "Elapsed time: " << elapsedSeconds << " seconds" << std::endl;
std::cout << "Average FPS: " << fps << std::endl;
    std::cout << "Total frames received: "
          << framesProcessed << std::endl;

    cap.release();

    return 0;
}
