#ifndef SRC_GUY_H_
#define SRC_GUY_H_

class guy {
 public:
    guy(int x_cord, int y_cord);
    // virtual ~guy() = default;

    // Coordinates
    int get_x_cord() { return _x_cord; }
    int get_y_cord() { return _y_cord; }
    void set_x_cord(const int &x) { _x_cord = x; }
    void set_y_cord(const int &y) { _y_cord = y; }

    // Velocity
    int get_x_velo() { return _x_velo; }
    int get_y_velo() { return _y_velo; }
    void set_x_velo(const int &x) { _x_velo = x; }
    void set_y_velo(const int &y) { _y_velo = y; }
 private:
    int _x_cord, _y_cord;
    int _x_velo, _y_velo;
};

#endif  // SRC_GUY_H_
