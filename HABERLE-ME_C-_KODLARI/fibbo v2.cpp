#include<stdio.h>
#include<iostream>
using namespace std;
int fak( int i )
{
	int ilk=0;
	int son=1;
	int toplam;
	cout<<"1";
	while(i>1)
	{
	i--;
	toplam = ilk + son;
	ilk=son;
	son=toplam;
	cout<<" "<<toplam;
}
	return toplam;
}
int main(){
	int a,y;
	scanf("%d",&a);
	y = fak(a);
	cout<<" "<< y<<endl;
	
	
}

	
	
	
	

	





