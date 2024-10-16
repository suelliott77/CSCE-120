# include <string>
# include <stdexcept>
# include "Tag.h"

using std::string, std::vector;

Tag::Tag(string tagName) : tagName(tagName), tagPosts() {
    // TODO: implement constructor checks
    int n = 0;
    int tagNamelen= tagName.length();
    for (int i = 0; i < tagNamelen; i++) {
        if (isupper(tagName.at(0))) {
            n+=1;
        }
    }

    if (tagNamelen < 2) {
        throw std::invalid_argument("invalid tag name");
    }
    else if (tagName.at(0) != '#' || !islower(tagName.at(1)) || n > 0 || 
        tagName.at(tagNamelen - 1) == '!' || tagName.at(tagNamelen - 1) == ',' || 
        tagName.at(tagNamelen - 1) == '.' || tagName.at(tagNamelen - 1) == '?') {
            throw std::invalid_argument("invalid tag name");
        }
    
    this -> tagName = tagName;
}

string Tag::getTagName() {
    // TODO: implement getter
    return tagName;
}

vector<Post*>& Tag::getTagPosts() {
    // TODO: implement getter
    return tagPosts;
}

void Tag::addTagPost(Post* post) {
    // TODO: add post to tag posts
    if (post == nullptr) {
        throw std::invalid_argument("null post");
    }
    else {
        tagPosts.push_back(post);
    }
}
