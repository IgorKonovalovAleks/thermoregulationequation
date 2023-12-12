#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <Q3DSurface>
#include <Q3DScatter>
#include <iostream>
#include <vector>
#include <QHeightMapSurfaceDataProxy>
#include <cmath>
#include "solver.h"
#include <fstream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget *leftWidget;
    QWidget *rightWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *splitLayout;
    QLineEdit *Nn;
    QLineEdit *Mn;
    QLineEdit *jn;
    QLineEdit *in;
    bool valid;
    Solver solver;

    QTableWidget *tableWidget;
    QChart *ichart;
    QChartView *ichartView;
    QChart *jchart;
    QChartView *jchartView;
    QValueAxis *iaxisX;
    QValueAxis *iaxisY;
    QValueAxis *jaxisX;
    QValueAxis *jaxisY;


    void onDrawButtonClicked();
    void onTableButtonClicked();
    void onClearPlotButtonClicked();
    void onTaskButtonClicked();
    void onSaveTableButtonClicked();
    void on3DPlotClicked();
};
#endif // MAINWINDOW_H
