#include "header.h"
Point ptc, ptm;//�洢���ӵ������������ĵ�����


//��һ�����ҳ����ӵĵ��µ�����
//�������ӵ������ǿ��Է�ֹ
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
			//�жϵ�ǰ����������µ���ɫ����
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
	//�ҳ�����ĵ�һ��
	//ɨ��ÿһ�У������һ�����һ�е������ܺ��������30������ô�Ͳ��Ǵ�ɫ����������
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
	//�ҳ�������ĵ�һ�к�
	//�����ҳ��Ǳ����ĵ�һ��
	int fl = i + 273;//������󲻻����273��
	int i_x = 0;
	int i_y = 0;
	int kk = 0;
	for (; i < fl; ++i)
	{
		for (j = 0; j<nCols-1; j++)
		{
			

		
			//���ǰһ�����һ�������ֵ������5����ô�����ҵ���

			kk = abs((int)img.at<uchar>(i, j) - (int)img.at<uchar>(i, j+1));
			//Ϊ�˷�ֹ���ӵ��Դ��������壬�������ҳ����ӵ�x�᷽���λ�ã�
			//�����ʱ�ҳ��ĵ�һ�������ӵ�������ӽ����������
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

	//�ҳ�������½磬�Ա����е�
	for (n = fl; n >= i; n--)
	{

		{
			//�������ҵ��������һ�������ֵ���жϣ�������10�����ҵ���
			if (abs((int)img.at<uchar>(i+1, j) - (int)img.at<uchar>(n, j)) < 10)
			{
				
				pt2.x = j;
				pt2.y = n;
				break;
			}
		}

	}

	
	ptc.x = (int)j;
	ptc.y = (int)((n - i) /2) + i;//���������е�

	//�����˵���һ���������ľ���
	//������빫ʽ�������ٳ���0.5�ٳ���0.25���ǰ�ѹʱ��
	int S = (int)sqrt((ptc.x - ptm.x)*(ptc.x - ptm.x) + (ptc.y - ptm.y)*(ptc.y - ptm.y))*0.5 / 0.25;
	char ch[50] = { " " };
	//�Ѱ�ѹʱ��������ŵ�һ���ַ�����
	sprintf(ch, "adb shell input swipe 320 410 310 410 %d", S);
	//��system��������
	system(ch);
	cout << "\n" << ch << endl;

}