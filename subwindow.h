#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QStandardItem>

#include <time.h>
#include <QDateTime>
#include <QMessageBox>

#include "utama.h"
#include "function_utility.h"

namespace Ui {
class subwindow;
}

class subwindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit subwindow(QWidget *parent = 0, QByteArray array = 0);
    ~subwindow();
    
private:
    Ui::subwindow *ui;

    QStandardItemModel *model_data;

    bool time_range;

    char dat2B[5];
    char dat4B[9];
    char dat8B[17];

    char binary2B[17];
    char binary4B[33];
    char binary8B[65];

    int cnt2B;
    int cnt4B;
    int cnt8B;
    int cntdat;
    int cnt_id;
    int cnt_fdat;
    int cntdelimit;

    int jum_id;
    int phase;
    int p_iseng;
    int tipe_data;

    int temp_time_range;
    int ind_time;

    int time_start;
    int time_stop;
    int ind_start;

    QString code4;
    QString code8;

    QString str;

    int cek_corupt_sampah(int j_id, int j_dat);
    int sampah = 0;
    int corupt = 0;
};

#endif // SUBWINDOW_H
