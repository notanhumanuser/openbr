#ifndef VIEW_H
#define VIEW_H

#include <QAction>
#include <QActionGroup>
#include <QLabel>
#include <QString>
#include <QToolBar>
#include <QToolButton>
#include <QWidget>

class View : public QToolBar
{
    Q_OBJECT
    QToolButton tbPhoto, tbRegistered, tbEnhanced, tbFeatures;
    QToolButton tb1, tb4, tb9, tb16;
    QActionGroup agFormat, agCount;

public:
    explicit View(QWidget *parent = 0);

private slots:
    void formatChanged(QAction *action);
    void countChanged(QAction *action);

signals:
    void newFormat(QString image);
    void newCount(int count);
};

#endif // VIEW_H
