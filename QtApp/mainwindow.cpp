#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    valid = false;
    this->setMinimumSize(1000, 700);
    //Создадим два виджета и поделим окошко сплитом пополам по вертикали
    QWidget *leftWidget = new QWidget(this);
    QWidget *rightWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *splitLayout = new QHBoxLayout;
    splitLayout->addWidget(leftWidget);
    splitLayout->addWidget(rightWidget);
    mainLayout->addLayout(splitLayout);
    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(mainLayout);

    //Создадим все поля ввода, текстовые обозначения и таблицу в левой части
    QLabel *label1 = new QLabel("Число разбиений по пространству:", leftWidget);
    QLabel *label2 = new QLabel("Число разбиений по времени:", leftWidget);
    Mn = new QLineEdit(leftWidget);
    Mn->setAlignment(Qt::AlignLeft);
    Mn->setText("100");
    Mn->setFixedWidth(150);
    Nn = new QLineEdit(leftWidget);
    Nn->setAlignment(Qt::AlignLeft);
    Nn->setText("100");
    Nn->setFixedWidth(150);
    QPushButton *drawButton = new QPushButton("Отрисовать", this);
    drawButton->setFixedWidth(150);
    QPushButton *tableButton  = new QPushButton("Таблица", this);
    tableButton->setFixedWidth(150);
    QPushButton *clearPlotButton = new QPushButton("Ограничение на шаг", this);
    clearPlotButton->setFixedWidth(150);
    QPushButton *taskButton = new QPushButton("Задача", this);
    taskButton->setFixedWidth(150);
    QPushButton* tSaveButton = new QPushButton("Сохранить таблицу", this);
    tSaveButton->setFixedWidth(150);
    QPushButton* fullPlotButton = new QPushButton("Полный график", this);
    fullPlotButton->setFixedWidth(150);
    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addWidget(label1, 0, 0);
    leftLayout->addWidget(Nn, 0, 1);
    leftLayout->addWidget(label2, 1, 0);
    leftLayout->addWidget(Mn, 1, 1);
    leftLayout->addWidget(drawButton, 2, 0);
    leftLayout->addWidget(tableButton, 2, 1);
    leftLayout->addWidget(clearPlotButton, 3, 0);
    leftLayout->addWidget(taskButton, 3, 1);
    leftLayout->addWidget(tSaveButton, 4, 0);
    leftLayout->addWidget(fullPlotButton, 4, 1);
    tableWidget = new QTableWidget(leftWidget);
    leftLayout->addWidget(tableWidget, 5, 0, 1, 3);
    leftWidget->setLayout(leftLayout);


    ichart = new QChart();
    ichart->createDefaultAxes();
    ichart->setAnimationOptions(QChart::AllAnimations);
    ichart->legend()->setVisible(false);
    ichart->legend()->setAlignment(Qt::AlignBottom);

    iaxisX = new QValueAxis;
    iaxisX->setTitleText("X");
    ichart->addAxis(iaxisX, Qt::AlignBottom);
    iaxisX->setGridLineVisible(true);

    iaxisY = new QValueAxis;
    iaxisY->setTitleText("U");
    ichart->addAxis(iaxisY, Qt::AlignLeft);
    iaxisY->setGridLineVisible(true);

    iaxisX->setGridLineVisible(true);
    iaxisY->setGridLineVisible(true);

    ichart->setMargins(QMargins(0, 0, 0, 0));

    ichartView = new QChartView(ichart);
    ichartView->setRenderHint(QPainter::Antialiasing, true);
    ichartView->setInteractive(true);
    ichartView->setRubberBand(QChartView::RectangleRubberBand);
    ichartView->setDragMode(QGraphicsView::ScrollHandDrag);
    ichartView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    jchart = new QChart();
    jchart->createDefaultAxes();
    jchart->setAnimationOptions(QChart::AllAnimations);
    jchart->legend()->setVisible(false);
    jchart->legend()->setAlignment(Qt::AlignBottom);

    jaxisX = new QValueAxis;
    jaxisX->setTitleText("X");
    jchart->addAxis(jaxisX, Qt::AlignBottom);
    jaxisX->setGridLineVisible(true);

    jaxisY = new QValueAxis;
    jaxisY->setTitleText("U");
    jchart->addAxis(jaxisY, Qt::AlignLeft);
    jaxisY->setGridLineVisible(true);

    jaxisX->setGridLineVisible(true);
    jaxisY->setGridLineVisible(true);

    jchart->setMargins(QMargins(0, 0, 0, 0));

    jchartView = new QChartView(jchart);
    jchartView->setRenderHint(QPainter::Antialiasing, true);
    jchartView->setInteractive(true);
    jchartView->setRubberBand(QChartView::RectangleRubberBand);
    jchartView->setDragMode(QGraphicsView::ScrollHandDrag);
    jchartView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    QGridLayout *rightLayout = new QGridLayout(rightWidget);
    QLabel *label3 = new QLabel("Срез по времени j = ", rightWidget);
    label3->setAlignment(Qt::AlignRight);
    QLabel *label4 = new QLabel("Судьба узла i = ", rightWidget);
    label4->setAlignment(Qt::AlignRight);
    in = new QLineEdit(leftWidget);
    in->setAlignment(Qt::AlignLeft);
    in->setText("0");
    in->setFixedWidth(160);
    jn = new QLineEdit(leftWidget);
    jn->setAlignment(Qt::AlignLeft);
    jn->setText("0");
    jn->setFixedWidth(160);

    rightLayout->addWidget(jchartView, 0, 0, 1, 2);
    rightLayout->addWidget(label3, 1, 0);
    rightLayout->addWidget(jn, 1, 1);
    rightLayout->addWidget(ichartView, 2, 0, 1, 2);
    rightLayout->addWidget(label4, 3, 0);
    rightLayout->addWidget(in, 3, 1);
    rightWidget->setLayout(rightLayout);

    connect(drawButton, &QPushButton::clicked, this, &MainWindow::onDrawButtonClicked);
    connect(tableButton, &QPushButton::clicked, this, &MainWindow::onTableButtonClicked);
    connect(clearPlotButton, &QPushButton::clicked, this, &MainWindow::onClearPlotButtonClicked);
    connect(taskButton, &QPushButton::clicked, this, &MainWindow::onTaskButtonClicked);
    connect(tSaveButton, &QPushButton::clicked, this, &MainWindow::onSaveTableButtonClicked);
    connect(fullPlotButton, &QPushButton::clicked, this, &MainWindow::on3DPlotClicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onDrawButtonClicked(){
    int m = Mn->text().toInt();
    int n = Nn->text().toInt();
    int i = in->text().toInt();
    int j = jn->text().toInt();
    if (solver.N != n || solver.M != m) {
        solver.solve(n, m);
    }
    ichart->removeAllSeries();
    ichart->createDefaultAxes();
    jchart->removeAllSeries();
    jchart->createDefaultAxes();
    QLineSeries* iseries = new QLineSeries();
    QLineSeries* jseries = new QLineSeries();
    double tau = solver.tau, h = solver.h;
    if (solver.N + 1 > 100) 
        h = 0.01;
    if (solver.M + 1 > 100)
        tau = 0.1;
    for (int k = 0; k < std::min(solver.N + 1, 100); k++) {
        iseries->append(k * h, solver.v[j][std::max((solver.N + 1) / 100 * k, k)]);
    }
    for (int k = 0; k < std::min(solver.M + 1, 100); k++) {
        jseries->append(k * tau, solver.v[std::max((solver.M + 1) / 100 * k, k)][i]);
    }
    ichart->addSeries(jseries);
    jchart->addSeries(iseries);
    ichart->createDefaultAxes();
    ichart->zoomReset();
    jchart->createDefaultAxes();
    jchart->zoomReset();
}

void MainWindow::onTableButtonClicked(){
    int m = Mn->text().toInt();
    int n = Nn->text().toInt();
    if (solver.N != n || solver.M != m) {
        solver.solve(n, m);
    }
    tableWidget->clearContents();
    tableWidget->clear();
    tableWidget->setColumnCount(0);
    tableWidget->setRowCount(0);
    tableWidget->verticalHeader()->hide();
    QHeaderView *header = tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidget->setSortingEnabled(false);
    tableWidget->setColumnCount(std::min(m + 2, 51));
    QStringList columnHeaders;
    columnHeaders.append(QString("i, j"));
    for (int i = 0; i < std::min(m + 1, 50); ++i) { // а можно и так
        columnHeaders.append(QString::number(i));
    }
    tableWidget->setHorizontalHeaderLabels(columnHeaders);
    for (int j = 0; j < std::min(n + 1, 50); ++j) {
        tableWidget->insertRow(j);
        tableWidget->setItem(j, 0, new QTableWidgetItem(QString::number(j)));
        for (int i = 0; i < std::min(m + 1, 50); ++i) {
            tableWidget->setItem(j, i + 1, new QTableWidgetItem(QString::number(solver.v[i][j])));
        }
    }
    
}

void MainWindow::onClearPlotButtonClicked(){
    QDialog* imageDialog = new QDialog(this);
    imageDialog->setWindowTitle("Ограничение на шаг");
    QLabel* imageLabel = new QLabel(imageDialog);
    if (solver.tau < (solver.h) * (solver.h) / (2 * sqrt(3)))
        imageLabel->setText("Условие на шаг выполнено");
    else
        imageLabel->setText("Условие на шаг не выполнено");
    QVBoxLayout* layout = new QVBoxLayout(imageDialog);
    layout->addWidget(imageLabel);
    imageLabel->setMaximumSize(300, 300);
    layout->addWidget(imageLabel);
    imageDialog->exec();
}

void MainWindow::onTaskButtonClicked(){
    QDialog *imageDialog= new QDialog(this);
    imageDialog->setWindowTitle("Задача");
    QLabel *imageLabel = new QLabel(imageDialog);
    imageLabel->setPixmap(QPixmap("task1.png"));
    QVBoxLayout *layout = new QVBoxLayout(imageDialog);
    layout->addWidget(imageLabel);
    imageLabel->setMaximumSize(800, 800);
    imageLabel->setScaledContents(true);
    layout->addWidget(imageLabel);
    imageDialog->exec();
}

void MainWindow::onSaveTableButtonClicked()
{
    int m = Mn->text().toInt();
    int n = Nn->text().toInt();
    if (solver.N != n || solver.M != m) {
        solver.solve(n, m);
    }

    std::ofstream myfile;

    myfile.open("table.csv");
    myfile << "i\j" << ';';
    for (int i = 0; i < solver.M + 1; i++) {
        myfile << i << ';';
    }
    myfile << "\n";
    for (int i = 0; i < solver.N + 1; i++) {
        myfile << i << ';';
        for (int j = 0; j < solver.M + 1; j++) {
            myfile << solver.v[j][i] << ';';
        }
        myfile << '\n';
    }
    myfile.close();
}

void MainWindow::on3DPlotClicked() //закоментил все что должно было делать градиент, но не работает
{
    
    int m = Mn->text().toInt();
    int n = Nn->text().toInt();
    if (solver.N != n || solver.M != m) {
        solver.solve(n, m);
    }

    Q3DSurface *surface = new Q3DSurface();
    QSurfaceDataArray* data = new QSurfaceDataArray;
    //заполнение 
    for (double j = 0; j <= solver.M; j++) {
        QSurfaceDataRow* dataRow = new QSurfaceDataRow;
        for (double i = 0; i <= solver.N; i++) {
            *dataRow << QVector3D(i * solver.h, solver.v[j][i], j * solver.tau);
        }
        *data << dataRow;
        
    }

    QSurface3DSeries* series = new QSurface3DSeries;
    series->dataProxy()->resetArray(data);
    surface->addSeries(series);

    //QImage heightMapImage(":/maps/mountain");
    //auto m_heightMapProxy = new QHeightMapSurfaceDataProxy(heightMapImage);
    //auto m_heightMapSeries = new QSurface3DSeries(m_heightMapProxy);
    //m_heightMapSeries->setItemLabelFormat(QStringLiteral("(@xLabel, @zLabel): @yLabel"));
    //m_heightMapProxy->setValueRanges(34.0f, 40.0f, 18.0f, 24.0f);

    //QLinearGradient gr;
    //gr.setColorAt(0.0, Qt::black);
    //gr.setColorAt(0.33, Qt::blue);
    //gr.setColorAt(0.67, Qt::red);
    //gr.setColorAt(1.0, Qt::yellow);

    //surface->seriesList().at(0)->setBaseGradient(gr);
    //surface->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    auto* container = QWidget::createWindowContainer(surface);
    auto* widget = new QWidget;
    auto* hLayout = new QHBoxLayout(widget);
    hLayout->addWidget(container, 1);

    widget->show();

}
