#pragma once
#include <vector>

class Geometry {
protected:
	int res_x;
	int res_y;
	int res_z;
	virtual void SetResolution(int resolution_) = 0;
public:
	virtual const std::vector<std::vector<std::vector<bool>>>& GetMask() const = 0;
	virtual double GetPixelSize() const = 0;
	int GetResolutionX() const;
	int GetResolutionY() const;
	int GetResolutionZ() const;
};