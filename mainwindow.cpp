#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //查找可用端口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
            if(serial.open(QIODevice::ReadWrite))
            {
                ui->portnum->addItem(serial.portName());
                serial.close();
            }
    }

    ui->baudrate->setCurrentIndex(3);
    ui->sendButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearRButton_clicked()
{
    ui->recievetext->clear();
}

void MainWindow::on_clearSButton_clicked()
{
    ui->sendtext->clear();
}

void MainWindow::on_sendButton_clicked()
{
    serial->write(ui->sendtext->toPlainText().toLatin1());
}

void MainWindow::on_saveButton_clicked()
{
    QFile file("./data-s.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        out<<ui->recievetext->toPlainText()<<endl;

        file.close();
    }
}

void MainWindow::read_data()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        QString str = ui->recievetext->toPlainText();
        str += tr(buf);
        ui->recievetext->clear();
        ui->recievetext->append(str);
    }
    buf.clear();
}

void MainWindow::on_openButton_clicked()
{
    if(ui->openButton->text() == tr("打开串口"))
    {
        serial = new QSerialPort;
        serial->setPortName(ui->portnum->currentText());
        serial->open(QIODevice::ReadWrite);
        serial->setBaudRate(ui->baudrate->currentText().toInt());

        switch (ui->databit->currentIndex())
        {
        case 5: serial->setDataBits(QSerialPort::Data5);break;
        case 6: serial->setDataBits(QSerialPort::Data6);break;
        case 7: serial->setDataBits(QSerialPort::Data7);break;
        case 8: serial->setDataBits(QSerialPort::Data8);break;
        default: break;
        }

        switch (ui->checkbit->currentIndex())
        {
        case 0: serial->setParity(QSerialPort::NoParity);break;
        case 1: serial->setParity(QSerialPort::OddParity);break;
        case 2: serial->setParity(QSerialPort::EvenParity);break;
        default: break;
        }

        switch (ui->stopbit->currentIndex())
        {
        case 1: serial->setStopBits(QSerialPort::OneStop);break;
        case 2: serial->setStopBits(QSerialPort::TwoStop);break;
        default: break;
        }
        serial->setFlowControl(QSerialPort::NoFlowControl);

        ui->portnum->setEnabled(false);
        ui->baudrate->setEnabled(false);
        ui->databit->setEnabled(false);
        ui->checkbit->setEnabled(false);
        ui->stopbit->setEnabled(false);
        ui->openButton->setText(tr("关闭串口"));
        ui->sendButton->setEnabled(true);

        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::read_data);
    }
    else
    {
        serial->clear();
        serial->close();
        serial->deleteLater();

        ui->portnum->setEnabled(true);
        ui->baudrate->setEnabled(true);
        ui->databit->setEnabled(true);
        ui->checkbit->setEnabled(true);
        ui->stopbit->setEnabled(true);
        ui->openButton->setText(tr("打开串口"));
        ui->sendButton->setEnabled(false);

    }
}

