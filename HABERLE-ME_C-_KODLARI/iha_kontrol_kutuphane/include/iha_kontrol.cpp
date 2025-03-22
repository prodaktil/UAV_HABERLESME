

#include "iha_kontrol.hpp"
 using namespace std;

    DroneController::DroneController() : mavsdk(std::make_shared<mavsdk::Mavsdk>()) {}

    void DroneController::connect(const std::string& connection_url) {
        mavsdk::ConnectionResult connection_result = mavsdk->add_any_connection(connection_url);
        if (connection_result != mavsdk::ConnectionResult::Success) {
            std::cerr << "Connection error: " << connection_result << std::endl;
            return;
        }
        std::cout << "Connected to drone!" << std::endl;
    }

    void DroneController::start() {
        std::cout << "Starting telemetry..." << std::endl;

        if (mavsdk->systems().empty()) {
            std::cerr << "No systems found!" << std::endl;
            return;
        }

        telemetry = std::make_shared<mavsdk::Telemetry>(*(mavsdk->systems()[0]));

        // Start a separate thread to continuously print telemetry data
        telemetry_thread = std::async(std::launch::async, [this]() { printTelemetry(); });
    }

	void DroneController::printTelemetry() {
    while (true) {
        const auto odometry = telemetry->odometry();
                   x = odometry.position_body.x_m;
                   y = odometry.position_body.y_m;
                   z = odometry.position_body.z_m;
        std::cout<<"\nx "<<x <<std::endl<<"y "<< y <<std::endl<<"z "<< z <<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Adjust sleep duration as needed
     }
    }

