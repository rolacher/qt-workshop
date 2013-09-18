#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace IM
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_nickname(const QString & nickname);

signals:
    void send_message(const QString & nickname, QString const & message);

private slots:
    void handleSendMessage();

private:
    QString _nickname;


private:
    Ui::MainWindow *ui;
};

} // IM

#endif // MAINWINDOW_H
