#include <QtGui>
#include "home.h"
#include "clock.h"

/*  Constructor of the Home class. It includes clocks,
    widgets and layouts instantiations
 */
Home::Home(QWidget *parent) : QWidget(parent)
{
  setupWindow();
  buildTimerAndClocks();
  buildWidgets();
  buildLayouts();
  setActions();
}

/*	Setup window method
 */
void Home::setupWindow()
{
  setWindowTitle("QFitnessTimer");
  setFixedWidth(300);
}

/*	Timer and clocks instantiations
 */
void Home::buildTimerAndClocks()
{
  timer = new QTimer;

  currentClock = new Clock(Clock::CURRENT_TIME, timer, this);
  activeClock = new Clock(Clock::INCREMENT_TIMER, timer, this);
  activeClock->setVisible(false);
  countDownClock = new Clock(Clock::DECREMENT_TIMER, timer, this);
  countDownClock->setVisible(false);
}

/*	Build widgets method
 */
void Home::buildWidgets()
{
  intervalLabel = new QLabel;
  intervalLabel->setText("Countdown :");

  pauseCountDownLabel = new QLabel;
  pauseCountDownLabel->setText("Press 'Space' to start the countdown");
  pauseCountDownLabel->setVisible(false);

  spinBoxMinutes = new QSpinBox;
  spinBoxMinutes->setFocusProxy(this);
  spinBoxMinutes->setRange(0, 5);
  spinBoxMinutes->setSuffix(" min");
  spinBoxMinutes->setValue(1);
  spinBoxSeconds = new QSpinBox;
  spinBoxSeconds->setFocusProxy(this);
  spinBoxSeconds->setRange(0, 59);
  spinBoxSeconds->setSuffix(" sec");
  spinBoxSeconds->setValue(30);

  startSessionButton = new QPushButton;
  startSessionButton->setText("Start session");

  countDownDataUpdateButton = new QPushButton;
  countDownDataUpdateButton->setText("Initialize countdown clock");
  countDownDataUpdateButton->setVisible(false);

  pauseSessionButton = new QPushButton;
  pauseSessionButton->setText("Pause");
  pauseSessionButton->setVisible(false);

  startSessionAfterBreakButton = new QPushButton;
  startSessionAfterBreakButton->setText("Start");
  startSessionAfterBreakButton->setVisible(false);
}

/*	Build layouts method
 */
void Home::buildLayouts()
{
  mainLayout = new QVBoxLayout;
  mainLayout->addWidget(currentClock);

  intervalLayout = new QHBoxLayout;
  intervalLayout->addWidget(intervalLabel);
  intervalLayout->addWidget(spinBoxMinutes);
  intervalLayout->addWidget(spinBoxSeconds);
  mainLayout->addLayout(intervalLayout);
  mainLayout->addWidget(startSessionButton);
  mainLayout->addWidget(countDownDataUpdateButton);
  mainLayout->addWidget(pauseSessionButton);
  mainLayout->addWidget(startSessionAfterBreakButton);
  mainLayout->addWidget(activeClock);
  mainLayout->addWidget(countDownClock);
  mainLayout->addWidget(pauseCountDownLabel);

  setLayout(mainLayout);
}

/*	Connect declarations
 */
void Home::setActions()
{
  connect(startSessionButton, SIGNAL(clicked()), this, SLOT(startSession()), Qt::UniqueConnection);
  connect(countDownDataUpdateButton, SIGNAL(clicked()), this, SLOT(stopAndUpdateCountDownClock()), Qt::UniqueConnection);
  connect(pauseSessionButton, SIGNAL(clicked()), this, SLOT(stopClocks()), Qt::UniqueConnection);
  connect(startSessionAfterBreakButton, SIGNAL(clicked()), this, SLOT(startClocks()), Qt::UniqueConnection);
}

/*  Start session method, with active and countdown clock
    activing and initializing
 */
void Home::startSession()
{
  startSessionButton->setVisible(false);
  countDownDataUpdateButton->setVisible(true);
  pauseSessionButton->setVisible(true);
  activeClock->setVisible(true);
  countDownClock->setVisible(true);
  pauseCountDownLabel->setVisible(true);
  countDownClock->initializeCountDown(spinBoxMinutes->value(),spinBoxSeconds->value());
  activeClock->startTime();
}

/*  Stop active and countdown clocks
 */
void Home::stopClocks()
{
  activeClock->stopTime();
  countDownClock->stopTime();
  pauseSessionButton->setVisible(false);
  startSessionAfterBreakButton->setVisible(true);
}

/*  Start active and countdown clocks, update layout
 */
void Home::startClocks()
{
  activeClock->startTime();
  countDownClock->startTime();
  startSessionAfterBreakButton->setVisible(false);
  pauseSessionButton->setVisible(true);
}

/*  Stop and update countdown clock with spin boxes values
 */
void Home::stopAndUpdateCountDownClock()
{
  countDownClock->stopTime();
  countDownClock->initializeCountDown(spinBoxMinutes->value(), spinBoxSeconds->value());
}

/*  Space key pressed event method
    event Event object <QKeyEvent>
 */
void Home::keyPressEvent(QKeyEvent *event)
{
  if(event->key() == Qt::Key_Space)
  {
    countDownClock->decrement();
  }
}
