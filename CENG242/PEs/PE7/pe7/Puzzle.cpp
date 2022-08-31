#include "Puzzle.h"


/****************************************************/
/****              *** PUZZLE ***                ****/

/* Contsructor : It takes three integers in the following order:
    The first argument is size of the puzzle which is 2^N for some N >= 0.
    The second argument is the initial row id of the puzzle.
    The third argument is the initial column id of the puzzle.
    
    After initialization with the above arguments, the necessary 
    pointers should be initialized to NULL.
    Note that the final row id in this puzzle is equal to: 
       initial_row_id + size - 1.
    Note that the final column id in this puzzle is equal to: 
       initial_column_id + size - 1.
       
    ATTENTION: If a sub-puzzle member does not include any Piece, namely, 
    if its piece is NULL, then do NOT construct it. In other words, do 
    NOT construct subpuzzles unless they are required. 
*/
Puzzle::Puzzle(int size, int row_id, int column_id) {
    this->top_left = NULL;
    this->top_right = NULL;
    this->bottom_left = NULL;
    this->bottom_right = NULL;
    
    this->size = size;
    this->first_row = row_id;
    this->first_column = column_id;
    
    this->piece = NULL;
}

/* Destructor  : It should destruct its sub-puzzles, yet it is NOT responsible
   of the destruction of its Piece member.
*/
Puzzle::~Puzzle() {
    // TODO
    delete top_left;
    delete top_right;
    delete bottom_left;
    delete bottom_right;
}

/* Copy constructor : It totally applies deep copy except the Piece
   member part. Do not deep copy Piece objects of the puzzle, instead
   do shallow copy for Pieces.
*/
Puzzle::Puzzle(const Puzzle& puzzle) {
    // TODO
    if (puzzle.size == 1)
    {
        this->top_left = NULL;
        this->top_right = NULL;
        this->bottom_left = NULL;
        this->bottom_right = NULL;
    
        this->size = 1;
        this->first_row = puzzle.first_row;
        this->first_column = puzzle.first_column;
    
        this->piece = new Piece(*(puzzle.piece));
    }
    else
    {
        // int new_size = puzzle.size / 2;
        // int row = puzzle.first_row;
        // int col = puzzle.first_column;

        // this->top_left = new Puzzle(new_size, row, col);
        // this->top_right = new Puzzle(new_size, row + new_size, col);
        // this->bottom_left = new Puzzle(new_size, row, col + new_size);
        // this->bottom_right = new Puzzle(new_size, row + new_size, col + new_size);

        // this->size = puzzle.size;
        // this->first_row = row;
        // this->first_column = col;

        // this->piece = piece; // NULL



        this->top_left = new Puzzle(*(puzzle.top_left));
        this->top_right = new Puzzle(*(puzzle.top_right));
        this->bottom_left = new Puzzle(*(puzzle.bottom_left));
        this->bottom_left = new Puzzle(*(puzzle.bottom_left));

        this->size = puzzle.size;
        this->first_row = puzzle.first_row;
        this->first_column = puzzle.first_column;

        this->piece = puzzle.piece; // NULL
    }
}

/* Assignment operator : It totally applies shallow copy.
*/
Puzzle& Puzzle::operator=(const Puzzle& puzzle) {
    this->top_left = puzzle.top_left;
    this->top_right = puzzle.top_right;
    this->bottom_left = puzzle.bottom_left;
    this->bottom_right = puzzle.bottom_right;

    this->size = puzzle.size;
    this->first_row = puzzle.first_row;
    this->first_column = puzzle.first_column;

    this->piece = puzzle.piece;

    return *this;
}

/* This method directly assigns (without copying) the given Piece object to
   the corresponding sub-puzzle (cell) whose indices given in the second 
   argument in array form as follows <row_id, column_id>.
   
    ATTENTION: If a sub-puzzle member does not include any Piece, namely, 
    if its piece is NULL, then do NOT construct it. In other words, do 
    NOT construct subpuzzles unless they are required.
*/
void Puzzle::placePiece(const Piece& piece, int cell[2]) {
    if (size == 1)
    {
        if (this->first_row == cell[0] && this->first_column == cell[1])
        {
            this->piece = &piece;
        }
        else
        {
            return;
        }
    }
    else
    {
        if (cell[0] < first_row + size / 2) // top
        {
            if (cell[1] < first_column + size / 2) // left
            {
                if (!top_left)
                    top_left = new Puzzle(size / 2, first_row, first_column);
                top_left->placePiece(piece, cell);
            }
            else // right
            {
                if (!top_right)
                    top_right = new Puzzle(size / 2, first_row, first_column + size / 2);

                top_right->placePiece(piece, cell);        
            }
        }
        else // bottom
        {
            if (cell[1] < first_column + size / 2) // left
            {
                if (!bottom_left)
                    bottom_left = new Puzzle(size / 2, first_row + size / 2, first_column);
                bottom_left->placePiece(piece, cell);
            }
            else // right
            {
                if (!bottom_right)
                    bottom_right = new Puzzle(size / 2, first_row + size / 2, first_column + size / 2);
                bottom_right->placePiece(piece, cell);
            }
        }
    }
}

/* It returns directly the piece object located in the sub-puzzle (cell)
   whose row id and column id are given in the first and second elements of 
   2D array as argument, respectively. If there is no piece in the requested 
   indices, then this method throws an EmptyCellRequest exception defined in 
   Exception.h file.
*/
const Piece& Puzzle::getPiece(int cell[2]) const {
    // TODO;
    if (size == 1)
    {
        if (this->first_row == cell[0] && this->first_column == cell[1])
        {
            if (this->piece) // not null
            {
                throw EmptyCellRequest();
            }
            else
                return *(this->piece);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        if (cell[0] < first_row + size / 2) // left
        {
            if (cell[1] < first_column + size / 2) // top
            {
                if (!top_left)
                    throw EmptyCellRequest();
                top_left->getPiece(cell);
            }
            else // bottom
            {
                if (!bottom_left)
                    throw EmptyCellRequest();
                bottom_left->getPiece(cell);
            }
        }
        else // right
        {
            if (cell[1] < first_column + size / 2) // top
            {
                if (!top_right)
                    throw EmptyCellRequest();
                top_right->getPiece(cell);
            }
            else // bottom
            {
                if (!top_left)
                    throw EmptyCellRequest();
                
                top_left->getPiece(cell);
            }
        }
    }
}

/* This method returns the sub-puzzle whose initial and final row-column ids 
   are given in the first and second arguments, respectively. The indices
   given in the arguments will be given as an exact correspondence to one of
   the sub-puzzles of the current puzzle object.
   
   ATTENTION: The sub-puzzle to be cropped may correspond to a NULL part of the
   Puzzle object. In that case, it is enough to you to create a new Puzzle 
   object that satisfies the asked properties and return it. OF course, do NOT 
   forget to do this operation by escaping from memory leaks!!!
*/
Puzzle Puzzle::crop(int from[2], int to[2]) const {
    int size_of_area = to[0] - from[0] + 1;
    return crop_helper(size_of_area, from);
}
