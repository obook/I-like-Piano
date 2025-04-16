#include "utils.hpp"
#include <iostream> //std::
#include "midi_main.h"

midi_main::midi_main() {

    std::vector<libremidi::observer> observers;

    for (auto api : libremidi::available_apis())
    {
        std::string_view api_name = libremidi::get_api_display_name(api);

        libremidi::observer_configuration cbs;
        cbs.input_added = [=](const libremidi::input_port& p) {
            ports_input[p] = api_name;
        };

        cbs.input_removed = [=](const libremidi::input_port& p) {
            auto it = ports_input.find(p);
            if(it != ports_input.end()) {
                std::cout << "Port INPUT " << api_name << " removed from map : " << p << "\n";
                ports_input.erase(it);
            }
            else {
                std::cout << "Port INPUT " << api_name << " removed not found in map : " << p << " \n";
            }
        };

        cbs.output_added = [=](const libremidi::output_port& p) {
            ports_output[p] = api_name;
        };

        cbs.output_removed = [=](const libremidi::output_port& p) {
            auto it = ports_output.find(p);
            if(it != ports_output.end()) {
                std::cout << "Port OUPUT " << api_name << " removed from map : " << p << "\n";
                ports_output.erase(it);
            }
            else {
                std::cout << "Port OUTPUT " << api_name << " removed not found in map : " << p << " \n";
            }
        };

        observers.emplace_back(cbs, libremidi::observer_configuration_for(api));

    }
}

std::map<libremidi::input_port, std::string_view> midi_main::midi_GetInput() {

    return(ports_input);
}

std::map<libremidi::output_port, std::string_view> midi_main::midi_GetOutput() {

    return(ports_output);
}
