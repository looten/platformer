#ifndef SRC_GUY_H_
#define SRC_GUY_H_

class guy {
 public:
    guy(int x, int y);
    // virtual ~guy() = default;
    int get_x_cord() { return _x_cord; }
    int get_y_cord() { return _y_cord; }
    void set_x_cord(const int &x) { _x_cord = x; }
    void set_y_cord(const int &y) { _y_cord = y; }
 private:
    void input();
    int _x_cord;
    int _y_cord;
};

#endif  // SRC_GUY_H_
