#include <iostream> //std::
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    midi = midi_main();

    ui->comboBox_Input->addItem("None");
    input_map = midi.midi_GetInput();
    for (const auto& pair : input_map) {
        libremidi::input_port p = (libremidi::input_port)pair.first;
        std::string device = std::string(pair.second) + std::string(" - ") + std::string(p.display_name);
        ui->comboBox_Input->addItem(QString::fromStdString(device), QVariant::fromValue(p));
    }

    ui->comboBox_Output->addItem("None");
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
    if (ui->comboBox_Input->currentIndex()) {
        QVariant data =	ui->comboBox_Input->itemData(index);
        libremidi::input_port p = data.value<libremidi::input_port>();
        std::cout << "input_port =" << p << "\n" << std::flush;

        midi.midi_OpenInput(p);
    }
    else {
        // Disconnect ?
    }
}

void MainWindow::ComboOuputChanged(int index)
{
    if (ui->comboBox_Output->currentIndex()) {
        QVariant data =	ui->comboBox_Output->itemData(index);
        libremidi::output_port p = data.value<libremidi::output_port>();
        std::cout << "output_port =" << p << "\n" << std::flush;
    }
    else {
        // Disconnect ?
    }
}
