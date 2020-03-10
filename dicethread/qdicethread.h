#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include <QThread>

class QDiceThread : public QThread
{
    Q_OBJECT
private:
    int mSeq=0;
    int mDiceValue;
    bool mPaused=true;
    bool mStop=false;
protected:
    void run() override;
public:
    QDiceThread();
    void beginDice();
    void pauseDice();
    void stopThread();
signals:
    void newValue(int seq,int diceValue);
};

class QThreadProducer:public QThread
{
    Q_OBJECT
private:
    bool mStop=false;
protected:
    void run() override;
public:
    QThreadProducer(){}
    void stopThread(){mStop=true;}
};

class QThreadConsumer:public QThread
{
    Q_OBJECT
private:
    bool mStop=false;
protected:
    void run() override;
public:
    QThreadConsumer(){}
    void stopThread(){mStop=true;}
signals:
    void newValue(int seq,int diceValue);
};
#endif // QDICETHREAD_H
