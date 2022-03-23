#include "pch.h"

#include "pch.h"
#include "../RayTracing/GeneralFun.h"



void compare2vec(std::vector<double> vec1, std::vector<double> vec2) {
	EXPECT_EQ(vec1.size(), vec2.size());
	for (size_t i = 0; i < vec1.size(); i++) {
		EXPECT_DOUBLE_EQ(vec1[i], vec2[i]);
	}
}

TEST(Linspace, VectorOf5) {
	std::vector<double> vec1 = { 0,1,2,3,4,5 };
	std::vector<double> vec2 = GenFunc::linspace(0, 5, 6);
	compare2vec(vec1, vec2);
}

TEST(Linspace, VectorOf5double) {
	std::vector<double> vec1 = { 0.0 ,0.2,0.4,0.6,0.8,1 };
	std::vector<double> vec2 = GenFunc::linspace(0, 1, 6);
	compare2vec(vec1, vec2);
}

TEST(Linspace, VectorOf5negative) {
	std::vector<double> vec1 = { -2,-1,0,1,2, };
	std::vector<double> vec2 = GenFunc::linspace(-2, 2, 5);
	EXPECT_EQ(vec1, vec2);
	//EXPECT_TRUE(true);
}

TEST(Linspace, Single) {
	std::vector<double> vec1 = { 3.2 };
	std::vector<double> vec2 = GenFunc::linspace(3.2, 3.5, 1);
	compare2vec(vec1, vec2);
}

TEST(Linspace, Empty) {
	std::vector<double> vec1;
	std::vector<double> vec2 = GenFunc::linspace(3.2, 3.5, 0);
	compare2vec(vec1, vec2);
}

TEST(Linspace, Inverted) {
	std::vector<double> vec1 = { 1, 0, -1, -2 };
	std::vector<double> vec2 = GenFunc::linspace(1, -2, 4);
	compare2vec(vec1, vec2);
}



TEST(RotMatrix, Zero) {
	Eigen::Matrix3d m1;
	m1 << 1, 0, 0,
		0, 1, 0,
		0, 0, 1;
	Eigen::Matrix3d m2 = GenFunc::rotationMatrix(0, { 0,0,1 });
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_DOUBLE_EQ(m1(i, j), m2(i, j));
		}
	}
}

TEST(RotMatrix, pi_2) {
	const double pi = 3.14159265358979323846;
	Eigen::Matrix3d m1;
	m1 << 0, -1, 0,
		1, 0, 0,
		0, 0, 1;
	Eigen::Matrix3d m2 = GenFunc::rotationMatrix(pi / 2, { 0,0,1 });
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_NEAR(m1(i, j), m2(i, j), 1e-14);
		}
	}
}
