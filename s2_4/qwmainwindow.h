#ifndef QWMAINWINDOW_H
#define QWMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class QWMainWindow; }
QT_END_NAMESPACE

class QWMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QWMainWindow(QWidget *parent = nullptr);
    ~QWMainWindow();

private slots:
    void on_txtEdit_copyAvailable(bool b);
    void on_txtEdit_selectionChanged();
    void on_spinBoxFontSize_valueChanged(int aFontSize);
    void on_comboFont_currentIndexChanged(const QString &arg1);
    void on_actFontBold_triggered(bool checked);

private:
     Ui::QWMainWindow *ui;
     QLabel *fLabCurFile;
     QProgressBar *progressBar1;
     QSpinBox *spinFontSize;
     QFontComboBox *comboFont;

     void initUI();
     void initSignalSlots();
};
#endif // QWMAINWINDOW_H
