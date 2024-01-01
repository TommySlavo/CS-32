#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;
    ~UserDatabase();

  private:
    TreeMultimap<std::string, User*> m_email_to_user;
    std::vector<User*> m_users; // want vector of string pointers
};

#endif // USERDATABASE_INCLUDED
