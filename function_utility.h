#ifndef FUNCTION_UTILITY_H
#define FUNCTION_UTILITY_H

#include <QString>
#include <QDebug>

#include <time.h>

#include "utama.h"

bool cek_delimiter(QString str);

int operasi_pangkat(int pangkat);
unsigned binary_to_decimal(QString str, int byte);

QString hex_to_binary(QString str, int byte);

#endif // FUNCTION_UTILITY_H
