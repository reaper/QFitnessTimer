#ifndef CLOCK_H
#define CLOCK_H

#include <QLCDNumber>
#include <QTime>
#include <QLineEdit>

class Clock : public QLCDNumber
{
  Q_OBJECT
  Q_ENUMS(ClockType)

public:
  enum ClockType {CURRENT_TIME,INCREMENT_TIMER, DECREMENT_TIMER};

  Clock(QWidget *parent = 0);
  Clock(ClockType type, QTimer *timer, QWidget *parent = 0);
  void decrement();
  void initializeCountDown(int min, int sec);
  void stopTime();
  void startTime();

private:
  void setupClock();

  ClockType clockType;
  QTimer *timer;
  QTime activeTime;
  int minCountDown;
  int secCountDown;

private slots:
  void displayCurrentTime();
  void displayIncrementTime();
  void displayDecrementTime();
};

#endif // CLOCK_H
