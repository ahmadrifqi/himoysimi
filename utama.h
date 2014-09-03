#ifndef UTAMA_H
#define UTAMA_H

#include <QString>

/* SUM OF CHAR */
#define  PHASE_ID       0
#define  PHASE_DATA     1

#define  TIME           2
#define  DATA           3

#define  BYTES2         4
#define  BYTES4         8
#define  BYTES8        16

#define  BIN2          16
#define  BIN4          32
#define  BIN8          64

#define  SIZE_ID_UKUR  4
#define  MAX_ID_UKUR   1100

#define  GMT7          25200

struct data_tabel{
    int id_ukur[64];
    int jumlah_id;

    QString waktu;
    int jumalh_data;
};
#endif //UTAMA_H



