#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "utilities.h"



#ifndef polygons_h_
#define polygons_h_

class Polygon {
	public:
		Polygon(const std::string _name, const std::vector<Point> _pts) : name(_name), pts(_pts) {}
		virtual ~Polygon(){}


		std::string getName() {return name;}
		bool HasAllEqualSides() {

			std::vector<double> distances;
			for(int i=0 ; i<(int)pts.size()-1; ++i) {
				distances.push_back(DistanceBetween(pts[i], pts[i+1]));
			}
			distances.push_back(DistanceBetween(pts[pts.size()-1],pts[0]));
			
			for (int i=0; i<(int)distances.size() ; ++i) {
				if (!EqualSides(distances[0], distances[i])) {return false;}
			}
			return true;
		}
		bool HasAllEqualAngles() {

			std::vector<double> angles;
			for(int i=0 ; i<(int)pts.size()-2; ++i) {
				angles.push_back(Angle(pts[i], pts[i+1], pts[i+2]));
			}
			angles.push_back(Angle(pts[pts.size()-2],pts[pts.size()-1], pts[0]));
			angles.push_back(Angle(pts[pts.size()-1],pts[0], pts[1]));
			
			for (int i=0; i<(int)angles.size() ; ++i) {
				if (!EqualAngles(angles[0], angles[i])) {return false;}
			}
			return true;
		}
		bool HasARightAngle() {
			std::vector <double> angles;
			for (int i=0 ; i<(int)pts.size()-2 ; ++i) {
				try {angles.push_back(Angle(pts[i],pts[i+1],pts[i+2]));}
				catch(std::string) {throw 3;}
			}
			try {
				angles.push_back(Angle(pts[pts.size()-2],pts[pts.size()-1],pts[0]));
				angles.push_back(Angle(pts[pts.size()-1],pts[0],pts[1]));
			}
			catch(std::string) {throw 3;}

			for (int i=0 ; i<(int)angles.size() ; ++i){
				if (RightAngle(angles[i])) {return true;}
			}
			return false;
		}

	protected:
		std::string name;
		std::vector<Point> pts;
};


class Triangle : public Polygon {
	public:
		Triangle(const std::string _name, const std::vector<Point> _pts) : Polygon(_name, _pts) {
			if (pts.size()!=3) {throw 42;}
		}
};


class IsoscelesTriangle : public virtual Triangle {
	public:
		IsoscelesTriangle(const std::string _name, const std::vector<Point> _pts) : Triangle(_name, _pts) {
			if (!(EqualSides(DistanceBetween(pts[0], pts[1]), DistanceBetween(pts[1], pts[2]))
			   || EqualSides(DistanceBetween(pts[1], pts[2]), DistanceBetween(pts[2], pts[0]))
			   || EqualSides(DistanceBetween(pts[2], pts[0]), DistanceBetween(pts[0], pts[1])))) {throw 42;}
			// WHICH TO DO? OR DOES IT MATTER?
			if (!(EqualAngles(Angle(pts[0], pts[1], pts[2]), Angle(pts[1], pts[2], pts[0]))
			   || EqualAngles(Angle(pts[1], pts[2], pts[0]), Angle(pts[2], pts[0], pts[1]))
			   || EqualAngles(Angle(pts[2], pts[0], pts[1]), Angle(pts[0], pts[1], pts[2])))) {throw 42;}
		}
};


class RightTriangle : public virtual Triangle {
	public:
		RightTriangle(const std::string _name, const std::vector<Point> _pts) : Triangle(_name, _pts) {
			if (!HasARightAngle()) {throw 42;}
		}
};

class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle {
	public:
		IsoscelesRightTriangle(const std::string _name, const std::vector<Point> _pts) : Triangle(_name, _pts), IsoscelesTriangle(_name, _pts), RightTriangle(_name, _pts) {}
};


class EquilateralTriangle : public IsoscelesTriangle {
	public:
		EquilateralTriangle(const std::string _name, const std::vector<Point> _pts) : Triangle(_name, _pts), IsoscelesTriangle(_name, _pts) {
			if (!(HasAllEqualSides())) {throw 42;}
		}
};


class Quadrilateral : public Polygon {
	public:
		Quadrilateral(const std::string _name, const std::vector<Point> _pts) : Polygon(_name, _pts) {
			if (pts.size()!=4) {throw 42;}
		}
};


class Trapezoid : public virtual Quadrilateral {
	public:
		Trapezoid(const std::string _name, const std::vector<Point> _pts) : Quadrilateral(_name, _pts) {}
};


class Kite : public virtual Quadrilateral {
	public:
		Kite(const std::string _name, const std::vector<Point> _pts) : Quadrilateral(_name, _pts) {}
};


class Parallelogram : public Trapezoid {
	public:
		Parallelogram(const std::string _name, const std::vector<Point> _pts) : Quadrilateral(_name, _pts), Trapezoid(_name, _pts) {}
};


class Rectangle : public virtual Parallelogram {
	public:
		Rectangle(const std::string _name, const std::vector<Point> _pts) : Quadrilateral(_name, _pts), Parallelogram(_name, _pts) {
			if (!RightAngle(Angle(pts[0], pts[1], pts[2]))
			 || !RightAngle(Angle(pts[1], pts[2], pts[3]))
			 || !RightAngle(Angle(pts[2], pts[3], pts[0]))
			 || !RightAngle(Angle(pts[3], pts[0], pts[1]))) {throw 42;}
			// WHICH TO DO? OR DOES IT MATTER?
			if (!Parallel(Vector(pts[0], pts[1]), Vector(pts[2], pts[3])) 
			 || !Parallel(Vector(pts[1], pts[2]), Vector(pts[3], pts[0]))) {throw 42;}
		}
};


class Rhombus : public virtual Parallelogram, public Kite {
	public:
		Rhombus(const std::string _name, const std::vector<Point> _pts) : Quadrilateral(_name, _pts), Parallelogram(_name, _pts), Kite(_name, _pts) {}
};


class Square : public Rectangle, public Rhombus {
	public:
		Square(const std::string _name, const std::vector<Point> _pts) : Quadrilateral(_name, _pts), Parallelogram(_name, _pts), Rectangle(_name, _pts), Rhombus(_name, _pts) {
			if (!(HasAllEqualSides())) {throw 42;}
		}
};


#endif