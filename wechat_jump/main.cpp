#include "header.h"


int main()
{
	cout << "΢����һ���������򣬱����ֲ����������python�İ汾\n�˰汾����C++��opencv���Ļ��кܶ�bug\n";
	cout << "��ȷ�������ֻ�΢����һ�� y or n��\n";
	getchar();
	while(1)
	{
	system("adb shell screencap -p /sdcard/autojump.jpg");
	system("adb pull /sdcard/autojump.jpg");
	Mat scree = imread("autojump.jpg");
	draw_color(scree);
	Sleep(4000);//��ʱ������̫��
	}
	system("pause");
	return 0;
}
