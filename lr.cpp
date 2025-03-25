#include <QDate>
#include <QDebug>

void MainWindow::processVariant() {
    QString inputText = ui->inputLineEdit->text();
    QVariant var;
    bool isNumber;
    int intValue = inputText.toInt(&isNumber);

    QDate dateValue = QDate::fromString(inputText, "dd.MM.yyyy");
    if (!dateValue.isValid()) {
        dateValue = QDate::fromString(inputText, "dd-MM-yyyy");
    }
    if (!dateValue.isValid()) {
        dateValue = QDate::fromString(inputText, "dd/MM/yyyy");
    }

    if (isNumber) {
        var = intValue;
    } else if (dateValue.isValid()) {
        var = dateValue;
    } else {
        var = inputText;
    }

    QString resultText;
    if (var.type() == QVariant::Int) {
        resultText = "Число: " + QString::number(var.toInt() * 2);
    } else if (var.type() == QVariant::Date) {
        resultText = "Дата: " + var.toDate().toString("dd.MM.yyyy");
    } else {
        resultText = "Строка: " + var.toString();
    }

    ui->resultLabel->setText(resultText);
}






///

#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <QObject>

class DataProcessor : public QObject {
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr) : QObject(parent) {}
signals:
    void dataProcessed(const QString &result);
};

#endif // DATA_PROCESSOR_H


///

#include "data_processor.h"

void DataProcessor::processData(const QString &input) {
    QString processedData = "Обработано: " + input;
    emit dataProcessed(processedData);
}