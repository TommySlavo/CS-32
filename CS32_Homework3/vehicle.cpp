//
//  vehicle.cpp
//  Homework3_Vehicle
//
//  Created by Tom Slavonia on 2/10/23.
//

#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    std::string id() const {
        return(m_id);
    }
    virtual std::string description() const = 0;
    Vehicle(std::string id){
        m_id = id;
    }
    virtual bool canHover() const {
        return(true);
    }
    virtual ~Vehicle() {} // cannot be purely virtual because of drone
    
private:
    std::string m_id;
};

class Drone : public Vehicle{
public:
    Drone(std::string id) : Vehicle(id) {
    }
    virtual std::string description() const {
        return("a drone");
    }
    ~Drone() {
        std::cout << "Destroying " << id() << ", " << description() << std::endl;
    }
    
private:
};

class Balloon : public Vehicle{
public:
    Balloon(std::string id, int size) : Vehicle(id) {
        m_size = size;
    }
    virtual std::string description() const {
        if (m_size >= 8.0) {
            return("a large balloon");
        }
        return("a small balloon");
    }
    virtual ~Balloon() {
        std::cout << "Destroying the balloon " << id() << std::endl;
    }
    
private:
    double m_size;
};

class Satellite : public Vehicle {
public:
    Satellite (std::string id) : Vehicle(id) {
    }
    virtual std::string description() const {
        return("a satellite");
    }
    virtual bool canHover() const {
        return(false);
    }
    virtual ~Satellite() {
        std::cout << "Destroying the satellite " << id() << std::endl;
    }
    
private:
};

void display(const Vehicle* v)
{
    cout << v->id() << " is " << v->description();
    if (v->canHover())
        cout << ", so it can hover";
    cout << endl;
}

int main()
{
    Vehicle* fleet[4];
    fleet[0] = new Drone("CB4UP");
      // Balloons have an id and a diameter in meters  Balloons with a
      // diameter under 8 meters are small balloons; those with a diameter
      // 8 meters or more are large balloons
    fleet[1] = new Balloon("99LB", 6.3);
    fleet[2] = new Balloon("CN20230201", 30.2);
    fleet[3] = new Satellite("EB8675309");

    for (int k = 0; k < 4; k++)
        display(fleet[k]);

      // Clean up the vehicles before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete fleet[k];
}
