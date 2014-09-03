#include "subwindow.h"
#include "ui_subwindow.h"

#include "qmath.h"

extern struct data_tabel tabel;

subwindow::subwindow(QWidget *parent, QByteArray array) :
    QWidget(parent),
    ui(new Ui::subwindow)
{
    ui->setupUi(this);

    model_data = new QStandardItemModel(this);

    phase = PHASE_ID;
    tipe_data = TIME;

    cnt2B  = 0;
    cnt4B  = 0;
    cnt8B  = 0;
    cntdat = 0;
    cnt_id = 1;
    cnt_fdat = 1;
    cntdelimit = 0;

    temp_time_range = 0;
    time_range = true;
    ind_time = 0;

    time_start = 0;
    time_stop  = 0;
    ind_start  = 0;

    jum_id = 0;

    for (int i = 0; i < BYTES2; i++){
        dat2B[i] = '-';
    }

    for (int i = 0; i < BYTES4; i++){
        dat4B[i] = '-';
    }

    for (int i = 0; i < BYTES8; i++){
        dat8B[i] = '-';
    }

    str = QString(array.toHex());
    char cr[str.size()];

    strcpy(cr, str.toLatin1());

    /* Get Id titik ukur */
    for (int i = 0; i < str.size(); i++){

        if (phase == PHASE_ID){
            dat2B[0] = dat2B[1];
            dat2B[1] = dat2B[2];
            dat2B[2] = dat2B[3];
            dat2B[3] = cr[i];

            code4.sprintf("%c%c%c%c", dat2B[0], dat2B[1], dat2B[2], dat2B[3]);

            bool yes = cek_delimiter(code4);

            cnt2B++;

            if (cnt2B == BYTES2){
                cnt2B = 0;

                if (yes == true){
                    qDebug() << "[DELIMITER]";
                    cntdelimit++;
                }
                else{
                    QString biner = hex_to_binary(code4, BYTES2);
                    int decimal = binary_to_decimal(biner, BYTES2);

                    QString decimal_string = QString::number(decimal);
                    if (decimal < MAX_ID_UKUR && decimal_string.size() == SIZE_ID_UKUR){
                        if (cnt_id == 1){
                            model_data->setHorizontalHeaderItem(0, new QStandardItem(QString("Waktu")));
                        };
                        model_data->setHorizontalHeaderItem(cnt_id, new QStandardItem(QString::number(decimal)));
                        cnt_id++;
                    }
                }
            }
            if (cntdelimit == 2) phase = PHASE_DATA;
        }
        else if(phase == PHASE_DATA){
            dat4B[0] = dat4B[1];
            dat4B[1] = dat4B[2];
            dat4B[2] = dat4B[3];
            dat4B[3] = dat4B[4];
            dat4B[4] = dat4B[5];
            dat4B[5] = dat4B[6];
            dat4B[6] = dat4B[7];
            dat4B[7] = cr[i];

            code4.sprintf("%c%c%c%c", dat4B[4], dat4B[5], dat4B[6], dat4B[7]);
            code8.sprintf("%c%c%c%c%c%c%c%c", dat4B[0], dat4B[1], dat4B[2], dat4B[3], dat4B[4], dat4B[5], dat4B[6], dat4B[7]);

            bool yes = cek_delimiter(code4);

            cnt4B++;

            if (yes == true){
                cnt4B = 0;
                //qDebug() << "[DELIMITER]";

                tipe_data = TIME;
                cntdelimit++;
            }

            if (cnt4B == BYTES4){
                cnt4B = 0;

                QString biner = hex_to_binary(code8, BYTES4);
                int decimal = binary_to_decimal(biner, BYTES4);

                if (tipe_data == TIME){
                    if (p_iseng == DATA){
                        cek_corupt_sampah(this->cnt_id, this->cnt_fdat);
                    }
                    cnt_fdat = 1;

                    if (ind_start == 0){
                        time_start = decimal;
                        ind_start = 1;
                    }
                    time_stop = decimal;

                    const QDateTime time = QDateTime::fromTime_t((decimal-GMT7));
                    QString epochtime = time.toString(Qt::TextDate).toAscii().data();

                    if (ind_time == 0){
                        temp_time_range = decimal;
                        ind_time = 1;
                    }
                    else if (ind_time == 1){
                        int cek = decimal - temp_time_range;

                        if (cek < 50 || cek > 70){
                            time_range = false;
                            ind_time = 2;
                        }
                        temp_time_range = decimal;
                    }

                    model_data->setItem(cntdat, 0, new QStandardItem(QString(epochtime)));

                    tipe_data = DATA;
                    cntdat++;
                }
                else{
                    p_iseng = tipe_data;

                    float data_f = *(float *) &decimal;

                    if (cnt_fdat > cnt_id){
                        model_data->setItem(cntdat-1, cnt_fdat, new QStandardItem(QString("SAMPAH")));

                    }
                    else{
                        model_data->setItem(cntdat-1, cnt_fdat, new QStandardItem(QString::number(data_f)));
                    }
                    cnt_fdat++;
                }                
            }
        }
    }

    cek_corupt_sampah(this->cnt_id, this->cnt_fdat);

    ui->tabel_data->setModel(model_data);
    ui->tabel_data->verticalHeader()->setHidden(true);

    QString record;
    int lama = (time_stop - time_start)/60;
    float round = ((time_stop - time_start)*1.00)/60;
    record.sprintf("- %d/%d data reccord, Rentang waktu %d menit %d detik.\r\n- %s\r\n- %s",
                   cntdat, qRound(round)+1, (time_stop - time_start)/60, (time_stop - time_start)%60,
                   (this->corupt?"Ada data corrupt.":"Tidak ada data corrupt."), (this->sampah?"Ada data sampah. ":"Tidak ada data sampah."));

    QString delay;
    if ((cntdat == qRound(+round)+1) && (this->corupt == 0) && (this->sampah == 0)){
        delay = "[  DATA NORMAL  ]";
    }
    else{
        delay = "[  DATA TIDAK NORMAL  ]";
    }

    QString msg;
    msg.sprintf("%s\r\n\r\n%s", record.toAscii().data(), delay.toAscii().data());

    QMessageBox::information(this, tr("[ STATUS ] : "), tr(msg.toAscii().data()), 0, 0);
}

subwindow::~subwindow()
{
    delete ui;
}

int subwindow::cek_corupt_sampah(int j_id, int j_dat){
    if (j_dat < j_id){
        this->corupt = 1;
    }
    else if (cnt_fdat > cnt_id){
        this->sampah = 1;
    }
}
