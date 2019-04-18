#include "controller.h"
#include "worker.h"
#include <QDebug>
#include <QColor>

Controller::Controller() {
  Worker *worker = new Worker();
  worker->moveToThread(&_worker_thread);
  connect(&_worker_thread, &QThread::finished, worker, &QObject::deleteLater);

  connect(this, &Controller::initializedWorkerRequested, worker, &Worker::init);
  connect(worker, &Worker::initialized, this, [=](bool success) {
      if(success) {
        qDebug() << "Worker thread initialized.";
      } else {
        qDebug() << "Worker thread failed to initialize.";
      }
  });

  connect(this, &Controller::startWorkerRequested, worker, &Worker::start);
  connect(worker, &Worker::started, this, [=](bool success) {
      if(success) {
        qDebug() << "Worker thread started\nStarting timer.";
        _timer.start();
      } else {
        qDebug() << "Worker thread is not stopped.";
      }
  });

  connect(this, &Controller::stopWorkerRequested, worker, &Worker::stop);
  connect(worker, &Worker::stopped, this, [=](bool success) {
      if(success) {
        qDebug() << "Worker thread stopped.\nSopping timer";
        _timer.stop();
      } else {
        qDebug() << "Worker thread is not stopped.";
      }
  });

  _timer.setTimerType(Qt::PreciseTimer);
  _timer.setSingleShot(false);
  _timer.setInterval(100);
  connect(&_timer, &QTimer::timeout, worker, &Worker::generateData);
  connect(worker, &Worker::dataGenerated, this, &Controller::onDataGenerated);

  _worker_thread.start();
}

Controller::~Controller() {
  _worker_thread.quit();
  _worker_thread.wait();
}

void Controller::start() {
  emit initializedWorkerRequested();
  emit startWorkerRequested();
}

void Controller::stop() {
  emit stopWorkerRequested();
}

void Controller::onDataGenerated(const QColor &data) {
  //qDebug() << "Data: " << data;
  emit passData(data);
}
