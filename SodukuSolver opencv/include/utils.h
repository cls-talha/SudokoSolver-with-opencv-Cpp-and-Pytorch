#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <opencv2/opencv.hpp>

class HelperFunctions{

public:
    // cli based print predictions or solution
    void printPredictions(std::vector<int> predictions){
        for (int i = 0; i< predictions.size(); i++){
        std::cout << predictions[i] << " ";
        if (i%9==0){
            std::cout << std::endl;
            }
        }
    }


    void displaySudokuNumbers(cv::Mat& frame, const std::vector<int>& numbers, int boardSize){
        // Loop through the detected numbers vector
        for (int i = 0; i < numbers.size(); ++i) {
            // Calculate the row and column indices of the current number
            int row = i / boardSize;
            int col = i % boardSize;

            // Convert the number to a string
            std::string number = std::to_string(numbers[i]);

            // Calculate the position of the text
            int x = col * frame.cols / boardSize + frame.cols / (boardSize * 2) - 10;
            int y = row * frame.rows / boardSize + frame.rows / (boardSize * 2) + 10;

            // Draw the number on the frame
            cv::putText(frame, number, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(188, 0, 0), 3 );
        }
    }

    // ehh , this function crop the individual box and resize it for further preprocessing
    cv::Mat cropAndResizeImage(cv::Mat inputImage, int startX, int startY, int endX, int endY, int resizeWidth, int resizeHeight) {
        int inputHeight = inputImage.size().height;
        int inputWidth = inputImage.size().width;

        // Ensure the coordinates are within the bounds of the input image
        if (startX < 0 || startY < 0 || endX > inputWidth || endY > inputHeight) {
            throw std::invalid_argument("Crop coordinates are out of bounds");
        }

        // Calculate the width and height of the cropped region
        int width = endX - startX;
        int height = endY - startY;

        // Create a rectangle representing the region of interest
        cv::Rect roi(startX, startY, width, height);

        // Crop the input image to the region of interest
        cv::Mat croppedImage = inputImage(roi);

        // Resize the cropped image
        cv::Mat resizedImage;
        cv::resize(croppedImage, resizedImage, cv::Size(resizeWidth, resizeHeight));

        return resizedImage;
    }
};

#endif // UTILS_H
