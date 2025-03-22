#include<iostream>
using namespace std;
class iha{
	private:
		int x;
	public:
		set(int b){
			x=b;
		}
	int get(){
		return x;
	}
	
	void fonk(int& m){
		m=5;
	}
};
int main(){
	int h=3;
	iha uav;
	cout<<h<<endl;
	
	uav.fonk(h);
	
	cout<<h<<endl;
	
	uav.set(h);
	
	cout<<uav.get();
}
