#include "./board.h"

namespace ca {
  Board::Board(int width, int height) {
    width_ = width;
    height_ = height;

    auto cellsLength = width_ * height_;
    cells_ = Cells(cellsLength);
    for (int i = 0; i < cellsLength; ++i) {
      std::unique_ptr<Cell> cell1(new Cell());
      cells_[i] = std::move(cell1);
    }

    cells_as_str = std::string(cellsLength + height_, kBlankChar);
    for (int i = 0; i < height; ++i) {
      cells_as_str[(i + 1) * width_ + i] = '\n';
    }
  }

  bool Board::IsCellAlive(int x, int y) {
    if (x < 0 || x >= width_) { return false; }
    if (y < 0 || y >= height_) { return false; }
    return cells_[x + width_ * y]->IsAlive(step_);
  }

  void Board::MakeCellAlive(int x, int y) {
    if (x < 0 || x >= width_) { return; }
    if (y < 0 || y >= height_) { return; }
    cells_[x + width_ * y]->SetLife(true);
    cells_as_str[x + width_ * y + y] = kCellChar;
  }

  int Board::Step() { return step_; }

  void Board::ToNextStep() {
    for (int i = 0; i < cells_.size(); ++i) {
      auto x = i % width_;
      auto y = i / width_;
      auto neighbors_count = CountAliveNeighbors(x, y);
      cells_[i]->ToNextStep(neighbors_count);

      cells_as_str[i + y] = cells_[i]->IsAlive(step_ + 1) ?  kCellChar : kBlankChar;
      if (x == width_ - 1) {
        cells_as_str[i + y + 1] = '\n';
      }
    }
    ++step_;
  }

  const std::string & Board::ToString() {
    return cells_as_str;
  }

  int Board::CountAliveNeighbors(int x, int y) {
    int result = 0;
    for (int i = -1; i < 2; ++i) {
      for (int j = -1; j < 2; ++j) {
        if (i == 0 && j == 0) {
          continue;
        }
        if (IsCellAlive(x + i, y + j)) {
          ++result;
        }
      }
    }
    return result;
  }
}
