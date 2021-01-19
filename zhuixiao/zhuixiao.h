#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_zhuixiao.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "highgui.hpp"
#include "imgproc.hpp"//»ô·ò±ä»»cvRoundº¯Êý
#include <ctype.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include<vector>
#include<cmath>
#include<QSettings>
#include<Windows.h>
using namespace cv;
using namespace std;

class zhuixiao : public QMainWindow
{
	Q_OBJECT

public:
	zhuixiao(QWidget *parent = Q_NULLPTR);
private slots:
	//button
	void on_dj_clicked();
	void on_tiaoshi_clicked();
	void on_value_changed();
	void on_tabWidget_tabBarClicked(int index);
private:
	Ui::zhuixiaoClass ui;
};
