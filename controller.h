#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QTimer>

class Controller : public QObject {
  Q_OBJECT
public:
  Controller();
  ~Controller();

signals:

public slots:
  void start();
  void stop();

signals:
  void initializedWorkerRequested();
  void startWorkerRequested();
  void stopWorkerRequested();
  void passData(const QColor &data);

private slots:
  void onDataGenerated(const QColor &data);

private:
  QThread _worker_thread;
  QTimer _timer;
};

#endif // CONTROLLER_H
