#ifndef AIRLINERESERVATIONSYSTEM_H
#define AIRLINERESERVATIONSYSTEM_H

#include "BST.h"
#include "Queue.h"
#include "Passenger.h"
#include "Flight.h"
#include "Ticket.h"

class AirlineReservationSystem {
public: // DO NOT CHANGE THIS PART.
    AirlineReservationSystem() {}

    void addPassenger(const std::string &firstname, const std::string &lastname);

    Passenger *searchPassenger(const std::string &firstname, const std::string &lastname);

    void addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity);

    std::vector<Flight *> searchFlight(const std::string &departureCity, const std::string &arrivalCity);

    void issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void executeTheFlight(const std::string &flightCode);

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void search_flight_helper(BSTNode<Flight>* const root, std::vector<Flight *> &matched_flights, const std::string departure_city, const std::string arrival_city) const {
        if (!root) // root == NULL
            return;
        
        if (root->data.getDepartureCity() == departure_city && root->data.getArrivalCity() == arrival_city)
            matched_flights.push_back(&(root->data));
        else;

        // Searching left side of the root
        search_flight_helper(root->left, matched_flights, departure_city, arrival_city);

        // Searching right side of the root
        search_flight_helper(root->right, matched_flights, departure_city, arrival_city);
    }

    BSTNode<Passenger>* find_passenger(BSTNode<Passenger>* const root, const Passenger &passenger) const {
        if (!root) // passenger is not found
            return NULL;
        
        if (passenger == root->data)
            return root;
        else if (passenger < root->data)
            return find_passenger(root->left, passenger);
        else // passenger > root->data
            return find_passenger(root->right, passenger);
    }

    BSTNode<Flight>* find_flight(BSTNode<Flight>* const root, const std::string &flight_code) const {
        if (!root) // flight is not found
            return NULL;
        
        if (flight_code == root->data.getFlightCode())
            return root;
        else if (flight_code < root->data.getFlightCode())
            return find_flight(root->left, flight_code);
        else // flight > root->data.getFlightCode
            return find_flight(root->right, flight_code);
    }

private: // DO NOT CHANGE THIS PART.
    BST<Passenger> passengers;
    BST<Flight> flights;

    Queue<Ticket> freeTicketRequests;
};

#endif //AIRLINERESERVATIONSYSTEM_H
