#include<iostream>
using namespace std;
class UAV
{
	private:
		int konum_x, konum_y , konum_z;
	public:
		UAV() : konum_x(0), konum_y(0), konum_z(0)
		{
		cout<<"ilk konum degerleri:";
		cout<<"\n x ekseni = "<<konum_x<<endl;
		cout<<" y ekseni = "<<konum_y<<endl;
		cout<<" z ekseni = "<<konum_z<<endl;
			}
		void veri_al(int x,int y, int z){
			konum_y=y;
			konum_x=x;
			konum_z=z;
		}
		~UAV(){
			~konum_y;
			cout<<"\n ÝHA objesinin sonu";
		}
		
		void veri_yazdir(){
			cout<<"\n x ekseni = "<<konum_x<<endl;
			cout<<" y ekseni = "<<konum_y<<endl;
			cout<<" z ekseni = "<<konum_z<<endl;
		}	
};
class HEDEF
{
	private:
		int pos_x, pos_y , pos_z;
	public:
		HEDEF(int x1,int y1 ,int z1): pos_x(x1),pos_y(y1),pos_z(z1)
		{
		cout<<"\n x ekseni = "<<pos_x<<endl;
		cout<<" y ekseni = "<<pos_y<<endl;
		cout<<" z ekseni = "<<pos_z<<endl;	
		}
		~HEDEF(){
			cout<<"\nHEDEF objesinin sonu\n"<<endl;
		}
};
	int main(){
		int a,b,c,x,y,z;
		cout<<"\n Hedefin son konum degerlerini girin:"<<endl;
		
		cin>>x;
		cin>>y;
		cin>>z;
		HEDEF h1(x,y,z);
		cout<<"\n IHA'nin son konum degerlerini girin:"<<endl;
		
		cin>>a;
		cin>>b;
		cin>>c;		
		if(a==1){
			cout<<"if 'in ici";
			UAV iha;
			iha.veri_al(a,b,c);
			iha.veri_yazdir();
	
		}
		cout<<"\n if' in sonu"<<endl;
	
}
