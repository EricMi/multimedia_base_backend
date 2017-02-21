//***************************************************************************************
//
//! @file Photo.h
//! La specification et l'implementation de la class Photo dérivant de Multimedia.
//!
//! @author    Pengfei Mi
//! @date      2016-11
//
//***************************************************************************************

#ifndef PHOTO_H
#define PHOTO_H

#include "Multimedia.h"
using namespace std;

/**
 * @class Photo header-file Photo.h
 * @brief
 * La class Photo dérivant de Multimedia.
 * Ses objets sont des photos.
 * @see Multimedia
 */
class Photo : public Multimedia {
	friend class MyBase;
	friend class Group;
private:
	int width = 0; /**La largeur de la photo.*/
	int height = 0; /**La longeur de la photo.*/
protected:
	// constructor
	Photo(string n = "", string f = "", int w = 0, int h = 0) : Multimedia(n, f) {
		this->setWidth(w);
		this->setHeight(h);
	};

	// function: get the width of photo.
	int getWidth() const {
		return this->width;
	};

	// function: set the width of photo.
	void setWidth(int w) {
		this->width = w;
	};

	// function: get the height of photo.
	int getHeight() const {
		return this->height;
	};

	// function: set the height of photo.
	void setHeight(int h) {
		this->height = h;
	};

	// function: print the information of photo.
	void print(ostream &os) const override {
		this->Multimedia::print(os);
		os << "Width:" << this->getWidth() << '\n'
			<< "Height:" << this->getHeight() << endl;
	};

	// function: play the photo.
	void play() const override {
		string command;
		#ifdef __APPLE__
			command = "open ";
		#elif __linux__
			command = "eog ";
		#elif __unix__
			command = "imagej "
		#else
		    cerr << "--->Error: unknown compiler."
		#endif
		command += this->getFileName() + " &";
		system(command.c_str());
	};

	// virtual function: write object to ostream.
	void write(ostream &os) const override {
		Multimedia::write(os);
		os << this->getWidth() << '\n' << this->getHeight() << '\n';
	};

	// virtual function: read object from istream.
	void read(istream &is) override {
		this->Multimedia::read(is);
		string s;
		getline(is, s);
		this->setWidth(stoi(s));
		getline(is, s);
		this->setHeight(stoi(s));
	};

	// virtual function: return class name.
	string className() const override {
		return "Photo";
	};
};

#endif // !PHOTO_H
