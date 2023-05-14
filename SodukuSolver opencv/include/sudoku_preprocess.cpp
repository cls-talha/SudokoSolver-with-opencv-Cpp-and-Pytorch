#include <opencv2/opencv.hpp>

#include <iostream>
#include "utils.h"


class PreProcessSoduku: public HelperFunctions {

private:
    cv::Mat Img;
    const int Width ;
    const int Height ;

public:
    // constructor
    PreProcessSoduku():Width(480),Height(640) {}

    struct CornerPoints {
        cv::Point top_left;
        cv::Point top_right;
        cv::Point bottom_right;
        cv::Point bottom_left;
    };

    CornerPoints get_sudokuBoard(cv::Mat im){

        // variable decleration
        cv::Mat detected_edges, gray_img,blured,thresh,bin;

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hier;

        // Canny thresholds
        int thresh1_canny = 50;
        int thresh2_canny = 70;


        cv::resize(im,Img,cv::Size(Height,Width));
        cv::cvtColor(Img, gray_img, cv::COLOR_BGR2GRAY);

        cv::GaussianBlur(gray_img, blured, cv::Size(5, 5), 0);
        cv::adaptiveThreshold(blured, bin, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 11, 2);

        cv::findContours(bin, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);


        double maxArea = 0;
        std::vector<cv::Point> largestContour;

        for (const auto& contour : contours) {
            double area = cv::contourArea(contour);
            if (area > maxArea) {
                maxArea = area;
                largestContour = contour;
            }
        }

        std::vector<cv::Point> approx;
        cv::approxPolyDP(largestContour, approx, cv::arcLength(largestContour, true) * 0.01, true);
        if (approx.size() == 4) {
            cv::Point top_left = approx[0];
            cv::Point top_right = approx[1];
            cv::Point bottom_right = approx[2];
            cv::Point bottom_left = approx[3];

        for (const auto& point : approx) {

          if (point.x + point.y < top_left.x + top_left.y) {
              top_left = point;
          }
          if (point.x - point.y > top_right.x - top_right.y) {
              top_right = point;
          }
          if (point.x + point.y > bottom_right.x + bottom_right.y) {
              bottom_right = point;
          }
          if (point.x - point.y < bottom_left.x - bottom_left.y) {
              bottom_left = point;
            }
          }

          cv::circle(Img, top_left, 10, cv::Scalar(0, 0, 0), -1);
          cv::circle(Img, top_right, 10, cv::Scalar(0, 0, 0), -1);
          cv::circle(Img, bottom_left, 10, cv::Scalar(0, 0, 0), -1);
          cv::circle(Img, bottom_right, 10, cv::Scalar(0, 0, 0), -1);

          CornerPoints corners;
          corners.top_left = top_left;
          corners.top_right = top_right;
          corners.bottom_right = bottom_right;
          corners.bottom_left = bottom_left;

          cv::drawContours(Img, std::vector<std::vector<cv::Point>> {largestContour} , -1, cv::Scalar(0, 255, 0), 2);

          cv::imshow("cornerPoints", Img);
          return corners;
        }

        CornerPoints corners;
        return corners;
  }

  cv::Mat extract_Sudoku(CornerPoints &Points,cv::Mat img){

        // Define the source and destination points
        cv::Point2f srcPoints[] = {
            cv::Point2f(Points.top_left),
            cv::Point2f(Points.top_right),
            cv::Point2f(Points.bottom_left),
            cv::Point2f(Points.bottom_right)
        };

        cv::Point2f dstPoints[] = {
            cv::Point2f(0, 0),
            cv::Point2f(Height, 0),
            cv::Point2f(0, Width),
            cv::Point2f(Height , Width)
        };

        // Compute the perspective transformation matrix
        cv::Mat perspectiveMatrix = cv::getPerspectiveTransform(srcPoints, dstPoints);

        // Apply the perspective transformation to the input image
        cv::Mat outputImg;
        cv::warpPerspective(img, outputImg, perspectiveMatrix, cv::Size(Height, Width));
        // cv::imshow("jdhjkshd", outputImg);
        return outputImg;
    }

    cv::Mat remove_lines(cv::Mat image){
        /*
         bro, ILY --> https://aishack.in/tutorials/sudoku-grabber-opencv-detection/
        */
        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        cv::Mat outerBox = cv::Mat(gray.size(), CV_8UC1);
        cv:: GaussianBlur(gray, gray, cv::Size(11,11), 0);

        cv::adaptiveThreshold(gray, outerBox, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 5, 2);
        cv::bitwise_not(outerBox, outerBox);

        cv::Mat kernel = (cv::Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
        cv::dilate(outerBox, outerBox, kernel);
        int count=0;
        int max=-1;

        cv::Point maxPt;

        for(int y=0;y<outerBox.size().height;y++){
            uchar *row = outerBox.ptr(y);
            for(int x=0;x<outerBox.size().width;x++){
                if(row[x]>=128){
                     int area = floodFill(outerBox, cv::Point(x,y), CV_RGB(0,0,64));
                     if(area>max){
                         maxPt = cv::Point(x,y);
                         max = area;
                     }
                }
            }
        }

        cv::floodFill(outerBox, maxPt, CV_RGB(255,255,255));

        for(int y=0;y<outerBox.size().height;y++){
            uchar *row = outerBox.ptr(y);
            for(int x=0;x<outerBox.size().width;x++){
                if(row[x]==64 && x!=maxPt.x && y!=maxPt.y){
                    int area = floodFill(outerBox, cv::Point(x,y), CV_RGB(0,0,0));
                }
            }
        }
        cv::erode(outerBox, outerBox, kernel);
        cv::Mat output;

        cv::cvtColor(image,image, cv::COLOR_BGR2GRAY);
        cv::bitwise_or(image, outerBox, output);
        // cv::imshow("", output);
        return output;
    }

    std::vector<cv::Mat> box_division(cv::Mat w_image) {
        // Define the number of rows and columns for the grid
        int rows = 9;
        int cols = 9;

        // Calculate the width and height of each box
        int boxWidth = w_image.cols / cols;
        int boxHeight = w_image.rows / rows;

        std::vector<cv::Mat> img_arr;

        // Loop through the rows and columns, and extract the corresponding region of interest
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                // Define the region of interest using the Rect function
                cv::Rect roi(c * boxWidth, r * boxHeight, boxWidth, boxHeight);

                // Extract ROI as a new image
                cv::Mat box = w_image(roi);

                // Save the box as a new image
                img_arr.push_back(box);
            }
        }
        return img_arr;
    }

    std::vector<cv::Mat> croped_array(std::vector<cv::Mat> img_arr, int startX, int startY, int endX, int endY, int resizeWidth, int resizeHeight){

      std::vector<cv::Mat> croped_array;
      for (int i = 0; i < img_arr.size(); ++i){
          cv::Mat crop_im = cropAndResizeImage(img_arr[i],startX, startY, endX, endY, resizeWidth, resizeHeight);
          croped_array.push_back(crop_im);
      }
      return croped_array;
    }

    cv::Mat unwrap(CornerPoints &Points,cv::Mat img){

        // Define the source and destination points
        cv::Point2f dstPoints[] = {
            cv::Point2f(Points.top_left),
            cv::Point2f(Points.top_right),
            cv::Point2f(Points.bottom_left),
            cv::Point2f(Points.bottom_right)
        };

        cv::Point2f srcPoints[] = {
            cv::Point2f(0, 0),
            cv::Point2f(Height, 0),
            cv::Point2f(0, Width),
            cv::Point2f(Height , Width)
        };

        // Compute the perspective transformation matrix
        cv::Mat perspectiveMatrix = cv::getPerspectiveTransform(srcPoints, dstPoints);

        // Apply the perspective transformation to the input image
        cv::Mat outputImg;
        cv::warpPerspective(img, outputImg, perspectiveMatrix, cv::Size(Height, Width));
        // cv::imshow("jdhjkshd", outputImg);
        return outputImg;
    }

    cv::Mat make_black_region(cv::Mat& image, const CornerPoints& sudoku_points) {
      // Create a mask with the same dimensions as the input image
      cv::Mat mask(image.rows, image.cols, CV_8UC1, cv::Scalar(0));

      // Create a polygon from the corner points and fill it with white color (255)
      std::vector<std::vector<cv::Point>> polygon{ {
          sudoku_points.top_left,
          sudoku_points.top_right,
          sudoku_points.bottom_right,
          sudoku_points.bottom_left
      } };
      cv::fillPoly(mask, polygon, cv::Scalar(255));

      // Set the pixels in the original image that correspond to the mask to black (0, 0, 0)
      image.setTo(cv::Scalar(0, 0, 0), mask);

      return image;
  }
};
