#include "mainwindow.h"
#include "ui_mainwindow.h"

struct data_tabel tabel;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QTextStream textStream;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open String File"), "./data/", "(*.str)");

    QFile StringFile(fileName);
    if(StringFile.open(QIODevice::ReadOnly)){
        QByteArray array = StringFile.readAll();
        StringFile.close();

        subwindow *subwin = new subwindow(this, array);
        subwin->setWindowTitle(fileName);
        ui->mdiArea->addSubWindow(subwin, 0);

        subwin->parentWidget()->resize(ui->mdiArea->width(), ui->mdiArea->height());
        subwin->show();
    }
}
