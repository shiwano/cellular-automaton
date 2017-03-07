#include "./cell.h"

namespace ca {
  bool Cell::IsAlive(int step) const {
    return step_ == step ? state_ : previous_state_;
  }

  void Cell::SetLife(bool is_alive) {
    state_ = is_alive;
  }

  void Cell::ToNextStep(int neighbors_count) {
    previous_state_ = state_;
    if (neighbors_count == 3) {
      state_ = true;
    } else if (neighbors_count != 2) {
      state_ = false;
    }
    ++step_;
  }
}
