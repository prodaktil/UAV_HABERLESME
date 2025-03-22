import asyncio
from mavsdk import System
import math
async def run():
    # Drone bağlantısı oluştur
    drone = System()
    await drone.connect(system_address="udp://:14540")
    asyncio.ensure_future(print_position(drone))
    asyncio.ensure_future(print_heading(drone))
    global angle # global bir değişken oluşturuyoruz ki her yerde kullanabilelim
    angle = 0  
    while True:  # sonsuz döngüye soktuk
        await asyncio.sleep(5)
async def print_position(drone):
    global angle
    # Drone'un odometri verilerini takip et
    async for position in drone.telemetry.odometry():
        x = position.position_body.x_m
        y = position.position_body.y_m
        z = position.position_body.z_m
        #dronun konumu verisini çektik
        # Konumu ekrana yazdır
        print(f"X: {x}, Y: {y}, Z: {z}")
        # Referans noktasına göre koordinatları hesapla
        xa = 0
        ya = 64
        xa = xa - x
        ya = ya - y
        # herhangi bir nokta ile dron arasıdnaki uzaklığı bulup tanjantan açıyı hesapladık
        # Yeni açıyı hesapla
        angle = math.atan2(ya, xa)  
        pi = 3.141592653589793
        angle = (pi / 180) * angle
async def print_heading(drone):
    async for heading in drone.telemetry.heading():
        head = heading.heading_deg   
        # heading verilerini kontrol edip ekrana yazdırıyoruz
      #  print(head)   # bu veri dronun x ekseni ile yaptığı açıyı veriyor
        fark = abs(angle - head)
        if fark > 180: 
            fark = 360 - fark 
        
        if fark < 30:       # bulduğumuz açıyla dronun açısısı arasındaki farkı kontrol edip 
            print("Cisim iha'nin önünde")          # onunde olup olmadını anlıyoruz
        else:
            print("Cisim iha'nin önünde değil")
if __name__ == "__main__":
    # Ana fonksiyonu başlattık
    asyncio.run(run())

