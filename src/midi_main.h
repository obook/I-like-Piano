#ifndef MIDI_MAIN_H
#define MIDI_MAIN_H

#include <cstdlib>
#include <libremidi/libremidi.hpp>

class midi_main
{
public:
    midi_main();
    std::map<libremidi::input_port, std::string_view> midi_GetInput();
    std::map<libremidi::output_port, std::string_view> midi_GetOutput();

    bool midi_OpenInput(libremidi::input_port p);

private:
    std::map<libremidi::input_port, std::string_view> ports_input;
    std::map<libremidi::output_port, std::string_view> ports_output;
};

#endif // MIDI_MAIN_H
