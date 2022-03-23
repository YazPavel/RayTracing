#include "pch.h"

#include "../RayTracing/PhotonicBall.h"


TEST(PhotonicBalltest, ConstructorSingleNP) {
	PhotonicBall PB=PhotonicBall::PhotonicBall("PBsingleNP.txt", 100);
	EXPECT_DOUBLE_EQ(100, PB.GetFeret_radius());
}
