#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    passengers.insert(Passenger(firstname, lastname));
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    return &(passengers.search(Passenger(firstname, lastname))->data);
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    flights.insert(Flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity));
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    std::vector<Flight *> matched_flights;
    
    search_flight_helper(flights.getRoot(), matched_flights, departureCity, arrivalCity);
    
    return matched_flights;
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    BSTNode<Passenger>* passenger = find_passenger(passengers.getRoot(), Passenger(firstname, lastname));
    BSTNode<Flight>* flight = find_flight(flights.getRoot(), flightCode);

    if (passenger && flight)
    {
        Ticket temp = Ticket(&(passenger->data), &(flight->data), ticketType);
        flight->data.addTicket(temp);
    }
    else;
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    BSTNode<Passenger>* passenger = find_passenger(passengers.getRoot(), Passenger(firstname, lastname));
    BSTNode<Flight>* flight = find_flight(flights.getRoot(), flightCode);

    if (passenger && flight)
    {
        freeTicketRequests.enqueue(Ticket(&(passenger->data), &(flight->data), ticketType));
    }
    else;
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    BSTNode<Flight>* flight = find_flight(flights.getRoot(), flightCode);

    if (flight)
    {
        int q_size = freeTicketRequests.size();
        Ticket temp;

        while (q_size--)
        {
            temp = freeTicketRequests.dequeue();

            // If flight is not matched, it will add queue again.
            if (flightCode != temp.getFlight()->getFlightCode())
                freeTicketRequests.enqueue(temp);
            // If flight is matched but ticket is not added, then the ticket will be added queue again
            else if (!(flight->data.addTicket(temp))) 
                freeTicketRequests.enqueue(temp);
            else; // If the ticket is added the "else if" block is not executed but the ticket will be added inside addTicket
        }

        flight->data.setCompleted(true);    }
    else;
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
