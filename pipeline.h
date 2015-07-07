#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>

#include <QGst/Element>
#include <QGst/Pipeline>

class Pipeline : public QObject
{
    Q_OBJECT
public:
    explicit Pipeline(const QGst::ElementPtr &source, const QGst::ElementPtr &videoSink, QGst::ElementPtr (*encoderElementFactory)(), QObject *parent = nullptr);
    ~Pipeline() { stop(); }

    void start();
    void stop();

signals:
    void recordingStarting();
    void recordingStarted();
    void recordingStopping();
    void recordingStopped();

public slots:
    void startRecording();
    void stopRecording();

private:
    static QGst::ElementPtr createRecordBin(QGst::ElementPtr (*encoderElementFactory)());
    void recordingEos();

    void onBusMessage(const QGst::MessagePtr &message);

    QGst::PipelinePtr pipeline;

    QGst::ElementPtr videoRecordValve;
    QGst::ElementPtr audioRecordValve;

    QGst::ElementPtr recordBin;

    QGst::ElementPtr (*encoderElementFactory)();
};

#endif // PIPELINE_H
