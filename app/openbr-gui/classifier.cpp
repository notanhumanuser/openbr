#include <QtConcurrentRun>
#include <openbr_plugin.h>

#include "classifier.h"

using namespace br;

/**** CLASSIFIER ****/
/*** PUBLIC ***/
Classifier::Classifier(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(this, SIGNAL(newClassification(QString,QString)), this, SLOT(setClassification(QString,QString)));
}

void Classifier::setAlgorithm(const QString &algorithm)
{
    this->algorithm = algorithm;
    _classify(File()); // Trigger algorithm initialization
}

/*** PUBLIC SLOTS ***/
void Classifier::classify(const File &file)
{
    QtConcurrent::run(this, &Classifier::_classify, file);
}

/*** PRIVATE SLOTS ***/
void Classifier::setClassification(const QString &key, const QString &value)
{
    if (key.isEmpty()) clear();
    else               setText(QString("<b>%1: </b>%2").arg(key, value));
}

/*** PRIVATE ***/
void Classifier::_classify(File file)
{
    file.setBool("forceEnrollment");

    QString key, value;
    foreach (const File &f, Enroll(file.flat(), File("[algorithm=" + algorithm + "]"))) {
        qDebug() << f.flat();
        if (!f.contains("Label"))
            continue;

        if (algorithm == "GenderClassification") {
            key = "Gender";
            value = (f.getInt("Label", 0) == 0 ? "Male" : "Female");
        } else if (algorithm == "AgeRegression") {
            key = "Age";
            value = QString::number(int(f.getFloat("Label", 0)+0.5)) + " Years";
        } else {
            key = algorithm;
            value = f.getString("Label");
        }
        break;
    }

    emit newClassification(key, value);
}

#include "moc_classifier.cpp"
