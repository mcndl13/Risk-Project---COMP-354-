#include <iostream>
#include <vector>

class Territory {
public:
    Territory(const std::string &name);
    ~Territory();

    Territory(const Territory &t); // copy constructor
    Territory& operator=(const Territory &t); // assignment operator
    friend std::ostream& operator<<(std::ostream &os, const Territory &t); // stream insertion operator

    void addAdjacency(Territory *territory);
    const std::vector<Territory*>& getAdjacencies() const;

private:
    std::string *name;
    std::string *owningPlayer;
    int *numArmies;
    std::vector<Territory*> adjacencies;
};
