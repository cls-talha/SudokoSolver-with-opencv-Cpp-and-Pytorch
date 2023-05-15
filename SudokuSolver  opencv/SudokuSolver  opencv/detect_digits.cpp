#include <string>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#include "utils.h"

class Inference_Pipeline : public HelperFunctions {

public:
    cv::dnn::Net net;
    double confidence_threshold;

    //constructor
    Inference_Pipeline(std::string m_path, double confidence_thr = 0.8) {
        net = cv::dnn::readNet(m_path); // load model
        confidence_threshold = confidence_thr; // confidence threshold
        std::cout << "[INFO] Model Loaded Sucessfully" << std::endl;

        if (net.empty()) {
            std::cout << "[INFO] Failed Loading Model" << std::endl;
        }
    }

    /*
      1- make image looks like train-set
      2- make blob of it
      3- pass blob to model
      4- print predictions
    */

    int preprocess_and_Prediction(cv::Mat img) {
        cv::Mat img_gray;
        cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

        // blur it
        cv::Mat blur;
        cv::GaussianBlur(img_gray, blur, cv::Size(9, 9), 0);

        // threshold it
        cv::Mat thresh;
        cv::adaptiveThreshold(blur, thresh, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 7, 2);

        // invert it so the grid lines and text are white
        cv::Mat inverted;
        cv::bitwise_not(thresh, inverted);

        // get a rectangle kernel
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
        // morph it to remove some noise like random dots
        cv::Mat morph;
        cv::morphologyEx(inverted, morph, cv::MORPH_OPEN, kernel);

        // dilate to increase border size
        cv::Mat result;
        cv::dilate(morph, result, kernel, cv::Point(-1, -1), 1);

        // Erode image
        cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::Mat eroded;

        cv::erode(result, eroded, kernel1, cv::Point(-1, -1), 1);
        cv::bitwise_not(eroded, eroded);

        cv::Mat floatImage;
        eroded.convertTo(floatImage, CV_32F);

        // Normalize image
        float mean = 0.5;
        float stddev = 0.5;
        floatImage = (floatImage / 255.0 - mean) / stddev;

        // Create a 4D blob from the image
        cv::Mat blob = cv::dnn::blobFromImage(floatImage);

        net.setInput(blob);
        cv::Mat prob = net.forward();

        cv::Point classIdPoint;
        double confidence;
        cv::minMaxLoc(prob.reshape(1, 1), 0, &confidence, 0, &classIdPoint);

        if (confidence > confidence_threshold) {
            int classId = classIdPoint.x;
            return classId;
        }

        return 0;
    }

    bool check_empty(cv::Mat im) {
        cv::Mat detected_edge;
        std::vector<std::vector<cv::Point>> contours;
        cv::Canny(im, detected_edge, 0, 100);
        cv::findContours(detected_edge, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        if (!contours.empty()) { // boxes empty to run condition make it true by !0 - > 1 return 0
            return false;
        }
        return true;
    }

    std::vector<int> detect_digits(std::vector<cv::Mat> boxes_arr) {

        std::vector<int> prediction_arr;

        for (int i = 0; i < boxes_arr.size(); i++) {

            if (check_empty(boxes_arr[i])) {
                prediction_arr.push_back(0);
            }
            else {
                int prediction = preprocess_and_Prediction(boxes_arr[i]);
                prediction_arr.push_back(prediction);
            }
        }
        return prediction_arr;
    }

    // code for debuging {preprocessing stuffs}
    void prep(cv::Mat img) {
        cv::Mat img_gray;
        cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

        // blur it
        cv::Mat blur;
        cv::GaussianBlur(img_gray, blur, cv::Size(9, 9), 0);

        // threshold it
        cv::Mat thresh;
        cv::adaptiveThreshold(blur, thresh, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 7, 2);

        // invert it so the grid lines and text are white
        cv::Mat inverted;
        cv::bitwise_not(thresh, inverted);

        // get a rectangle kernel
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
        // morph it to remove some noise like random dots
        cv::Mat morph;
        cv::morphologyEx(inverted, morph, cv::MORPH_OPEN, kernel);

        // dilate to increase border size
        cv::Mat result;
        cv::dilate(morph, result, kernel, cv::Point(-1, -1), 1);

        // Erode image
        cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::Mat eroded;

        cv::erode(result, eroded, kernel1, cv::Point(-1, -1), 1);

        cv::bitwise_not(eroded, eroded);
        cv::imshow("Debug Preprocessing", eroded);
    }

};
