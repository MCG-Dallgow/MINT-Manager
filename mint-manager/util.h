#pragma once

#include <QList>

namespace Util {
    // get average of given values
    float average(QList<float> values)
    {
        // remove negative values and return 0 if empty
        values.removeIf([](float value) { return value < 0; });
        if (values.isEmpty()) return -1;

        // calculate sum of values
        float sum = 0;
        for (float value : values)
        {
            if (value >= 0) sum += value;
        }

        // calculate and return average
        return sum / (float)values.length();
    }

    // OVERLOAD - get average of given integer values
    float average(QList<int> values)
    {
        // cast int list to float list
        QList<float> valuesFloat;
        for (int value : values)
        {
            valuesFloat << (float)value;
        }

        return average(valuesFloat);
    }

    // format float with specified number of decimal places
    QString formatDecimal(float average, int places)
    {
        return QString::number(QString::number(average, 'f', places).toDouble(), 'g', 10);
    }
}
