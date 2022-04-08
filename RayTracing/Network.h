#pragma once
#include "Geometry.h"
#include "Params.h"
#include "Eigen/Eigen/Dense"


class Rod {
private:
    double radius;
    Eigen::Vector3d vertex1;
    Eigen::Vector3d vertex2;
    friend class Network;
    friend std::istream& operator>>(std::istream& input, Rod& rod);
};


class Network : public Geometry
{
private:
    std::vector<Rod> edge_list;
    int N_edges;
    std::vector<std::vector<std::vector<bool>>> Mask;
    double voxel_size;

public:
    Network(const Params& parameters);
    const std::vector<std::vector<std::vector<bool>>>& GetMask() const override;
    double GetPixelSize() const override;
};

