#include "utils.hpp"
#include <iostream> //std::
#include <libremidi/libremidi.hpp>
#include <libremidi/configurations.hpp>
#include <libremidi/backends.hpp>

int main()
{
    std::cout << "Hello World!\n" << std::flush;

    // libremidi::observer observer; // API par défaut = "ALSA (sequencer)"

    auto api = libremidi::API::ALSA_SEQ;

    libremidi::observer observer{
        {
            .track_any = true
        },
        api
    };

    if (observer.get_input_ports().empty())
        return -1;

    if (observer.get_output_ports().empty())
        return -1;

    std::vector<libremidi::input_port> input_ports = observer.get_input_ports();
    int index = 0;
    for(const libremidi::input_port& p : input_ports)
        std::cout << "INPUT device " << index++ << " = " << p << "\n\n" << std::flush;

#ifdef _NOTDEF
    libremidi::midi_in midiin
    {
        libremidi::input_configuration{
          .on_message = [&](const libremidi::message& message){
                std::cout << "message 1 " << message << "\n" << std::flush;
            }
        },
        /*
        libremidi::pipewire_input_configuration{
            .client_name = "My app"
        }, */
        libremidi::midi_in_configuration_for(observer)
    };

#endif


    libremidi::midi_in midiin{
        libremidi::input_configuration{
            .on_message  = [&](const libremidi::message& message){
               std::cout << "message 1 " << message << "\n" << std::flush;
            }
        },/*
        libremidi::alsa_seq::input_configuration{
            .client_name = "my client"
        },*/
        libremidi::midi_in_configuration_for(observer)
    };

    libremidi::API current_api_in = midiin.get_current_api();
    std::string_view api_name_in = libremidi::get_api_display_name(current_api_in);
    std::cout << "INPUT current_api = " << api_name_in << "\n" << std::flush;

    while (1)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    char input;
    std::cin.get(input);

    return 0;
}
