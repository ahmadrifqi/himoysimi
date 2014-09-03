#include "function_utility.h"

bool cek_delimiter(QString str){
    bool cek;

    if (str == "0d0a" || str == "0D0A") cek = true;
    else cek = false;

    return (bool) cek;
}

int operasi_pangkat(int pangkat){
    int hasil = 1;

    for (int i = 0; i < pangkat; i++){
        hasil *= 2;
    }

    return (int) hasil;
}

QString hex_to_binary(QString str, int byte){
    /* LITTLE ENDIEN */
    char temp[65];
    char dat[65];

    int len;

    QString binary = "";
    QString word;

    strcpy(temp, str.toLatin1());

    if (byte == BYTES2){
        dat[0] = temp[2];
        dat[1] = temp[3];
        dat[2] = temp[0];
        dat[3] = temp[1];

        len = BYTES2;
    }
    else if(byte == BYTES4){

        dat[0] = temp[6];
        dat[1] = temp[7];
        dat[2] = temp[4];
        dat[3] = temp[5];
        dat[4] = temp[2];
        dat[5] = temp[3];
        dat[6] = temp[0];
        dat[7] = temp[1];

        len = BYTES4;
    }

    for (int i = 0; i < len; i++){
       if (dat[i] == 'F' || dat[i] == 'f') word = "1111";
       if (dat[i] == 'E' || dat[i] == 'e') word = "1110";
       if (dat[i] == 'D' || dat[i] == 'd') word = "1101";
       if (dat[i] == 'C' || dat[i] == 'c') word = "1100";
       if (dat[i] == 'B' || dat[i] == 'b') word = "1011";
       if (dat[i] == 'A' || dat[i] == 'a') word = "1010";
       if (dat[i] == '9') word = "1001";
       if (dat[i] == '8') word = "1000";
       if (dat[i] == '7') word = "0111";
       if (dat[i] == '6') word = "0110";
       if (dat[i] == '5') word = "0101";
       if (dat[i] == '4') word = "0100";
       if (dat[i] == '3') word = "0011";
       if (dat[i] == '2') word = "0010";
       if (dat[i] == '1') word = "0001";
       if (dat[i] == '0') word = "0000";

       binary.sprintf("%s%s", binary.toAscii().data(), word.toAscii().data());
    }
    return (QString) binary;
}

unsigned binary_to_decimal(QString str, int byte){
    char temp[65];
    int decimal = 0;
    int len;

    strcpy(temp, str.toLatin1());

    if (byte == BYTES2){
        len = BIN2;
    }
    else if (byte == BYTES4){
        len = BIN4;
    }

    for (int i = 0; i < len; i++){
        if (temp[i] == '1'){
            decimal += operasi_pangkat(len-(i+1));
        }
    }

    return (unsigned) decimal;
}
