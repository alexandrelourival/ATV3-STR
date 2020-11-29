#include "sistema4trens.h"
#include "ui_sistema4trens.h"

void* thread_functionTrem1(void*);
void* thread_functionTrem2(void*);
void* thread_functionTrem3(void*);
void* thread_functionTrem4(void*);
void* thread_functionInterface(void*);
void* thread_functionPainel(void*);

int velocidade_trem1, velocidade_trem2, velocidade_trem3, velocidade_trem4;

int x1, x2, x3, x4, y1, y2, y3, y4;

sem_t bin_semL3, bin_semL4, bin_semL5, bin_semL6, bin_semL10;

Ui::sistema4trens ui_aux;

sistema4trens::sistema4trens(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sistema4trens)
{
    ui->setupUi(this);

    ui_aux = *ui;

    velocidade_trem1 = 6 - ui->verticalSlider_trem1->value();
    velocidade_trem2 = 6 - ui->verticalSlider_trem2->value();
    velocidade_trem3 = 6 - ui->verticalSlider_trem3->value();
    velocidade_trem4 = 6 - ui->verticalSlider_trem4->value();

    ui->label_trem1->setVisible(false);
    ui->label_trem1->setGeometry(150,40,30,30);
    ui->label_trem1->setPixmap(QPixmap("/home/lourival/ATV3-STR/azul.png"));

    ui->label_trem2->setVisible(false);
    ui->label_trem2->setGeometry(250,40,30,30);
    ui->label_trem2->setPixmap(QPixmap("/home/lourival/ATV3-STR/vermelho.png"));

    ui->label_trem3->setVisible(false);
    ui->label_trem3->setGeometry(370,40,30,30);
    ui->label_trem3->setPixmap(QPixmap("/home/lourival/ATV3-STR/verde.png"));

    ui->label_trem4->setVisible(false);
    ui->label_trem4->setGeometry(260,260,30,30);
    ui->label_trem4->setPixmap(QPixmap("/home/lourival/ATV3-STR/amarelo.png"));

    x1 = ui->label_trem1->x();
    y1 = ui->label_trem1->y();
    x2 = ui->label_trem2->x();
    y2 = ui->label_trem2->y();
    x3 = ui->label_trem3->x();
    y3 = ui->label_trem3->y();
    x4 = ui->label_trem4->x();
    y4 = ui->label_trem4->y();

}

sistema4trens::~sistema4trens()
{
    delete ui;
}


void sistema4trens::on_actionStart_triggered()
{
    ui->label_trem1->setVisible(true);
    ui->label_trem2->setVisible(true);
    ui->label_trem3->setVisible(true);
    ui->label_trem4->setVisible(true);

    res = sem_init(&bin_semL3, 0, 1); // criação do semaforo do trilho L3
    if (res != 0){
        perror("Iniciação do semaforo do trilho L3 falhou");
        exit(EXIT_FAILURE);
    }

    res = sem_init(&bin_semL4, 0, 1); // criação do semaforo do trilho L4
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Iniciação do semaforo do trilho L4 falhou.");
        exit(EXIT_FAILURE);
    }

    res = sem_init(&bin_semL5, 0, 1); // criação do semaforo do trilho L5
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Iniciação do semaforo do trilho L5 falhou.");
        exit(EXIT_FAILURE);
    }

    res = sem_init(&bin_semL6, 0, 1); // criação do semaforo do trilho L6
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Iniciação do semaforo do trilho L6 falhou.");
        exit(EXIT_FAILURE);
    }

    res = sem_init(&bin_semL10, 0, 1); // criação do semaforo do trilho L10
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Iniciação do semaforo do trilho L10 falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread_interface, NULL, thread_functionInterface, NULL);
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Criação da Thread Interface falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread_painel, NULL, thread_functionPainel, NULL);
    if (res != 0){
        QMessageBox::warning(this,"ERRO", "Criação da Thread Painel falhou.");
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

    res = pthread_create(&thread_trem3, NULL, thread_functionTrem3, NULL);
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

    res = pthread_join(thread_painel, &thread_result);
    if (res != 0) {
        QMessageBox::warning(this,"ERRO", "Junção da Thread Painel falhou.");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread_interface, &thread_result);
    if (res != 0) {
        QMessageBox::warning(this,"ERRO", "Junção da Thread Interface falhou.");
        exit(EXIT_FAILURE);
    }


    sem_destroy(&bin_semL3); // destruição do semaforo L3
    sem_destroy(&bin_semL4);  // destruição do semaforo L4
    sem_destroy(&bin_semL5);  // destruição do semaforo L5
    sem_destroy(&bin_semL6);  // destruição do semaforo L6
    sem_destroy(&bin_semL10);  // destruição do semaforo L10

}

void sistema4trens::on_actionQuit_triggered()
{
    on_actionStop_triggered();
    QApplication::quit();
}

void* thread_functionPainel(void*)
{
    sleep(1);
    while(1)
    {
        velocidade_trem1 = 6 - ui_aux.verticalSlider_trem1->value();
        ui_aux.lcdNumber_trem1->display(ui_aux.verticalSlider_trem1->value());

        velocidade_trem2 = 6 - ui_aux.verticalSlider_trem2->value();
        ui_aux.lcdNumber_trem2->display(ui_aux.verticalSlider_trem2->value());

        velocidade_trem3 = 6 - ui_aux.verticalSlider_trem3->value();
        ui_aux.lcdNumber_trem3->display(ui_aux.verticalSlider_trem3->value());

        velocidade_trem4 = 6 - ui_aux.verticalSlider_trem4->value();
        ui_aux.lcdNumber_trem4->display(ui_aux.verticalSlider_trem4->value());

        usleep(100000);

    }
}

void *thread_functionInterface(void *)
{
    sleep(1);
    while(1)
    {
        ui_aux.label_trem1->setGeometry(x1,y1,30,30);
        ui_aux.label_trem2->setGeometry(x2,y2,30,30);
        ui_aux.label_trem3->setGeometry(x3,y3,30,30);
        ui_aux.label_trem4->setGeometry(x4,y4,30,30);
        usleep(100000);
    }
}

void *thread_functionTrem1(void *)
{
    sleep(1);
    while(1)
    {
        // Sai de L1 vai para L2
        x1 = 150;
        y1 = 40;
        sleep(velocidade_trem1);

        //Sai de L2 vai para L3
        sem_wait(&bin_semL3);
        x1 = 200;
        y1 = 90;
        sleep(velocidade_trem1);

        //Sai de L3 vai para L4
        sem_wait(&bin_semL4);
        x1 = 150;
        y1 = 150;
        sem_post(&bin_semL3);
        sleep(velocidade_trem1);

        //Sai de L4 vai para L1
        x1 = 90;
        y1 = 90;
        sem_post(&bin_semL4);
        sleep(velocidade_trem1);
    }
    pthread_exit(0);
}

void *thread_functionTrem2(void *)
{
    sleep(1);
    while(1)
    {
        // Sai de L3 vai para L7
        x2 = 250;
        y2 = 40;
        sleep(velocidade_trem2);

        //Sai de L7 vai para L5
        sem_wait(&bin_semL5);
        x2 = 310;
        y2 = 90;
        sleep(velocidade_trem2);

        //Sai de L5 vai para L6
        sem_wait(&bin_semL6);
        x2 = 250;
        y2 = 150;
        sem_post(&bin_semL5);
        sleep(velocidade_trem2);

        //Sai de L6 vai para L3
        x2 = 200;
        y2 = 90;
        sem_post(&bin_semL6);
        sleep(velocidade_trem2);
    }
    pthread_exit(0);
}

void *thread_functionTrem3(void *)
{
    sleep(1);
    while(1)
    {
        // Sai de L5 vai para L8
        x3 = 370;
        y3 = 40;
        sem_post(&bin_semL5);
        sleep(velocidade_trem3);

        //Sai de L8 vai para L9
        x3 = 420;
        y3 = 90;
        sleep(velocidade_trem3);

        //Sai de L9 vai para L10
        sem_wait(&bin_semL10);
        x3 = 360;
        y3 = 150;
        sleep(velocidade_trem3);

        //Sai de L10 vai para L5
        sem_wait(&bin_semL5);
        x3 = 310;
        y3 = 90;
        sem_post(&bin_semL10);
        sleep(velocidade_trem3);
    }
    pthread_exit(0);
}

void *thread_functionTrem4(void *)
{
    sleep(1);
    while(1)
    {
        // Sai de L12 vai para L13
        x4 = 260;
        y4 = 260;
        sleep(velocidade_trem4);

        //Sai de L13 vai para L11
        x4 = 90;
        y4 = 200;
        sleep(velocidade_trem4);

        //Sai de L11 vai para L4
        sem_wait(&bin_semL4);
        x4 = 150;
        y4 = 150;
        sleep(velocidade_trem4);

        //Sai de L4 vai para L6
        sem_wait(&bin_semL6);
        x4 = 250;
        y4 = 150;
        sem_post(&bin_semL4);
        sleep(velocidade_trem4);

        //Sai de L6 vai para L10
        sem_wait(&bin_semL10);
        x4 = 360;
        y4 = 150;
        sem_post(&bin_semL6);
        sleep(velocidade_trem4);

        //Sai de L10 vai para L12
        x4 = 420;
        y4 = 200;
        sem_post(&bin_semL10);
        sleep(velocidade_trem4);
    }
    pthread_exit(0);
}
