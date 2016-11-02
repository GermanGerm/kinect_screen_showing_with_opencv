#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtCore>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qtimer = new QTimer(this);
    connect(qtimer, SIGNAL(timeout()), this, SLOT(submain()));
    qtimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::submain()
{
    // 1a. Get default Sensor
    //cout << "Try to get default sensor" << endl;
    ui->text_panel->appendPlainText(QString("Try to open sensor"));
    IKinectSensor* pSensor = nullptr;

    GetDefaultKinectSensor(&pSensor);
    // 1b. Open sensor
    //cout << "Try to open sensor" << endl;
    ui->text_panel->appendPlainText(QString("Try to open sensor"));

    pSensor->Open();

    // 2a. Get frame source
    //cout << "Try to get color source" << endl;
    ui->text_panel->appendPlainText(QString("Try to get color source"));
    IColorFrameSource* pFrameSource = nullptr;

    pSensor->get_ColorFrameSource(&pFrameSource);

    // 2b. Get frame description
    //cout << "get color frame description" << endl;
    ui->text_panel->appendPlainText(QString("get color frame description"));
    int		iWidth = 0;
    int		iHeight = 0;
    IFrameDescription* pFrameDescription = nullptr;
    if (pFrameSource->get_FrameDescription(&pFrameDescription) == S_OK)
    {
        pFrameDescription->get_Width(&iWidth);
        pFrameDescription->get_Height(&iHeight);
    }
    pFrameDescription->Release();
    pFrameDescription = nullptr;

    // 3a. get frame reader
    //cout << "Try to get color frame reader" << endl;
    ui->text_panel->appendPlainText(QString("Try to get color frame reader"));
    IColorFrameReader* pFrameReader = nullptr;

    pFrameSource->OpenReader(&pFrameReader);

    // 2c. release Frame source
    //cout << "Release frame source" << endl;
    ui->text_panel->appendPlainText(QString("Release frame source"));
    pFrameSource->Release();
    pFrameSource = nullptr;

    // Prepare OpenCV data
    cv::Mat	mImg(iHeight,iWidth,CV_8UC4);
    UINT uBufferSize = iHeight * iWidth * 4 * sizeof(BYTE);
    cv::namedWindow("Color Map");

    // Enter main loop
    while (true)
    {
        // 4a. Get last frame
        IColorFrame* pFrame = nullptr;
        if (pFrameReader->AcquireLatestFrame(&pFrame) == S_OK)
        {
            // 4c. Copy to OpenCV image
            if (pFrame->CopyConvertedFrameDataToArray(uBufferSize, mImg.data, ColorImageFormat_Bgra) == S_OK)
            {
                cv::imshow("Color Map", mImg);
                QImage temp = convertOpenCVMatToQtQImage(mImg);
                ui->kinect_screen->setPixmap(QPixmap::fromImage(temp));
            }

            // 4e. release frame
            pFrame->Release();
        }

        // 4f. check keyboard input
        if (cv::waitKey(30) == VK_ESCAPE){
            break;
        }
    }

    // 3b. release frame reader
    //cout << "Release frame reader" << endl;
    ui->text_panel->appendPlainText(QString("Release frame reader"));
    pFrameReader->Release();
    pFrameReader = nullptr;

    // 1c. Close Sensor
    //cout << "close sensor" << endl;
    ui->text_panel->appendPlainText(QString("close sensor"));
    pSensor->Close();

    // 1d. Release Sensor
    //cout << "Release sensor" << endl;
    ui->text_panel->appendPlainText(QString("Release sensor"));
    pSensor->Release();
    pSensor = nullptr;

}

QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                                   // if 1 channel (grayscale or black and white) image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // return QImage
    } else if(mat.channels() == 3) {                            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);                     // flip colors
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // return QImage
    }// else {
    //    qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    //}
    return QImage();        // return a blank QImage if the above did not work
}
