#include "Edge.h"


/****************************************************/
/****                *** EDGE ***                ****/

/* 
@param id initializes the <id> of the object
@param pwd initializes the <password> of the object
*/
Edge::Edge(int id, Password pwd) {
    this->id = id;
    this->password = pwd;
    matchingEdge = NULL;
}

/*
It is NOT responsible of the destruction of the matchingEdge!
*/
Edge::~Edge() {}

/* 
@returns <id> of the object
*/
int Edge::getId() const {
	return this->id;
}

/*
@returns the pointer to the matching partner of the current edge.
*/
Edge* Edge::getMatchingEdge() const {
    return matchingEdge;
}

/*
StraightEdge <-> StraightEdge
InwardsEdge <-> OutwardsEdge

Note that match operation is a mutual operation. Namely, if the current edge is matched, then its partner edge should be matched with the current one too.

@param edge will be tried to be matched.

@returns true and matching by storing <matchingEdge> variables with each other if the two edges are matchable; otherwise false.
*/
bool Edge::matchWith(Edge& edge) {
    if (!this->matchWithHelper(edge.password)) // not matchable
        return false;
    else;

    /* If here, they are matchable. Match */
    if (this->matchingEdge)
        this->breakMatch();
    else;

    if (edge.matchingEdge)
        edge.breakMatch();
    else;

    this->matchingEdge = &edge;
    edge.matchingEdge = this;
    
    return true;
}

/* If the current edge was matched with some edge before, then this method
   breaks the match, i.e. there is no match between those two edges anymore.
   Note that breaking match operation is a mutual operation. Namely, if the 
   matching of the current edge is broken, the matching recorded in its partner 
   edge should be broken too.
*/
void Edge::breakMatch() {
    this->matchingEdge->matchingEdge = NULL;
    this->matchingEdge = NULL;
}

/****************************************************/
/****            *** STRAIGHT EDGE ***           ****/

/* 
@param id initializes the <id> of the object
@param password = SEND_ME_STRAIGHT,
*/
StraightEdge::StraightEdge(int id) : Edge(id, SEND_ME_STRAIGHT) {}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
StraightEdge::~StraightEdge() {}

/* 
This method clones the current object and returns the pointer to its clone. Cloning is actually a deep-copy operation, so construct a new StraightEdge object.
   
Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched 
   with each other.
*/
Edge* StraightEdge::clone() const {
    StraightEdge* cloned_edge = new StraightEdge(this->id);

    if (this->matchingEdge) // not null
    {
        StraightEdge *matching_edge = new StraightEdge(this->matchingEdge->getId());

        cloned_edge->matchWith(*matching_edge);
    }
    else;

    return cloned_edge;
}


// @returns true if edges are matchable otherwise false
bool StraightEdge::matchWithHelper(Password pwd) {
    return SEND_ME_STRAIGHT == pwd;
}


/****************************************************/
/****            *** INWARDS EDGE ***            ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_OUTWARDS,
   therefore it is not given as an argument.
*/
InwardsEdge::InwardsEdge(int id) : Edge(id, SEND_ME_OUTWARDS) {}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
InwardsEdge::~InwardsEdge() {}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   InwardsEdge object.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched 
   with each other.
*/
Edge* InwardsEdge::clone() const {
    InwardsEdge* cloned_edge = new InwardsEdge(this->id);

    if (this->matchingEdge) // not null
    {
        OutwardsEdge *matching_edge = new OutwardsEdge(this->matchingEdge->getId());

        cloned_edge->matchWith(*matching_edge);
    }
    else;

    return cloned_edge;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool InwardsEdge::matchWithHelper(Password pwd) {
    return SEND_ME_INWARDS == pwd;
}

/****************************************************/
/****            *** OUTWARDS EDGE ***           ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_INWARDS,
   therefore it is not given as an argument.
*/
OutwardsEdge::OutwardsEdge(int id) : Edge(id, SEND_ME_INWARDS) {}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
OutwardsEdge::~OutwardsEdge() {}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   OutwardsEdge object.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched 
   with each other.
*/
Edge* OutwardsEdge::clone() const {
    OutwardsEdge* cloned_edge = new OutwardsEdge(this->id);

    if (this->matchingEdge) // not null
    {
        InwardsEdge *matching_edge = new InwardsEdge(this->matchingEdge->getId());

        cloned_edge->matchWith(*matching_edge);
    }
    else;

    return cloned_edge;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool OutwardsEdge::matchWithHelper(Password pwd) {
	return SEND_ME_OUTWARDS == pwd;
}
