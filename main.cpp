
#include <iostream>
#include <Windows.h>


const std::string metric_reference[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
const std::string XTurn = "X";
const std::string OTurn = "O";

namespace inputcode 
{
    constexpr int rerun = -99;
    constexpr int exit = -1;
    constexpr int newgame = -2;
    constexpr int toggleslot = -11;
    constexpr int blank = -10;
}


std::string metric[9];
std::string turns;

int input;

bool is_first_loop = true;
bool is_slot_visible = true;

int loops = 0;




template<typename VAR>
void get_input(VAR& target)
{
    std::cin >> target;
    //clear error and flag stuffs
    std::cin.clear();
    // ignores cin memory thing for 999 and newline? i guess
    std::cin.ignore(999, '\n');
}


void setup_new_game()
{
    //return the introduction
    is_first_loop = true;
    // set metric display to reference
    for (int slot = 0; slot < 9; slot++)
    {
        metric[slot] = (is_slot_visible) ? metric_reference[slot] : " ";
    }
    // set first player
    turns = XTurn;
    // set loops
    loops = 0;
}


void setup_console()
{
    //ask for da size
    std::string do_want_size;
    std::cout << " do you want to use games custom size?\n [] yes\n [] no\n input your choice here : ";
    get_input(do_want_size);
    if (do_want_size == "yes")
    {
        int option, X, Y;
        std::cout 
        << "\n enter size for centering. \n"
        << " >choose the closes< \n"
        << " 1 : 1280 720 \n"
        << " 2 : 1920 1080\n"
        << " 3 : 3840 2160 \n"
        << " input your option here : ";
        std::cin >> option;
        std::cout << " resizing ... \n";
        Sleep(500);
        switch (option)
        {
            default:
            X = 1280;
            Y = 720;
            break;
            case 1:
            X = 1280;
            Y = 720;
            break;
            case 2:
            X = 1920;
            Y = 1080;
            break;
            case 3:
            X = 3840;
            Y = 2160;
            break;
        }
        //set the console size
        HWND console = GetConsoleWindow();
        MoveWindow(console, X/3, Y/4, 8 * 57, 16 * 29, TRUE); // estimate: 8px width, 16px height
    }
}

// display the board using the current data from metric variable
void display_board()
{
    std::cout
    << "                " << "      |     |      \n"
    //                       "   1  |  2  |  3   \n"
    << "                " << "   " << metric[0] << "  |  " << metric[1] << "  |  " << metric[2] << "   \n"
    
    << "                " << " _____|_____|_____ \n"
    << "                " << "      |     |      \n"
    //                       "   4  |  5  |  6   \n"
    << "                " << "   " << metric[3] << "  |  " << metric[4] << "  |  " << metric[5] << "   \n"
    
    << "                " << " _____|_____|_____ \n"
    << "                " << "      |     |      \n"
    //                       "   7  |  8  |  9   \n"
    << "                " << "   " << metric[6] << "  |  " << metric[7] << "  |  " << metric[8] << "   \n"

    << "                " << "      |     |      \n"
    ;
    //  ----------------------------------------------------  maxlenght refernece

}


bool is_metric_empty(int& slot)
{
    return (metric[slot] != XTurn && metric[slot] != OTurn) ? true : false;
}


void toggle_slot_visibility()
{
    for (int slot = 0; slot < 9; slot++)
    {
        if (is_metric_empty(slot)) 
        {
            metric[slot] = (is_slot_visible) ? " " : metric_reference[slot];
        }
    }
    is_slot_visible = !is_slot_visible;
}


void players_turn_input()
{
    std::cout << " [" << turns << "] Player's turn : " ;
    get_input(input);
}


int game_loop()
{   while (true)    {

    // display header
    std::cout <<   "                      Loop " << loops << "                        "; 
    std::cout << "\n ------------------ Tic Tac Toe ------------------- \n\n"; 
    //              ----------------------------------------------------  maxlenght refernece

    // duh
    display_board();

    // greetings
    if (is_first_loop)
    {
        std::cout
        << "\n Be the first to align three marks together to win.\n"
        <<   " Enter a number    ( 1 - 9 )    to place your mark.\n\n"
        <<   " (exit : -1)   (new game : -2)  (re-run game : -99)\n"
        <<   " (toggle slot : -11)                               \n"
        <<   "                                                 :)\n";
    }

    // seperate game gui
    std::cout << "\n -------------------------------------------------- \n\n";
    //              ----------------------------------------------------  maxlenght refernece
  

    // get input and do calculations
    // if wrong reloop and get input do nothing
    players_turn_input();
    
    // handling input code stuff
    switch (input) 
    {
    // input exit code
    case inputcode::rerun:
    system("color 8");
    std::cout << " standby...                                      !! ";
    Sleep(2000);
    return -99; 

    // input exit code
    case inputcode::exit:
    system("color 8");
    std::cout << " exiting...                        have a good day! ";
    Sleep(1500);
    return 0; 

    // new game code
    case inputcode::newgame:
    setup_new_game(); 
    break;

    // toogle slot
    case inputcode::toggleslot:
    toggle_slot_visibility();
    break;


    default:
    // if player input is legit
    if (input >= 1 && input <=9 && metric[input - 1] != "X" && metric[input - 1] != "O") 
    {
        // game is started
        if (is_first_loop) 
        { 
            is_first_loop = false; 
        }
        
        // insert player's mark into metric
        metric[input - 1] = turns;
        // this = that if bla bla bal
        turns = (turns == XTurn) ? OTurn : XTurn;
        // next loop
        loops++;
    }
    break;
    
    }
    
    // refresh console
    system("cls");

}   }

int main()
{
    system("cls");
    system("color 7");
    setup_console();

    system("cls");
    //initailize game
    setup_new_game();

    if (game_loop() == -99)
    {
        main();
    }
    
    
    return 0;
}

