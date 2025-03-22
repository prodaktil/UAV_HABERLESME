#include<iostream>
using namespace std;

class dortgen{
	private:
		int kenar_a;
		int kenar_b;
		int al;
		
	public:
		dortgen():kenar_a(5),kenar_b(5)
		{}
	    dortgen(int a,int b):kenar_a(a),kenar_b(b)
		 {}
		 
    void alan(){
    	al=kenar_a*kenar_b;
	}
	int alan_deg(){
		return al;
	}
	int alan_top(dortgen,dortgen,dortgen);	
};

 int dortgen::alan_top(dortgen x,dortgen y,dortgen z){
	z.al=(x.kenar_a*x.kenar_b)+(y.kenar_a*y.kenar_b);
	return z.al;
}

int main(){
	
	dortgen d1;
	dortgen d2(6,5);
	dortgen d3;
	
	
	d1.alan();
	cout<<d1.alan_deg()<<endl;
	
	d2.alan();
	cout<<d2.alan_deg()<<endl;
	
	cout<<d3.alan_top(d1,d2,d3);	 
}
