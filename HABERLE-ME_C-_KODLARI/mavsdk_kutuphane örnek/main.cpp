#include <iostream>
#include "mylibrary.hpp"

int main() {
    MyDroneController my_drone_controller;

    std::string connection_url = "udp://:14540";
    my_drone_controller.connect(connection_url);

    // Start moving with a speed of 2 m/s
    float speed = 2.0;
    std::cout << "Moving forward with a speed of " << speed << " m/s..." << std::endl;
    my_drone_controller.setSpeed(speed);

    // Wait for some time
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Stop moving
    std::cout << "Stopping..." << std::endl;
    my_drone_controller.setSpeed(0.0);

    return 0;
}

