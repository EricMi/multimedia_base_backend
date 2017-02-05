#include "MyBase.h"
using namespace std;

MyBase::MyBase() {
}

MyBase::~MyBase() {
    for(GroupMap::iterator it = this->group.begin(); it != this->group.end(); it++) {
        it->second.reset();
    }
    for(MultimediaMap::iterator it = this->multimedia.begin(); it != this->multimedia.end(); it++) {
        it->second.reset();
    }
}

MultimediaPtr MyBase::createPhoto(string name, string fileName, int width, int height) {
    MultimediaPtr mPtr = MultimediaPtr(new Photo(name, fileName, width, height));
    this->multimedia[name] = mPtr;
    return mPtr;
}

MultimediaPtr MyBase::createVideo(string name, string fileName, int duration) {
    MultimediaPtr mPtr = MultimediaPtr(new Video(name, fileName, duration));
    this->multimedia[name] = mPtr;
    return mPtr;
}

MultimediaPtr MyBase::createFilm(string name, string fileName, int duration, int *ptrDurations, int numDurations) {
    MultimediaPtr mPtr = MultimediaPtr(new Film(name, fileName, duration, ptrDurations, numDurations));
    this->multimedia[name] = mPtr;
    return mPtr;
}

GroupPtr MyBase::createGroup(string name) {
    GroupPtr gPtr = GroupPtr(new Group(name));
    this->group[name] = gPtr;
    return gPtr;
}

void MyBase::addToGroup(string mName, string pName) {
    this->group.find(pName)->second->push_back(this->multimedia.find(mName)->second);
}

void MyBase::print(string name) const {
    if(this->multimedia.find(name) != this->multimedia.end()) {
        this->multimedia.find(name)->second->print(cout);
    } else if(this->group.find(name) != this->group.end()) {
        this->group.find(name)->second->print(cout);
    } else {
        cerr << "--->Error: No multimedia object or group with name \"" + name + "\" exist!" << endl;
    }
}

void MyBase::play(string name) const {
    if(this->multimedia.find(name) != this->multimedia.end()) {
        this->multimedia.find(name)->second->play();
    } else {
        cerr << "--->Error: No multimedia object with name \"" + name + "\" exist for playing!\n" << endl;
    }
}

void MyBase::remove(string name) {
    if(this->group.find(name) != this->group.end()) {
        this->group.find(name)->second.reset();
        this->group.erase(this->group.find(name));
        cout << "--->Group \"" + name + "\" is deleted!" << endl;
    } else if(this->multimedia.find(name) != this->multimedia.end()) {
        MultimediaPtr mPtr = this->multimedia.find(name)->second;
        for(GroupMap::iterator it = this->group.begin(); it != this->group.end(); it++) {
            it->second->remove(mPtr);
        }
        mPtr.reset();
        this->multimedia.find(name)->second.reset();
        this->multimedia.erase(this->multimedia.find(name));
        cout << "--->Multimedia \"" + name + "\" is deleted!" << endl;
    } else {
        cerr << "--->Error: No multimedia object or group with name \"" + name + "\" exist!" << endl;
    }
}
