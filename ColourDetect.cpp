// //
// // Created by Lenovo on 18-06-2024.
// //
// #include <opencv2/opencv.hpp>
// #include <iostream>
// #include <vector>
//
// using namespace cv;
// using namespace std;
//
// // Define color ranges in HSV
// map<char, pair<Scalar, Scalar>> color_ranges = {
//     {'W', make_pair(Scalar(0, 0, 200), Scalar(180, 20, 255))},  // White
//     {'G', make_pair(Scalar(40, 40, 40), Scalar(80, 255, 255))},  // Green
//     {'R', make_pair(Scalar(0, 100, 100), Scalar(10, 255, 255))},  // Red
//     {'B', make_pair(Scalar(100, 150, 100), Scalar(140, 255, 255))},  // Blue
//     {'O', make_pair(Scalar(10, 100, 100), Scalar(25, 255, 255))},  // Orange
//     {'Y', make_pair(Scalar(20, 100, 100), Scalar(30, 255, 255))}   // Yellow
// };
//
// // Function to detect and warp the Rubik's Cube
// Mat detect_and_warp_cube(Mat& frame) {
//     Mat gray, blurred, edged;
//
//     cvtColor(frame, gray, COLOR_BGR2GRAY);
//     GaussianBlur(gray, blurred, Size(5, 5), 0);
//     Canny(blurred, edged, 50, 150);
//
//     vector<vector<Point>> contours;
//     findContours(edged.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//     sort(contours.begin(), contours.end(), [](const vector<Point>& c1, const vector<Point>& c2) {
//         return contourArea(c1) > contourArea(c2);
//     });
//
//     for (const auto& contour : contours) {
//         vector<Point> approx;
//         double peri = arcLength(contour, true);
//         approxPolyDP(contour, approx, 0.02 * peri, true);
//
//         if (approx.size() == 4) {
//             vector<Point2f> pts;
//             pts.push_back(approx[0]);
//             pts.push_back(approx[1]);
//             pts.push_back(approx[2]);
//             pts.push_back(approx[3]);
//
//             // Order the points in a clockwise order
//             sort(pts.begin(), pts.end(), [](const Point2f& p1, const Point2f& p2) {
//                 return p1.x < p2.x && p1.y < p2.y;
//             });
//
//             // Find the top-left, top-right, bottom-right, and bottom-left corners
//             Point2f tl = pts[0];
//             Point2f tr = pts[1];
//             Point2f br = pts[2];
//             Point2f bl = pts[3];
//
//             // Compute the width and height of the new image
//             float maxWidth = max(sqrt(pow(br.x - bl.x, 2) + pow(br.y - bl.y, 2)),
//                                  sqrt(pow(tr.x - tl.x, 2) + pow(tr.y - tl.y, 2)));
//             float maxHeight = max(sqrt(pow(tr.x - br.x, 2) + pow(tr.y - br.y, 2)),
//                                   sqrt(pow(tl.x - bl.x, 2) + pow(tl.y - bl.y, 2)));
//
//             // Create a destination array to store the transformed image
//             Mat dst = Mat::zeros(maxHeight, maxWidth, CV_8UC3);
//
//             // Calculate the perspective transform matrix
//             Point2f src[4] = {tl, tr, br, bl};
//             Point2f dst_pts[4] = {Point2f(0, 0), Point2f(maxWidth - 1, 0),
//                                   Point2f(maxWidth - 1, maxHeight - 1), Point2f(0, maxHeight - 1)};
//             Mat M = getPerspectiveTransform(src, dst_pts);
//
//             // Apply the perspective transformation to the original image
//             warpPerspective(frame, dst, M, dst.size());
//
//             return dst;
//         }
//     }
//
//     return Mat();
// }
//
// // Function to detect colors of the Rubik's Cube face
// vector<vector<char>> detect_cube_colors(Mat& frame) {
//     Mat hsv;
//     cvtColor(frame, hsv, COLOR_BGR2HSV);
//
//     vector<vector<char>> cube_colors(3, vector<char>(3, 'U'));  // Initialize with unknown colors
//
//     int step_x = frame.cols / 3;
//     int step_y = frame.rows / 3;
//
//     for (int j = 0; j < 3; ++j) {
//         for (int k = 0; k < 3; ++k) {
//             Rect roi(k * step_x, j * step_y, step_x, step_y);
//             Mat sticker = hsv(roi);
//
//             Scalar avg_color = mean(sticker);
//             char detected_color = 'U';  // Default to unknown color
//
//             for (const auto& color_range : color_ranges) {
//                 if (avg_color[0] >= color_range.second.first[0] && avg_color[0] <= color_range.second.second[0] &&
//                     avg_color[1] >= color_range.second.first[1] && avg_color[1] <= color_range.second.second[1] &&
//                     avg_color[2] >= color_range.second.first[2] && avg_color[2] <= color_range.second.second[2]) {
//                     detected_color = color_range.first;
//                     break;
//                 }
//             }
//
//             cube_colors[j][k] = detected_color;
//         }
//     }
//
//     return cube_colors;
// }
//
// int main() {
//     VideoCapture cap(0);
//     if (!cap.isOpened()) {
//         cerr << "Error: Unable to open the camera." << endl;
//         return -1;
//     }
//
//     vector<vector<char>> faces(6, vector<char>(9, 'U'));
//     vector<string> face_names = {"White", "Green", "Red", "Blue", "Orange", "Yellow"};
//     int face_count = 0;
//
//     while (face_count < 6) {
//         Mat frame;
//         cap >> frame;
//         if (frame.empty()) {
//             cerr << "Error: Unable to capture frame." << endl;
//             break;
//         }
//
//         resize(frame, frame, Size(640, 480));  // Resize frame for faster processing
//
//         Mat warped_cube = detect_and_warp_cube(frame);
//         if (!warped_cube.empty()) {
//             vector<vector<char>> face_colors = detect_cube_colors(warped_cube);
//
//             // Display detected face colors
//             for (int j = 0; j < 3; ++j) {
//                 for (int k = 0; k < 3; ++k) {
//                     int x = k * warped_cube.cols / 3;
//                     int y = j * warped_cube.rows / 3;
//                     putText(warped_cube, string(1, face_colors[j][k]), Point(x + 20, y + 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
//                 }
//             }
//
//             imshow("Rubik's Cube - " + face_names[face_count] + " Face", warped_cube);
//
//             char key = waitKey(100);
//             if (key == 'c') {
//                 faces[face_count] = face_colors[0];
//                 faces[face_count + 1] = face_colors[1];
//                 faces[face_count + 2] = face_colors[2];
//                 face_count += 3;
//             }
//         } else {
//             imshow("Rubik's Cube", frame);
//         }
//     }
//
//     cap.release();
//     destroyAllWindows();
//
//     // Print the result
//     if (face_count == 6) {
//         for (int i = 0; i < 6; ++i) {
//             cout << face_names[i] << " face:" << endl;
//             for (int j = 0; j < 3; ++j) {
//                 for (int k = 0; k < 3; ++k) {
//                     cout << faces[i][j * 3 + k] << " ";
//                 }
//                 cout << endl;
//             }
//         }
//     } else {
//         cerr << "Failed to capture all faces of the Rubik's Cube." << endl;
//     }
//
//     return 0;
// }
