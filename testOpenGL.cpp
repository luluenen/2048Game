#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class Game{

public:
	void init() ;
	void displayScreen();
	void getKeyPress();
	string getkp() const {return keyPress;}
	void checkEndGame();
	void randseek();
	void moveUp(int j);
	void moveDown(int j);
	void moveLeft(int i);
	void moveRight(int i);
	void displayScreenEnd();
	void displayScreenQuit();
	void move_grid();// "move_order = LEFT, RIGHT, UP, DOWN"
	
private:
	int grid[4][4];
	int score;
	string keyPress;
	int checkEndVector[2];
	bool end = false;
	const int microseconds=100;
};

void Game::getKeyPress()
{
  system("stty raw");
  cin>>keyPress;
  system("stty cooked");
}


void Game::init() 
{
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			grid[i][j] = 0;
		}
	}
	randseek();
	randseek();
	score = 0;
	for (int i=0;i<2;i++){
		checkEndVector[i]=0;
	}
}


void Game::randSeek()
{	
	vector<int> myvector;
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if (grid[i][j]==0){
				myvector.push_back(4*i+j);
			}
		}
	}
	
	int index;
	index=rand()%(myvector.size());
	int i;
	i=myvector[index];
	if (((double) rand()/(RAND_MAX))<0.9){
		grid[i/4][i%4]=2;
	}
	else{
		grid[i/4][i%4]=4;
	}
}

void Game::moveGrid(){
	int tempGrid[4][4];
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			tempGrid[i][j]=grid[i][j];
		}
	}
	
	if (keyPress == "w"){
		for(int i=0; i<4; i++){
			moveUp(i);
		}
		bool equalGrid = true;
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if(tempGrid[i][j]!=grid[i][j]){
					equalGrid = false;
					break;
				}
			}
		}
		
		
		if (!equalGrid){
			randseek();
			displayScreen();
			checkEndVector[0]=0;
			checkEndVector[1]=0;
		}
		else{
			checkEndVector[1]=1;
			}
	}
	
	if (keyPress == "d"){
		for(int i=0; i<4; i++){
			moveRight(i);
		}
		
		bool equalGrid = true;
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if(tempGrid[i][j]!=grid[i][j]){
					equalGrid = false;
					break;
				}
			}
		}
		
		
		if (!equalGrid){
			randseek();
			displayScreen();
			checkEndVector[0]=0;
			checkEndVector[1]=0;
		}
		else{
			checkEndVector[0]=1;
			}
		
	}
	if (keyPress == "s"){
		for(int i=0; i<4; i++){
			moveDown(i);
		}
		bool equalGrid = true;
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if(tempGrid[i][j]!=grid[i][j]){
					equalGrid = false;
					break;
				}
			}
		}
		
		
		if (!equalGrid){
			randseek();
			displayScreen();
			checkEndVector[0]=0;
			checkEndVector[1]=0;
		}
		else{
			checkEndVector[1]=1;
			}
	}
	if (keyPress == "a"){
		for(int i=0; i<4; i++){
			moveLeft(i);
		}
		bool equalGrid = true;
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if(tempGrid[i][j]!=grid[i][j]){
					equalGrid = false;
					break;
				}
			}
		}
		
		
		if (!equalGrid){
			randseek();
			displayScreen();
			checkEndVector[0]=0;
			checkEndVector[1]=0;
		}
		else{
			checkEndVector[0]=1;
			}
	}
	if (keyPress == "r"){
		init();
		displayScreen();
	}

}

void Game::moveRight(int i)
{	
	if (grid[i][3]!=0 || grid[i][2]!=0 || grid[i][1]!=0 || grid[i][0]!=0){
		if (grid[i][3]==0){
			grid[i][3]=grid[i][2];
			grid[i][2]=grid[i][1];
			grid[i][1]=grid[i][0];
			grid[i][0]=0;
			moveRight(i);
		}
		else{
			if (grid[i][2]!=0 || grid[i][1]!=0 || grid[i][0]!=0){
				if (grid[i][2]==0){
					grid[i][2]=grid[i][1];
					grid[i][1]=grid[i][0];
					grid[i][0]=0;
					moveRight(i);
				}
				else{
					if (grid[i][2]==grid[i][3]){
						grid[i][3]=grid[i][3]*2;
						score+=grid[i][3];
						if (grid[i][1]==grid[i][0]){
							grid[i][2]=grid[i][1]*2;
							score+=grid[i][2];
							grid[i][1]=0;
							grid[i][0]=0;
						}
						else{
							grid[i][2]=grid[i][1];
							grid[i][1]=grid[i][0];
							grid[i][0]=0;
						}
					}
					else{
						if (grid[i][1]==0){
							if (grid[i][0]==grid[i][2]){
								grid[i][2]=grid[i][2]*2;
								score+=grid[i][2];
								grid[i][0]=0;
							}
							else{
								grid[i][1]=grid[i][0];
								grid[i][0]=0;
							}
						}
						else{
							if (grid[i][1]==grid[i][2]){
								grid[i][2]=grid[i][2]*2;
								score+=grid[i][2];
								grid[i][1]=grid[i][0];
								grid[i][0]=0;
							}
							else{
								if (grid[i][0]==grid[i][1]){
									grid[i][1]=grid[i][1]*2;
									score+=grid[i][1];
									grid[i][0]=0;
								}
							}
						}
					}
				}
			}
		}
	}
}


void Game::moveLeft(int i)
{	
	if (grid[i][3]!=0 || grid[i][2]!=0 || grid[i][1]!=0 || grid[i][0]!=0){
		if (grid[i][0]==0){
			grid[i][0]=grid[i][1];
			grid[i][1]=grid[i][2];
			grid[i][2]=grid[i][3];
			grid[i][3]=0;
			moveLeft(i);
		}
		else{
			if (grid[i][1]!=0 || grid[i][2]!=0 || grid[i][3]!=0){
				if (grid[i][1]==0){
					grid[i][1]=grid[i][2];
					grid[i][2]=grid[i][3];
					grid[i][3]=0;
					moveLeft(i);
				}
				else{
					if (grid[i][1]==grid[i][0]){
						grid[i][0]=grid[i][0]*2;
						score+=grid[i][0];
						if (grid[i][2]==grid[i][3]){
							grid[i][1]=grid[i][2]*2;
							score+=grid[i][1];
							grid[i][2]=0;
							grid[i][3]=0;
						}
						else{
							grid[i][1]=grid[i][2];
							grid[i][2]=grid[i][3];
							grid[i][3]=0;
						}
					}
					else{
						if (grid[i][2]==0){
							if (grid[i][3]==grid[i][1]){
								grid[i][1]=grid[i][1]*2;
								score+=grid[i][1];
								grid[i][3]=0;
							}
							else{
								grid[i][2]=grid[i][3];
								grid[i][3]=0;
							}
						}
						else{
							if (grid[i][2]==grid[i][1]){
								grid[i][1]=grid[i][1]*2;
								score+=grid[i][1];
								grid[i][2]=grid[i][3];
								grid[i][3]=0;
							}
							else{
								if (grid[i][3]==grid[i][2]){
									grid[i][2]=grid[i][2]*2;
									score+=grid[i][2];
									grid[i][3]=0;
								}
							}
						}
					}
				}
			}
		}
	}

}


void Game::moveUp(int j)
{	
	if (grid[0][j]!=0 || grid[1][j]!=0 || grid[2][j]!=0 || grid[3][j]!=0){
		if (grid[0][j]==0){
			grid[0][j]=grid[1][j];
			grid[1][j]=grid[2][j];
			grid[2][j]=grid[3][j];
			grid[3][j]=0;
			moveUp(j);
		}
		else{
			if (grid[1][j]!=0 || grid[2][j]!=0 || grid[3][j]!=0){
				if (grid[1][j]==0){
					grid[1][j]=grid[2][j];
					grid[2][j]=grid[3][j];
					grid[3][j]=0;
					moveUp(j);
				}
				else{
					if (grid[1][j]==grid[0][j]){
						grid[0][j]=grid[0][j]*2;
						score+=grid[0][j];
						if (grid[2][j]==grid[3][j]){
							grid[1][j]=grid[2][j]*2;
							score+=grid[1][j];
							grid[2][j]=0;
							grid[3][j]=0;
						}
						else{
							grid[1][j]=grid[2][j];
							grid[2][j]=grid[3][j];
							grid[3][j]=0;
						}
					}
					else{
						if (grid[2][j]==0){
							if (grid[3][j]==grid[1][j]){
								grid[1][j]=grid[1][j]*2;
								score+=grid[1][j];
								grid[3][j]=0;
							}
							else{
								grid[2][j]=grid[3][j];
								grid[3][j]=0;
							}
						}
						else{
							if (grid[2][j]==grid[1][j]){
								grid[1][j]=grid[1][j]*2;
								score+=grid[1][j];
								grid[2][j]=grid[3][j];
								grid[3][j]=0;
							}
							else{
								if (grid[3][j]==grid[2][j]){
									grid[2][j]=grid[2][j]*2;
									grid[3][j]=0;
								}
							}
						}
					}
				}
			}
		}
	}

}


void Game::moveDown(int j)
{	
	if (grid[0][j]!=0 || grid[1][j]!=0 || grid[2][j]!=0 || grid[3][j]!=0){
		if (grid[3][j]==0){
			grid[3][j]=grid[2][j];
			grid[2][j]=grid[1][j];
			grid[1][j]=grid[0][j];
			grid[0][j]=0;
			moveDown(j);
		}
		else{
			if (grid[2][j]!=0 || grid[1][j]!=0 || grid[0][j]!=0){
				if (grid[2][j]==0){
					grid[2][j]=grid[1][j];
					grid[1][j]=grid[0][j];
					grid[0][j]=0;
					moveDown(j);
				}
				else{
					if (grid[2][j]==grid[3][j]){
						grid[3][j]=grid[3][j]*2;
						score+=grid[3][j];
						if (grid[1][j]==grid[0][j]){
							grid[2][j]=grid[1][j]*2;
							score+=grid[2][j];
							grid[0][j]=0;
							grid[1][j]=0;
						}
						else{
							grid[2][j]=grid[1][j];
							grid[1][j]=grid[0][j];
							grid[0][j]=0;
						}
					}
					else{
						if (grid[1][j]==0){
							if (grid[0][j]==grid[2][j]){
								grid[2][j]=grid[2][j]*2;
								score+=grid[2][j];
								grid[0][j]=0;
							}
							else{
								grid[1][j]=grid[0][j];
								grid[0][j]=0;
							}
						}
						else{
							if (grid[1][j]==grid[2][j]){
								grid[2][j]=grid[2][j]*2;
								score+=grid[2][j];
								grid[1][j]=grid[0][j];
								grid[0][j]=0;
							}
							else{
								if (grid[0][j]==grid[1][j]){
									grid[1][j]=grid[1][j]*2;
									score+=grid[1][j];
									grid[0][j]=0;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Game::displayScreenQuit(){

	system("clear");
	cout<<"Thank you, see you later"<<endl;
}


void Game::displayScreenEnd(){

	system("clear");
	cout<<"Thank you, see you later"<<endl;
}

void Game::displayScreen()
{	
	system("clear");
	
	if(end == false){
			
		cout<<"Welcome to 2048 game, enjoy your game"<<endl;			
		cout<<"SCORE::"<< score <<" \n\n\n\n";
			
			for(int i=0;i<4;i++)
			{
				cout<<"\t\t     |";
					for(int j=0;j<4;j++)
					{
						if(grid[i][j])
							printf("%4d    |",grid[i][j]);
						else
							printf("%4c    |",' ');
					} 
				cout<<endl<<endl;
			}
				
		cout<<"\n\n Controls (+ :: o)\n \t\t\t   \t\t\t\tu - undo\n\tw\t\t     ^    \t\t\tq - quit\n\t\t\t\t\t\t\t\t"
			<<" \n   A    S    D\t\t<    v    >\t\t\t" << "r - restart"
			<<" \n\t\t\t\t";
	}
	else{
		
		cout<<"End of game, thank you"<<endl;			
		
	}

		
}

void Game::checkEndGame(){
	
	
	bool count = true;
	
	for(int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if(grid[i][j] == 0){
				count = false;
				break;
			}
		}
	}
	
	if (count && checkEndVector[0]==1 && checkEndVector[1]==1){
		end=true;
		}
	
	/*
	if (count==16){
		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;
		
		for(int i=0; i<4; i++){
			for(int j=0; j<3; j++){
				if(grid[i][j]=grid[i][j+1]){
					left = true;
					right = true;
					break;
				}
			}
		}
		
		for(int i=0; i<3; i++){
			for(int j=0; j<4; j++){
				if(grid[i][j]=grid[i+1][j]){
					down = true;
					up = true;
					break;
				}
			}
		}
		
		if (up==false && down==false && left==false && right==false){
			end = true;
		}
			
		}*/
	}



int main(int argc, char *argv[])
{
    Game exec;
    
    exec.init();
    exec.displayScreen();
    while(1){
		
		
		exec.getKeyPress();
		cout<< exec.getkp() << endl;
		exec.move_grid();
		exec.checkEndGame();
	}
	return 0;
}
