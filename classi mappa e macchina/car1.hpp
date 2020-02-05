#include "map.hpp"

class car1 {
protected:
    int x1;
    int y1;
    int x2;
    int y2;
public:
    car1();
    void appear(map *);
    void disappear(map *);
    void moveleft(map *);
    void moveright(map *);
};


