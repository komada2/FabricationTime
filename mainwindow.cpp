#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int fn = 1;
    QString firstnumber = QString(QString::number(fn));
    ui->datenum_lineEdit->setText(firstnumber);

//    ui->checkBox->checkState()->Checked();

    QObject::connect(ui->end_button,SIGNAL(clicked()),this,SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "renew";

    //準備
    QString number = ui->datenum_lineEdit->text();
    int n = number.toInt();

    QString velocity = ui->time_lineEdit->text();
    float v = velocity.toFloat();

    float tmptime = 0;
    float fulltime = 0;

    float oldX, oldY;
    float newX, newY;

    //造形方法ごとの補正
    int a = 1000;   //造形時間補正用ファイバー造形1000，一光子，二光子

    if(ui->radioButton->isChecked() == 1)
    {
        a = 1000;
    }

    if(ui->radioButton_2->isChecked() == 1)
    {
        a = 100;
    }

    if(ui->radioButton_3->isChecked() == 1)
    {
        a = 10;
    }


    //処理内容

    if (ui->time_lineEdit->text().isEmpty()) return; // 造形時間がないときは終了
    if (ui->refer_lineEdit->text().isEmpty()) return; // パスがないときは終了

    //　パスがあるとき

    for(int i=0;i<n;i++){
        QString str = ui->refer_lineEdit->text();
        QString str2 = QString("/model.%1%2%3.csv").arg(0).arg(0).arg(i);
        str.append(str2);

        qDebug() << str;

        //    for (int i=0;i<10;i++){
        //        QString str2 = QString("model.%1%2,csv").arg(00).arg(1);
        //        qDebug() << str2;
        //    }

        QFile file(str);

        if (file.open(QIODevice::ReadOnly))//読込のみでオープンできたかチェック
        {
            qDebug("open!");
        }else
        {
            qDebug("Couldn't open!");
            QMessageBox msgbox;
            msgbox.setText("error");
            msgbox.exec();
        }

        QTextStream in(&file);

        oldX = 0; oldY = 0;

        while(!in.atEnd()){
            QString line = in.readLine();
            //        float num = line.toFloat();
            QStringList list = line.split(",");
            //        float num = list.at(0).toFloat();

            newX = list.at(0).toFloat();
            newY = list.at(1).toFloat();

            qDebug() << "old x : " << oldX << ", old y : " << oldY;
            qDebug() << "new x : " << newX << ", new y : " << newY;

            //計算
            qDebug()<< "compute";
            tmptime = sqrt((newX-oldX)*(newX-oldX)+(newY-oldY)*(newY-oldY))/a/v;
            fulltime = fulltime + tmptime;

            // 更新
            oldX = newX;
            oldY = newY;
        }
    }

    //計算結果表示
    QString full = QString(QString::number(fulltime));
    ui->result_lineEdit->setText(full);


    //    if(!ui->refer_lineEdit->text().isEmpty())
    //    {

    //        QString str;

    //        QFile file(ui->refer_lineEdit->text());

    //        if (file.open(QIODevice::ReadOnly))//読込のみでオープンできたかチェック
    //        {
    //            return;
    //            qDebug("open!");
    //        }else
    //        {
    //             qDebug("Couldn't open!");
    //        }

    //        QTextStream in(&file);
    //       in >> str;

    //        qDebug ("ok!");
    //    }else{
    //        qDebug ("NG!");
    //    }

}

void MainWindow::on_refer_button_clicked()
{
    //    ui->refer_lineEdit->setText("komadaPC");
//    int o = 1;
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;

    QString strDir = QFileDialog::getExistingDirectory(
                this,
                tr("造形フォルダを選んでください"),
                tr("初期ディレクトリ"), options);

    if ( !strDir.isEmpty() )
    {
        // ファイルに対する処理
        ui->refer_lineEdit->setText(strDir);
    }
    //        else{
    //            QMessageBox msgbox;
    //            msgbox.setText("error");
    //            msgbox.exec();
    //        }


}

void MainWindow::on_danger_pushButton_clicked()
{
    QMessageBox msgbox2;
    msgbox2.setText("DANGER");
    msgbox2.setIcon(QMessageBox::Warning);
    msgbox2.exec();
}



