#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actOpenIODevice_triggered();

    void on_actSaveIODevice_triggered();

    void on_actOpenStream_triggered();

    void on_actSaveStream_triggered();

private:
    Ui::MainWindow *ui;

    bool openTextByIODevice(QString &fileName);
    bool saveTextByIODevice(QString &fileName);

    bool openTextByStream(const QString &fileName);
    bool saveTextByStream(const QString &fileName);
};
#endif // MAINWINDOW_H
