#include <windows.h>
#include <conio.h>
#include <iostream>
#include <vector>

#define BLACK "\x1b[48;2;0;0;0m"
#define GRAY "\x1b[48;2;127;127;127m"
#define BROWN "\x1b[48;2;136;0;21m"
#define RED "\x1b[48;2;237;28;36m"
#define ORANGE "\x1b[48;2;255;127;39m"
#define YELLOW "\x1b[48;2;255;242;0m"
#define GREEN "\x1b[48;2;34;177;76m"
#define CYAN "\x1b[48;2;0;162;232m"
#define BLUE "\x1b[48;2;63;72;204m"
#define PURPLE "\x1b[48;2;163;73;164m"
#define WHITE "\x1b[48;2;255;255;255m"

void moveCursor(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    COORD position;
    position.X = x;
    position.Y = y;

    SetConsoleCursorPosition(hConsole, position);
}

void drawGUI(std::vector<std::string> colors, std::string currentColor){
	int x=1; int y=0;
	moveCursor(x,y);
	std::cout<<"╔════════════════════╗ PRESS 'E' FOR ERASE"; moveCursor(x,++y);
	std::cout<<"║                    ║"; moveCursor(x,++y);
	std::cout<<"╚════════════════════╝ PRESS 'Q' TO EXIT";

	x=2; y=1;
	moveCursor(x,y);
	for(int i=0; i<colors.size(); i++){
		std::cout<<"\x1b[48;2;255;255;255m"<<colors[i]<<"  ";
	}
}

int main() {
	//Clear console
	system("cls");
	//Change BG color to white
	system("color F0");
	//OutputCP
	SetConsoleOutputCP(65001);

	std::vector<std::string> colors = {
		BLACK,
		GRAY,
		BROWN,
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		CYAN,
		BLUE,
		PURPLE };
	std::string currentColor = "\x1b[48;2;0;0;0m";
	drawGUI(colors, currentColor);

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    INPUT_RECORD inputRecord;
    DWORD events;

    while (true) {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);
        if (inputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mouseEvent = inputRecord.Event.MouseEvent;

            if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                COORD pos = mouseEvent.dwMousePosition;
            	moveCursor(pos.X, pos.Y);
                if(pos.Y == 1){
	                switch(pos.X){
	            			case 2: case 3:
	            				currentColor = BLACK;
	            				break;
	            			case 4: case 5:
	            				currentColor = GRAY;
	            				break;
	            			case 6: case 7:
	            				currentColor = BROWN;
	            				break;
	            			case 8: case 9:
	            				currentColor = RED;
	            				break;
	            			case 10: case 11:
	            				currentColor = ORANGE;
	            				break;
	            			case 12: case 13:
	            				currentColor = YELLOW;
	            				break;
	            			case 14: case 15:
	            				currentColor = GREEN;
	            				break;
	            			case 16: case 17:
	            				currentColor = CYAN;
	            				break;
	            			case 18: case 19:
	            				currentColor = BLUE;
	            				break;
	            			case 20: case 21:
	            				currentColor = PURPLE;
	            				break;
	            			default:
	            				break;

	            	}
	            }

	            if(pos.X>1 && pos.Y>2){
	            	if(pos.X%2 !=0 ){
	            		pos.X--;
	            		moveCursor(pos.X, pos.Y);
            		}
            		std::cout<<currentColor<<"  ";
	            }
            }

        }

		if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
		    char key = inputRecord.Event.KeyEvent.uChar.AsciiChar;

		    switch (key) {
		        case 'q':
		            return 0;
		        case 'e':
		            currentColor = WHITE;
		            break;
		        default:
		            break;
		    }
		}

        Sleep(1);
    }

	std::cout<<"\x1b[0m";
    
    return 0;
}