#ifndef _BOARDCELL_H
#define _BOARDCELL_H

using namespace std;

/// @file "boardcell.h"
///
/// Program 7: Outlast the Baddies & Avoid the Abyss
/// Course: CS 211, Fall 2023, UIC
/// System: Advanced zyLab
/// Author: Owen Neal
///

// First, the BoardCell abstract base class 

class BoardCell {
	
    public:  
		BoardCell() {} // default contstructor (do nothing)
        virtual ~BoardCell() {} // destructor (do nothing)
        
        virtual char display( ) = 0; // pure virtual function; this is an abstract base class

    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            newR = myRow;
            newC = myCol; 
            
        }
        
        virtual bool isHero( ) {return false;}
    	virtual bool isBaddie( ) {return false;}
    	virtual bool isSpace( ) {return false;}
        virtual bool isBarrier( ) {return false;}
        virtual bool isHole( ) {return false;}
    	virtual bool isExit( ) {return false;}
    	virtual bool isStatic( ) {return true;}

        virtual void setPower(int num) {}
        virtual int getPower() {return 1;}
        virtual void setNextMove(char inChar) {}
        
        void setMoved(bool m) {moved = m;}
        bool getMoved() {return moved;}
        void setRow(size_t r) {myRow = r;}
        size_t getRow() {return myRow;}
        void setCol(size_t c) {myCol = c;}
        size_t getCol() {return myCol;}
        void setPos(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

    private:
        size_t myRow; // current row for this board cell in a 2D grid
        size_t myCol; // current column for this board cell in a 2D grid
        bool moved;   // true = this board cell already moved in the current round

}; // BoardCell (abstract base class)


// Then, all the derived classes

class Hero: public BoardCell {
	
    public:
    	Hero(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        
        virtual bool isHero( ) {return true;}
        virtual bool isStatic( ) {return false;}
        virtual char display( ) {return 'H';}
        
        virtual void setNextMove(char inChar ) {
            nextMove = inChar;
        }
    	
        virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            switch (nextMove) {
                case 'q': // up and left
                    newR = hRow - 1;
                    newC = hCol - 1;
                    break;
                case 'w': // up
                    newR = hRow - 1;
                    newC = hCol;
                    break;
                case 'e': // up and right
                    newR = hRow - 1;
                    newC = hCol + 1;
                    break;
                case 'a': // left
                    newR = hRow;
                    newC = hCol - 1;
                    break;
                case 's': // stay
                    newR = hRow;
                    newC = hCol;
                    break;
                case 'd': // right
                    newR = hRow;
                    newC = hCol + 1;
                    break;
                case 'z': // down and left
                    newR = hRow + 1;
                    newC = hCol - 1;
                    break;
                case 'x': // down
                    newR = hRow + 1;
                    newC = hCol;
                    break;
                case 'c': // down and right
                    newR = hRow + 1;
                    newC = hCol + 1;
                    break;
                default: // interpret all other input as 's' = stay
                    newR = hRow;
                    newC = hCol;
                    break;
            }
        }

    private:
        char nextMove;

}; // Hero


class Monster: public BoardCell {
    
    public:
		Monster(size_t r, size_t c) {
            setRow(r);
            setCol(c);
            power = 1;
        }
        
        virtual bool isBaddie( ) {return true;}
        virtual bool isStatic( ) {return false;}
        
        virtual char display( ) {
            if (power == 2) {
                return 'M'; // Super Monster
            } else {
                return 'm'; // Monster
            } 
        }

        virtual void setPower(int num) {
            power = num;
        }

        virtual int getPower() {
            return power;
        }
        
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            if (power == 1) {
                // regular monster
                newR = (hRow < getRow()) ? getRow() - 1 : (hRow > getRow()) ? getRow() + 1 : getRow();
                newC = (hCol < getCol()) ? getCol() - 1 : (hCol > getCol()) ? getCol() + 1 : getCol();
            } else {
                // super monster
                newR = (hRow < getRow()) ? getRow() - 2 : (hRow > getRow()) ? getRow() + 2 : getRow();
                newC = (hCol < getCol()) ? getCol() - 2 : (hCol > getCol()) ? getCol() + 2 : getCol();
            }
        }
    
    private:
        int power; // power = 1 for Monster, power = 2 for SuperMonster

}; // Monster

class Bat: public BoardCell {
    public:
		Bat(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual bool isBaddie( ) {return true;}
        virtual bool isStatic( ) {return false;}
        virtual char display( ) {return '~';}
        
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            newR = getRow(); // bats cannot change rows
            newC = hCol;       
        }

}; // Bat


class Abyss: public BoardCell {
	public:
    	Abyss(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '#';}
        virtual bool isHole( ) {return true;}
}; // Abyss


class Wall: public BoardCell {
	public:
    	Wall(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '+';}
    	virtual bool isBarrier( ) {return true;}
}; // Wall


class Nothing: public BoardCell {
	public:
    	Nothing(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return ' ';}
    	virtual bool isSpace( ) {return true;}
}; // Nothing


class EscapeLadder: public BoardCell {
	public:
    	EscapeLadder(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '*';}
    	virtual bool isExit( ) {return true;}
}; // EscapeLadder


#endif //_BOARDCELL_H
