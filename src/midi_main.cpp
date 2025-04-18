#include "utils.hpp"
#include <iostream> //std::
#include "midi_main.h"

std::vector<libremidi::observer> observers;

midi_main::midi_main() {

    /* Nouveau

    libremidi::observer observer; // API par défaut = ?
    if (observer.get_input_ports().empty())
        return;
    if (observer.get_output_ports().empty())
        return;

    std::vector<libremidi::input_port> input_ports = observer.get_input_ports();
    int index = 0;
    for(const libremidi::input_port& p : input_ports)
        std::cout << "INPUT device " << index++ << " = " << p << "\n\n" << std::flush;

    return;

    libremidi::midi_in midi_in{{.on_message = [](const libremidi::message& message) {
        std::cout << message << std::endl;
    }}};

    if (auto err = midi_in.open_port(observer.get_input_ports()[0]); err != stdx::error{})
        err.throw_exception();

    libremidi::midi_out midi_out;
    if (auto err = midi_out.open_port(observer.get_output_ports()[0]); err != stdx::error{})
        err.throw_exception();

    midi_out.send_message(176, 7, 100);

    */

    // auto in_api = libremidi::midi1::in_default_configuration();
    // auto out_api = libremidi::midi1::out_default_configuration();
    for (auto api : libremidi::available_apis())
    {
        std::string_view api_name = libremidi::get_api_display_name(api);

        libremidi::observer_configuration cbs;

        cbs.track_any = true, // All interfaces
        cbs.input_added = [=, this](const libremidi::input_port& p) {
            ports_input[p] = api_name;
        };

        cbs.input_removed = [=, this](const libremidi::input_port& p) {
            auto it = ports_input.find(p);
            if(it != ports_input.end()) {
                std::cout << "Port INPUT " << api_name << " removed from map : " << p << "\n";
                ports_input.erase(it);
            }
            else {
                std::cout << "Port INPUT " << api_name << " removed not found in map : " << p << " \n";
            }
        };

        cbs.output_added = [=, this](const libremidi::output_port& p) {
            ports_output[p] = api_name;
        };

        cbs.output_removed = [=, this](const libremidi::output_port& p) {
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
        /*
        libremidi::midi_out out{
            {},
            out_api
        };
        */
        auto input_callback = [&](const libremidi::message& m) {
            std::cout << "input_callback";
        };

        /// libremidi::midi_in in{{.on_message = input_callback}, in_api};
        ///
        /*
        libremidi::midi_in midiin {
            {
                // Set our callback function.
                .on_message  = [&](const libremidi::message& message) {
                    std::cout << message << std::endl;
                    auto _ = midiout.send_message(message);
                },
            },
            libremidi::midi_in_configuration_for(obs)
        }; */

    }


}

std::map<libremidi::input_port, std::string_view> midi_main::midi_GetInput() {

    return(ports_input);
}

std::map<libremidi::output_port, std::string_view> midi_main::midi_GetOutput() {

    return(ports_output);
}

bool midi_main::midi_OpenInput(libremidi::input_port p) {

    libremidi::observer obs{
        libremidi::observer_configuration{},
        libremidi::observer_configuration_for(libremidi::API::ALSA_SEQ) // see api-c.h for API list
    };

    libremidi::midi_in midiin
        {
            {
                // Set our callback function.
                .on_message = [&](const libremidi::message& message){
                    std::cout << "message 1 " << message << "\n" << std::flush;

                    //using namespace std::chrono_literals;
                    //std::this_thread::sleep_for(200ms);
                    // auto _ = midiout.send_message(message);
                    /*
            std::this_thread::sleep_for(200ms);
            std::cout << "message 2 " << message << "\n" << std::flush;
            midiout.send_message(message);
            */
                },
            },
            libremidi::midi_in_configuration_for(obs)
        };

    midiin.open_port(p);
    if (!midiin.is_port_connected())
    {
        std::cerr << "Could not connect to midi in\n"<< std::flush;
        return false;
    }
    else
    {
        std::cout << "PORT CONNECTé " << std::flush;
    }

    return true;
}
