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
    std::vector<Rod> rod_list;
    int N_edges;
    std::vector<std::vector<std::vector<bool>>> Mask;
    double voxel_size;
    double length_mean;
    Eigen::Vector3d network_center;
public:
    Network(const Params& parameters);
    const std::vector<std::vector<std::vector<bool>>>& GetMask() const override;
    double GetPixelSize() const override;
private:
    void normalise(); // move network to 0 and put <L>=1
    void rescale(double scale); //  put <L>=Ltarget
    void createMask(const int& resolution_);
    void SetResolution(const int& resolution_);
    void calculateMean();
};


