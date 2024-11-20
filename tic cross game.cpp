#include<iostream>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdio.h>

using namespace std;

	bool draw=false;
	int choice;
	string ply1,ply2;
	char turns='X';
	char red[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
	int row,coloumn;
	
	
	
	int main_board(){
		system("cls");
		cout<<" T "<<"^"<<"\t\t"<<ply1<<"[X]"<<endl;
	cout<<" I "<<"^"<<"\t\t"<<ply2<<"[O]"<<endl;
	cout<<" C "<<"^"<<"\t\t\t\t\t"<<"        |        |        "<<endl;
	cout<<"   "<<"^"<<"\t\t\t\t\t"<<"   "<<red[0][0]<<"    |   "<<red[0][1]<<"    |   "<<red[0][2]<<"    "<<endl;
	cout<<" C "<<"^"<<"\t\t\t\t\t"<<"        |        |        "<<endl;
	cout<<" R "<<"^"<<"\t\t\t\t\t"<<"--------|--------|--------"<<endl;
	cout<<" O "<<"^"<<"\t\t\t\t\t"<<"        |        |        "<<endl;
	cout<<" S "<<"^"<<"\t\t\t\t\t"<<"   "<<red[1][0]<<"    |   "<<red[1][1]<<"    |   "<<red[1][2]<<"    "<<endl;
	cout<<" S "<<"^"<<"\t\t\t\t\t"<<"        |        |        "<<endl;
	cout<<"   "<<"^"<<"\t\t\t\t\t"<<"--------|--------|--------"<<endl;
	cout<<" G "<<"^"<<"\t\t\t\t\t"<<"        |        |        "<<endl;
	cout<<" A "<<"^"<<"\t\t\t\t\t"<<"   "<<red[2][0]<<"    |   "<<red[2][1]<<"    |   "<<red[2][2]<<"    "<<endl;
	cout<<" M "<<"^"<<"\t\t\t\t\t"<<"        |        |        "<<endl;
	cout<<" E "<<"^";
	
	
	}
	
	void ply_turn()
	{
		
			
	 	if(turns=='X')
			cout<<"\t\t\t"<<ply1<<" turns: ";
		  if(turns=='O')
			cout<<"\t\t\t"<<ply2<<" turns: ";
			cin>>choice;
			
		switch(choice)
		{
			case 1:row=0;coloumn=0;break;
			case 2:row=0;coloumn=1;break;	
			case 3:row=0;coloumn=2;break;
			case 4:row=1;coloumn=0;break;
			case 5:row=1;coloumn=1;break;
			case 6:row=1;coloumn=2;break;
			case 7:row=2;coloumn=0;break;
			case 8:row=2;coloumn=1;break;
			case 9:row=2;coloumn=2;break;
			default: 
			cout<<"invalid choice!!!";
			break;
		}
		if(turns=='X' && red[row][coloumn]!='X' && red[row][coloumn]!='O')
		{
			red[row][coloumn]='X';
			turns='O';
		}
		else if(turns=='O' && red[row][coloumn]!='X' && red[row][coloumn]!='O')
		{
			red[row][coloumn]='O';
			turns='X';
		}
		else 
		{
			cout<<"\n\t\a\tThe block is already fill :(";
			cout<<"\n\t\tPlease try again";
			cout<<"\n\t\t****************";
			
			ply_turn();
		}
		
	}
 int gameover()
{			
			for(int i=0;i<3;i++)
			if(red[i][0]==red[i][1] && red[i][0]==red[i][2] || red[0][i]==red[1][i] && red[0][i]==red[2][i] || red[0][0]==red[1][1] && red[0][0]==red[2][2] || red[2][0]==red[1][1] && red[2][0]==red[0][2] )
			return false;
			for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
			if(red[i][j]!='X' && red[i][j]!='O')
			return true;
			
			if(draw=true)
			return false;
}
	
	void drawO()
	{
		system("cls");
		cout<<"\n\n\n\a";
		cout<<"\t\t\t\t"<<"_________________________________________"<<endl;
		cout<<"\t\t\t\t"<<"|                                       |"<<endl;
		cout<<"\t\t\t\t"<<"|                                       |"<<endl;
		cout<<"\t\t\t\t"<<"|                                       |"<<endl;
		cout<<"\t\t\t\t"<<"|                                       |"<<endl;
		cout<<"\t\t\t\t"<<"|          ******************           |"<<endl;
		cout<<"\t\t\t\t"<<"|           G A M E  D R A W            |"<<endl;
		cout<<"\t\t\t\t"<<"|          ******************           |"<<endl;
		cout<<"\t\t\t\t"<<"|                                       |"<<endl;
		cout<<"\t\t\t\t"<<"|                                       |"<<endl;
		cout<<"\t\t\t\t"<<"|                                       |"<<endl;
		cout<<"\t\t\t\t"<<"|                                       |"<<endl;
		cout<<"\t\t\t\t"<<"|_______________________________________|"<<endl;
	}
	
int main()
{
	cout<<"Enter the name of first player: ";
	cin>>ply1;
	cout<<"Enter the name of second player: ";
	cin>>ply2;
	system("cls");
	while(gameover())
	{
	main_board();
	ply_turn();
	gameover();
	

	}
	if(turns=='X' && draw==false)
	{	
	cout<<"\a\n\t C O N G R U E L A T I O N S";
	cout<<"\t"<<ply2<<" wins";
	}
	else if(turns=='O' && draw==false)
	{
			cout<<"\a\n\t C O N G R U E L A T I O N S";
			cout<<"\t"<<ply1<<" wins";
	}
	
	else
	{
		drawO();
	}
}
