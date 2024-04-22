// opencv_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <vector>


using namespace cv;
using namespace std;

void processing(Mat& frame){
        Mat  frame_hsv, mask, thresh;
        cvtColor(frame, frame_hsv, COLOR_BGR2HSV);
        inRange(frame_hsv, Scalar(95, 12, 138), Scalar(255, 50, 255), mask);
        GaussianBlur(mask, mask, Size(5, 5), 0);
        threshold(mask, thresh, 100, 255, THRESH_BINARY);
        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++)
        {
            Rect boundingBox = boundingRect(contours[i]);
            if (boundingBox.width > 40 && boundingBox.height > 40) {
                rectangle(frame, boundingBox, Scalar(0, 255, 0), 2);
                putText(frame, "Rectangle", Point(boundingBox.x, boundingBox.y + 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
            }

        }
}
int main()
{
    VideoCapture video("video1.mp4");
    video.isOpened();
    int width = static_cast<int>(video.get(CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(video.get(CAP_PROP_FRAME_HEIGHT));
    VideoWriter outputVideo("output_video1.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(width, height));
    namedWindow("Processed", WINDOW_AUTOSIZE);
    
    while (true)
    {
        Mat frame;
        video >> frame;
        if (frame.empty())
        {
            break;
        }
        processing(frame);
        outputVideo.write(frame);
        imshow("Processed", frame);

        if (waitKey(30) == 27)
        {
            break;
        }
    }

    video.release();
    outputVideo.release();
    destroyAllWindows();

    VideoCapture video2("video2.mp4");
    video2.isOpened();
    int width2 = static_cast<int>(video2.get(CAP_PROP_FRAME_WIDTH));
    int height2 = static_cast<int>(video2.get(CAP_PROP_FRAME_HEIGHT));
    VideoWriter outputVideo2("output_video2.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(width2, height2));
    namedWindow("Processed", WINDOW_AUTOSIZE);

    while (true)
    {
        Mat frame;
        video2 >> frame;
        if (frame.empty())
        {
            break;
        }
        processing(frame);
        outputVideo.write(frame);
        imshow("Processed", frame);

        if (waitKey(30) == 27)
        {
            break;
        }
    }
   
    video2.release();
    outputVideo2.release();
    destroyAllWindows();
    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
