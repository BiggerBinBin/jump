
#define _CRT_SECURE_NO_WARNINGS//关闭安全检查，须放到最前面
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace cv;
using namespace std;
void draw_color(Mat &img);
void draw_garry(Mat &img, int x);//找出物体的中心位置
