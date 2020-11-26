#include "sistema4trens.h"
#include "ui_sistema4trens.h"

void *thread_functionTrem1(void *arg);
void *thread_functionTrem2(void *arg);
void *thread_functionTrem3(void *arg);
void *thread_functionTrem4(void *arg);

pthread_mutex_t mutexL3, mutexL4, mutexL5, mutexL6, mutexL10;

int velocidade_trem1, velocidade_trem2, velocidade_trem3, velocidade_trem4;


sistema4trens::sistema4trens(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sistema4trens)
{
    ui->setupUi(this);
}

sistema4trens::~sistema4trens()
{
    delete ui;
}

void *thread_functionTrem1(void *arg)
{
    sleep(1);
    while(1)
    {
        // Sai de L1 vai para L2
        sleep(velocidade_trem1);

        //Sai de L2 vai para L3
        pthread_mutex_lock(&mutexL3);
        sleep(velocidade_trem1);

        //Sai de L3 vai para L4
        pthread_mutex_unlock(&mutexL3);
        pthread_mutex_lock(&mutexL4);
        sleep(velocidade_trem1);

        //Sai de L4 vai para L1
        pthread_mutex_unlock(&mutexL4);
        sleep(velocidade_trem1);
    }
    pthread_exit(0);
}

void *thread_functionTrem2(void *arg)
{
    sleep(1);
    while(1)
    {
        // Sai de L3 vai para L7
        sleep(velocidade_trem2);

        //Sai de L7 vai para L5
        pthread_mutex_lock(&mutexL5);
        sleep(velocidade_trem2);

        //Sai de L5 vai para L6
        pthread_mutex_unlock(&mutexL5);
        pthread_mutex_lock(&mutexL6);
        sleep(velocidade_trem2);

        //Sai de L6 vai para L3
        pthread_mutex_unlock(&mutexL6);
        sleep(velocidade_trem2);
    }
    pthread_exit(0);
}

void *thread_functionTrem3(void *arg)
{
    sleep(1);
    while(1)
    {
        // Sai de L5 vai para L8
        pthread_mutex_unlock(&mutexL5);
        sleep(velocidade_trem2);

        //Sai de L8 vai para L9
        sleep(velocidade_trem2);

        //Sai de L9 vai para L10
        pthread_mutex_lock(&mutexL10);
        sleep(velocidade_trem2);

        //Sai de L10 vai para L5
        pthread_mutex_unlock(&mutexL10);
        pthread_mutex_lock(&mutexL5);
        sleep(velocidade_trem2);
    }
    pthread_exit(0);
}

void *thread_functionTrem4(void *arg)
{
    sleep(1);
    while(1)
    {
        // Sai de L12 vai para L13
        sleep(velocidade_trem2);

        //Sai de L13 vai para L11
        sleep(velocidade_trem2);

        //Sai de L11 vai para L4
        pthread_mutex_lock(&mutexL4);
        sleep(velocidade_trem2);

        //Sai de L4 vai para L6
        pthread_mutex_unlock(&mutexL4);
        pthread_mutex_lock(&mutexL6);
        sleep(velocidade_trem2);

        //Sai de L6 vai para L10
        pthread_mutex_unlock(&mutexL6);
        pthread_mutex_lock(&mutexL10);
        sleep(velocidade_trem2);

        //Sai de L10 vai para L12
        pthread_mutex_unlock(&mutexL10);
        sleep(velocidade_trem2);
    }
    pthread_exit(0);
}


void sistema4trens::on_actionStart_triggered()
{
    res = pthread_mutex_init(&mutexL3, NULL);   // criação do mutexL3
    if (res != 0){
        perror("Iniciação do MutexL3 falhou");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&mutexL4, NULL);   // criação do mutexL4
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Iniciação do MutexL4 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&mutexL5, NULL);   // criação do mutexL5
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Iniciação do MutexL5 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&mutexL6, NULL);   // criação do mutexL6
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Iniciação do MutexL6 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&mutexL10, NULL);   // criação do mutexL10
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Iniciação do MutexL10 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread_trem1, NULL, thread_functionTrem1, NULL);
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Criação da Thread Trem 1 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread_trem2, NULL, thread_functionTrem2, NULL);
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Criação da Thread Trem 2 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread_trem3, NULL, &thread_functionTrem3, NULL);
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Criação da Thread Trem 3 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread_trem4, NULL, thread_functionTrem4, NULL);
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Criação da Thread Trem 4 falhou.");
        exit(EXIT_FAILURE);
    }
}

void sistema4trens::on_actionStop_triggered()
{
    res = pthread_join(thread_trem1, &thread_result);
    if (res != 0) {
        QMessageBox::warning(this,"ERRO", "Junção da Thread Trem 1 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread_trem2, &thread_result);
    if (res != 0) {
        QMessageBox::warning(this,"ERRO", "Junção da Thread Trem 2 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread_trem3, &thread_result);
    if (res != 0) {
        QMessageBox::warning(this,"ERRO", "Junção da Thread Trem 1 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread_trem4, &thread_result);
    if (res != 0) {
        QMessageBox::warning(this,"ERRO", "Junção da Thread Trem 2 falhou.");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_destroy(&mutexL3);  // destruição do mutexL3
    pthread_mutex_destroy(&mutexL4);  // destruição do mutexL4
    pthread_mutex_destroy(&mutexL5);  // destruição do mutexL5
    pthread_mutex_destroy(&mutexL6);  // destruição do mutexL6
    pthread_mutex_destroy(&mutexL10);  // destruição do mutexL10

}

void sistema4trens::on_actionQuit_triggered()
{
    on_actionStop_triggered();
    QApplication::quit();
}
