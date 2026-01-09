/*
Line -> Point
*/
#include <vector> 
#include <iostream>

struct Point {
    int x, y;
};

struct Line {
    Point start, end;
    Line(Point start, Point end): start(start), end(end) 
    { }
};

class LineToPointAdapter {
    
    bool line_vertical;
    int sX;
    int fX;
    int sY;
    int fY;
    
    public:
    LineToPointAdapter(const Line& line): 
        line_vertical { false },
        sX {std::min(line.start.x, line.end.x)},
        fX {std::max(line.start.x, line.end.x)},
        sY {std::min(line.start.y, line.end.y)},
        fY {std::max(line.start.y, line.end.y)}
    {
        // ONLY vertical or horizontal allowed

        int dx = fX - sX;
        int dy = fY - sY;
        
        if (dx == 0) 
        {
            line_vertical = true;
        }
        /*
        if Vertical then start point = x, y and add -1 to x 
        */
    }

    class iterator {
        int offset;
        LineToPointAdapter* adapter;
        public: iterator(LineToPointAdapter* adapter): offset {0}, adapter { adapter } 
        { 

        }
        Point operator++() {
            return next();
        }

        Point next() 
        {
            Point ret;
            if (adapter->line_vertical)
            {
                ret.x = adapter->sX;
                ret.y = adapter->sY + offset;
            }
            else 
            {
                ret.x = adapter->sX + offset;
                ret.y = adapter->sY;
            }

            offset++;
            return ret;
            
        }
        
        bool hasNext()
        {
            if (adapter->line_vertical)
            {
                return adapter->sY + offset <= adapter->fY;
            }
            return adapter->sX + offset <= adapter->fX;
        }

    };

    iterator begin() {
        return iterator(this);
    }
    


};

int main() {
    Line line { Point {1, 10}, Point {15, 10} };
    LineToPointAdapter adapter(line);
    for (auto it = adapter.begin(); it.hasNext(); ) {
        auto point = it.next();
        std::cout << "Point: " << point.x << ", " << point.y << std::endl;
    }
}