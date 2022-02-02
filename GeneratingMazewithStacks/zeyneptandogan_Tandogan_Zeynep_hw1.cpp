//Zeynep Tandogan  25200
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>   
#include "randgen.h"
#include "stack.h"
#include "strutils.h"
#include <vector>
using namespace std;

struct data{
	int l,r,u,d,row,col;//for directions and matrix
	int xcor,ycor;//coordinates
	bool visited;//Whether it is passed or not
};

int chosen_unvisited_path(vector<vector<data> > matrix ,int i,int j,int M,int N){//to know how many options we have (for path)
	RandGen random;
	vector<int>boundaries;
	int count=0;
    if (i+1<M && matrix[i+1][j].visited==false&& matrix[i][j].d==0){//down=0
		boundaries.push_back(0);
	}
	if(j+1<N && matrix[i][j+1].visited==false&& matrix[i][j].r==0){//right=1
		boundaries.push_back(1);
	}
	if (i-1>=0 && matrix[i-1][j].visited==false&&  matrix[i][j].u==0){//up=2
		boundaries.push_back(2);
	}
	if(j-1>=0 && matrix[i][j-1].visited==false&& matrix[i][j].l==0){//left=3
		boundaries.push_back(3);
	}
	int choice_count=boundaries.size();
	if(choice_count==0)//it means there is no place to go
		return -1;
	int rand_num=random.RandInt(0,choice_count-1);//randomness
	return boundaries[rand_num];//the one that is chosen 
}


int chosen_unvisited(vector<vector<data> > matrix ,int i,int j,int M,int N){//to know how many options we have (for maze) 
	RandGen random;
	vector<int>boundaries;
	int count=0;
    if (i+1<M && matrix[i+1][j].visited==false){//down=0
		boundaries.push_back(0);
	}
	if(j+1<N && matrix[i][j+1].visited==false){//right=1
		boundaries.push_back(1);
	}
	if (i-1>=0 && matrix[i-1][j].visited==false){//up=2
		boundaries.push_back(2);
	}
	if(j-1>=0 && matrix[i][j-1].visited==false){//left=3
		boundaries.push_back(3);
	}
	int choice_count=boundaries.size();
	if(choice_count==0)//it means there is no place to go
		return -1;
	int rand_num=random.RandInt(0,choice_count-1);//randomness
	return boundaries[rand_num];
}

void maze_formation(int K,int M,int N){
	string strK=to_string(K);//for the file name
	//Forming the matrix
	vector<vector<data> > matrix (M,vector<data>(N));
	//matrix with full of walls
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){

			matrix[i][j].row=i;
			matrix[i][j].col=j;
			matrix[i][j].xcor=j;//i consider them as coordinates coordinate  not as (row,col), i organized them accordingly
			matrix[i][j].ycor=M-i-1;
			matrix[i][j].l=1;
			matrix[i][j].r=1;
			matrix[i][j].u=1;
			matrix[i][j].d=1;//with walls everywhere
			matrix[i][j].visited=false;
		}
	}
	Stack<data> stack;
	matrix[M-1][0].visited=true;
	stack.push(matrix[M-1][0]);//push all the values in the struct
	int direction;
	int x=M-1;
	int y=0;

	ofstream outfile;//creating the file maze_mazeID.txt
	string name="maze_"+strK+".txt";
	outfile.open(name);
	outfile<<M<<" " <<N<<endl;//first line
	bool continueputwalls=true;
	while(continueputwalls){
		if(!stack.isEmpty()){
		data mat=stack.top();//to learn what is in the stack lastly
		int x=mat.row;
		int y=mat.col;
		direction=chosen_unvisited(matrix,x,y,M, N);
		
			if(direction!=-1){	
				//check the conditions and update the changed values
				if(direction==1){//right
					matrix[x][y+1].visited=true;
					matrix[x][y].r=0;
					matrix[x][y+1].l=0;
					y=y+1;
					matrix[x][y].xcor=y;//converting them to coordinates
					matrix[x][y].ycor=M-x-1;
					stack.push(matrix[x][y]);
				}
				if(direction==3){
					matrix[x][y-1].visited=true;//l=0
					matrix[x][y].l=0;
					matrix[x][y-1].r=0;
					y=y-1;
					matrix[x][y].xcor=y;//converting them to coordinates
					matrix[x][y].ycor=M-x-1;
					stack.push(matrix[x][y]);
				}
				if(direction==0){
					matrix[x+1][y].visited=true;//u=0
					matrix[x][y].d=0;
					matrix[x+1][y].u=0;
					x=x+1;
					matrix[x][y].xcor=y;//converting them to coordinates
					matrix[x][y].ycor=M-x-1;//x+1;
					stack.push(matrix[x][y]);
					
				}
				if(direction==2){ 
					matrix[x-1][y].visited=true;
					matrix[x][y].u=0;
					matrix[x-1][y].d=0;
					x=x-1;
					matrix[x][y].xcor=y;//converting them to coordinates
					matrix[x][y].ycor=M-x-1;
					stack.push(matrix[x][y]);
				}
			}
			
			else{
				if(!stack.isEmpty()){
					stack.pop();
					continueputwalls=true;
				}
				else
					continueputwalls=false;//stack is empty now all of them are visited.
				}
		}
		else
			continueputwalls=false;
	}
	//writing all info to the file
	for(int j=0;j<N;j++){
		for(int i=M-1;i>=0;i--){
			outfile<< "x="<<matrix[i][j].xcor<<" "<<"y="<<matrix[i][j].ycor<<" "<<"l="<<matrix[i][j].l<<" "<<"r="<<matrix[i][j].r<<" "<<"u="<<matrix[i][j].u<<" "<<"d="<<matrix[i][j].d<<endl;
		}
	}
	outfile.close();
}

void path_finding(int ID,int entryX,int entryY,int exitX,int exitY){
	
	ifstream inFile;
	//opening the file that formed in maze_formation
	string s,xstr,ystr,lstr,rstr,ustr,dstr;
	int x,y,l,r,u,d,totalrow,totalcol;

	string strid=to_string(ID);
	string filename="maze_"+strid+".txt";
	inFile.open(filename);
	getline(inFile,s);//taking row and col numbers
	istringstream iss(s);
	iss>>totalrow>>totalcol;
	vector<vector<data> > newmat (totalrow,vector<data>(totalcol));//forming the matrix
	while(getline(inFile,s)){//reading line by line and store the info
			istringstream iss(s);
			iss>>xstr>>ystr>>lstr>>rstr>>ustr>>dstr;
			int idx=xstr.find("=");//taking the number part only
			string x_coor_str=xstr.substr(idx+1,xstr.length());
			int idx2=ystr.find("=");
			string y_coor_str=ystr.substr(idx2+1,ystr.length());
			int x_coor=atoi(x_coor_str);
			int y_coor=atoi(y_coor_str);
			x=totalrow-1-(y_coor);
			y=x_coor;
			l=lstr[2]-'0';
			r=rstr[2]-'0';
			u=ustr[2]-'0';
			d=dstr[2]-'0';
			newmat[x][y].row=x;
			newmat[x][y].col=y;
			newmat[x][y].l=l;
			newmat[x][y].r=r;
			newmat[x][y].u=u;
			newmat[x][y].d=d;
			newmat[x][y].xcor=x_coor;
			newmat[x][y].ycor=y_coor;
			newmat[x][y].visited=false;	
	}

	Stack<data> pathstack;
	ofstream pathfile;//forming the second file and open it
	string pathname="maze_"+strid+"_path_"+to_string(entryX)+"_"+to_string(entryY)+"_"+to_string(exitX)+"_"+to_string(exitY)+".txt";
	pathfile.open(pathname);
	newmat[totalrow-1-entryY][entryX].visited=true;//pushing the starting point 
	newmat[totalrow-1-entryY][entryX].row=totalrow-1-entryY;//creating row and col not to mix them with the coordinates
	newmat[totalrow-1-entryY][entryX].col=entryX;
	pathstack.push(newmat[totalrow-1-entryY][entryX]);
	int x_row=totalrow-1-entryY;
	int y_col=entryX;
	bool continuesearch=true;//for while loop
	int direction=0;

	while (continuesearch){
		if(!pathstack.isEmpty()){
			int count=0;
			data mat=pathstack.top();//to learn what we have lastly in stack
			x_row=mat.row;
			y_col=mat.col;
			direction=chosen_unvisited_path(newmat,x_row,y_col,totalrow, totalcol);
			if(mat.xcor==exitX && mat.ycor==exitY)
				continuesearch=false;
			else if(direction!=-1){//if direction is -1, it means there is no place to go further
				//Check the conditions
				if(direction==1){//right
					newmat[x_row][y_col+1].visited=true;
					y_col=y_col+1;
					newmat[x_row][y_col].xcor=y_col;
					newmat[x_row][y_col].ycor=totalrow-x_row-1;//converting them to coordinates
					pathstack.push(newmat[x_row][y_col]);

				}
				else if(direction==3){//left
					newmat[x_row][y_col-1].visited=true;
					y_col=y_col-1;
					newmat[x_row][y_col].xcor=y_col;
					newmat[x_row][y_col].ycor=totalrow-x_row-1;//converting them to coordinates
					pathstack.push(newmat[x_row][y_col]);
				}
				else if(direction==0){//down
					newmat[x_row+1][y_col].visited=true;
					x_row=x_row+1;
					newmat[x_row][y_col].xcor=y_col;
					newmat[x_row][y_col].ycor=totalrow-x_row-1;//converting them to coordinates
					pathstack.push(newmat[x_row][y_col]);
				}
				else if(direction== 2){//up
					newmat[x_row-1][y_col].visited=true;
					x_row=x_row-1;
					newmat[x_row][y_col].xcor=y_col;
					newmat[x_row][y_col].ycor=totalrow-x_row-1;//converting them to coordinates
					pathstack.push(newmat[x_row][y_col]);
				}
				
			}
			else{
				if(!pathstack.isEmpty()){
						pathstack.pop();// pop if there is no place to go
						continuesearch=true;
				}
				else
					continuesearch=false;//stack is empty now all of them are visited.
				}
		}
		else
			continuesearch=false;
	}
	Stack<data>writepath;//to be able to write it in reverse order i need the second stack
	while(!pathstack.isEmpty()){
		data x=pathstack.topAndPop();
		writepath.push(x);
	}
	while(!writepath.isEmpty()){
		data y=writepath.topAndPop();
		pathfile<<y.xcor<<" " <<y.ycor<<endl;//writing information to the file
	}
	pathfile.close();
}
	
int main(){
	int K,M,N;
	//taking all information that needed from the user
	cout<<"Enter the number of mazes: ";
	cin>>K;

	cout<<"Enter the number of rows and columns (M and N): ";
	cin>>M>>N;
	
	for(int z=1;z<=K;z++){//forming all the mazes
		maze_formation(z,M,N);
	}
	cout<<"All mazes are generated."<<endl;
	cout<<endl;

	int mazeID;
	int entryX, entryY, exitX,exitY;
	cout<<"Enter a maze ID between "<<1<<" to "<<K<<" inclusive to find a path: " ;
	cin>>mazeID;

	cout<<"Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin>>entryX>>entryY;

	cout<<"Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin>>exitX>>exitY;
	path_finding(mazeID,entryX, entryY, exitX,exitY);
	return 0;
}