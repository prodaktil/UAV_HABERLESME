#include "uav_kontrol.hpp"
#include<iostream>
#include <mavsdk/mavsdk.h>
#include <vector>

using namespace std;
using namespace mavsdk;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;

std::shared_ptr<mavsdk::Mavsdk> mavsdk1;
void connect()
{
    mavsdk::ConnectionResult connection_result = mavsdk1->add_any_connection("udp://:14550");
    if (connection_result != mavsdk::ConnectionResult::Success)
    {
        std::cerr << "Connection error: " << connection_result << std::endl;
        return;
    }
    std::cout << "Connected to drone!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

}
void multiplane_connect (std::shared_ptr<mavsdk::Mavsdk> &mavsdk2){

mavsdk2 = mavsdk1;    // bağlanan mavsdk1' i objenin mavsdk pointer' ına eşitliyoruz ki o da bağlanmış olsun
std::this_thread::sleep_for(std::chrono::seconds(5));

}

int main(){

mavsdk1 = std::make_shared<mavsdk::Mavsdk>();
connect();  // mavsdk1' i sişsteme bağladık
std::vector<UavKontrol> ihavector;  // UavKontrol classına ait bir vektör oluşturduk
UavKontrol iha1(0);    // 0 dan değil de 1 den de başlayabilir onu kontrol etmek lazım
UavKontrol iha2(1);   // objeleri oluşturduk
UavKontrol iha3(2);
UavKontrol iha4(3);
UavKontrol iha5(4);
ihavector.push_back(iha1);
ihavector.push_back(iha2);
ihavector.push_back(iha3);   // objeleri oluşturduğumuz vektörün içine yerleştirdik 
ihavector.push_back(iha4);
ihavector.push_back(iha5);
for(int i = 1; i < 6 ; i++){
multiplane_connect(ihavector[i-1].mavsdk); // her objeyi sırayla bağlıyoruz
ihavector[i-1].takeoff(); // constructor' ın içine fonksyonları koyunca connect kısmında sıkıntı çıkıyordu
//ihavector[i-1].konum_yaz();   // vektörün sırayla 0 1 2 3 elemanlarına erişiyoruz
// konum yazdırma fonskyonunu çalıştıramadım
}
return 0;
}