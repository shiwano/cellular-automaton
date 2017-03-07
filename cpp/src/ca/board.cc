#include "./board.h"

namespace ca {
  Board::Board(int width, int height) {
    width_ = width;
    height_ = height;

    auto cells_length = width_ * height_;
    cells_ = Cells(cells_length);
    for (int i = 0; i < cells_length; ++i) {
      std::unique_ptr<Cell> cell(new Cell());
      cells_[i] = std::move(cell);
    }

    cells_as_str_ = std::string(cells_length + height_, kBlankChar);
    for (int i = 0; i < height; ++i) {
      cells_as_str_[(i + 1) * width_ + i] = '\n';
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
    cells_as_str_[x + width_ * y + y] = kCellChar;
  }

  void Board::ToNextStep() {
    for (int i = 0; i < cells_.size(); ++i) {
      auto x = i % width_;
      auto y = i / width_;
      auto neighbors_count = CountAliveNeighbors(x, y);
      cells_[i]->ToNextStep(neighbors_count);

      cells_as_str_[i + y] = cells_[i]->IsAlive(step_ + 1) ?  kCellChar : kBlankChar;
      if (x == width_ - 1) {
        cells_as_str_[i + y + 1] = '\n';
      }
    }
    ++step_;
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
