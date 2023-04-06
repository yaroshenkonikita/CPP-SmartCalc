#include "graphplot.h"

#include "ui_graphplot.h"

using namespace s21;

GraphPlot::GraphPlot(QLineSeries *series_, int xAxisSize, int yAxisSize,
                     QWidget *parent)
    : QDialog(parent), ui(new Ui::GraphPlot), series(series_) {
  ui->setupUi(this);

  PrintAxis(xAxisSize, yAxisSize);

  if (series) {
    series->setColor("Blue");
    chart->addSeries(series);
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);
  }

  chart->legend()->hide();
  chartView->setChart(chart);

  ui->horizontalLayout->addWidget(chartView);
}

void GraphPlot::PrintAxis(int xAxisSize, int yAxisSize) {
  chart = new QChart();
  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  xAxis = new QValueAxis();
  xAxis->setTitleText("X");
  xAxis->setLabelFormat("%.1f");
  xAxis->setTickCount(9);
  chart->addAxis(xAxis, Qt::AlignLeft);

  yAxis = new QValueAxis();
  yAxis->setTitleText("Y");
  yAxis->setLabelFormat("%.1f");
  yAxis->setTickCount(9);
  chart->addAxis(yAxis, Qt::AlignBottom);

  xAxis->setRange(-xAxisSize, xAxisSize);
  yAxis->setRange(-yAxisSize, yAxisSize);

  seriesAxis = new QLineSeries();
  seriesAxis->append(0, -xAxisSize);
  seriesAxis->append(0, xAxisSize);
  seriesAxis->append(0, 0);

  seriesAxis->append(-yAxisSize, 0);
  seriesAxis->append(yAxisSize, 0);
  seriesAxis->setColor("Green");

  chart->addSeries(seriesAxis);

  seriesAxis->attachAxis(xAxis);
  seriesAxis->attachAxis(yAxis);
}

GraphPlot::~GraphPlot() {
  delete ui;
  delete series;
  delete xAxis;
  delete yAxis;
  delete chart;
  delete chartView;
}
