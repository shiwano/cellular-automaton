#ifndef CA_CA_TABLE_H_
#define CA_CA_TABLE_H_

#include <vector>
#include <memory>
#include "./cell.h"
#include <string>

namespace ca {
  typedef std::vector<std::unique_ptr<Cell>> Cells;

  class Board {
  public:
    explicit Board(int width, int height);
    bool IsCellAlive(int x, int y);
    void MakeCellAlive(int x, int y);
    void ToNextStep();
    int Step();
    const std::string & ToString();
  private:
    const char kCellChar = 'O';
    const char kBlankChar = '_';

    int step_ = 0;
    int width_ = 0;
    int height_ = 0;
    Cells cells_;
    std::string cells_as_str;

    int CountAliveNeighbors(int x, int y);
  };
}

#endif  // CA_CA_TABLE_H_
