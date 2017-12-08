#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Game{

public:
	void init() ;
	void displayScreen();
	void getKeyPress();
	string getkp() const {return keyPress;}
	bool checkEndGame();
	void randseek();
	
	void move_grid();// "move_order = LEFT, RIGHT, UP, DOWN"
	
private:
	int grid[4][4];
	int score;
	string keyPress;
	bool end = false;

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
}


void Game::randseek()
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

bool Game::checkEndGame(){
	int count = 0;
	for(int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if(grid[i][j] != 0){
				count ++;
			}
		}
	}
	if (count==16){
		
		for(int i=0; i<4; i++){
			for (int j=0; j<4; j++){
				bool left = true;
				bool right = true;
				bool up = true;
				bool down = true;
				if(i!=0){
					if (grid[i-1][j] != grid[i][j]){
						left = false;
					}
				}	
				if(i!=3){
					if (grid[i+1][j] != grid[i][j]){
						right = false;
					}
				}
				if(j!=0){
					if (grid[i][j-1] != grid[i][j]){
						up = false;
					}
				}
				if(j!=3){
					if (grid[i][j+1] != grid[i][j]){
						down = false;
					}
				}
				if (up==false && down==false && left==false && right==false){
					end = true;
				}
			}
		}
	}
	return true;
}


int main(int argc, char *argv[])
{
    Game exec;
    exec.init();
    while(1){
		
		exec.displayScreen();
		exec.getKeyPress();
		cout<< exec.getkp() << endl;
	}
	return 0;
}
