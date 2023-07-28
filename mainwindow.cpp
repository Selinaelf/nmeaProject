#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //QSerialPort serial, s2;
    serial.setPortName("/dev/ttys001");

    s2.setPortName("/dev/ttys002");


    // Open the serial port
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();

    }

    if (!s2.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();

    }
    qDebug () << serial.isOpen() << " " << s2.isOpen();



    serial.setBaudRate(QSerialPort::Baud115200); // Adjust the baud rate as per your requirements
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    s2.setBaudRate(QSerialPort::Baud115200); // Adjust the baud rate as per your requirements
    s2.setDataBits(QSerialPort::Data8);
    s2.setParity(QSerialPort::NoParity);
    s2.setStopBits(QSerialPort::OneStop);
    s2.setFlowControl(QSerialPort::NoFlowControl);


    qDebug() << "Serial port opened.Port name is " << ""<<" Sending and receiving data...";



    qDebug() << serial.isOpen() << s2.isOpen();
    connect (&this->s2, SIGNAL(readyRead()), this, SLOT(DoStuff()));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendSerialData(){

};


void MainWindow::on_pushButton_clicked()
{

    QStringList x;


    QString text = this->ui->lineEdit->text();
    QString text2 = this->ui->lineEdit_2->text();
    QString text3 = this->ui->r3->text();
    QString text4 = this->ui->r4->text();



    x={text,",",text2,",",text3,",",text4};




    qDebug() << "Oluşturulan Dizi:";
        for (int i=0;i<x.size();i++ ) {
        qDebug() << x[i];
        }

        // Send data to the serial port
        QStringList sendData = x;

        QByteArray output;

        // inputArray - your QStringList
        foreach (const QString &str, x)
        {
        output.append(str.toUtf8());
        }



        qint64 bytesWritten = serial.write(output);
        qDebug()<<"writed data: "<<output;

        if (bytesWritten == -1) {
        qDebug() << "Failed to write data:" << serial.errorString();
        } else {
        qDebug() << "Data sent successfully Bytes written: " << bytesWritten;



}

        // Read data from the serial port
        QByteArray data;
        int a = 0;
   while (s2.waitForReadyRead(100)) { // Wait for data to be available for 100 milliseconds
        data = s2.readAll();

//        a++;
//        qDebug() <<"a: "<<a;
//        qDebug() << "Received data:" << data;
        }


}




