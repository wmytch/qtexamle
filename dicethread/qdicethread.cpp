#include "qdicethread.h"
#include <QTime>
#include <QMutex>
#include <QWaitCondition>

QDiceThread::QDiceThread()
{

}

void QDiceThread::beginDice()
{
    mPaused=false;
}

void QDiceThread::pauseDice()
{
    mPaused=true;
}

void QDiceThread::stopThread()
{
    mStop=true;
}

void QDiceThread::run()
{
    mStop=false;
    mSeq=0;
    qsrand(QTime::currentTime().msec());
    while(!mStop)
    {
        if(!mPaused)
        {
            mDiceValue=(qrand()%6)+1;
            mSeq++;
            emit newValue(mSeq,mDiceValue);
        }
        msleep(500);
    }
    quit();
}

QMutex mutex;
QWaitCondition newDataAvailable;
int seq=0;
int diceValue;

void QThreadProducer::run()
{
    mStop=false;
    seq=0;
    qsrand(QTime::currentTime().msec());
    while(!mStop)
    {
        mutex.lock();
        diceValue=(qrand()%6)+1;
        seq++;
        mutex.unlock();
        newDataAvailable.wakeAll();
        msleep(500);
    }
}

void QThreadConsumer::run()
{
    mStop=false;
    while(!mStop)
    {
        mutex.lock();
        newDataAvailable.wait(&mutex);
    }
}