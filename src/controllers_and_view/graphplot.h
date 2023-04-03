#ifndef GRAPHPLOT_H_
#define GRAPHPLOT_H_

#include <QChartView>
#include <QDialog>
#include <QLineSeries>
#include <QMouseEvent>
#include <QtCharts>

namespace Ui {
class GraphPlot;
}

namespace s21 {

class GraphPlot : public QDialog {
  Q_OBJECT

 public:
  explicit GraphPlot(QLineSeries *series_ = nullptr, int xAxisSize = 1000000,
                     int yAxisSize = 1000000, QWidget *parent = nullptr);
  ~GraphPlot();

 private:
  void PrintAxis(int xAxisSize, int yAxisSize);

  Ui::GraphPlot *ui{};
  QLineSeries *series{}, *seriesAxis{};
  QValueAxis *xAxis{}, *yAxis{};
  QChart *chart{};
  QChartView *chartView{};
};

}  // namespace s21

#endif  // GRAPHPLOT_H_
