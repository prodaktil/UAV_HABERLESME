#include "iha_kontrol.hpp"

 using namespace std;

int main() {
    DroneController iha;
    iha.connect("udp://:14540");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    iha.start();
    // The telemetry thread is now handling continuous printing, so no need to call printTelemetry here.
    std::this_thread::sleep_for(std::chrono::minutes(5)); // Keep the program running for 5 minutes (for example)
    return 0;
}