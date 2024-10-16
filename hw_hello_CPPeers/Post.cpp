# include <iostream>
# include <string>
# include <stdexcept>
# include "Post.h"

using std::string, std::vector;

Post::Post(unsigned int postId, string userName, string postText) : postId(postId), userName(userName), postText(postText) {
    if (postId == 0 || userName == "" || postText == "") {
        throw std::invalid_argument("post constructor: invalid parameter values");
    }
}

unsigned int Post::getPostId() {
    return postId;
}

string Post::getPostUser() {
    return userName;
}

string Post::getPostText() {
    return postText;
}

vector<string> Post::findTags() {
    // TODO: extracts candidate tags based on occurrences of # in the post
    string c;
    string tag;
    vector<string> tags;
    int posttextlen = postText.length();

    for (int i = 0; i < posttextlen; i++) {
        if (postText.at(i) == '#') {
            tag.append("#");
            for (int j = i+1; j < posttextlen; j++) {
                if (postText.at(j) == '!' || postText.at(j) == ',' || postText.at(j) == '.'
                || postText.at(j) == '?' || postText.at(j) == ' ') {
                    break;
                }
                else { 
                    c = (tolower(postText.at(j)));
                    tag.append(c);
                }
            }
            tags.push_back(tag);
            tag = "";
        }
    }
    return tags;
}