#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
    // TODO
    map = Graph(mapFilePath);
    cachedPaths = KeyedHashTable(potentialPathCount * map.TotalVertexCount());

    this->potentialPathCount = potentialPathCount;
    
    inJourney = false;
    startingLoc = "";
    currentLoc = "";
    destination = "";
}

void METUMaps::SetDestination(const std::string& name)
{
    // TODO
    if (inJourney) {
        PrintUnableToChangeDestination();
    } else {
        destination = name;
    }
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    // TODO
    if (inJourney) {
        PrintUnableToChangeStartingLoc();
    } else {
        startingLoc = name;
    }
}

void METUMaps::StartJourney()
{
    // TODO
    PrintCalculatingRoutes(startingLoc, destination);

    if (inJourney) {
        PrintAlreadyInJourney();
    }
    else
    {
        if (find_location_on_map(startingLoc) == -1 || find_location_on_map(destination) == -1) { // Not on the map
            PrintLocationNotFound();
        }
        else
        {
            int i, j, path_count;
            std::vector<std::vector<int> > shortest_paths;

            // Finding the shortest paths between startingLoc, destination
            path_count = map.MultipleShortPaths(shortest_paths, startingLoc, destination, potentialPathCount);

            // Caching
            for (i = 0; i < path_count; i++)
            {
                int cache_loop_size = shortest_paths[i].size() - 1;

                for (j = 0; j < cache_loop_size; j++)
                {                    
                    std::string starting_name = map.VertexName(shortest_paths[i][j]);
                    std::string key = GenerateKey(starting_name, destination);
                    
                    // Assigning the proper intArray
                    std::vector<int> int_array;
                    int_array.assign(shortest_paths[i].begin()+j, shortest_paths[i].end());

                    cachedPaths.Insert(key, int_array);
                }
            }

            // Additionally, it sets currentLoc to startingLoc. 
            currentLoc = startingLoc;

            //Finally, it sets the currentRoute to the first route that is found.
            currentRoute = shortest_paths[0];

            inJourney = true;
        }
    }
}

void METUMaps::EndJourney()
{
    // TODO
    if (inJourney) {
        inJourney = false;

        cachedPaths.ClearTable();
        startingLoc = "";
        currentLoc = "";
        destination = "";
    } else {
        PrintJourneyIsAlreadFinished();
    }
}

void METUMaps::UpdateLocation(const std::string& name)
{
    // TODO
    if (!inJourney) {
        PrintNotInJourney();
    }
    else if (currentLoc == destination) {
        PrintJourneyCompleted();
    }
    else if (find_location_on_map(name) == -1) {
        PrintLocationNotFound();
    }
    else if (name == destination) {
        PrintJourneyCompleted();
    }
    else
    {
        std::string key = GenerateKey(name, destination);
        std::vector<int> route;

        if (cachedPaths.Find(route, key)) 
        {
            PrintCachedLocationFound(name, destination);

            currentRoute = route;
        }
        else
        {
            int i, j, path_count;
            std::vector<std::vector<int> > shortest_paths;

            PrintCalculatingRoutes(name, destination);

            path_count = map.MultipleShortPaths(shortest_paths, name, destination, potentialPathCount);

            // Caching
            for (i = 0; i < path_count; i++)
            {
                int cache_loop_size = shortest_paths[i].size() - 1;

                std::string destination_name = map.VertexName(shortest_paths[i].back());

                for (j = 0; j < cache_loop_size; j++)
                {                    
                    std::string vertex_name = map.VertexName(shortest_paths[i][j]);
                    std::string key = GenerateKey(vertex_name, destination_name);
                    std::vector<int> int_array; // add all necessary value

                    // Assigning the proper intArray
                    int_array.assign(shortest_paths[i].begin()+i, shortest_paths[i].end());
                    cachedPaths.Insert(key, int_array);
                }
            }

            currentRoute = shortest_paths[0];
        }

        currentLoc = name;
    }
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}
