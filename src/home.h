#ifndef HOME_H
#define HOME_H

#include "clock.h"
#include <QtGui>

class Home : public QWidget
{
  Q_OBJECT

public:
  explicit Home(QWidget *parent = 0);

private:
  void setupWindow();
  void buildTimerAndClocks();
  void buildWidgets();
  void buildLayouts();
  void setActions();
  void keyPressEvent(QKeyEvent *event);

  Clock *currentClock;
  Clock *activeClock;
  Clock *countDownClock;
  QTimer *timer;
  QVBoxLayout *mainLayout;
  QHBoxLayout *intervalLayout;
  QLabel *intervalLabel;
  QLabel *pauseCountDownLabel;
  QSpinBox *spinBoxMinutes;
  QSpinBox *spinBoxSeconds;
  QPushButton *startSessionButton;
  QPushButton *pauseSessionButton;
  QPushButton *startSessionAfterBreakButton;
  QPushButton *countDownDataUpdateButton;

public slots:
  void startSession();
  void stopClocks();
  void startClocks();
  void stopAndUpdateCountDownClock();
};

#endif // HOME_H
