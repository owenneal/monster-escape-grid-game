#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

/// @file "gameboard.h"
///
/// Program 7: Outlast the Baddies & Avoid the Abyss
/// Course: CS 211, Fall 2023, UIC
/// System: Advanced zyLab
/// Author: Owen Neal
///

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

#include "boardcell.h"
#include "grid.h"

using namespace std;

class GameBoard {
	private: 
	    Grid<BoardCell*> board;
        size_t numRows;
        size_t numCols;
        int HeroRow; // Hero's position row
	    int HeroCol; // Hero's position column
        int numMonsters;
        int numSuperMonsters;
        int numAbysses;
        int numBats;
        bool wonGame; // false, unless the Hero reached the exit successfully

		
	public: 
		/* default constructor */
        GameBoard() {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 50;
            numBats = 2;
            wonGame = false;
            
            this -> numRows = 15;
            this -> numCols = 40;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* param constructor */
        GameBoard(size_t numRows, size_t numCols) {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 20;
            numBats = 3;
            wonGame = false;
            
            this -> numRows = numRows;
            this -> numCols = numCols;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* destructor */
        virtual ~GameBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    delete board(row, col);
                }
            }
        }

        void blankBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    board(row, col) = new Nothing(row,col);
                }
            }
        }

        char getCellDisplay(size_t r, size_t c) {
            return board(r,c)->display();
        }

        void setCell(BoardCell* myCell, size_t r, size_t c) {
            board(r,c) = myCell;
        }
    
        void freeCell(size_t r, size_t c) {
            delete board(r,c);
        }

        // fills board with by randomly placing...
        //  - Hero (H) in the first three columns
        //  - EscapeLadder (*) in last three columns
        //  - 3 vertical Walls (+), each 1/2 of board height, in middle segment
        //  - Abyss cells (#), quantity set by numAbysses, in middle segment
        //  - Baddies [Monsters (m), Super Monsters (M), & Bats (~)] in middle segment;
        //    number of Baddies set by numMonsters, numSuperMonsters, & numBats
        void setupBoard(int seed) {
            srand(seed);
            size_t r,c;

            r = rand() % numRows;
            c = rand() % 3;
            delete board(r,c);
            board(r,c) = new Hero(r,c);
            HeroRow = r;
            HeroCol = c;

            r = rand() % numRows;
            c = numCols - 1 - (rand() % 3);
            delete board(r,c);
            board(r,c) = new EscapeLadder(r,c);
            
            int sizeMid = numCols - 6;

            c = 3 + (rand() % sizeMid);
            for (r = 0; r < numRows/2; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }
            size_t topc = c;

            while (c == topc || c == topc-1 || c == topc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows-1; r > numRows/2; --r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);           
            }
            size_t botc = c;

            while (c == topc || c == topc-1 || c == topc+1 || c == botc || c == botc-1 || c == botc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows/4; r < 3*numRows/4; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }

            for (int i = 0; i < numMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c);  
                board(r,c)->setPower(1);        
            }

            for (int i = 0; i < numSuperMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c); 
                board(r,c)->setPower(2);               
            }

            for (int i = 0; i < numBats; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Bat(r,c); 
            }

            for (int i = 0; i < numAbysses; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Abyss(r,c);              
            }
        }

        // neatly displaying the game board 
		void display( ) {
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            for (size_t row = 0; row < board.numrows(); row++) {
                cout << '|';
                for (size_t col = 0; col < board.numcols(row); col++) {
                    cout << board(row,col)->display();
                }
                cout << '|';
                cout << endl;
            }
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            
        }
		
        bool getWonGame() {
            return wonGame;
        }
        
        // distributing total number of monsters so that 
        //  ~1/3 of num are Super Monsters (M), and
        //  ~2/3 of num are Regular Monsters (m)
        void setNumMonsters(int num) {
            numSuperMonsters = num/3;
            numMonsters = num - numSuperMonsters;
        }

        void setNumAbysses(int num) {
            numAbysses = num;
        }

        void setNumBats(int num) {
            numBats = num;
        }

        size_t getNumRows() {
            return numRows;
        }

        size_t getNumCols() {
            return numCols;
        }


        // when moving a monster need to make sure the correct monster is being placed in the new cell
        void setCorrectMonster(size_t& row, size_t& col, char& sym) {
            if (sym == 'm') {
                board(row,col) = new Monster(row,col);
            } else if (sym == '~') {
                board(row, col) = new Bat(row, col);
            } else {
                board(row, col) = new Monster(row, col);
                board(row, col)->setPower(2);
            }
            board(row,col)->setMoved(true);
        }
        
        //---------------------------------------------------------------------------------
        // void getHeroPosition(size_t& row, size_t& col)
        //
        // getter for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        // note: row and col are passed-by-reference
        //---------------------------------------------------------------------------------
        void getHeroPosition(size_t& row, size_t& col) {
            row = HeroRow;
            col = HeroCol;
        }

        
        //---------------------------------------------------------------------------------
        // void setHeroPosition(size_t row, size_t col)
        //
        // setter for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        //---------------------------------------------------------------------------------
        void setHeroPosition(size_t row, size_t col) {
            HeroRow = row;
            HeroCol = col;
        }

        
        //---------------------------------------------------------------------------------
        // findHero()
        //
        // updater for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        // this function should find Hero in board and update
        //      HeroRow and HeroCol with the Hero's updated position;
        // if Hero cannot be found in board, then set Hero's position to (-1,-1)
        //---------------------------------------------------------------------------------
        void findHero() {
            for (size_t row = 0; row < board.numrows(); ++row) {
                for (size_t col = 0; col < board.numcols(row); ++col) {
                    if (board(row, col)->isHero()) {
                        // found the Hero on the board, update its position
                        setHeroPosition(row, col);
                        return; // no need to continue searching
                    }
                }
            }

            // hero not found on the board, set position to (-1, -1) as a sentinel value
            setHeroPosition(-1, -1);
        }

        //---------------------------------------------------------------------------------
        // bool makeMoves(char HeroNextMove)
        // 
        // This is the primary gameplay operation for a single round of the game. 
        // A LOT happens in this function... 
        // General steps:
        //  - Allow user to input their next move 
        //  - Get the attempted move position for the Hero
        //  - Move the hero, catching/resolving any potential collision exceptions...
        //      - attempted move out-of-bounds: change row &/or col to stay on board
        //      - attempted move into a barrier: change row &/or col to stay off barrier
        //      - attempted move to the exit: remove hero from board, hero escaped!
        //      - attempted move into a hole: remove hero from board, hero did not escape
        //      - attempted move to a baddie: remove hero from board, hero did not escape
        //      - attempted move to an empty space: actual move is the attempted move
        //  - For each baddie (regular Monster, super Monster, or Bat) on the board...
        //      - check that this baddies hasn't already moved this round
        //      - get its attempted move position
        //      - move the baddie, catching/resolving any potential collision exceptions...
        //          - attempted move out-of-bounds: change row &/or col to stay on board
        //          - attempted move into a barrier: change row &/or col to stay off barrier
        //          - attempted move to the exit: change row &/or col to stay off exit
        //          - attempted move into a hole: remove baddie from board
        //          - attempted move to hero: remove hero from board, hero did not escape
        //          - attempted move to a baddie: ignore attempted move, no position change
        //          - attempted move to an empty space: actual move is the attempted move 
        // 
        // Note: all baddies (and the hero) fall into holes if their attempted 
        //       move ENDs on a hole (i.e. even Bats are drawn into the 
        //       Abyss if their attempted move takes them to an Abyss cell); 
        //       BUT, baddies can travel over holes, as long as their attempted 
        //       move does NOT END on a hole; this only applies, in practice, 
        //       to super monsters and bats, since their step sizes can be more 
        //       than 1 (monsters and the hero are limited to steps of size 1)
        //
        // Note: also, whereas baddies (and the hero) can never move onto a 
        //       barrier (i.e. a wall), they can step over barriers as long
        //       as the attempted move does NOT END on a barrier; this only 
        //       applies, in practice, to super monsters and bats, since their 
        //       step sizes can be more than 1 (monsters and the hero are limited 
        //       to steps of size 1)
        //
        // Note: to prevent a single baddie from making multiple moves
        //       during a single round of the game, whenever a baddie 
        //       has moved, it should be marked as "already moved" in 
        //       some way; this can be done using the [moved] data member
        //       of the BoardCell base class, which has setter/getter 
        //       functions provided. The [moved] data members must be 
        //       reset for all BoardCells at the beginning of each round.
        //
        // Note: the [myRow] and [myCol] data members for BoardCell derived
        //       class objects must be updated whenever a move is made; 
        //       additionally, [HeroRow] and [HeroCol] data members for the 
        //       GameBoard must be updated whenever the Hero has moved, 
        //       which can be done easily with a call to findHero()
        //
        // Note: many actual moves made by non-static board cell objects 
        //       (i.e. Heros, Monsters, Bats) involve constructing and/or 
        //       destructing objects; be careful with memory management; 
        //       specifically, make sure to free (delete) the memory for 
        //       BoardCell derived class objects when you are done with it
        //
        // return true if Hero is still on board at the end of the round
        // return false if Hero is NOT on board at the end of the round
        //---------------------------------------------------------------------------------
        bool makeMoves(char HeroNextMove) {
            // reset the has moved for each cell, used to make sure the monsters do not move more than once
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    board(row, col)->setMoved(false);
                }
            }
            // determine where hero proposes to move to
            size_t newR, newC;
            size_t oldR, oldC; // to check if the hero changed positon
            oldR = HeroRow;
            oldC = HeroCol;
            board(HeroRow,HeroCol)->setNextMove(HeroNextMove);
            board(HeroRow,HeroCol)->attemptMoveTo(newR,newC,HeroRow,HeroCol);
       
            try {
                // hero attempts to move out-of-bounds in rows
                if (newR < 0 || newR >= numRows) { 
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid row");
                } 
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                newR = HeroRow; // stay still for this round
                cout << "Changing row for Hero position to stay in-bounds" << endl;
            }

            try {
                // hero attempts to move out-of-bounds in cols
                if (newC < 0 || newC >= numCols) {
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid column");
                }
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                newC = HeroCol;
                cout << "Changing column for Hero position to stay in-bounds" << endl;
            }

            // handle getting to wall
            // check if the new position is a wall
            if (board(newR, newC)->display() == '+') {
                newC = HeroCol;
                if (board(newR, HeroCol)->display() == '+') {
                    newR = HeroRow;
                }
                //setHeroPosition(newR, newC);
                findHero();
            }
            // check if the position has a monster/abyss
            // results in a loss - hero is removed
            if (board(newR, newC)->display() == 'M' || board(newR, newC)->display() == 'm' || board(newR, newC)->display() == '~' || board(newR, newC)->display() == '#')  {
                HeroRow = -1;
                HeroCol = -1;
                delete board(oldR, oldC); // remove hero
                board(oldR, oldC) = new Nothing(oldR, oldC); // make the spot where the hero was a nothing space
                wonGame = false;
                return false; // return false as hero is no longer on the board, game ends instantly
            }

            // check if the position has nothing in it
            // just do the move
            if (board(newR, newC)->display() == ' ') {
                HeroRow = newR;
                HeroCol = newC;
                delete board(newR, newC);
                delete board(oldR, oldC);
                board(newR, newC) = new Hero(newR, newC);
                board(oldR,oldC) = new Nothing(oldR,oldC);
                setHeroPosition(newR, newC);
                findHero();
            }

            // check if the position has the escape in it
            // results in a win - hero is removed
            try {
                if (board(newR, newC)->display() == '*') {
                    throw runtime_error("Found the exit");
                }
            }
            catch (runtime_error& excpt) {
                HeroRow = -1;
                HeroCol = -1;
                // delete hero from board, make it a nothing object
                delete board(oldR, oldC);
                board(oldR,oldC) = new Nothing(oldR,oldC);
                setHeroPosition(-1,-1); // remove hero from board
                findHero();
                wonGame = true;
                return false; // game ends instantly upon hero escaping, monsters do not move
            }
            // end of hero movement

            // baddie movement
            // all monsters go to the last known position of the hero if the hero is removed from the board
            // baddie symbols: m M ~
            int lastHeroR = HeroRow;
            int lastHeroC = HeroCol;
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    BoardCell* cell = board(row, col);
                    char baddieSymbol = board(row, col)->display();
                    if (cell->isBaddie() && !cell->getMoved()) {
                        size_t bnewR, bnewC;
                        cell->attemptMoveTo(bnewR,bnewC,lastHeroR,lastHeroC); // should go to the heros last position, so doesnt try to go to -1,-1 and monsters can still take their turn after the hero dies
                        // handle wall/escape collison
                        try {
                        // monster attempts to move out-of-bounds in rows
                            if (bnewR < 0 || bnewR >= numRows) { 
                                throw runtime_error("Monster trying to move out-of-bounds with an invalid row");
                            } 
                        }
                        catch (runtime_error& excpt) {
                            cout << excpt.what() << endl;
                            bnewR = row; // stay still for this round
                            cout << "Changing row for Monster position to stay in-bounds" << endl;
                        }

                        try {
                            // monster attempts to move out-of-bounds in cols
                            if (bnewC < 0 || bnewC >= numCols) {
                                throw runtime_error("Monster trying to move out-of-bounds with an invalid column");
                            }
                        }
                        catch (runtime_error& excpt) {
                            cout << excpt.what() << endl;
                            bnewC = col; // stay still for this round
                            cout << "Changing column for Monster position to stay in-bounds" << endl;
                        }

                        // handle getting to wall
                        // check if the new position is a wall
                        if (board(bnewR, bnewC)->display() == '+' || board(bnewR, bnewC)->display() == '*') {
                            bnewC = col; // ignore column movement
                            if (board(bnewR, bnewC)->display() == '+' || board(bnewR, bnewC)->display() == '*') {
                                bnewR = row; // ignore row movement
                            }
                        }

                        // handle baddie collison
                        // ignore proposed move 
                        // do not make new monster in proposed cell, do not make nothing object in old cell
                        if (board(bnewR, bnewC)->display() == 'M' || board(bnewR, bnewC)->display() == 'm' || board(bnewR, bnewC)->display() == '~') {
                            cell->setMoved(true);
                        }
                        // handle abyss collison
                        // do not add have moved, monster is gone
                        if (board(bnewR, bnewC)->display() == '#') {
                            delete board(row, col);
                            board(row, col) = new Nothing(row, col);
                        }

                        // handle hero collison
                        // monster replaces hero, hero is off board and loses
                        if (board(bnewR, bnewC)->display() == 'H') {
                            delete board(bnewR, bnewC);
                            delete board(row, col);
                            board(row, col) = new Nothing(row, col);
                            setCorrectMonster(bnewR, bnewC, baddieSymbol);
                            setHeroPosition(-1,-1);
                            findHero();
                        }
                        // handle nothing collison
                        // do actual move
                        try {
                            if (board(bnewR, bnewC)->display() == ' ') {
                                throw runtime_error("Hit nothing");
                            }
                        }
                        catch (runtime_error& excpt) {
                            delete board(bnewR, bnewC);
                            delete board(row, col);
                            board(row, col) = new Nothing(row, col);
                            setCorrectMonster(bnewR, bnewC, baddieSymbol);
                        }
                    }
                }
            }
            // end of baddie movement
            if (HeroCol != -1 && HeroRow != -1) {
                return true;
            } 
            return false;
        }

};

#endif //_GAMEBOARD_H