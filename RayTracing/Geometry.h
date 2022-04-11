#pragma once
#include <vector>

class Geometry {
public:
	virtual const std::vector<std::vector<std::vector<bool>>>& GetMask() const = 0;
	virtual double GetPixelSize() const = 0;
	//virtual void random_rotation() = 0;
};