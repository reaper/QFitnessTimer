#include "clock.h"
#include <QtGui>

/* Main clock constructor
 */
Clock::Clock(QWidget *parent) : QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    setDigitCount(8);
}

/* Clock constructor with specific arguments
 */
Clock::Clock(ClockType type, QTimer *vTimer, QWidget *parent) : QLCDNumber(parent)
{
    setupClock();

    clockType = type;
    timer = vTimer;

    if(type == Clock::CURRENT_TIME)
    {
        displayCurrentTime();
        connect(timer, SIGNAL(timeout()), this, SLOT(displayCurrentTime()), Qt::UniqueConnection);
    }
    timer->start(1000);
}

/*	Setup current clock
 */
void Clock::setupClock()
{
    setSegmentStyle(Filled);
    setDigitCount(8);
    display("00:00:00");
    setFixedHeight(40);
    activeTime.setHMS(0,0,0,0);
}

/* clock decrement method (countdown clock method)
 */
void Clock::decrement()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(displayDecrementTime()), Qt::UniqueConnection);
}

/* SLOT : Display the current time in the current clock
 */
void Clock::displayCurrentTime()
{
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    display(currentTime);
}

/* SLOT : Display increment time
 */
void Clock::displayIncrementTime()
{
    activeTime = activeTime.addSecs(1);
    display(activeTime.toString("hh:mm:ss"));
}

/* SLOT : Display decrement time method
 */
void Clock::displayDecrementTime()
{
    activeTime = activeTime.addSecs(-1);
    display(activeTime.toString("hh:mm:ss"));
    if(activeTime.secsTo(QTime(0,0,0,0)) == 0)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(displayDecrementTime()));
        initializeCountDown(minCountDown, secCountDown);
    }
}

/* Initialize countdown clock method
 */
void Clock::initializeCountDown(int min, int sec)
{
    minCountDown = min;
    secCountDown = sec;

    activeTime = QTime(0, minCountDown, secCountDown, 0);
    display(activeTime.toString("hh:mm:ss"));
}

/* Disconnect slots to stop time
 */
void Clock::stopTime()
{
    if(clockType == Clock::DECREMENT_TIMER)
    {
    	disconnect(timer, SIGNAL(timeout()), this, SLOT(displayDecrementTime()));
    } else if (clockType == Clock::INCREMENT_TIMER)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(displayIncrementTime()));
    }
}

/* Connect slots to start time again
 */
void Clock::startTime()
{
    if(clockType == Clock::DECREMENT_TIMER)
    {
        if((activeTime.minute() == minCountDown && activeTime.second() < secCountDown) || activeTime.minute() < minCountDown)
            connect(timer, SIGNAL(timeout()), this, SLOT(displayDecrementTime()), Qt::UniqueConnection);
    } else if (clockType == Clock::INCREMENT_TIMER)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(displayIncrementTime()), Qt::UniqueConnection);
    }
}