#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

UserDatabase::~UserDatabase() {
    for (int i = 0; i < m_users.size(); i++) {
        delete m_users[i];
    }
}

bool UserDatabase::load(const string& filename)
{
    
    ifstream infile(filename);
    
    if(infile) {
        std::string line, email, name;
        int numMovies = -1;
        std::vector<std::string> theMovies;
        int read = 1;
        while (getline(infile, line)) {
            if (read == 1) {
                name = line;
                read++;
                continue;
            }
            if(read == 2) {
                email = line;
                read++;
                continue;
            }
            if (read == 3) {
                read++;
                numMovies = stoi(line);
                continue;
            }
            if (line.empty() == false && numMovies >= theMovies.size()) {
                // makes all ids lower case
                theMovies.push_back(line);
                continue;
            }
            if (line.empty() == true) {
                read = 1;
                User* u = new User(name, email, theMovies);
                m_users.push_back(u);
                m_email_to_user.insert(email, u);
                theMovies.clear();
                numMovies = -1;
                name = "";
                email = "";
            }
        }
        
        if (name != "") { // if there is an extra user at the end
            User* u = new User(name, email, theMovies);
            m_users.push_back(u);
            m_email_to_user.insert(email, u);
            theMovies.clear();
            numMovies = -1;
            name = "";
            email = "";
            
        }
        
        return(true);
    }
    
    return(false);  // Replace this line with correct code.
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User*>::Iterator it = m_email_to_user.find(email);
    if (it.is_valid()) { // checks if iterator is valid before trying to get the value
        return(it.get_value());
    }
    
    return(nullptr);
    
}

