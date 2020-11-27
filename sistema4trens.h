#ifndef SISTEMA4TRENS_H
#define SISTEMA4TRENS_H

#include <QMainWindow>
#include <QMessageBox>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui { class sistema4trens; }
QT_END_NAMESPACE

class sistema4trens : public QMainWindow
{
    Q_OBJECT

public:
    sistema4trens(QWidget *parent = nullptr);
    ~sistema4trens();

private slots:

    void on_actionStart_triggered();

    void on_actionStop_triggered();

    void on_actionQuit_triggered();

    void on_verticalSlider_trem1_valueChanged(int value);

    void on_verticalSlider_trem2_valueChanged(int value);

    void on_verticalSlider_trem3_valueChanged(int value);

    void on_verticalSlider_trem4_valueChanged(int value);

private:
    Ui::sistema4trens *ui;

    int res;

    pthread_t thread_trem1, thread_trem2, thread_trem3, thread_trem4;

    void *thread_result;


};
#endif // SISTEMA4TRENS_H
