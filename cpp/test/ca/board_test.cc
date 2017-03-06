#include "ca/board.h"
#include <iostream>
#include "../test_helper.h"
#include <string>

class BoardTest : public ::testing::Test {
 protected:
  ca::Board b = ca::Board(3, 3);
};

TEST_F(BoardTest, Board) {
  EXPECT_EQ(b.ToString(), "___\n___\n___\n");
  EXPECT_FALSE(b.IsCellAlive(1, 1));

  b.ToNextStep();
  EXPECT_EQ(b.ToString(), "___\n___\n___\n");
  EXPECT_FALSE(b.IsCellAlive(1, 1));

  b.MakeCellAlive(0, 0);
  b.MakeCellAlive(0, 1);
  b.MakeCellAlive(2, 2);
  EXPECT_EQ(b.ToString(), "O__\nO__\n__O\n");
  EXPECT_FALSE(b.IsCellAlive(1, 1));

  b.ToNextStep();
  EXPECT_EQ(b.ToString(), "___\n_O_\n___\n");
  EXPECT_TRUE(b.IsCellAlive(1, 1));

  b.ToNextStep();
  EXPECT_EQ(b.ToString(), "___\n___\n___\n");
  EXPECT_FALSE(b.IsCellAlive(1, 1));

  b.MakeCellAlive(0, 0);
  b.MakeCellAlive(1, 1);
  b.MakeCellAlive(0, 1);
  EXPECT_EQ(b.ToString(), "O__\nOO_\n___\n");
  EXPECT_TRUE(b.IsCellAlive(1, 1));

  b.ToNextStep();
  EXPECT_EQ(b.ToString(), "OO_\nOO_\n___\n");
  EXPECT_TRUE(b.IsCellAlive(1, 1));

  b.ToNextStep();
  EXPECT_EQ(b.ToString(), "OO_\nOO_\n___\n");
  EXPECT_TRUE(b.IsCellAlive(0, 0));
}
