#include "ca/cell.h"
#include "../test_helper.h"
#include <random>

TEST(CellTest, Cell) {
  ca::Cell c;

  EXPECT_EQ(false, c.IsAlive(0));
  c.SetLife(true);
  EXPECT_EQ(true, c.IsAlive(0));
  c.SetLife(false);
  EXPECT_EQ(false, c.IsAlive(0));

  c.ToNextStep(3);
  EXPECT_EQ(true, c.IsAlive(1));
  c.ToNextStep(2);
  EXPECT_EQ(true, c.IsAlive(2));

  std::random_device rand;
  std::mt19937 mt(rand());
  std::uniform_int_distribution<int> rand4_8(4, 8);
  std::uniform_int_distribution<int> rand0_1(0, 1);

  c.ToNextStep(rand4_8(mt));
  EXPECT_EQ(false, c.IsAlive(3));

  c.ToNextStep(rand0_1(mt));
  EXPECT_EQ(false, c.IsAlive(3));
}
