# include <iostream>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include "Network.h"

using std::string, std::vector;

Network::Network() : users({}), posts({}), tags({}) {}

void Network::loadFromFile(string fileName) {
    // TODO: load user and post information from file
    std::ifstream fileStuff;
    fileStuff.open(fileName);
    if (!(fileStuff.is_open())) {
        throw std::invalid_argument("File is not open");
    }

    string stuff, type, userName, text;
    unsigned int postId;

    while (getline(fileStuff , stuff)) {
        std::stringstream stuffStream(stuff);
        stuffStream >> type;
        if (type == "User") {
            if (!(stuffStream >> userName)) {
                throw std::runtime_error("Content Invalid");
            }
            try {
                addUser(userName);
                
            } 
            catch (...) {
                throw std::runtime_error("Content Invalid");
                }
                continue;
        }

        if (type == "Post") {
            if (stuffStream >> postId >> userName) {
            } 
            else {
                throw std::runtime_error("Content Invalid");
                }
            getline(stuffStream , text);
            text.erase(0,1);
            try {
                addPost(postId , userName , text);
            } 
            catch (...) {
                throw std::runtime_error("Content Invalid");
            }
            continue;
        }

        throw std::runtime_error("Content Invalid");
    }
}

void Network::addUser(string userName) {
    // TODO: create user and add it to network
    string name;
    int usernamelen = userName.length();

    for (int i = 0; i < usernamelen ; i++) {
        userName.at(i) = tolower(userName.at(i));
    }

    int userssize = users.size();
    for (int i = 0; i < userssize; i++) {
        if (userName == (users.at(i))->getUserName()) {
            throw std::invalid_argument("network add user check");
        }
    }

    User newuser(userName);
    User* ptr = new User(userName);
    users.push_back(ptr);
    std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
    // TODO: create post and add it to network
    unsigned int location;
    for (unsigned int i = 0 ; i < posts.size() ; i++) {
        if (posts.at(i) -> getPostId() == postId) {
            throw std::invalid_argument("Duplicate post ID.");
        }
    }
    
    bool found = false;
    for (unsigned int i = 0 ; i < users.size() ; i++) {
        if (users.at(i) -> getUserName() == userName) {
            found = true;
            location = i;
        }
    }

    if (!found) {
        throw std::invalid_argument("User is not in database!");
    }

    posts.push_back(new Post(postId , userName , postText));
    users.at(location) -> addUserPost(posts.back());
    vector<string> postTags = posts.back() -> findTags();

    bool tagFound = false;

    for (unsigned int i = 0 ; i < postTags.size() ; i++) {
        tagFound = false;
        for (unsigned int j = 0 ; j < tags.size() ; j++) {
            if (postTags.at(i) == tags.at(j) -> getTagName()) {
                tagFound = true;
                tags.at(j) -> addTagPost(posts.back());
            }
        }
        if (!tagFound) {
            try {
                tags.push_back(new Tag(postTags.at(i)));

                tags.back() -> addTagPost(posts.back());
        } 
        catch (...) {}
        }
    }
    std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
    // TODO: return posts created by the given user
    int num = 0;
    int userIndex;
    if (userName == "") {
        throw std::invalid_argument("Empty Username");
    }
    
    int usersize = users.size();
    for (int i = 0; i < usersize; i++) {
        if (userName == users.at(i) -> getUserName()) {
            num++;
            userIndex = i;
        }
    }

    if (num == 0) {
        throw std::invalid_argument("No Matching Username");
    }
    int size = ((users.at(userIndex) -> getUserPosts())).size();
    for (int i = 0; i < size; i++) {
        std::cout << ((users.at(userIndex) -> getUserPosts().at(i)) -> getPostText()) << std::endl;
    }
    return ((users.at(userIndex) -> getUserPosts()));
}

vector<Post*> Network::getPostsWithTag(string tagName) {
    // TODO: return posts containing the given tag
    int num = 0;
    int tagIndex;
    if (tagName == "") {
        throw std::invalid_argument("empty tagname");
    }

    int tagsize = tags.size();
    for (int i = 0; i < tagsize; i++) {
        if (tagName == tags.at(i)->getTagName()) {
            num++;
            tagIndex = i;
            break;
            //std::cout << num << std::endl;
        }
    }

    if (num == 0) {
        throw std::invalid_argument("no matching tag");
    }

    int numOfPosts = tags.at(tagIndex)->getTagPosts().size();

    for (int i = 0; i < numOfPosts; i++) {
        std::cout << (tags.at(tagIndex) -> getTagPosts()).at(i) -> getPostText() <<std::endl;
    }

    return (tags.at(tagIndex)) -> getTagPosts();
}

vector<string> Network::getMostPopularHashtag() {
    // TODO: return the tag occurring in most posts
    vector<string> mostPop;
    int numOfPosts;
    int mostNumOfPosts = 0;
    int tagsIndex;
    int tagsize = tags.size();

    for (int i = 0; i < tagsize; i++) {
        numOfPosts = tags.at(i)->getTagPosts().size();
        if (numOfPosts > mostNumOfPosts){
            mostNumOfPosts = numOfPosts;tagsIndex = i;
        }
    }

    mostPop.push_back(tags.at(tagsIndex)->getTagName());
    for (int i = 0; i < tagsize; i++) {
        numOfPosts = tags.at(i)->getTagPosts().size();
        if (i == tagsIndex) {
            continue;
        }
        if (numOfPosts == mostNumOfPosts) {
            mostPop.push_back(tags.at(i)->getTagName());
        }
    } 
    
    int size = mostPop.size();

    for (int i = 0; i < size; i++) {
        std::cout << mostPop.at(i) << std::endl;
    }
    
    return mostPop;
}

Network::~Network() {
    for (unsigned int i = 0; i < users.size(); ++i) {
        delete users.at(i);
    }

    for (unsigned int i = 0; i < tags.size(); ++i) {
        delete tags.at(i);
    }
    
    for (unsigned int i = 0; i < posts.size(); ++i) {
        delete posts.at(i);
    }
}
