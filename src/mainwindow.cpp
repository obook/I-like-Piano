#include <iostream> //std::
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    midi_main midi = midi_main();

    input_map = midi.midi_GetInput();
    for (const auto& pair : input_map) {
        libremidi::input_port p = (libremidi::input_port)pair.first;
        std::string device = std::string(pair.second) + std::string(" - ") + std::string(p.display_name);
        ui->comboBox_Input->addItem(QString::fromStdString(device), QVariant::fromValue(p));
    }

    output_map = midi.midi_GetOutput();
    for (const auto& pair : output_map) {
        libremidi::output_port p = (libremidi::output_port)pair.first;
        std::string device = std::string(pair.second) + std::string(" - ") + std::string(p.display_name);
        ui->comboBox_Output->addItem(QString::fromStdString(device), QVariant::fromValue(p));
    }

    connect(ui->comboBox_Input, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboInputChanged(int)));
    connect(ui->comboBox_Output, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboOuputChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "utils.hpp"

void MainWindow::ComboInputChanged(int index)
{
    QVariant data =	ui->comboBox_Input->itemData(index);
    libremidi::input_port p = data.value<libremidi::input_port>();
    std::cout << "input_port =" << p << "\n" << std::flush;
}

void MainWindow::ComboOuputChanged(int index)
{
    QVariant data =	ui->comboBox_Output->itemData(index);
    libremidi::output_port p = data.value<libremidi::output_port>();
    std::cout << "output_port =" << p << "\n" << std::flush;
}
