#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/geometry.hpp>
#include <chrono>

int main()
{
    const int width = 640;
    const int height = 480;

    double previousX = -1.0;
    double previousY = -1.0;

    // Условный интервал между кадрами: 0,1 секунды.
    const double dt = 0.1;

    auto start = std::chrono::steady_clock::now();
    int framesProcessed = 0;
    // Переменные для сглаживания координаты X
    double smoothX = -1.0;
    const double alpha = 0.8;

    for (int frame = 0; frame < 10; frame++)
    {
        cv::Mat image(height, width, CV_8UC3);
        image.setTo(cv::Scalar(0, 0, 0));

        // Перемещаем квадрат на 20 пикселей вправо каждый кадр.
        int x = 50 + frame * 10;
        int y = 200;

        cv::rectangle(
            image,
            cv::Point(x, y),
            cv::Point(x + 40, y + 40),
            cv::Scalar(0, 0, 255),
            -1
        );

        // Переводим изображение в HSV.
        cv::Mat hsv;
        cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

        // Создаём маску красного цвета.
        cv::Mat mask;
        cv::inRange(
            hsv,
            cv::Scalar(0, 100, 100),
            cv::Scalar(10, 255, 255),
            mask
        );

        // Находим центр красного объекта.
        cv::Moments m = cv::moments(mask, true);

        if (m.m00 > 0)
        {
            double centerX = m.m10 / m.m00;
	    double noisyX = centerX;

	    if (frame % 2 == 0){
		noisyX += 8;
                }
	    else{
		noisyX -= 8;
		}
            double centerY = m.m01 / m.m00;

            //Первое измерение используем как начальное значение
            if (smoothX < 0)
            {
                smoothX = noisyX;
            }
            else
            {
                smoothX = alpha * noisyX
                        + (1.0 - alpha) * smoothX;
            }

            std::cout << "Frame: " << frame
                      << " | X: " << centerX
                      << " | Y: " << centerY
                      << " | Smooth X: " << smoothX
		      << " | NoisyX: " << noisyX;
	if (frame % 2 == 0)
		{
		centerX += 8;
		}
	    else
                {
		centerX -= 8;
                }
// Скорость вычисляем начиная со второго измерения.
            if (previousX >= 0)
            {
                double vx = (centerX - previousX) / dt;
                double vy = (centerY - previousY) / dt;

                std::cout << " | Vx: " << vx
                          << " | Vy: " << vy;
            }

            std::cout << std::endl;

            previousX = centerX;
            previousY = centerY;
        }
    framesProcessed++;}
   auto end = std::chrono::steady_clock::now();

double elapsedSeconds =
    std::chrono::duration<double>(end - start).count();

if (elapsedSeconds > 0 && framesProcessed > 0)
{
    double fps = framesProcessed / elapsedSeconds;

    double millisecondsPerFrame =
        elapsedSeconds * 1000.0 / framesProcessed;

    std::cout << "Processed frames: " << framesProcessed << std::endl;
    std::cout << "Total time: " << elapsedSeconds << " seconds" << std::endl;
    std::cout << "Average FPS: " << fps << std::endl;
    std::cout << "Average time per frame: "
              << millisecondsPerFrame << " ms" << std::endl;
}
}
