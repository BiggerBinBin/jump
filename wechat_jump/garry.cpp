#include "header.h"
Point ptc, ptm;//存储棋子底下与物体中心的坐标


//第一步，找出棋子的底下的坐标
//先找棋子的坐标是可以防止
void draw_color(Mat &img)
{
	
	
	int average = 0;
	int channels = img.channels();
	int nRows = img.rows;
	int nCols = img.cols* channels;
	int i = (int)nRows * 1 / 3;
	int b_color = 102;
	int g_color = 54;
	int r_color = 53;

	int man_x = 0;
	int man_y = 0;
	int fla = 0;
	for (man_y = i + 350; man_y>i + 100; man_y--)
	{
		for (man_x = 99; man_x < nCols - 99; man_x += 3)
		{
			//判断当前点与人物底下的颜色相似
			if ((abs((int)img.at<uchar>(man_y, man_x) - b_color) +
				abs((int)img.at<uchar>(man_y, man_x + 1) - g_color) +
				abs((int)img.at<uchar>(man_y, man_x + 2) - r_color)) < 20)
			{
				ptm.x = (int)man_x / 3.0;
				ptm.y = man_y - 5;
				fla = 1;
				break;
			}
		}
		if (fla)
			break;
	}
	draw_garry(img, ptm.x);
}
void draw_garry(Mat &thr,int man_xx)
{
	Mat img;
	cvtColor(thr, img, COLOR_RGB2GRAY);

	int sum = 0;
	int average = 0;
	int channels = img.channels();
	int nRows = img.rows;
	int nCols = img.cols* channels;

	int k = 0;
	int f = 0;
	Rect r1;
	Rect r2;
	Point pt1, pt2;
	int stat_y = (int)(nRows*(2.0 / 6.0));
	pt2.x = nCols;
	pt1.x = 0;
	pt1.y = 0;
	pt2.y = 0;


	int i;
	int j;
	//找出物体的第一行
	//扫描每一行，如果下一行与第一行的像素总和相差正负30个，那么就不是纯色，有物体了
	for (i = stat_y; i < nRows; ++i)
	{
		for (j = 0; j<nCols; j++)
		{
			sum += img.at<uchar>(i, j);

		}
		if (sum != 0)
			if (k == 0)
			{
				f = sum;
				k = 1;
			}
		
		if (sum <f - 30|| sum>f + 30)
		{
			average = 1;
			break;

		}
		if (average)
			break;
		sum = 0;
	}
	//找出有物体的第一行后
	//接着找出非背景的第一点
	int fl = i + 273;//物体最大不会高于273行
	int i_x = 0;
	int i_y = 0;
	int kk = 0;
	for (; i < fl; ++i)
	{
		for (j = 0; j<nCols-1; j++)
		{
			

		
			//如果前一点与后一点的像素值相差大于5，那么就是找到了

			kk = abs((int)img.at<uchar>(i, j) - (int)img.at<uchar>(i, j+1));
			//为了防止棋子的脑袋超过物体，所以先找出棋子的x轴方向的位置，
			//如果这时找出的第一点与棋子的坐标相接近，则继续找
			if (abs(j - man_xx) < 30)
				continue;
			if (kk>5)
			{
				i_x = j;
				i_y = i;
				pt1.x = i_x;
				pt1.y = i_y;
				break;
			}


		}
		if (i_x != 0)
			break;
	}


	int n;
	int n_x = 0;
	int n_y = 0;

	//找出物体的下界，以便求中点
	for (n = fl; n >= i; n--)
	{

		{
			//用上面找到物体的那一点的像素值来判断，相差不大于10就是找到了
			if (abs((int)img.at<uchar>(i+1, j) - (int)img.at<uchar>(n, j)) < 10)
			{
				
				pt2.x = j;
				pt2.y = n;
				break;
			}
		}

	}

	
	ptc.x = (int)j;
	ptc.y = (int)((n - i) /2) + i;//计算物体中点

	//计算人到下一个物体中心距离
	//两点距离公式，距离再乘以0.5再除以0.25就是按压时间
	int S = (int)sqrt((ptc.x - ptm.x)*(ptc.x - ptm.x) + (ptc.y - ptm.y)*(ptc.y - ptm.y))*0.5 / 0.25;
	char ch[50] = { " " };
	//把按压时间与命令放到一个字符串上
	sprintf(ch, "adb shell input swipe 320 410 310 410 %d", S);
	//用system命令输入
	system(ch);
	cout << "\n" << ch << endl;

}