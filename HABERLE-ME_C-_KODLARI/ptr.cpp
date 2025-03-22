#include <iostream>
#include <memory> // std::shared_ptr için gerekli başlık dosyası

class uav {
public:
    uav(int value) : m_value(value) {
        std::cout << "MyClass constructor called with value: " << m_value << std::endl;
    }
    
    ~uav() {
        std::cout << "MyClass destructor called with value: " << m_value << std::endl;
    }
    
    void deger() {
        std::cout << "Value: " << m_value << std::endl;
    }
    
private:
    int m_value;
};

int main() {
    // std::shared_ptr oluşturarak uav nesnesini paylaşan bir işaretçi oluşturuldu
    std::shared_ptr<uav> ptr1(new uav(10));
    
    // Başka bir std::shared_ptr'e aynı nesne atandı
    std::shared_ptr<uav> ptr2 = ptr1;
    
    // Nesneler kullanıldı
    ptr1->deger();
    ptr2->deger();
    
    

    ptr1.reset();
    //ilk pointeron ömrü sonlanmış oldu ama destructer çağrılmaz çünkü aynı nesneyi paylaşan iki tane pointer var
    
    ptr2.reset();
    //iki nesne de öldüğü için destructer fonksiyonu çağrılır
    
    return 0;
}
