#include <opencv2/opencv.hpp>
#include <conio.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <opencv2/geometry.hpp>

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
int frameNumber = 1;
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
cv::inRange(hsv, cv::Scalar(30,50,50), cv::Scalar(85, 255, 255),mask);
cv::bitwise_and(frame, frame, greenOnly, mask);
std::vector<std::vector<cv::Point>> contours;

cv::findContours(
    mask,
    contours,
    cv::RETR_EXTERNAL,
    cv::CHAIN_APPROX_SIMPLE
);

if (!contours.empty())
{
    int largestIndex = 0;
    double largestArea = 0.0;

    for (int i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);

        if (area > largestArea)
        {
            largestArea = area;
            largestIndex = i;
        }

    }

    std::cout << "Largest contour area: "
              << largestArea << std::endl;
cv::Moments M = cv::moments(contours[largestIndex]);

	if (M.m00 > 0)
	{
		int centerX = static_cast<int>(M.m10 / M.m00);
		int centerY = static_cast<int>(M.m01 / M.m00);

	cv::circle(
		frame,
		cv::Point(centerX, centerY),
		12,
		cv::Scalar(0, 0, 255),
		-1
		);

		std::cout << "Object center: "
		<< centerX << ", "
		<< centerY << std::endl;

		std::cout << "Frame: " << frameNumber
                << " | Center: "
                << centerX << ", " << centerY
                << std::endl;
	}

}

std::cout << "Contours found: " << contours.size() << std::endl;
if (!maskSaved)
{
    cv::imwrite("green_only.png", greenOnly);
    cv::imwrite("original_frame.png", frame);
    cv::imwrite("green_mask.png", mask);
    cv::imwrite("tracked_frame.png", frame);
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
frameNumber++;
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
