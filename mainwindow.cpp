#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QProcess>

#include <iostream>
#include <exception>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(280, 150);
    statusBar()->showMessage("Welcome to show my hidden file application");

    // triggered about_qt
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionAbout_Applications, SIGNAL(triggered()), this, SLOT(onAboutClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString getDir = QFileDialog::getExistingDirectory(
                this, "Open Directory", "C://"
                );
    ui->lineEdit->setText(getDir);
}

void MainWindow::onAboutClicked()
{
    QMessageBox::about(this, tr("About Application"),
             tr("This applications can show hidding folder after malware attack"));
}

void MainWindow::on_okButton_clicked()
{
    QString dir = ui->lineEdit->text();
    if (dir.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please select a directory"));
        return;
    }

    QStringList args;
    args << "/C" << "attrib -s -h -a /s /d " + dir + "*.*";
    try {
        QProcess process;
        process.start("cmd.exe", args);
        process.waitForFinished(); // will wait forever until finished
        QMessageBox::information(this, tr("Success"),
                 tr("Success showing hidden files"));
    } catch (const exception& e) {
        QMessageBox::warning(this, tr("Warning"), tr(e.what()));
    }
}
