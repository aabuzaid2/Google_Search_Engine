#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include<time.h>

using namespace std;

//add destructors for both classes with go through the whole hash table and delete all the information

class website {
private:
	
public:
	website();
	website(string);
	string name;
	vector<string> inlinks;
	vector<string> outlinks;
	vector<string> keywords;
	website* collisions;
	int impressions;
	int clicks;
	double p_rank;
	double pscore;
	~website();
};



website::website() {	//should never occur but only implemented it to avoid error
	name = "none";
	collisions = NULL;
	impressions = 0;
	clicks = 0;
	p_rank = 0;
}

website::website(string websitename) {
	name = websitename;
	collisions = NULL;
	impressions = 0;
	clicks = 0;
}

website::~website() {
	collisions = NULL;
	outlinks.clear();
	inlinks.clear();
	keywords.clear();
}

class keyword {
private:

public:
	keyword();
	keyword(string);
	string word;
	vector<string> websites;
	keyword* collisions;
	~keyword();
};

keyword::keyword() {
	word = "none";
	collisions = NULL;
}

keyword::keyword(string name) {
	word = name;
	collisions = NULL;
}

keyword::~keyword() {
	collisions = NULL;
}
