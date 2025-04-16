#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "midi_main.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::map<libremidi::input_port, std::string_view> input_map;
    std::map<libremidi::output_port, std::string_view> output_map;
private slots:
    void ComboInputChanged(int index);
    void ComboOuputChanged(int index);
};
#endif // MAINWINDOW_H
