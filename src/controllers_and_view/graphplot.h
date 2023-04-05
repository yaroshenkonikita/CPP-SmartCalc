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
/**
 * @brief Класс отрисовки графика по заданным QLineSeries
 */
class GraphPlot : public QDialog {
  Q_OBJECT

 public:
  explicit GraphPlot(
      QLineSeries *series_ = nullptr, int xAxisSize = 1000000,
      int yAxisSize = 1000000,
      QWidget *parent = nullptr);  ///< Дефолтный конструктор с вариационными
                                   ///< параметрами QLineSeries график функции,
                                   ///< размеры плота и  указателем на родителя
  ~GraphPlot();  ///< Дефолтный деструктор

 private:
  void PrintAxis(
      int xAxisSize,
      int yAxisSize);  ///< Функция отрисовки поля без серий QLineSeries

  Ui::GraphPlot *ui{};  ///< Указатель на View
  QLineSeries *series{},  ///< Указатель на график функций(серии QLineSeries)
      *seriesAxis{};  ///< Указатель на оси(серии QLineSeries)
  QValueAxis *xAxis{},      ///< Указатель на ось X
      *yAxis{};             ///< Указатель на ось Y
  QChart *chart{};          ///< Указатель на chart
  QChartView *chartView{};  ///< Указатель на chartView
};

}  // namespace s21

#endif  // GRAPHPLOT_H_
