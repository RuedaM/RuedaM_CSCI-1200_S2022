#include <iostream>
#include <string>
#include <vector>


#ifndef _movie_data_h
#define _movie_data_h

typedef std::string str;
typedef std::vector<str> strvec;

class MOVIE_DATA {
public:
	// CONSTRUCTOR
	MOVIE_DATA() {
		title="_UNTITLED"; year=0; runtime=0;
		GenreCount=0; ActorCount=0; RoleCount=0;
	}
	MOVIE_DATA(str t, int y, int rt, int gct, strvec gl, int act, strvec al, int rct, strvec rl) {
		title=t;   year=y;   runtime=rt;
		GenreCount=gct;  ActorCount=act;  RoleCount=rct;
		GenreList=gl;  ActorList=al;  RoleList=rl;
	}

	// REPRESENTATION VARIABLES
	str title;
	int year, runtime, GenreCount, ActorCount, RoleCount;
	strvec GenreList, ActorList, RoleList;
};

#endif