#include <MusicBeatDetector/Utils/Data/ShiftRegister.h>

#include <gtest/gtest.h>

#include <string>

using namespace introlab;
using namespace std;

TEST(ShiftRegisterTests, construtor_size_shouldAllocateMemory)
{
    constexpr std::size_t Size = 3;

    ShiftRegister<string> shiftRegister(Size);

    EXPECT_EQ(shiftRegister.size(), Size);
    EXPECT_EQ(shiftRegister[0], "");
    EXPECT_EQ(shiftRegister[1], "");
    EXPECT_EQ(shiftRegister[2], "");
}

TEST(ShiftRegisterTests, construtor_initializerList_shouldAllocateMemoryAndCopyTheData)
{
    ShiftRegister<int> shiftRegister({1, 2, 3});

    EXPECT_EQ(shiftRegister.size(), 3);
    EXPECT_EQ(shiftRegister[0], 3);
    EXPECT_EQ(shiftRegister[1], 2);
    EXPECT_EQ(shiftRegister[2], 1);
}

TEST(ShiftRegisterTests, copyConstrutor_shouldCopy)
{
    ShiftRegister<int> shiftRegister({1, 2, 3});
    ShiftRegister<int> copy(shiftRegister);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 3);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 1);

    EXPECT_EQ(shiftRegister.size(), 3);
    EXPECT_EQ(shiftRegister[0], 3);
    EXPECT_EQ(shiftRegister[1], 2);
    EXPECT_EQ(shiftRegister[2], 1);
}

TEST(ShiftRegisterTests, moveConstructor_shouldMove)
{
    ShiftRegister<int> shiftRegister({1, 2, 3});
    ShiftRegister<int> movedShiftRegister(move(shiftRegister));

    EXPECT_EQ(movedShiftRegister.size(), 3);
    EXPECT_EQ(movedShiftRegister[0], 3);
    EXPECT_EQ(movedShiftRegister[1], 2);
    EXPECT_EQ(movedShiftRegister[2], 1);

    EXPECT_EQ(shiftRegister.size(), 0);
}

TEST(ShiftRegisterTests, assignationOperator_shouldCopy)
{
    ShiftRegister<int> shiftRegister({1, 2, 3});
    ShiftRegister<int> copy(5);
    copy = shiftRegister;

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 3);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 1);

    EXPECT_EQ(shiftRegister.size(), 3);
    EXPECT_EQ(shiftRegister[0], 3);
    EXPECT_EQ(shiftRegister[1], 2);
    EXPECT_EQ(shiftRegister[2], 1);
}

TEST(ShiftRegisterTests, moveAssignationOperator_shouldMove)
{
    ShiftRegister<int> shiftRegister({1, 2, 3});
    ShiftRegister<int> movedShiftRegister(5);
    movedShiftRegister = move(shiftRegister);

    EXPECT_EQ(movedShiftRegister.size(), 3);
    EXPECT_EQ(movedShiftRegister[0], 3);
    EXPECT_EQ(movedShiftRegister[1], 2);
    EXPECT_EQ(movedShiftRegister[2], 1);

    EXPECT_EQ(shiftRegister.size(), 0);
}

TEST(ShiftRegisterTests, shift_shouldAddANewValue)
{
    ShiftRegister<int> shiftRegister({0, 0, 0});

    shiftRegister.shift(1);
    EXPECT_EQ(shiftRegister.size(), 3);
    EXPECT_EQ(shiftRegister[0], 1);
    EXPECT_EQ(shiftRegister[1], 0);
    EXPECT_EQ(shiftRegister[2], 0);

    shiftRegister.shift(2);
    EXPECT_EQ(shiftRegister.size(), 3);
    EXPECT_EQ(shiftRegister[0], 2);
    EXPECT_EQ(shiftRegister[1], 1);
    EXPECT_EQ(shiftRegister[2], 0);

    shiftRegister.shift(3);
    EXPECT_EQ(shiftRegister.size(), 3);
    EXPECT_EQ(shiftRegister[0], 3);
    EXPECT_EQ(shiftRegister[1], 2);
    EXPECT_EQ(shiftRegister[2], 1);

    shiftRegister.shift(4);
    EXPECT_EQ(shiftRegister.size(), 3);
    EXPECT_EQ(shiftRegister[0], 4);
    EXPECT_EQ(shiftRegister[1], 3);
    EXPECT_EQ(shiftRegister[2], 2);
}
