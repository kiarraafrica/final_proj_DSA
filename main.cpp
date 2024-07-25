#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

main() {
    char ch;
	start:	
	
	string username, password, choice;
    cout << "\n\n \n                              -----------------------------------------Log In----------------------------------------- ";
	cout << "\n\n\n               Username: ";
	cin  >> username;
    cout << "\n               Password: ";
	ch = getch();

	while (ch != 13) {
    if (ch == 8) {
        // backspace was pressed
        if (password.length()) {
            cout << "\b \b";
            password.pop_back();
        }
        ch = getch();
        continue;
      }
    //character 13 is enter
    password.push_back(ch);
    cout << '*';
    ch = getch();
	}


	 cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";

	if (username == "player1" && password == "player1pass") {
	    mainmenu:
	    system ("cls");
	    cout << "\n\n \n                              -------------------------------------What are the Odds?-------------------------------------- ";
		cout << "\n\n \n                                             Game Levels:";
		cout << "\n\n \n                                             Press 1 -----------------------------> Easy";
		cout << "\n\n \n                                             Press 2 -----------------------------> Intermediate";
		cout << "\n\n \n                                             Press 3 -----------------------------> Hard" << endl;
		cout << "\n\n \n                                                                 Press any key to go back" << endl;
        cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
        cout << "\n\n \n                                                                         Input: ";
		cin >> choice;

		if (choice == "1") {
			easylevel:
			system ("cls");
	        cout << "\n\n \n                              -------------------------------------What are the Odds?-------------------------------------- ";
		    cout << "\n\n \n                                             Easy Level:";
		    cout << "\n\n \n                                             Press 1 -----------------------------> Slot";
		    cout << "\n\n \n                                             Press 2 -----------------------------> Lotto";
		    cout << "\n\n \n                                             Press 3 -----------------------------> Color Game" << endl;
		    cout << "\n\n \n                                                                 Press any key to go back" << endl;
            cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
            cout << "\n\n \n                                                                         Input: ";
		    cin >> choice;
		    
		    if (choice == "1") {
		    	system ("cls");
	            cout << "\n\n \n                              ---------------------------------------------Slot--------------------------------------------- " << endl;
		        cout << "\n\n \n                                             Press 1 -----------------------------> Go Back";
				cout << "\n\n \n                                                                   Press any key to exit" << endl;
                cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
                cout << "\n\n \n                                                                         Input: ";
                cin >> choice;
                
                if (choice == "1") {
                	goto easylevel;
				    return 0;
		        
				}
			}
			
			else if (choice == "2") {
		    	system ("cls");
	            cout << "\n\n \n                              --------------------------------------------Lotto--------------------------------------------- " << endl;
		        cout << "\n\n \n                                             Press 1 -----------------------------> Go Back";
				cout << "\n\n \n                                                                   Press any key to exit" << endl;
                cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
                cout << "\n\n \n                                                                         Input: ";
                cin >> choice;
                
                if (choice == "1") {
                	goto easylevel;
				    return 0;
		        
				}
			}
			
			else if (choice == "3") {
		    	system ("cls");
	            cout << "\n\n \n                              ------------------------------------------Color Game------------------------------------------ " << endl;
		        cout << "\n\n \n                                             Press 1 -----------------------------> Go Back";
				cout << "\n\n \n                                                                   Press any key to exit" << endl;
                cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
                cout << "\n\n \n                                                                         Input: ";
                cin >> choice;
                
                if (choice == "1") {
                	goto easylevel;
				}
				
		        return 0;
		        
		    }
		    
	    
		    else {	
				system ("cls");
				goto mainmenu;		
			}
	
		}
		
		else if (choice == "2") {
			intermediatelevel:
			system ("cls");
	        cout << "\n\n \n                              -------------------------------------What are the Odds?-------------------------------------- ";
		    cout << "\n\n \n                                             Intermediate Level:";
		    cout << "\n\n \n                                             Press 1 -----------------------------> Blackjack";
		    cout << "\n\n \n                                             Press 2 -----------------------------> Baccarat" << endl;
		    cout << "\n\n \n                                                                 Press any key to go back" << endl;
            cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
            cout << "\n\n \n                                                                         Input: ";
		    cin >> choice;
		    
		    if (choice == "1") {
		    	system ("cls");
	            cout << "\n\n \n                              ------------------------------------------Blackjack------------------------------------------- " << endl;
		        cout << "\n\n \n                                             Press 1 -----------------------------> Go Back";
				cout << "\n\n \n                                                                   Press any key to exit" << endl;
                cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
                cout << "\n\n \n                                                                         Input: ";
                cin >> choice;
                
                if (choice == "1") {
                	goto intermediatelevel;
				
		        return 0;
		        
				}
			}
			
			else if (choice == "2") {
		    	system ("cls");
	            cout << "\n\n \n                              -------------------------------------------Baccarat------------------------------------------- " << endl;
		        cout << "\n\n \n                                             Press 1 -----------------------------> Go Back";
				cout << "\n\n \n                                                                   Press any key to exit" << endl;
                cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
                cout << "\n\n \n                                                                         Input: ";
                cin >> choice;
                
                if (choice == "1") {
                	goto intermediatelevel;
					return 0;
					
				}
							
			}
		        
				
			else {	
				system ("cls");
				goto mainmenu;				
			}
		
		}
		
		else if (choice == "3") {
			hardlevel:
			system ("cls");
	        cout << "\n\n \n                              -------------------------------------What are the Odds?-------------------------------------- ";
		    cout << "\n\n \n                                             Hard Level:";
		    cout << "\n\n \n                                             Press 1 -----------------------------> Sudoku" << endl;
		    cout << "\n\n \n                                                                 Press any key to go back" << endl;
            cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
            cout << "\n\n \n                                                                         Input: ";
		    cin >> choice;
		    
		    if (choice == "1") {
		    	system ("cls");
	            cout << "\n\n \n                              --------------------------------------------Sudoku-------------------------------------------- " << endl;
		        cout << "\n\n \n                                             Press 1 -----------------------------> Go Back";
				cout << "\n\n \n                                                                   Press any key to exit" << endl;
                cout << "\n\n \n                              ---------------------------------------------------------------------------------------------- ";
                cout << "\n\n \n                                                                         Input: ";
                cin >> choice;
                
                if (choice == "1") {
                	goto hardlevel;
				
		        return 0;
		        
				}
			}
			
			else {	
				system ("cls");
				goto mainmenu;				
			}
			
		}
			
		else {
		    system ("cls");
		    goto start;
	    }
		
	}
	

	else {
		cout << "\n\n\n                                              You entered the wrong username or password. Please try again. "<<endl;
		goto start;
        cout << "\n\n \n                              ---------------------------------------------------------------------------------------- ";
	 	
    }
    
}
