#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->input_Width->setValidator(new QIntValidator);
    ui->input_Height->setValidator(new QIntValidator);
    ui->input_Size->setValidator(new QIntValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_ChangePhoto_pressed()
{
    MainWindow::ChangeImage();
    if (MainWindow::LoadImage())
        MainWindow::ChangeAvatar();
}

void MainWindow::ChangeAvatar()
{
    ui->label_Image->setPixmap(QPixmap::fromImage(MainWindow::GetImage()));
}

bool MainWindow::CheckFields(){
    int label_Width = ui->input_Width->text().toInt();
    int label_Height = ui->input_Height->text().toInt();
    int label_Size = ui->input_Size->text().toInt();
    QString format = ui->comboBox->currentText();
    qInfo()<<label_Width<<label_Height<<format;
    if( label_Width && label_Height && !MainWindow::GetImage().isNull() && !format.isNull()){
        MainWindow::CopyThings(label_Width, label_Height, label_Size, format);
        return true;
    }
    else
        return false;
}

void MainWindow::on_pushButton_pressed()
{
    if (MainWindow::OnClickSubmit()){
    MainWindow::ResizeImage();
    MainWindow::SaveImage();
   }
}
