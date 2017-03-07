#ifndef CA_CA_CELL_H_
#define CA_CA_CELL_H_

namespace ca {
  class Cell {
  public:
    bool IsAlive(int step) const;
    void SetLife(bool is_alive);
    void ToNextStep(int neighbors_count);

  private:
    int step_ = 0;
    bool state_ = false;
    bool previous_state_ = false;
  };
}

#endif // CA_CA_CELL_H_
