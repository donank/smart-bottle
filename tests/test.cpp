#include <gtest/gtest.h>
#include "../main/ph/ph.h"
#include "../main/volume/volume.h"
#include "../main/turbidity/turbidity.h"
#include "../main/temperature/temperature.h"
#include "ads1115rpi.h"

TEST(PHTest, TypeTest) {
    ph* ph;
    ph->setData(7);
    ph->calcThreshold();
    EXPECT_STRNE(ph->getType(), "BASE");
    EXPECT_STRE(ph->getType(), "BASE");
    EXPECT_STRNE(ph->getType(), "ACID");
    EXPECT_STRNE(ph->getType(), "NEUTRAL");
}

TEST(PHTest2, TypeTest) {
    ph* ph;
    ph->setData(0.1);
    ph->calcThreshold();
    EXPECT_STRE(ph->getType(), "ACID");
}

TEST(VolumeTest, WaterDetectionTest) {
    volume* vm;
    vm->setData(0.2);
    vm->calcThreshold();
    ASERT_EQ(ph->waterDetected(), true);
}

TEST(VolumeTest2, WaterDetectionTest) {
    volume* vm;
    vm->setData(7);
    vm->calcThreshold();
    ASERT_EQ(ph->waterDetected(), true);
}

TEST(TurbidityTest, TypeTest) {
    turbidity* tb;
    tb->setData(0.1);
    tb->calcThreshold();
    EXPECT_STRE(tb->getType(), "OPAQUE");
}

TEST(TurbidityTest2, TypeTest) {
    turbidity* tb;
    tb->setData(7);
    tb->calcThreshold();
    EXPECT_STRE(tb->getType(), "TRANSPARENT");
}

TEST(TemperatureTest, TypeTest) {
    temperature* tp;
    tp->setData(7);
    tp->calcThreshold();
    EXPECT_STRNE(tp->getType(), "HOT");
}

TEST(TemperatureTest2, TypeTest) {
    temperature* tp;
    tp->setData(7);
    tp->calcThreshold();
    EXPECT_STRNE(tp->getType(), "COLD");
}