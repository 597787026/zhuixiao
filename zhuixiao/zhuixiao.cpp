#include "zhuixiao.h"
 char* imagename = "G:\\Programsavedworks\\vsworks\\zhuixiao\\zhuixiao\\bi.jpg";

zhuixiao::zhuixiao(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}
void zhuixiao::on_dj_clicked() {
	
	Mat image = imread(imagename);
	//显示原图
	cvtColor(image, image, COLOR_BGR2RGB);
	cv::resize(image, image, Size(300,300));
	QImage img = QImage((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);
	QPixmap pix = QPixmap::fromImage(img);
	QPixmap scaledPixmap = pix.scaled(QSize(300, 300), Qt::KeepAspectRatio);
	ui.label_16->setPixmap(scaledPixmap);
	ui.scrollArea->setWidget(ui.label_16);


	//去除干扰
	Mat src;
	int thresholds = ui.horizontalSlider->value();
	threshold(image, src, thresholds, 255, THRESH_BINARY);
	//显示降噪后图形
	QImage img_2 = QImage((const unsigned char*)(src.data), src.cols, src.rows, QImage::Format_RGB888);
	QPixmap pix_2 = QPixmap::fromImage(img_2);
	QPixmap scaledPixmap_2 = pix_2.scaled(QSize(300, 300), Qt::KeepAspectRatio);
	ui.label_17->setPixmap(scaledPixmap_2);
	ui.scrollArea_2->setWidget(ui.label_17);
	

}
void zhuixiao::on_tiaoshi_clicked() {
	Mat image = imread(imagename);
	Mat src;
	cvtColor(image, image, COLOR_BGR2RGB);

	cv::resize(image, image, Size(300, 300));
	
	QImage img = QImage((const unsigned char*)(src.data), src.cols, src.rows, QImage::Format_RGB888);
	QPixmap pix = QPixmap::fromImage(img);
	QPixmap scaledPixmap = pix.scaled(QSize(300, 300), Qt::KeepAspectRatio);
	ui.label_21->setPixmap(scaledPixmap);
	ui.scrollArea_5->setWidget(ui.label_21);
	
}
void zhuixiao::on_value_changed() {
	int thresholds = ui.horizontalSlider->value();
	ui.spinBox->setValue(ui.horizontalSlider->value());
	Mat image = imread(imagename);
	Mat src_c,src_t;
	cvtColor(image, image, COLOR_RGB2BGR);
	
	

    
	threshold(image,src_t, thresholds, 255, THRESH_BINARY);
	//bilateralFilter(src_t, src_t, 5, 10.0, 2.0);
	GaussianBlur(image, image, Size(0, 0), 1);
	Mat src_tt = src_t;
    cv::resize(src_tt, src_tt, Size(300, 300));
	QImage img_2 = QImage((const unsigned char*)(src_tt.data), src_tt.cols, src_tt.rows, QImage::Format_RGB888);
	img_2 = img_2.scaled(QSize(300, 300), Qt::KeepAspectRatio);
	QPixmap pix_2 = QPixmap::fromImage(img_2);
	ui.label_19->setPixmap(pix_2);
	ui.scrollArea_4->setWidget(ui.label_19);


    cvtColor(src_t, src_t, COLOR_BGR2GRAY);

	
	vector<vector<Point> >contours;
	vector<Vec4i> hierarchy;
	
	findContours(src_t, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);
	Mat drawing=Mat::zeros(src_t.cols,src_t.rows,CV_8UC3);
	//Mat drawing = image;
	int k = contours.size();
	vector<vector<Point>> selected_con;
	for (int i = 0; i < k; i++)
	{
		if (contours[i].size() >100)
		{
			selected_con.push_back(contours[i]);
		}
	}
	for (int i = 0; i < selected_con.size(); i++)
	{
		Scalar color = Scalar(255, 0, 0);
		drawContours(drawing, selected_con, i, color, 1, 1.5, hierarchy, 0, Point(0, 0));
	}
	src_c = drawing;

	cvtColor(drawing, drawing, COLOR_BGR2GRAY);
	vector<Vec4i> lines;
	HoughLinesP(drawing, lines, 5, CV_PI / 180, 5, 10, 0);
	cvtColor(drawing, drawing, COLOR_GRAY2BGR);
	vector<double> mid;
	
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i I = lines[i];
		double x1 = I[0];
		double y1 = I[1];
		double x2 = I[2];
		double y2 = I[3];
		double x3 = 0.5*(x1 + x2);
		double y3 = 0.5*(y1 + y2);
		double length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1)*(y2 - y1));
	
		string str = std::to_string(length);
		//string str2 = std::to_string(i);//显示直线序号
		if (i == 11 || i == 13) {
			putText(src_c, str, Point(x3, y3), FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 3, 8);
			mid.push_back(length);
		}
		
		
	
				line(src_c, Point2d(x1, y1), Point2d(x2, y2), Scalar(0, 0, 255), 1);
		
	}
	if (mid.size() >1) {
		double d = fabs(mid[1] - mid[0]);
		string str2 = std::to_string(d);
		putText(src_c, "length=", Point(50, 300), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 0), 3, 8);
		putText(src_c, str2, Point(200, 300), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 0), 3, 8);
	}
	
	
	/*Canny(image, src_c, thresholds, thresholds * 2, 3);
	Mat drawing = image;
	vector<Vec4i> lines;
	HoughLinesP(src_c, lines, 0.5, CV_PI / 180, 10, 10, 0);
	cvtColor(src_c, src_c, COLOR_GRAY2BGR);//Canny处理完是二值图，每次显示时需要注意图像格式
	src_c = drawing;
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i I = lines[i];
		double x1 = I[0];
		double y1 = I[1];
		double x2 = I[2];
		double y2 = I[3];


		line(src_c, Point2d(x1, y1), Point2d(x2, y2), Scalar(255, 0, 0), 1);

	}*/


	
	//显示trackbar处理后的图形
	Mat src_cc = src_c;
	cv::resize(src_c, src_c, Size(500, 500));
	QImage img = QImage((const unsigned char*)(src_c.data), src_c.cols, src_c.rows, QImage::Format_RGB888);
	img = img.scaled(QSize(500, 500), Qt::KeepAspectRatio);
	QPixmap pix = QPixmap::fromImage(img);
	ui.label_21->setPixmap(pix);
	ui.scrollArea_5->setWidget(ui.label_21);
}
void zhuixiao::on_tabWidget_tabBarClicked(int index) {
	if (index == 0) 
	{
	
	}

}