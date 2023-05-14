#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "include/sudoku_preprocess.cpp"
#include "include/detect_digits.cpp"
#include "include/solve.cpp"

/*
--------------------------------------------------------------------------------
[ Recipe for Sudoko xtended version with double blushon and extra concealer ] xD
--------------------------------------------------------------------------------
    [-->] read image resize (BGR)
    [-->] detect sudoku board (gray)
    [-->] extract board wrap perspective
    [-->] remove vertical and horizontal lines from it
    [-->] divide board into 81 boxes
    [-->] image processing for deep learning
    [-->] pass image to model
    [-->] get prediction array
    [-->] put prediction on the extracted box
    [-->] solve board via backtracking
    [-->] put solved board on the extracted board
    [-->] unwrap it
    [-->] Done !
------------------------------------------------------------------------------
*/



int main() {

  // std::string image_path = "/home/talha/Documents/opencv/SodukuSolver opencv/imgs/e1.jpg";
  // std::string video_path = "/home/talha/Documents/opencv/SodukuSolver opencv/this.mp4";
  // std::string model_path = "/home/talha/Documents/opencv/SodukuSolver opencv/model/lenet-2-SodukuImg.onnx";


  std::string image_path = "imgs/e1.jpg";
  std::string model_path = "/home/talha/Documents/opencv/SodukuSolver opencv/model/lenet-2-SodukuImg.onnx";

  auto size = cv::Size(640,480);



  PreProcessSoduku Soduku_preprocess;
  Inference_Pipeline Predict_digits(model_path);
  Sudoku_Solver Solve;

  cv::Mat image;

  //for photos
  // image = cv::imread(image_path);

  //for videos
  cv::VideoCapture cap;
  cap.open(0);


  while (1) {

      cap >> image;
      cv::resize(image,image,size);

      // Finding corners of Soduku board for wrap perspective {at theis moment I hate Soduku game SMH}
      PreProcessSoduku::CornerPoints board_points = Soduku_preprocess.get_sudokuBoard(image);
      cv::Mat wraped_sodukuBoard = Soduku_preprocess.extract_Sudoku(board_points,image);

      // cv::Mat VerticalHorizontalLines_removal = Soduku_preprocess.remove_lines(wraped_sodukuBoard);
      // Dividing soduku board into 81 boxes
      std::vector<cv::Mat> boxes_array = Soduku_preprocess.box_division(wraped_sodukuBoard);
      std::vector<cv::Mat> crop_array = Soduku_preprocess.croped_array(boxes_array, 13, 10, 60, 50, 28, 28);

      //20 11 57 47
      //6, 7, 60, 50

      /*
        croped_array
        "params": {array(Mat) 22 11 55 45 28 28}
        cv::Mat, x-start, y-start, x-end, y-end, resize-width, resize-height
      */


      std::vector<int> predictions = Predict_digits.detect_digits(crop_array);
      std::vector<int> solution = Solve.solve_sudoku(predictions);

      Predict_digits.displaySudokuNumbers(wraped_sodukuBoard, predictions,9);
      // Predict_digits.displaySudokuNumbers(wraped_sodukuBoard, solution,9);

      // hahahha i found funny bug in my code, I passed prediction by reference and it overwrite it
      // and my solution is also prediction

      int index = 4;
      Predict_digits.prep(crop_array[index]);

      cv::Mat orignal_cpy = image.clone();

      cv::Mat unwraped = Soduku_preprocess.unwrap(board_points, wraped_sodukuBoard);
      cv::Mat img = Soduku_preprocess.make_black_region(orignal_cpy, board_points);
      cv::Mat sol = img + unwraped;


      cv::imshow("frame", image);
      // cv::imshow("wraped",wraped_sodukuBoard);
      // cv::imshow("unwraped",unwraped);
      // cv::imshow("new",img);
      cv::imshow("Solution",sol);

      // cv::imshow("cropped_array",crop_array[index]);
      // cv::imshow("box",boxes_array[index]);

      std::cout << Solve.check_solution(solution) << '\n';

      int k = cv::waitKey(solution.size() > 80 ? 0 : 1);
      if (k == 'q' || k == 'Q') {
          break;
}
  }

  return 0;
}
