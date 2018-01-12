#include "header.h"


int main()
{
	cout << "微信跳一跳辅助程序，彬彬移植于网络大神的python的版本\n此版本是用C++与opencv定的还有很多bug\n";
	cout << "请确保打开了手机微信跳一跳 y or n？\n";
	getchar();
	while(1)
	{
	system("adb shell screencap -p /sdcard/autojump.jpg");
	system("adb pull /sdcard/autojump.jpg");
	Mat scree = imread("autojump.jpg");
	draw_color(scree);
	Sleep(4000);//延时，不能太快
	}
	system("pause");
	return 0;
}
