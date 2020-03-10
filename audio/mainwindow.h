#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QAudioRecorder>
#include <QAudioProbe>
#include <QMediaRecorder>
#include <QAudioDeviceInfo>
#include <QtCharts/QtCharts>
#include <QAudioInput>
#include <QCamera>
#include <QCameraImageCapture>

#include "qmydisplaydevice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMediaPlayer *player,*videoPlayer;
    QMediaPlaylist *playlist;
    QString duration,videoDuration;
    QString position,videoPosition;
    QAudioRecorder *recorder;
    QAudioProbe *probe;
    const qint64 displayPointsCount=4000;
    QLineSeries *lineSeries;
    QList<QAudioDeviceInfo> deviceList;
    QAudioDeviceInfo curDevice;
    QmyDisplayDevice *displayDevice{nullptr};
    QAudioInput *audioInput{nullptr};
    QString sampleTypeString(QAudioFormat::SampleType sampleType);
    QString byteOrderString(QAudioFormat::Endian endian);

    QCamera *curCamera=nullptr;
    QCameraImageCapture *imageCapture;
    QMediaRecorder *mediaRecorder;

    void initCamera();
    void initImageCapture();
    void initVideoRecorder();

private slots:
    void onStateChanged(QMediaPlayer::State state);
    void onPlaylistChanged(int position);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void on_btnAppend_clicked();
    void onVideoStateChanged(QMediaPlayer::State state);
    void onVideoDurationChanged(qint64 duration);
    void onVideoPositionChanged(qint64 position);

    void onRecordStateChanged(QMediaRecorder::State state);
    void onRecordDurationChanged(qint64 duration);
    void processBuffer(const QAudioBuffer& buffer);

    void onIODeviceUpdateBlockSize(qint64 blockSize);

    void on_btnRemove_clicked();

    void on_btnClear_clicked();

    void on_btnPlay_clicked();

    void on_btnStop_clicked();

    void on_btnSound_clicked();

    void on_soundness_valueChanged(int value);

    void on_slidePosition_valueChanged(int value);

    void on_btnRecord_clicked();

    void on_btnPauseRecord_clicked();

    void on_btnStopRecord_clicked();

    void on_btnSave_clicked();

    void on_comboInputDevices_currentIndexChanged(int index);

    void on_btnDeviceTest_clicked();

    void on_btnStart_clicked();

    void on_btnEnd_clicked();

    void on_btnAdd_clicked();

    void on_btnVideoPlay_clicked();

    void on_btnVideoPause_clicked();

    void on_btnVideoStop_clicked();

    void on_sliderVolumn_valueChanged(int value);

    void on_btnMute_clicked();

    void on_sliderVideoPosition_valueChanged(int value);

    void on_btnFullScreen_clicked();

    void on_cameraStateChanged(QCamera::State state);
    void on_cameraCaptureModeChanged(QCamera::CaptureModes mode);
    void on_imageReadyForCapture(bool ready);
    void on_imageCaptured(int id,const QImage &preview);
    void on_imageSaved(int id,const QString &fileName);
    void on_videoStateChanged(QMediaRecorder::State state);
    void on_videoDurationChanged(qint64 duration);

    void on_btnCameraOpen_clicked();

    void on_btnCameraClose_clicked();

    void on_btnCameraCapture_clicked();

    void on_btnCameraRecord_clicked();

    void on_btnCameraStop_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
