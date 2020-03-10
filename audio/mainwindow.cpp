#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QCameraInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player=new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    ui->soundness->setValue(30);
    ui->btnPlay->setEnabled(false);
    player->setVolume(30);

    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(onStateChanged(QMediaPlayer::State)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(onPositionChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(onDurationChanged(qint64)));
    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(onPlaylistChanged(int)));

    recorder= new QAudioRecorder(this);
    connect(recorder,SIGNAL(stateChanged(QMediaRecorder::State)),this,SLOT(onRecordStateChanged(QMediaRecorder::State)));
    connect(recorder,SIGNAL(durationChanged(qint64)),this,SLOT(onRecordDurationChanged(qint64)));

    probe=new QAudioProbe;
    connect(probe,SIGNAL(audioBufferProbed(QAudioBuffer)),this,SLOT(processBuffer(QAudioBuffer)));
    probe->setSource(recorder);

    if(recorder->defaultAudioInput().isEmpty())
        return;
    foreach(const QString &device,recorder->audioInputs())
    {
        ui->comboDevices->addItem(device);
    }
    foreach(const QString &codecName,recorder->supportedAudioCodecs())
    {
        ui->comboCodec->addItem(codecName);
    }
    foreach(int sampleRate,recorder->supportedAudioSampleRates())
    {
        ui->comboSampleRate->addItem(QString::number(sampleRate));
    }

    ui->comboChannels->addItem("1");
    ui->comboChannels->addItem("2");
    ui->comboChannels->addItem("4");

    ui->sliderQuallity->setRange(0,int(QMultimedia::VeryHighQuality));
    ui->sliderQuallity->setValue(int(QMultimedia::NormalQuality));

    ui->comboBitRate->addItem("32000");
    ui->comboBitRate->addItem("64000");
    ui->comboBitRate->addItem("96000");
    ui->comboBitRate->addItem("128000");

    QChart *chart=new QChart;
    chart->setTitle("Audio orignal input signal");
    ui->chartView->setChart(chart);

    lineSeries=new QLineSeries;
    chart->addSeries(lineSeries);

    QValueAxis *axisX=new QValueAxis;
    axisX->setRange(0,displayPointsCount);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    QValueAxis *axisY=new QValueAxis;
    axisY->setRange(0,256);
    axisY->setTitleText("Audio level");

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);

    chart->legend()->hide();

    ui->comboInputDevices->clear();
    deviceList=QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for(auto device:deviceList)
    {
        ui->comboInputDevices->addItem(device.deviceName());
    }
    if(deviceList.size()>0)
    {
        ui->comboInputDevices->setCurrentIndex(0);
        curDevice=deviceList[0];
    }
    else
    {
        ui->btnStart->setEnabled(false);
        ui->btnDeviceTest->setEnabled(false);
        ui->groupBoxDevice->setTitle("支持的音频输入设置(none)");
    }

    videoPlayer=new QMediaPlayer(this);
    videoPlayer->setNotifyInterval(1000);
    videoPlayer->setVideoOutput(ui->videoWidget);
    videoPlayer->setVolume(30);
    ui->videoWidget->setMediaPlayer(videoPlayer);
    connect(videoPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(onVideoStateChanged(QMediaPlayer::State)));
    connect(videoPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(onVideoPositionChanged(qint64)));
    connect(videoPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(onVideoDurationChanged(qint64)));

    QList<QCameraInfo> cameras=QCameraInfo::availableCameras();
    if(cameras.size()>0)
    {
        initCamera();
        initImageCapture();
        initVideoRecorder();
        curCamera->start();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStateChanged(QMediaPlayer::State state)
{
    if(state==QMediaPlayer::PlayingState)
    {
        QIcon icon(":pause.PNG");
        ui->btnPlay->setIcon(icon);
    }
    else
    {
        QIcon icon(":play.png");
        ui->btnPlay->setIcon(icon);
    }
    ui->btnStop->setEnabled(state==QMediaPlayer::PlayingState);
}

void MainWindow::onPlaylistChanged(int position)
{
    ui->listWidget->setCurrentRow(position);
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(item)
    {
        ui->labelCurMedia->setText("当前曲目："+item->text());
    }
}

void MainWindow::onDurationChanged(qint64 duration)
{
    ui->slidePosition->setMaximum(duration);
    int secs=duration/1000;
    int mins=secs/60;
    secs%=60;
    this->duration=QString::asprintf("%02d:%02d",mins,secs);
    ui->labelRatio->setText(this->position+"/"+this->duration);
}

void MainWindow::onPositionChanged(qint64 position)
{
    if(ui->slidePosition->isSliderDown())
        return;
    ui->slidePosition->setSliderPosition(position);
    int secs=position/1000;
    int mins=secs/60;
    secs%=60;
    this->position=QString::asprintf("%02d:%02d",mins,secs);
    ui->labelRatio->setText(this->position+"/"+this->duration);
}
void MainWindow::on_btnAppend_clicked()
{
    QString curPath=QDir::homePath();
    QString dlgTitle="Select audio file";
    QString filter="Audio file(*.mp3 *.wav *.wma);;mp3(*.mp3);;wav(*.wav);;wma(*.wma);;All file(*.*)";
    QStringList fileList=QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
    if(fileList.count()<1)
    {
        return;
    }
    for(auto file:fileList)
    {
        playlist->addMedia(QUrl::fromLocalFile(file));
        QFileInfo fileInfo(file);
        ui->listWidget->addItem(fileInfo.fileName());
    }
    ui->btnPlay->setEnabled(true);
    if(player->state()!=QMediaPlayer::PlayingState)
    {
        playlist->setCurrentIndex(0);
    }
    player->play();
}



void MainWindow::on_btnRemove_clicked()
{
    int pos=ui->listWidget->currentRow();
    QListWidgetItem *item=ui->listWidget->takeItem(pos);
    delete item;
    playlist->removeMedia(pos);
}

void MainWindow::on_btnClear_clicked()
{
    playlist->clear();
    ui->listWidget->clear();
    player->stop();
}

void MainWindow::on_btnPlay_clicked()
{
    if(playlist->mediaCount()<1)
        return;
    if(player->state()==QMediaPlayer::PlayingState)
    {
        QIcon icon(":play.png");
        ui->btnPlay->setIcon(icon);
        player->pause();
    }
    else
    {
        QIcon icon(":pause.png");
        ui->btnPlay->setIcon(icon);
        if(playlist->currentIndex()<0)
            playlist->setCurrentIndex(0);
        player->play();
    }
}



void MainWindow::on_btnStop_clicked()
{
    player->stop();
}


void MainWindow::on_btnSound_clicked()
{
    bool mute=player->isMuted();
    player->setMuted(!mute);
    if(mute)
    {
        ui->btnSound->setIcon(QIcon(":sound.png"));
    }
    else
    {
        ui->btnSound->setIcon(QIcon(":mute.png"));
    }
}

void MainWindow::on_soundness_valueChanged(int value)
{
    player->setVolume(value);
}

void MainWindow::on_slidePosition_valueChanged(int value)
{
    player->setPosition(value);
}

void MainWindow::onRecordStateChanged(QMediaRecorder::State state)
{
    ui->btnRecord->setEnabled(state!=QMediaRecorder::RecordingState);
    ui->btnPauseRecord->setEnabled(state==QMediaRecorder::RecordingState);
    ui->btnStopRecord->setEnabled(state==QMediaRecorder::RecordingState);
    ui->btnSave->setEnabled(state==QMediaRecorder::StoppedState);
    ui->editOutputFile->setEnabled(state==QMediaRecorder::StoppedState);
}

void MainWindow::onRecordDurationChanged(qint64 duration)
{
    ui->labPassTime->setText(QString::asprintf("Recorded %lld seconds",duration/1000));
}

void MainWindow::on_btnRecord_clicked()
{
    if(recorder->state()==QMediaRecorder::StoppedState)
    {
        QString selectedFile=ui->editOutputFile->text().trimmed();
        if(selectedFile.isEmpty())
        {
            QMessageBox::critical(this,"Error","Set record output file first");
            return;
        }
        if(QFile::exists(selectedFile))
        {
            if(!QFile::remove(selectedFile))
            {
                QMessageBox::critical(this,"Errof","Cannot reset output file");
                return;
            }
        }
        recorder->setOutputLocation(QUrl::fromLocalFile(selectedFile));
        recorder->setAudioInput(ui->comboDevices->currentText());

        QAudioEncoderSettings setting;
        setting.setCodec(ui->comboCodec->currentText());
        setting.setSampleRate(ui->comboSampleRate->currentText().toInt());
        setting.setBitRate(ui->comboBitRate->currentText().toInt());
        setting.setChannelCount(ui->comboChannels->currentText().toInt());
        setting.setQuality(QMultimedia::EncodingQuality(ui->sliderQuallity->value()));
        if(ui->rbQuality->isChecked())
        {
            setting.setEncodingMode(QMultimedia::ConstantQualityEncoding);
        }
        else
        {
            setting.setEncodingMode(QMultimedia::ConstantBitRateEncoding);
        }
        recorder->setAudioSettings(setting);
    }
    recorder->record();
}

void MainWindow::on_btnPauseRecord_clicked()
{
    recorder->pause();
}

void MainWindow::on_btnStopRecord_clicked()
{
    recorder->stop();
}

void MainWindow::on_btnSave_clicked()
{
    QString curPath=QDir::currentPath();
    QString fileName=QFileDialog::getSaveFileName(this,"Input or select a file",curPath);
    if(!fileName.isEmpty())
        ui->editOutputFile->setText(fileName);
}

void MainWindow::processBuffer(const QAudioBuffer &buffer)
{
    ui->spinBufferSize->setValue(buffer.byteCount());
    ui->spinBufferDuration->setValue(buffer.duration()/1000);
    ui->spinBufferFrame->setValue(buffer.frameCount());
    ui->spinBufferSample->setValue(buffer.sampleCount());

    QAudioFormat audioFormat=buffer.format();
    ui->spinChannelCount->setValue(audioFormat.channelCount());
    ui->spinSampleSize->setValue(audioFormat.sampleSize());
    ui->spinBytesPerFrame->setValue(audioFormat.bytesPerFrame());
    ui->spinSampleRate->setValue(audioFormat.sampleRate());
    if(audioFormat.byteOrder()==QAudioFormat::LittleEndian)
        ui->editByteOrder->setText("Little Endian");
    else
        ui->editByteOrder->setText("Big Endian");
    ui->editCodec->setText(audioFormat.codec());
    if(audioFormat.sampleType()==QAudioFormat::SignedInt)
        ui->editSampleType->setText("Signed Int");
    else if(audioFormat.sampleType()==QAudioFormat::UnSignedInt)
        ui->editSampleType->setText("Unsigned Int");
    else if(audioFormat.sampleType()==QAudioFormat::Float)
        ui->editSampleType->setText("Float");
    else
        ui->editSampleType->setText("Unknown");

}
void MainWindow::on_comboInputDevices_currentIndexChanged(int index)
{
    curDevice=deviceList[index];

    ui->cbCodec->clear();
    for(auto codec:curDevice.supportedCodecs())
    {
        ui->cbCodec->addItem(codec);
    }

    ui->cbSamplRate->clear();
    for(auto sampleRate:curDevice.supportedSampleRates())
    {
        ui->cbSamplRate->addItem(QString("%1").arg(sampleRate));
    }

    ui->cbChannels->clear();
    for(auto channel:curDevice.supportedChannelCounts())
    {
        ui->cbChannels->addItem(QString("%1").arg(channel));
    }

    ui->cbSampleType->clear();
    for(auto sampletype:curDevice.supportedSampleTypes())
    {
        ui->cbSampleType->addItem(sampleTypeString(sampletype),QVariant(sampletype));
    }

    ui->cbSampleSize->clear();
    for(auto samplSize:curDevice.supportedSampleSizes())
    {
        ui->cbSampleSize->addItem(QString("%1").arg(samplSize));
    }

    ui->cbByteOrder->clear();
    for(auto endian:curDevice.supportedByteOrders())
    {
        ui->cbByteOrder->addItem(byteOrderString(endian));
    }
}

QString MainWindow::sampleTypeString(QAudioFormat::SampleType sampleType)
{
    QString result("Unknown");
    switch(sampleType)
    {
    case QAudioFormat::SignedInt:
        result="SignedInt";
        break;
    case QAudioFormat::UnSignedInt:
        result="UnSignedInt";
        break;
    case QAudioFormat::Float:
        result="Float";
        break;
    case QAudioFormat::Unknown:
        result="Unknown";
        break;
    }
    return result;
}

QString MainWindow::byteOrderString(QAudioFormat::Endian endian)
{
    if(endian==QAudioFormat::LittleEndian)
        return "LittleEndian";
    else if(endian==QAudioFormat::BigEndian)
        return "BigEndian";
    else
        return "Unknown";
}
void MainWindow::on_btnDeviceTest_clicked()
{
    QAudioFormat settings;
    settings.setCodec(ui->cbCodec->currentText());
    settings.setSampleRate(ui->cbSamplRate->currentText().toInt());
    settings.setChannelCount(ui->cbChannels->currentText().toInt());
    settings.setSampleType(QAudioFormat::SampleType(ui->cbSampleType->currentData().toInt()));
    settings.setSampleSize(ui->cbSampleSize->currentText().toInt());
    if(ui->cbByteOrder->currentText()=="LittleEndian")
    {
        settings.setByteOrder(QAudioFormat::LittleEndian);
    }
    else
    {
        settings.setByteOrder(QAudioFormat::BigEndian);
    }

    if(curDevice.isFormatSupported(settings))
    {
        QMessageBox::information(this,"Audio test","Test success,this device supportted");
    }
    else
    {
        QMessageBox::critical(this,"Audio test","Test failed,this device unsupportted");
    }
}

void MainWindow::onIODeviceUpdateBlockSize(qint64 blockSize)
{
    ui->labBufferSize->setText(QString::asprintf("QAudioInput:bufferSize=%d",audioInput->bufferSize()));
    ui->labBlockSize->setText(QString("IODevice data block size=%1").arg(blockSize));
}

void MainWindow::on_btnStart_clicked()
{
    QAudioFormat defaultAudioFormat;
    defaultAudioFormat.setSampleRate(8000);
    defaultAudioFormat.setChannelCount(1);
    defaultAudioFormat.setSampleSize(8);
    defaultAudioFormat.setCodec("audio/pcm");
    defaultAudioFormat.setByteOrder(QAudioFormat::LittleEndian);
    defaultAudioFormat.setSampleType(QAudioFormat::UnSignedInt);
    if(!curDevice.isFormatSupported(defaultAudioFormat))
    {
        QMessageBox::critical(this,"Test","Test failed,this device unsupportted");
        return;
    }

    audioInput=new QAudioInput(curDevice,defaultAudioFormat,this);
    audioInput->setBufferSize(displayPointsCount);
    displayDevice=new QmyDisplayDevice(lineSeries,displayPointsCount,this);
    connect(displayDevice,SIGNAL(updateBlockSize(qint64)),this,SLOT(onIODeviceUpdateBlockSize(qint64)));
    displayDevice->open(QIODevice::WriteOnly);

    audioInput->start(displayDevice);
    ui->btnStart->setEnabled(false);
    ui->btnEnd->setEnabled(true);
}

void MainWindow::on_btnEnd_clicked()
{
    if(audioInput)
    {
        audioInput->stop();
        ui->btnStart->setEnabled(true);
        ui->btnEnd->setEnabled(true);
    }
}

void MainWindow::onVideoStateChanged(QMediaPlayer::State state)
{
    ui->btnVideoPlay->setEnabled(state!=QMediaPlayer::PlayingState);
    ui->btnVideoPause->setEnabled(state==QMediaPlayer::PlayingState);
    ui->btnVideoStop->setEnabled(state==QMediaPlayer::PlayingState);
}

void MainWindow::onVideoDurationChanged(qint64 duration)
{
    ui->sliderVideoPosition->setMaximum(duration);
    int second=duration/1000;
    int minute=second/60;
    second%=60;
    videoDuration=QString::asprintf("%02d:%02d",minute,second);
    ui->labRatio->setText(videoPosition+"/"+videoDuration);
}

void MainWindow::onVideoPositionChanged(qint64 position)
{
    if(ui->sliderVideoPosition->isSliderDown())
        return;
    ui->sliderVideoPosition->setSliderPosition(position);
    int second=position/1000;
    int minute=second/60;
    second%=60;
    videoPosition=QString::asprintf("%02d:%02d",minute,second);
    ui->labRatio->setText(videoPosition+"/"+videoDuration);
}

void MainWindow::on_btnAdd_clicked()
{
    QString curPath=QDir::homePath();
    QString dlgTitle="Select a video file";
    QString filter="wmv file(*.wmv);;mp4 file(*.mp4);;all file(*.*)";
    QString file=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(file.isEmpty())
    {
        return;
    }
    QFileInfo fileInfo(file);
    ui->labCurMedia->setText(fileInfo.fileName());
    videoPlayer->setMedia(QUrl::fromLocalFile(file));
    videoPlayer->play();
}

void MainWindow::on_btnVideoPlay_clicked()
{
    videoPlayer->play();
}

void MainWindow::on_btnVideoPause_clicked()
{
    videoPlayer->pause();
}

void MainWindow::on_btnVideoStop_clicked()
{
    videoPlayer->stop();
}

void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    videoPlayer->setVolume(value);
}

void MainWindow::on_btnMute_clicked()
{
    bool mute=videoPlayer->isMuted();
    videoPlayer->setMuted(!mute);
    if(mute)
        ui->btnMute->setIcon(QIcon(":sound.png"));
    else
        ui->btnMute->setIcon(QIcon(":mute.png"));
}

void MainWindow::on_sliderVideoPosition_valueChanged(int value)
{
    if(ui->sliderVideoPosition->isSliderDown())
        videoPlayer->setPosition(value);
}

void MainWindow::on_btnFullScreen_clicked()
{
    ui->videoWidget->setFullScreen(true);
}

void MainWindow::initCamera()
{
    QCameraInfo curCameraInfo=QCameraInfo::defaultCamera();
    ui->comboCamera->addItem(curCameraInfo.description());
    ui->comboCamera->setCurrentIndex(0);

    curCamera=new QCamera(curCameraInfo,this);
    QCameraViewfinderSettings viewfinderSettings;
    viewfinderSettings.setResolution(640,480);
//    viewfinderSettings.setMaximumFrameRate(30.0);
//    viewfinderSettings.setMinimumFrameRate(15.0);
    curCamera->setViewfinderSettings(viewfinderSettings);
    curCamera->setViewfinder(ui->viewFinder);
    curCamera->setCaptureMode(QCamera::CaptureViewfinder);
    ui->checkStillImage->setChecked(curCamera->isCaptureModeSupported(QCamera::CaptureStillImage));
    ui->checkVideo->setChecked(curCamera->isCaptureModeSupported(QCamera::CaptureVideo));

    connect(curCamera,SIGNAL(stateChanged(QCamera::State)),this,SLOT(on_cameraStateChanged(QCamera::State)));
    connect(curCamera,SIGNAL(captureModeChanged(QCamera::CaptureModes)),this,SLOT(on_cameraCaptureModeChanged(QCamera::CaptureModes)));
}

void MainWindow::on_cameraStateChanged(QCamera::State state)
{
    switch(state)
    {
    case QCamera::UnloadedState:
        ui->labCameraState->setText("Camera state:UnloadedState");
        break;
    case QCamera::LoadedState:
        ui->labCameraState->setText("Camera state:LoadedState");
        break;
    case QCamera::ActiveState:
        ui->labCameraState->setText("Camera state:ActiveState");
        break;
    }
    ui->btnCameraOpen->setEnabled(state!=QCamera::ActiveState);
    ui->btnCameraClose->setEnabled(state==QCamera::ActiveState);
}

void MainWindow::on_cameraCaptureModeChanged(QCamera::CaptureModes mode)
{
    if(mode==QCamera::CaptureStillImage)
    {
        ui->labCameraMode->setText("Capture Mode:StillImage");
    }
    else if(mode==QCamera::CaptureStillImage)
    {
        ui->labCameraMode->setText("Capture Mode:Video");
    }
    else
    {
        ui->labCameraMode->setText("Capture Mode:ViewFinder");

    }
}
void MainWindow::on_btnCameraOpen_clicked()
{
    curCamera->start();
}

void MainWindow::on_btnCameraClose_clicked()
{
    curCamera->stop();
}

void MainWindow::initImageCapture()
{
    imageCapture=new QCameraImageCapture(curCamera,this);
    imageCapture->setBufferFormat(QVideoFrame::Format_Jpeg);
    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    connect(imageCapture,SIGNAL(readyForCaptureChanged(bool)),this,SLOT(on_imageReadyForCapture(bool)));
    connect(imageCapture,SIGNAL(imageCaptured(int,const QImage &)),this,SLOT(on_imageCaptured(int,const QImage&)));
    connect(imageCapture,SIGNAL(imageSaved(int,const QString &)),this,SLOT(on_imageSaved(int,const QString&)));
}

void MainWindow::on_imageReadyForCapture(bool ready)
{
    ui->btnCameraCapture->setEnabled(ready);
}

void MainWindow::on_imageCaptured(int id,const QImage &preview)
{
    Q_UNUSED(id)
    QImage scaledImage=preview.scaled(ui->labCapturedImage->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->labCapturedImage->setPixmap(QPixmap::fromImage(scaledImage));
}

void MainWindow::on_imageSaved(int id,const QString &fileName)
{
    Q_UNUSED(id)
    ui->labInfo->setText("Image saved as:"+fileName);
}

void MainWindow::initVideoRecorder()
{
    mediaRecorder=new QMediaRecorder(curCamera,this);
    ui->checkMute->setChecked(mediaRecorder->isMuted());
    connect(mediaRecorder,SIGNAL(stateChanged(QMediaRecorder::State)),this,SLOT(on_videoStateChanged(QMediaRecorder::State)));
    connect(mediaRecorder,SIGNAL(durationChanged(qint64)),this,SLOT(on_videoDurationChanged(qint64)));
}

void MainWindow::on_videoStateChanged(QMediaRecorder::State state)
{
    ui->btnCameraRecord->setEnabled(state!=QMediaRecorder::RecordingState);
    ui->btnCameraStop->setEnabled(state==QMediaRecorder::RecordingState);
}

void MainWindow::on_videoDurationChanged(qint64 duration)
{
    ui->labCameraDuration->setText(QString("Recored:%1seconds").arg(duration/1000));
}
void MainWindow::on_btnCameraCapture_clicked()
{
    if(curCamera->captureMode()!=QCamera::CaptureStillImage)
    {
        curCamera->setCaptureMode(QCamera::CaptureStillImage);
    }
    imageCapture->capture();
}

void MainWindow::on_btnCameraRecord_clicked()
{
    if(!mediaRecorder->isAvailable())
    {
        QMessageBox::critical(this,"Error","video recording unsupportted");
        return;
    }
    if(curCamera->captureMode()!=QCamera::CaptureVideo)
        curCamera->setCaptureMode(QCamera::CaptureVideo);

    QString selectedFile=ui->lineEdit->text().trimmed();
    if(selectedFile.isEmpty())
    {
        QMessageBox::critical(this,"Error","set output file first");
        return;
    }
    if(QFile::exists(selectedFile))
    {
        if(!QFile::remove(selectedFile))
        {
            QMessageBox::critical(this,"Error","file in used,cannot be removed");
            return;
        }
        mediaRecorder->setOutputLocation(QUrl::fromLocalFile(selectedFile));
        mediaRecorder->record();
    }

}

void MainWindow::on_btnCameraStop_clicked()
{
    mediaRecorder->stop();
}
