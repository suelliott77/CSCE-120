# include <string>
# include <stdexcept>
# include "User.h"

using std::string, std::vector;

User::User(string userName) : userName(userName), userPosts() {
    // TODO: implement constructor checks
    int n = 0;
    int userNamelen = userName.length();
    for (int i = 0; i < userNamelen; i++) {
        if (isupper(userName.at(i))) {
            n+=1;
        }
    }

    if (userName == "" || !islower(userName.at(0)) || n > 0) {
        throw std::invalid_argument("invalid username");
    }

    this -> userName = userName;
}

string User::getUserName() {
    // TODO: implement getter
    return userName;
}

vector<Post*>& User::getUserPosts() {
    // TODO: implement getter
    return userPosts;
}

void User::addUserPost(Post* post) {
    // TODO: add post to user posts
    if (post == nullptr) {
        throw std::invalid_argument("add user post: null post");
    }
    else {
        userPosts.push_back(post);
    }
}
