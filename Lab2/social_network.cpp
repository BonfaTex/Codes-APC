///Header include
#include "social_network.hpp"
#include "user.hpp"

///STD include
#include <iostream>

namespace SocialNetworkNS {
size_t SocialNetwork::CUserIndex(const std::string &name,
                                 const std::string &surname) const {
  size_t i;

  User u(name, surname);

  bool found = false;

  for (i = 0; i < users.size() && !found; ++i)
    if (users[i] == u)
      found = true;

  if (found)
    return --i;
  else
    return users.size();
}

// =========================================
// Matteo's version
// =========================================

void SocialNetwork::AddUser(const std::string &name,
                            const std::string &surname) {

     // YOUR CODE GOES HERE

    size_t dim = CUserIndex(name, surname);

    if(dim==users.size()) { // i.e. if the new user is not in the network

        User newUs(name, surname);
        users.push_back(newUs);

        std::vector<size_t> f_list{}; // or just
        friends.push_back(f_list);    // friends.push_back({});
    }

}

const std::vector<User> SocialNetwork::CGetUsers() const {
  return users;
}

const std::vector<User> SocialNetwork::CGetFriends(const User &user) const {

   // YOUR CODE GOES HERE

  return CGetFriends(user.CGetName(), user.CGetSurname());

}

const std::vector<User> SocialNetwork::CGetFriends(const std::string &name,
                                                   const std::string &surname) const {
  std::vector<User> ret{};

   // YOUR CODE GOES HERE

  size_t dim = CUserIndex(name, surname); // fix the raw

  if (dim<users.size()) { // if new user is already in the network

      for ( size_t i : friends[dim] ) {

          ret.push_back(users[i]);

      }
  }

  return ret;

}

void SocialNetwork::AddFriendship(const std::string &first_name,
                                  const std::string &first_surname,
                                  const std::string &second_name,
                                  const std::string &second_surname) {

    // YOUR CODE GOES HERE

  size_t dim1 = CUserIndex(first_name, first_surname);
  size_t dim2 = CUserIndex(second_name, second_surname);

  if (  dim1!=dim2                                                // same user?
        && dim1!=users.size() && dim2!=users.size()               // already in the network?
        && !Check_friendship(dim1, dim2)                   // already friends?
        ) {
      friends[dim1].push_back(dim2);
      friends[dim2].push_back(dim1);
  }

}

bool SocialNetwork::Check_friendship(const size_t &f1, const size_t &f2) {
    bool areUfriends = false;
    for (size_t i=0; i<friends[f1].size() && !areUfriends; ++i) {
        if (friends[f1][i]==f2) {
            areUfriends = true;
        }
    }
    return areUfriends;
}

// =========================================
// Lorenzo's version
// =========================================
/*
void SocialNetwork::AddUser(const std::string &name,
                            const std::string &surname) {

    // YOUR CODE GOES HERE
    unsigned size = users.size();
    for(unsigned i=0; i<size; i++){
        if(users[i].CGetName()==name && users[i].CGetSurname()==surname) {
            std::cout << "User already in the network"<<std::endl;
            return;
        }
    }
    users.push_back(User(name,surname));
    std::vector<size_t> aux;
    friends.push_back(aux);
}

const std::vector<User> SocialNetwork::CGetUsers() const {
    return users;
}

const std::vector<User> SocialNetwork::CGetFriends(const User &user) const {

    // YOUR CODE GOES HERE
    std::vector<User> ret;
    unsigned ind = CUserIndex(user.CGetName(), user.CGetSurname());

    unsigned size = friends[ind].size();
    for (unsigned i = 0; i < size; i++) {
        std::string nm = users[friends[ind][i]].CGetName();
        std::string sr = users[friends[ind][i]].CGetSurname();
        ret.push_back(User(nm, sr));
    }
    *//*
    for (size_t i : friends[ind]) {
        std::string nm = users[i].CGetName();
        std::string sr = users[i].CGetSurname();
        ret.push_back(User(nm, sr));
    }
     *//*
    return ret;
}

const std::vector<User> SocialNetwork::CGetFriends(const std::string &name,
                                                   const std::string &surname) const {
    // YOUR CODE GOES HERE
    User aux=User(name,surname);
    //std::vector<User> ret{User("","")};
    //ret = CGetFriends(aux);
    return CGetFriends(aux);
}

void SocialNetwork::AddFriendship(const std::string &first_name,
                                  const std::string &first_surname,
                                  const std::string &second_name,
                                  const std::string &second_surname) {

    // YOUR CODE GOES HERE
    size_t size = users.size();
    if(first_name==second_name && first_surname==second_surname){
        std::cout<<"a user cannot be friend of her/himself."<<std::endl;
        return;
    }
    size_t ind1= CUserIndex(first_name,first_surname);
    size_t ind2= CUserIndex(second_name,second_surname);
    if(ind1==size || ind2==size){
        std::cout<<"a user cannot be friend of another user who is not in the social network."<<std::endl;
        return;
    }
    bool flag=false;
    size_t size2=friends[ind1].size();
    for(size_t i = 0 ; i < size2 ; ++i){
        if(friends[ind1][i]==ind2){
            flag=true;
        }
    }
    if(flag){
        std::cout<<"users are already friends."<<std::endl;
        return;
    }
    friends[ind1].push_back(ind2);
    friends[ind2].push_back(ind1);
}
*/

// =========================================
// Carlotta's version
// =========================================
/*
void SocialNetwork::AddUser(const std::string &name,
                            const std::string &surname) {

    // YOUR CODE GOES HERE
    if (CUserIndex(name, surname) != users.size())
        return;

    User u(name, surname);
    std::vector<size_t> f_list{};

    users.push_back(u);
    friends.push_back(f_list);

}

const std::vector<User> SocialNetwork::CGetUsers() const {
    return users;
}

const std::vector<User> SocialNetwork::CGetFriends(const User &user) const {


    // YOUR CODE GOES HERE
    std::vector<User> ret{};

    size_t idx = CUserIndex(user.CGetName(), user.CGetSurname());
    if(idx == users.size())
        return ret;

    for (size_t i : friends[idx])
        ret.push_back(users[i]);

    return ret;

}

const std::vector<User> SocialNetwork::CGetFriends(const std::string &name,
                                                   const std::string &surname) const {
    // YOUR CODE GOES HERE

    User u(name, surname);

    return CGetFriends(u);

}

void SocialNetwork::AddFriendship(const std::string &first_name,
                                  const std::string &first_surname,
                                  const std::string &second_name,
                                  const std::string &second_surname) {

    // YOUR CODE GOES HERE

    size_t idx1 = CUserIndex(first_name, first_surname);
    size_t idx2 = CUserIndex(second_name, second_surname);

    if (idx1 == idx2)
        return;

    if (idx1 == users.size() || idx2 == users.size())
        return;

    for (size_t i : friends[idx1])
        if (idx2 == i)
            return;

    friends[idx1].push_back(idx2);
    friends[idx2].push_back(idx1);

}
*/

// =========================================
// Davide's version
// =========================================
/*
void SocialNetwork::AddUser(const std::string &name,
                            const std::string &surname) {

 // YOUR CODE GOES HERE

    if (CUserIndex(name, surname) != users.size())
        return;

    User u(name, surname);
    std::vector<size_t> f_list{};

    users.push_back(u);
    friends.push_back(f_list);

}

const std::vector<User> SocialNetwork::CGetUsers() const {
    return users;
}

const std::vector<User> SocialNetwork::CGetFriends(const User &user) const {


 // YOUR CODE GOES HERE

    std::vector<User> ret{};

    size_t idx = CUserIndex(user.CGetName(), user.CGetSurname());
    if(idx == users.size())
        return ret;

    for (size_t i : friends[idx])
        ret.push_back(users[i]);

    return ret;

}

const std::vector<User> SocialNetwork::CGetFriends(const std::string &name,
                                                   const std::string &surname) const {
 // YOUR CODE GOES HERE


    User u(name, surname);

    return CGetFriends(u);

}

void SocialNetwork::AddFriendship(const std::string &first_name,
                                  const std::string &first_surname,
                                  const std::string &second_name,
                                  const std::string &second_surname) {

 // YOUR CODE GOES HERE


    size_t idx1 = CUserIndex(first_name, first_surname);
    size_t idx2 = CUserIndex(second_name, second_surname);

    if (idx1 == idx2)
        return;

    if (idx1 == users.size() || idx2 == users.size())
        return;

    for (size_t i : friends[idx1])
        if (idx2 == i)
            return;

    friends[idx1].push_back(idx2);
    friends[idx2].push_back(idx1);

}
*/

}