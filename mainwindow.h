#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QBuffer>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    bool CheckFields();
    void ChangeAvatar();
    QImage GetImage(){
        return this->ImageFile;
    }
    void SaveImage(){
        QString option = "Save File (." + this->format + ")";
        QString filepath = QFileDialog::getSaveFileName(this,
                                tr("Save Image"), "", tr(format.toLocal8Bit().constData()));
        if(!filepath.isNull()){
            if (this->format == "jpeg"){
                this->ImageFile.save(filepath, "JPEG");
            }
            else if(this->format == "png"){
                this->ImageFile.save(filepath, "PNG");
            }
            else if(this->format == "pdf"){
                qInfo()<<"I'm here !";
                QPdfWriter pdfWriter(filepath);
                QPainter painter(&pdfWriter);
                const QPoint imageCoordinates(0,0);
                painter.drawImage(imageCoordinates, this->ImageFile);
            }
        }
    }

    void ChangeImage() {
        QString temp = QFileDialog::getOpenFileName(this,
                                tr("Open Image"), "/home/rosh/Pictures", tr("Image Files (*.png *.jpg *jpeg *.bmp)"));
        if(temp != ""){
            qInfo()<<temp;
            this->filePath = temp;        }
        this->fileName = this->filePath.split('/').last();
    }

    bool LoadImage() {
        bool valid = this->ImageFile.load(this->filePath);
        QImage::Format format = this->ImageFile.format();
        qInfo()<<format;
        return valid;
    }

    bool OnClickSubmit(){
        if(!this->CheckFields()){
            this->ShowError();
            return false;
        }
        else qInfo()<<"Done..";
        return true;
    }

    void ShowError(){
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText("Plese put all the required fields");
        messageBox.exec();
    }

    void ResizeImage(){
        this->ImageFile = this->ImageFile.scaled(this->input_Width,
                             this->input_Height, Qt::IgnoreAspectRatio);
        qInfo()<<this->ImageFile.size();
    }

    void CopyThings(int input_Width, int input_Height,  QString format){
        this->input_Width = input_Width;
        this->input_Height = input_Height;
        this->format = format;
        qInfo()<<"Copied Stuff"<<this->input_Width
              <<this->input_Height<<this->format;
    }

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_ChangePhoto_pressed();

    void on_pushButton_pressed();

private:
    QString filePath;
    QString fileName;
    QImage ImageFile;
    int input_Height;
    int input_Width;
    int lowestSize;
    QString format;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
