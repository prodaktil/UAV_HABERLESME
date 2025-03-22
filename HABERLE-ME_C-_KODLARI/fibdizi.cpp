#include<iostream>
using namespace std;
void fak( int i , int dizi[] )
{
	int ilk=0;
	int son=1;
	int toplam,a;
	int k=0;
	dizi[k]=1;
	a=i;
	while(i>1)
	{
	k++;
	i--;
	toplam = ilk + son;
	ilk=son;
	son=toplam;
	
	dizi[k]=toplam;
}
printf("\n \n dizi =  ");
}
int main(){
	int a;
	cin>>a;
	int deneme[a];
    fak(a, deneme);
    for(int i=0;i<a;i++ ){
    	cout<<'\t'<<deneme[i];
	}
	cout<<"\ndizinin son elemani="<<deneme[a-1];
}

	
