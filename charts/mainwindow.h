#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStandardItemModel *theModel;
    void initData();
    void surveyData();

    void initBarChart();
    void buildBarChart();

    void initPieChart();
    void buildPieChart();

    void initStackedBar();
    void buildStackedBar();

    void initPercentBar();
    void buildPercentBar();

    void initScatterChart();
    void buildScatterChart();

private slots:
    void on_itemChanged(QStandardItem *item);

    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabBarClicked(int index);

    void on_tabWidget_tabBarDoubleClicked(int index);

    void on_PieSliceHighlight(bool show);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
