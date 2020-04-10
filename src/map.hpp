#ifndef SRC_MAP_H_
#define SRC_MAP_H_

class map {
 public:
    map(int height, int width);
    int get_height_cord() { return _height_cord; }
    int get_width_cord() { return _width_cord; }
    void set_height_cord(const int &height) { _height_cord = height; }
    void set_width_cord(const int &width) { _width_cord = width; }
 private:
    int _height_cord;
    int _width_cord;
};

#endif  // SRC_MAP_H_
