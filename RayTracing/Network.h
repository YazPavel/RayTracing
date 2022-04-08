#pragma once
#include "Geometry.h"
#include "Params.h"

class Network :
    public Geometry
{
private:

public:
    Network(const Params& parameters);
    const std::vector<std::vector<std::vector<bool>>>& GetMask() const override;
    double GetPixelSize() const override;
};

