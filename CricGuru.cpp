#include <iostream>
#include <fstream>
#include <string.h>
using namespace std ;

/* 
PROFILE (friend with PLAYER) ----------->  STATS ----------------> PLAYER -----------------> FILES  
                            (virtually)                                                            */

class Profile
{
    public :
        char fName[25] , sName[25] ;
        string name , role , country , arm ;
        int mats , inns , runs , stat ;
        int notOut , wkts ;
        float avg , quo ; 
        string style , best ;
        Profile() // default ctor
        {
            name = style = best = country = arm = role = "NULL" ;
            mats = inns = runs = notOut = wkts = 0 ;
            avg = quo = 0.0 ;
        }
        Profile(string n , string c , string r , string s , int m , int i , int run , int no , float a , int w , string b , string ar , float q)
        {                     // param. ctor
            name = n ;
            country = c ;
            role = r ;
            style = s ;
            mats = m ;
            inns = i ;
            runs = run ;
            notOut = no ;
            avg = a ;
            quo = q ;
            arm = ar ;
            wkts = w ;
            best = b ;
        } 
        friend class Player ; // friend class
        inline void disp() ; // function prototyping
        inline void disp(int) ; // function overloading
} ;

void Profile :: disp() // display function to show basic player info
{                      // calls disp(int) recursively (indirect recursion) 
    cout << "Name : " << name << endl ;
    cout << "Country : " << country << endl ;
    cout << "Role : " << role << endl ;
    cout << "Matches : " << mats << endl ;
    cout << "Stats Available : " ;
    if(stat == 1) // stat is a member variable that is set to 1 or 2 to show if player stats are available or not
    {
        cout << "Yes" << endl ;
        if(role == "BAT")
            disp(1) ;
        if(role == "BWL")
            disp(2) ;
    }
    if(stat == 2)
        cout << "No" << endl ;
}

void Profile :: disp(int key) // overloaded display function that passes a key value - 
{                             // 1 to show batting stats & 2 for bowling stats
    if(key == 1) 
    {
        cout << "Bat. Style : " << style << "    < >    " ;
        cout << "Runs Scored : " << runs << "    < >    " ;
        cout << "Best Score : " << best << "    < >    " ;
        cout << "Bat. Avg : " << avg << "    < >    " ;
        cout << "Player Quotient : " << quo << endl ;
    }
    if(key == 2)
    {
        cout << "Bwl Arm/Style : " << arm << "/" << style << "    < >    " ;
        cout << "Wickets : " << wkts << "    < >    " ; 
        cout << "Best Match Figures : " << best << "    < >    " ;
        cout << "Bwl Avg : " << avg << "    < >    " ;
        cout << "Player Quotient : " << quo << endl ;
    }
}


class Stats : virtual public Profile // class containing functions for calculation of statistics and quotients
{
    public :
        inline float calcAvg(int key) // function to calculate bat and bwl avg
        {
            if(key == 1)
            {
                if(inns != notOut)
                    avg = float(runs) / (inns - notOut) ;
                else
                    avg = runs ;
                return avg ;
            }
            if(key == 2)
            {
                if(wkts != 0)
                    avg = float(runs) / wkts ;
                if(wkts == 0)
                {
                    avg = -1 ;
                    cout << "\n-> can't calc. bowling avg for 0 wickets" << endl ;
                }
                return avg ;
            }
        }
        inline float calcQuo(int key)        // function to calculate quotient
        {                                   // key = 1 for bat , 2 for bwl
            float x ;
            if(key == 1)
            {
                if(inns > 8)
                {
                    if (avg < 20.0)
                        x = 0.5 ;
                    if(avg >= 20.0 && avg < 23.0)
                        x = 1.0 ;
                    if(avg >= 23.0 && avg < 30.0)
                        x = 1.5 ;
                    if(avg >= 30.0 && avg < 33.0)
                        x = 2 ;
                    if(avg >= 33.0 && avg < 37.0)
                        x = 2.5 ;
                    if(avg >= 37.0 && avg < 40.0)
                        x = 3 ;
                    if(avg >= 40.0 && avg < 43.0)
                        x = 3.5 ;
                    if(avg >= 43.0 && avg < 47.0)
                        x = 4 ;
                    if(avg >= 47.0 && avg < 50.0)
                        x = 4.5 ;
                    if(avg >= 50.0)
                        x = 5.0 ; 
                }
                else
                    x = 0.0 ;

                return x ;
            }

            if(key == 2)
            {
                if(mats > 5)
                {
                    if(avg >= 50.0)
                        x = 0.5 ;
                    if(avg >= 45.0 && avg < 50.0)
                        x = 1.0 ;
                    if(avg >= 40.0 && avg < 45.0)
                        x = 1.5 ;
                    if(avg >= 37.0 && avg < 40.0)
                        x = 2.0 ;
                    if(avg >= 35.0 && avg < 37.0)
                        x = 2.5 ;
                    if(avg >= 33.0 && avg < 35.0)
                        x = 3 ;
                    if(avg >= 31.0 && avg < 33.0)
                        x = 3.5 ;
                    if(avg >= 29.0 && avg < 31.0)
                        x = 4 ;
                    if(avg >= 27.0 && avg < 29.0)
                        x = 4.5 ;
                    if(avg < 27.0)
                        x = 5.0 ;
                }
                else
                    x = 0.0 ;
                return x ;
            }
        }

        template<typename T> // use of function templates to create a bubble sort function
        void sort(T* arr , int n)
        {
            T temp ;
            for(int i = 0 ; i < n ; i ++)
            {
                for(int j = i + 1 ; j < n ; j ++)
                {
                    if(arr[i] > arr[j])
                    {
                        temp = arr[i] ;
                        arr[i] = arr[j] ;
                        arr[j] = temp ;
                    }
                }
            }
        }
} ;

class Player : public Stats // class with member fns to read player info , predict match , compare player and operator ovl
{
    public :
        Player() // ctor
        {
            Profile() ;
        }
        inline void read(int) ; // function prototyping
        inline void read(char) ; // function overloading

        // op overloading

        int operator > (Player p1)
        {
            if(quo > p1.quo)
                return 1 ;
        
            if(quo < p1.quo)
                return 0 ;
        }

        int operator == (Player p1)
        {
            if(quo == p1.quo)
                return 1 ;
            if(quo != p1.quo)
                return 0 ;
        }
        
        // friend fns

        friend void Predict(Player *Ind[] , int ind , Player *Aus[] , int aus)
        {
            float indTQA , ausTQA , sum1 = 0.0 , sum2 = 0.0 ;
            for(int i = 0 ; i < ind ; i ++)
                sum1 += Ind[i] -> quo ;     
            indTQA = sum1/float(ind) ;
            for(int i = 0 ; i < aus ; i ++)
                sum2 += Aus[i] -> quo ;          
            ausTQA = sum2/float(aus) ;
            cout << "PredictGuru says...." << endl ; // TQA
            cout << "INDIA  :   " << indTQA << endl ;
            cout << "AUSTRALIA :  " << ausTQA << endl ;
            if(indTQA > ausTQA)
                cout << "India stands a better chance of victory.\n" ;
            else if(indTQA < ausTQA)
                cout << "Australia stands a better chance of victory.\n" ;
            else
                cout << "Both teams are equally good and stand a chance.\n" ;      
        }

        friend void Compare(Player *Ind[] , int ind , Player *Aus[] , int aus , int key) // player comparison
        {
            int p1 , p2 ; // index variables
            if(key == 1)
            {
                cout << "Choose [Player 1] : " ;
                cin >> p1 ;
                cout << "Choose [Player 2] : " ; 
                cin >> p2 ;
                cout << "CompareGuru says...\n" ;
                if(Ind[p1 - 1] > Ind[p2 - 1]) // use of operator ovl
                    cout << Ind[p1 - 1] -> sName << " is the better player head-to-head.\n" ; 
                else if(Ind[p1 - 1] == Ind[p2 - 1])
                    cout << Ind[p1 - 1] -> sName << " & " << Ind[p2 -1] -> sName << " are equally good head-to-head.\n" ; 
                else
                    cout << Ind[p2 - 1] -> sName << " is the better player head-to-head.\n" ;
            }
            if(key == 2)
            {
                cout << "Choose [Player 1] : " ;
                cin >> p1 ;
                cout << "Choose [Player 2] : " ; 
                cin >> p2 ;
                if(Aus[p1 - 1] > Aus[p2 - 1])
                    cout << Aus[p1 - 1] -> sName << " is the better player head-to-head.\n" ; 
                else if(Aus[p1 - 1] == Aus[p2 - 1])
                    cout << Aus[p1 - 1] -> sName << " & " << Aus[p2 -1] -> sName << " are equally good head-to-head.\n" ; 
                else
                    cout << Aus[p2 - 1] -> sName << " is the better player head-to-head.\n" ; 
            }
            if(key == 3)
            {
                cout << "Choose IND [Player] : " ;
                cin >> p1 ;
                cout << "Choose AUS [Player] : " ; 
                cin >> p2 ;
                if(Ind[p1 - 1] > Aus[p2 - 1])
                    cout << Ind[p1 - 1] -> sName << " is the better player head-to-head.\n" ;
                else if(Ind[p1 - 1] == Aus[p2 - 1]) 
                    cout << Ind[p1 - 1] -> sName << " & " << Aus[p2 -1] -> sName << " are equally good head-to-head.\n" ; 
                else
                    cout << Aus[p2 - 1] -> sName << " is the better player head-to-head.\n" ;
            }
}

} ; 

inline void Player :: read(char key = 'A')
{
    int key1 ;
    if(key == 'A')
    {
        fstream fc ;
        fc.open("players_book.txt" , ios::app) ;                // use of file operations
        cout << "First Name : " ;
        cin >> fName ;
        cout << "Surname : " ;
        cin >> sName ;
        name = strcat(strcat(fName , " ") , sName) ;            // using in-built strcat function
        try                                                     // use of exception handling                        
        {
            cout << "Country ([I]ND or [A]US) : " ;             // try-catch blocks have been used for 
            cin >> country ;                                    // parts of code with if/else if/else 
            if(country == "i" || country == "I")                // blocks throughout the code
                country = "IND" ;
            else if(country == "a" || country == "A")
                country = "AUS" ;
            else
                throw 0 ;
        }
        catch(...) // demonstrating catch all                       
        {                                                           // in case an entry is invalid or
            cout << "ERR : Wrong entry, try again." << endl ;       // there is a lack of info (eg - no stats entered)
            fc.close() ;                                            // the file will be closed without any data written
            read() ;                                                // to it & exception handling has been used for this 
        }                                                   // user will be asked to re-enter in case of invalid entry and
        cout << "Enter Stats? [1]Yes [2]No : " ;            // read() will be called recursively
        cin >> stat ;
        if(stat != 1)
        {
            cout << "WARNING : You have opted not to enter player stats." << endl ;
            cout << "Player data will not be saved to book and all stats will be stored as 0/NULL." << endl ;
            cout << "Stats can be entered later using Statistics & Sort Menu [7]." << endl ;
            fc.close() ; // only players with available statistics will be stored in players_book , ind_players and aus_players
            return ; 
        }
        fc << name << "[" << country << "]" << endl ;
        fc.close() ;
    }
    
    if(key == 'B' || stat == 1)
    {
        if(key == 'B') // when key is B it indicates player stats was not entered previously and is now being entered
        {
            fstream fc ;
            fc.open("players_book.txt" , ios::app) ; // so now that the user has opted to enter player stats
            fc << name << "[" << country << "]" << endl ;  // we will write the player data to players_book
            fc.close() ; 
        }
        fstream fc ;
        fc.open("players_book.txt" , ios::app) ;
        cout << "-> CAREER INFO <-" << endl ;
        cout << "Role ([1]BAT  [2]BWL) : " ;
        cin >> key1 ;
        if(key1 == 1)
            role = "BAT" ;
        if(key1 == 2)
            role = "BWL" ;
        try
        {
            cout << "Matches : " ;
            cin >> mats ;
            if(mats == 0)
                throw 0 ;
            try
            {
                if(mats < 0)
                    throw -1 ;
            }
            catch(int j)
            {
                cout << "ERR : Invalid entry." << endl ;
                fc.close() ;
            }
        }
        catch(int i)
        {
            cout << "WARNING : Can't calculate statistics for player with 0 match experience." << endl ;
        }
        fc << "Matches : " << mats << "   < >   " << "Role : " << role << endl ;
        fc.close() ;
        if(mats > 0)
            read(key1) ;
    }
}

inline void Player :: read(int key) 
{
    fstream fc ;
    fc.open("players_book.txt" , ios::app) ;                // As and when a user enters information about a player
    if(key == 1)                                            // it is simultaneously written into a file called 
    {                                                       // players_book.txt 
        cout << "-> BATTING STATS <-" << endl ;             // depending on whether a player is bat/bwl
        cout << "Bat. Style ([R]HB or [L]HB) : " ;          // bat/bwl stats are asked to be input
        cin >> style ;                                      // and relevant stats are calculated & written to
        try                                                 
        {
            if(style == "r" || style == "R")
                style = "RHB" ;
            else if(style == "l" || style == "L")
                style = "LHB" ;
            else
                throw 1 ;
        }
        catch(...)
        {
            cout << "ERR : Invalid entry. Re-enter please." << endl ;
            fc.close() ;
            read(1) ;
        }
        cout << "Innings : " ;                              // players_book.txt 
        cin >> inns ;
        cout << "Runs Scored : " ;
        cin >> runs ;
        cout << "Not Outs : " ;
        cin >> notOut ;
        try
        {
            if(notOut > inns)
                throw 1 ;
        }   
        catch(int i)
        {
            cout << "ERR : Innings > Not Outs. Re-enter please." << endl ;
            fc.close() ;
            read(1) ;
        }
        cout << "Best Score : " ;
        cin >> best ;
        avg = calcAvg(1) ;
        quo = calcQuo(1) ;
        fc << "Innings : " << inns << "   < >   " << "Style : " << style << endl << "Runs Scored : " << runs << "   < >   " << "Not Outs : " << notOut << "   < >   " << "Bat Avg : "<< avg << endl << "Best Score : " << best << "   < >   " << "Player Quotient : " << quo << endl << endl << endl ;
    }
    if(key == 2)
    {
        cout << "-> BOWLING STATS <-" << endl ;
        try
        {
            cout << "Bwl Arm ([R]ight or [L]eft): " ;
            cin >> arm ;
            if(arm == "r" || arm == "R")
                arm = "Right Arm" ;
            else if(arm == "l" || arm == "L")
                arm = "Left Arm" ;
            else
                throw 0 ;
        }
        catch(int i)
        {
            cout << "ERR : Wrong entry, try again." << endl ;
            fc.close() ;
            read(2) ;
        }
        try
        {
            cout << "Bwl Style ([F]ast / [O]ff-Spin / [L]eg-Spin) : " ;
            cin >> style ;
            if(style == "f" || style == "F")
                style = "Fast" ;
            else if(style == "o" || style == "O")
                style = "Off-Spin" ;
            else if(style == "l" || style == "L")
                style = "Leg-Spin" ;
            else
                throw 'k' ; // throwing char 
        }
        catch(...) // demonstrating catch all
        {
            cout << "ERR : Wrong entry, try again." << endl ;
            fc.close() ;
            read(2) ;
        }
        cout << "Wickets : " ;
        cin >> wkts ;
        cout << "Runs Conceded : " ;
        cin >> runs ;
        cout << "Best Figures: " ;
        cin >> best ;
        avg = calcAvg(2) ;
        quo = calcQuo(2) ;
        fc << "Bwl Arm/Style : " << arm << "/" << style << endl << "Wickets : " << wkts << "   < >   " << "Runs Conceded : " << runs << endl << "Best Match Figures : " << best << "   < >   " << "Bowl Avg : " << avg << endl << "Player Quotient : " << quo << endl << endl << endl ;
    }
    fc.close() ;
}



class Files : public Player // class with member functions that perform file operations
{
    public :
        void teamsort(Player p) // function to write Ind and Aus player profiles to separate files
        {
            if(p.country == "IND") 
            {
                fstream fi ;
                fi.open("ind_players.txt" , ios::app) ;
                fi << p.name << " (" << p.role << ")" << endl ; // write to file
                fi << "Matches : " << mats << "   < >   " << "Role : " << role << endl ;
                if(p.role == "BAT")
                    fi << "Innings : " << inns << "   < >   " << "Style : " << style << endl << "Runs Scored : " << runs << "   < >   " << "Not Outs : " << notOut << "   < >   " << "Bat Avg : "<< avg << endl << "Best Score : " << best << "   < >   " << "Player Quotient : " << quo << endl << endl << endl ;
                else
                    fi << "Bwl Arm/Style : " << arm << "/" << style << endl << "Wickets : " << wkts << "   < >   " << "Runs Conceded : " << runs << endl << "Best Match Figures : " << best << "   < >   " << "Bowl Avg : " << avg << endl << "Player Quotient : " << quo << endl << endl << endl ;
                fi.close() ;
            }
            if(p.country == "AUS")
            {
                fstream fa ;
                fa.open("aus_players.txt" , ios::app) ;
                fa << p.name << " (" << p.role << ")" << endl ;
                fa << "Matches : " << mats << "   < >   " << "Role : " << role << endl ;
                if(p.role == "BAT")
                    fa << "Innings : " << inns << "   < >   " << "Style : " << style << endl << "Runs Scored : " << runs << "   < >   " << "Not Outs : " << notOut << "   < >   " << "Bat Avg : "<< avg << endl << "Best Score : " << best << "   < >   " << "Player Quotient : " << quo << endl << endl << endl ;
                else
                    fa << "Bwl Arm/Style : " << arm << "/" << style << endl << "Wickets : " << wkts << "   < >   " << "Runs Conceded : " << runs << endl << "Best Match Figures : " << best << "   < >   " << "Bowl Avg : " << avg << endl << "Player Quotient : " << quo << endl << endl << endl ;
                fa.close() ;
            }
        }

        void guide() // function to read from pre existing text file GUIDE containing information about the program
        {
            string read ;
            ifstream fc("GUIDE.txt") ; // reading from file
            while(getline(fc , read))
            {
                cout << read ;
                cout << "\n" ;
            }
            fc.close() ;
        }

        void readpb(int opt) // reading files players_book , ind_players and aus_players
        {
            string read ;
            ifstream fc ;
            if(opt == 1) // read from players_book
            {
                fc.open("players_book.txt") ;
                while(getline(fc , read))
                {
                    cout << endl ;
                    cout << read ;
                    cout << endl ;
                }
            }
            if(opt == 2) // read from ind_players
            {
                fc.open("ind_players.txt") ;
                while(getline(fc , read))
                {
                    cout << endl ;
                    cout << read ;
                    cout << endl ;
                }
            }
            if(opt == 3) // read from aus_players
            {
                fc.open("aus_players.txt") ;
                while(getline(fc , read))
                {
                    cout << endl ;
                    cout << read ;
                    cout << endl ;
                }
            }
            fc.close() ;
        }
} ;

                    // MAIN 



int main()
{
    Player *Ind[100] , *Aus[100] , *Tot[200] ; // array of pointers to objects of class Player
    Files* fptr = new Files() ; // will be used to access member functions of class Player (base) and class Files (derived)
    int key , opt , opt1 , opt2 ; 
    int ind = 0 , aus = 0 , tot = 0 ; // index variables 
    int totMat[200] ; 
    float totQuo[200] ;
    cout << endl << "_____________________________________________________________________________________" << endl << endl ;
    cout << "                               ** CricGuru ** " << endl << endl ;
    cout << "\t\t\t    INDIA vs AUSTRALIA   " << endl << "\t\t TEST MATCH PLAYERS BOOK & MATCH PREDICTOR   " << endl ;
    cout << "_____________________________________________________________________________________" << endl << endl ;
    cout << "                                                developed by Aryan Goel & Ayush Malik" << endl ;
    cout << "_____________________________________________________________________________________" << endl << endl ;
    cout << "Read program guide ( Main Menu -> [4] ) for info about the program." << endl ; 
    cout << "_____________________________________________________________________________________" << endl << endl ;
    do
    {
        cout << "_____________________________________________________________________________________" << endl << endl ;
        cout << "                              MAIN MENU     " << endl ;                 // SWITCH CASE MENU
        cout << "_____________________________________________________________________________________" << endl << endl ;
        cout << "[1] Create Player Profile  [2] View Current Players [3] Team Sheets [4] View Program Guide" << endl ; 
        cout << "[5] CompareGuru  [6] PredictGuru  [7] Stats & Sort [8] Player book [9] Exit" << endl ;       
        cout << "Choose [Option] : " ;                                           
        cin >> key ;
        switch(key)
        {
        case 1 :                                        // CREATE PLAYER
                Tot[tot] = new Player() ;               // create new Player object using pointer to object
                    	                                // Player is created and stored in ptr array Tot (Total Players)
                Tot[tot] -> read() ;                    // reads player info
                totMat[tot] = Tot[tot] -> mats ;        // int array that stores no. of matches
                totQuo[tot] = Tot[tot] -> quo ;           // float array that stores PQ of player
                fptr -> teamsort(*Tot[tot]) ;
                if (Tot[tot] -> country == "IND")       // assigned to ptr array Ind or Aus depending on nationality
                {
                    Ind[ind] = Tot[tot] ;
                    ind ++ ;
                    
                }
                else
                {
                    Aus[aus] = Tot[tot] ;
                    aus ++ ;
                }
                tot ++ ;
                break ;
            case 2 :                                                            // VIEW CURRENT PLAYERS 
                cout << "  => ALL PLAYERS AVAILABLE <=  " << endl ;             // displays all players data that has been entered at run time
                for(int i = 0 ; i < tot ; i ++)                                 // (not those in any of the files)
                    cout << "[" << i + 1 << "] " << Tot[i] -> name << " (" << Tot[i] -> country << ")" << endl ;
                cout << "Choose [Player] : " ;                                  
                cin >> opt ;
                cout << "     ** PLAYER PROFILE **     " << endl ;
                Tot[opt - 1] -> disp() ;
                break ;                                        
            case 3 :                   // TEAM SHEETS                            // displays the list of players entered at run time
                do                                                              // sorted in their teams 
                {                                                               
                    cout << "  ** TEAM SHEETS **" << endl ;
                    cout << "View : [1] Team Ind  [2] Team Aus  [3] return to Main Menu" << endl ;
                    cout << "Choose [Option] : " ;
                    cin >> opt ;
                    if(opt == 1)
                    {
                        cout << "->TEAM INDIA<-" << endl ;
                        for(int i = 0 ; i < ind ; i ++)
                            cout << "[" << i + 1 << "]  " << Ind[i] -> name << endl ;
                    }
                    if(opt == 2)
                    {
                        cout << "->TEAM AUSTRALIA<-" << endl ;
                        for(int j = 0 ; j < aus ; j ++)
                            cout << "[" << j + 1 << "]  " << Aus[j] -> name << endl ;
                    }
                } while (opt != 3);
                break ;
            case 4 :                // GUIDE
                fptr -> guide() ;   // reads GUIDE.txt and displays on terminal
                break ;
            case 5 :                // CompareGuru -PLAYER COMPARISON
                cout << "  ** CompareGuru ** " << endl ;        // displays surnames of players of both teams
                cout << "-> IND PLAYERS <-" << endl ;                       // and their roles
                for(int i = 0 ; i < ind ; i ++)                             
                    cout << "[" << i + 1 << "] " << Ind[i] -> sName << "  " << "(" << Ind[i] -> role << ")  " ;   
                cout << endl ;                                              
                cout << "-> AUS PLAYERS <-" << endl ;
                for(int i = 0 ; i < aus ; i ++)
                    cout << "[" << i + 1 << "] " << Aus[i] -> sName << "  " << "(" << Aus[i] -> role << ")"  ;
                cout << endl ;
                do                          // to choose which players to compare
                {                           // within or across teams
                    cout << "Compare players of [1] Ind [2] Aus [3] Ind vs Aus or [4] return to return to Main Menu" << endl ;
                    cout << "Choose [Option] : " ;
                    cin >> opt1 ;
                    if(opt1 > 0 && opt1 < 4)
                        Compare(Ind , ind , Aus , aus , opt1) ;
                } while(opt1 != 4) ;
                break ;
            case 6 :                // PredictGuru - PREDICT MATCH RESULT OF INDIA v AUSTRALIA
                cout << "  ** PredictGuru ** " << endl ;
                Predict(Ind , ind , Aus , aus) ;
                break ;
            case 7 :
                int p ;
                do
                {
                    cout << "  ** STATISTICS & SORT MENU **  " << endl ;        // STATS & SORT MENU 
                    cout << "[1] Enter data of a player [2] Re-enter data of a player [3] View data & stats of a player [4] Sort menu [5] return to Main Menu" << endl ;
                    cout << "Choose [Option] : " ;                  // using this menu user can -
                    cin >> opt ;                                    // 1) enter stats of a player whose stats were not entered initially
                    switch(opt)                                     // 2) re-enter and change info and data of a player of choice
                    {                                                   // 3) view data and stats of players available at run time
                        case 1 :                                    // 4) call function to sort array of matches or PQ's 
                            cout << "  => PLAYERS WITH NO AVAILABLE DATA <= " << endl ;
                            for(int i = 0 ; i < tot ; i ++)
                            {
                                if(Tot[i] -> stat == 2)
                                    cout << "[" << i + 1 << "] " << Tot[i] -> name << " (" << Tot[i] -> country << ")" << endl ;
                            }
                            cout << "Choose [Player] : " ;
                            cin >> p ;
                            Tot[p - 1] -> stat = 1 ;
                            Tot[p - 1] -> read('B') ;
                            totMat[p - 1] = Tot[p - 1] -> mats ;
                            totQuo[p - 1] = Tot[p - 1] -> quo ;
                            if(Tot[p - 1] -> country == "IND")
                            {
                                Ind[ind] = Tot[p - 1] ;
                                fptr -> teamsort(*Ind[ind]) ;
                                ind += 1 ;
                            }
                            if(Tot[p - 1] -> country == "AUS")
                            {
                                Aus[aus] = Tot[p - 1] ;
                                fptr -> teamsort(*Aus[aus]) ;
                                aus += 1 ;
                            }
                            break ;
                        case 2 :
                            cout << "  => ALL PLAYERS AVAILABLE <=  " << endl ;
                            for(int i = 0 ; i < tot ; i ++)
                                cout << "[" << i + 1 << "] " << Tot[i] -> name << " (" << Tot[i] -> country << ")" << endl ;
                            cout << "Choose [Player] : " ;
                            cin >> opt1 ;
                            Tot[opt1 - 1] -> read() ;
                            break ;
                        case 3 :
                            cout << "  => ALL PLAYERS AVAILABLE <=  " << endl ;
                            for(int i = 0 ; i < tot ; i ++)
                                cout << "[" << i + 1 << "] " << Tot[i] -> name << " (" << Tot[i] -> country << ")" << endl ;
                            cout << "Choose [Player] : " ;
                            cin >> opt1 ;
                            Tot[opt1 - 1] -> disp() ;
                            break ;
                        case 4 :
                            cout << " => SORT MENU <= " << endl ;
                            cout << "   ALL PLAYERS AVAILABLE   " << endl ;
                            for(int i = 0 ; i < tot ; i ++)
                                cout << "[" << i + 1 << "] " << Tot[i] -> name << " (" << Tot[i] -> country << ")" << endl ;
                            
                            cout << "View sorted - [1] Matches [2] Player Quotients\n[Select] : " ;
                            cin >> opt1 ;
                            if(opt1 == 1)
                            {
                                fptr -> sort<int>(totMat , tot) ;
                        	    cout << "Sorted matches : [ " ;
                                for(int i = 0 ; i < tot ; i ++)
                                    cout << totMat[i] << " " ;
                                cout << "]" << endl ; 
                            }
                            if(opt1 == 2)
                            {
                                fptr -> sort<float>(totQuo , tot) ;
                        	    cout << "Sorted player Quotients : [ " ;
                                for(int i = 0 ; i < tot ; i ++)
                                    cout << totQuo[i] << " " ;
                                cout << "]" << endl ;
                            }
                    } 
                } while (opt != 5) ;
                break ;

            case 8 :                                                // using this menu user can read player books
                cout << "  ** PLAYER BOOK ** " << endl ;        // ie the txt files players_book , ind_players , aus_players
                cout << "[1] All players [2] India players [3] Australia players \n[Select] : " ;
                cin >> opt ;                                        // that are acting like dummy read only books
                fptr -> readpb(opt) ;
                break ;   
        }
    } while (key != 9) ;
    cout << endl << "_____________________________________________________________________________________" << endl << endl ;
    cout << "Thank you for using CricGuru." << endl ;
    cout << "_____________________________________________________________________________________" << endl << endl ;
    delete fptr ;
    for(int i = 0 ; i < tot ; i ++)
        delete Tot[i] ;
    for(int i = 0 ; i < ind ; i ++)
        delete Ind[i] ;
    for(int i = 0 ; i < aus ; i ++)
        delete Aus[i] ;    
    return 0 ;
}
