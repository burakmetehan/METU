#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include "Edge.h"
#include "Piece.h"
#include "Exception.h"

//////////////////////////////////////////////////////
//  DO NOT CHANGE *SPECIFIED PARTS* OF THIS FILE!   // 
//////////////////////////////////////////////////////
class Puzzle {

    /**/ /**************************/ /**/
	/**/ Puzzle* top_left;            /**/
	/**/ Puzzle* top_right;           /**/
	/**/ Puzzle* bottom_left;         /**/
	/**/ Puzzle* bottom_right;        /**/
	/**/ int size;                    /**/
	/**/ int first_row, first_column; /**/
	/**/ const Piece* piece;          /**/
	/**/ /**************************/ /**/
    // DO NOT MODIFY ABOVE

    // YOU CAN DEFINE YOUR OWN VARIABLES, METHODS, DATA STRUCTURES, etc. HERE!
    /// ...
    Puzzle crop_helper(int size_of_area, int cell[2]) const
	{
		if (size == size_of_area)
		{
			return *this;
		}
		else
		{
			if (cell[0] < first_row + size / 2) // top
			{
				if (cell[1] < first_column + size / 2) // left
				{
					if (!top_left)
						return Puzzle(size_of_area, cell[0], cell[1]);
					top_left->crop_helper(size_of_area, cell);
				}
				else // right
				{
					if (!top_right)
						return Puzzle(size_of_area, cell[0], cell[1]);

					top_right->crop_helper(size_of_area, cell);        
				}
			}
			else // bottom
			{
				if (cell[1] < first_column + size / 2) // left
				{
					if (!bottom_left)
						return Puzzle(size_of_area, cell[0], cell[1]);
					bottom_left->crop_helper(size_of_area, cell);
				}
				else // right
				{
					if (!bottom_right)
						return Puzzle(size_of_area, cell[0], cell[1]);
					bottom_right->crop_helper(size_of_area, cell);
				}
			}
    }
	}

    // DO NOT MODIFY BELOW
public:
	Puzzle(int, int, int);
	~Puzzle();
	Puzzle(const Puzzle&);
	Puzzle& operator=(const Puzzle&);
	void placePiece(const Piece&, int[2]);
	const Piece& getPiece(int[2]) const;
	Puzzle crop(int[2], int[2]) const ;
	void patch(const Puzzle&);
	friend ostream& operator<< (ostream&, const Puzzle&);

};

#endif