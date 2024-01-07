/// @file "grid.h"
///
/// Program 7: Outlast the Baddies & Avoid the Abyss
/// Course: CS 211, Fall 2023, UIC
/// System: Advanced zyLab
/// Author: Owen Neal
///
#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
  struct ROW {
    T*  Cols;     // array of column elements
    size_t NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // array of ROWs
  size_t  NumRows;  // total # of rows (0..NumRows-1)
    
public:

  /// default constructor:
  ///
  /// called automatically by to construct a 4x4 Grid
  /// all elements initialized to default value of T
  ///
  Grid() {
    Rows = new ROW[4];  // 4 rows
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (size_t r = 0; r < NumRows; ++r) {
        Rows[r].Cols = new T[4];
        Rows[r].NumCols = 4;
        
        // initialize the elements to their default value:
        for (size_t c = 0; c < Rows[r].NumCols; ++c) {
            Rows[r].Cols[c] = T();  // default value for type T:
        }
    }
  }

  ///   parameterized constructor:
  /// 
  ///   automatically called to construct a Grid with R rows and C columns
  ///   all elements are initialized to default value of T
  ///
  Grid(size_t R, size_t C) {
    Rows = new ROW[R];
    NumRows = R;

    for (size_t r = 0; r < NumRows; r++) {
        Rows[r].Cols = new T[C];
        Rows[r].NumCols = C;
        for (size_t c = 0; c < Rows[r].NumCols; ++c) {
            Rows[r].Cols[c] = T();  // default value for type T:
        }
    }
  }

  /// destructor:
  ///
  /// called automatically to free memory for this grid
  ///
  virtual ~Grid() {
    for (size_t r = 0; r < NumRows; ++r) {
      delete[] Rows[r].Cols;
    }
    delete[] Rows;
  }

  /// copy constructor:
  ///
  /// automatically called to construct a Grid that contains a
  /// copy of an existing grid
  ///
  Grid(const Grid<T>& other) {
    NumRows = other.NumRows;
    Rows = new ROW[NumRows];

    for (size_t r = 0; r < NumRows; ++r) {
        Rows[r].NumCols = other.Rows[r].NumCols;
        Rows[r].Cols = new T[Rows[r].NumCols];

      for (size_t c = 0; c < Rows[r].NumCols; ++c) {
          Rows[r].Cols[c] = other.Rows[r].Cols[c];
      }
    }
  }
    

  /// copy operator=
  ///
  /// called when one Grid is assigned into another, i.e. this = other;
  /// overwrites the original grid on left side of =
  Grid& operator=(const Grid& other) {
      if (this != &other) {
        // clear existing data
        for (size_t r = 0; r < NumRows; ++r) {
            delete[] Rows[r].Cols;
      }
        delete[] Rows;

        // copy new data
        NumRows = other.NumRows;
        Rows = new ROW[NumRows];

        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r].NumCols = other.Rows[r].NumCols;
            Rows[r].Cols = new T[Rows[r].NumCols];

            for (size_t c = 0; c < Rows[r].NumCols; ++c) {
                Rows[r].Cols[c] = other.Rows[r].Cols[c];
            }
        }
    }
    return *this;   
  }


  /// numrows
  ///
  /// returns the # of rows in the grid
  /// the indices for these rows are 0..numrows-1
  ///
  size_t numrows() const {
      return NumRows;
  }
  
  /// numcols
  ///
  /// returns the # of columns in row r parameter
  /// the indices for these columns are 0..numcols-1.  
  /// for now, each row has the same number of columns.
  ///
  size_t numcols(size_t r) const {
    if (r < NumRows) {
        return Rows[r].NumCols;
    } else {
        throw out_of_range("Invalid row index");
    }
  }

  /// size
  ///
  /// returns the total # of elements in the grid
  ///
  size_t size() const {
    size_t totalSize = 0;
    for (size_t r = 0; r < NumRows; ++r) {
        totalSize += Rows[r].NumCols;
    }
    return totalSize;
  }

  /// ()
  ///
  /// returns a reference to the element at location (r, c);
  /// allows access or assign the element:
  ///
  ///    grid(r, c) = ...
  ///    cout << grid(r, c) << endl;
  ///
  T& operator()(size_t r, size_t c) {
    if (r < NumRows && c < Rows[r].NumCols) {
        return Rows[r].Cols[c];
    } else {
        throw out_of_range("Invalid row or column index");
    }
  }

  /// _output
  ///
  /// outputs the grid for testing purposes  
  /// this is not tested.
  ///
  void _output() {
    for (size_t r = 0; r < NumRows; ++r) {
        for (size_t c = 0; c < Rows[r].NumCols; ++c) {
            cout << Rows[r].Cols[c] << " ";
        }
        cout << endl;
    }
  }
};
