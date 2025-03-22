#include <iostream>
#include <future>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/action/action.h>

class DroneController {

private:
    std::shared_ptr<mavsdk::Mavsdk> mavsdk;
    std::shared_ptr<mavsdk::Telemetry> telemetry;
    std::shared_ptr<mavsdk::Action> action;
    std::future<void> telemetry_thread;
    float x,y,z;
    
public:
    DroneController() : mavsdk(std::make_shared<mavsdk::Mavsdk>()) {}

    void connect(const std::string& connection_url) {
        mavsdk::ConnectionResult connection_result = mavsdk->add_any_connection(connection_url);
        if (connection_result != mavsdk::ConnectionResult::Success) {
            std::cerr << "Connection error: " << connection_result << std::endl;
            return;
        }
        std::cout << "Connected to drone!" << std::endl;
    }

    void start() {
        std::cout << "Starting telemetry..." << std::endl;

        if (mavsdk->systems().empty()) {
            std::cerr << "No systems found!" << std::endl;
            return;
        }

        telemetry = std::make_shared<mavsdk::Telemetry>(*(mavsdk->systems()[0]));

        // Start a separate thread to continuously print telemetry data
        telemetry_thread = std::async(std::launch::async, [this]() { printTelemetry(); });
    }

void printTelemetry() {
    while (true) {
        const auto odometry = telemetry->odometry();
                   x = odometry.position_body.x_m;
                   y = odometry.position_body.y_m;
                   z = odometry.position_body.z_m;
        std::cout<<"\nx "<<x <<std::endl<<"y "<< y <<std::endl<<"z "<< z <<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Adjust sleep duration as needed
    }
}

};

int main() {
    DroneController iha;
    iha.connect("udp://:14540");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    iha.start();
    // The telemetry thread is now handling continuous printing, so no need to call printTelemetry here.
    std::this_thread::sleep_for(std::chrono::minutes(5)); // Keep the program running for 5 minutes (for example)
    return 0;
}


