#include <boost/asio.hpp>

namespace flappyBird {
    struct GameInfo
    {
        int WIDTH; 
        int HEIGHT;
    };
    
    struct Point {
        int x;
        int y;
    };

    class Game {
        public:
            Game(GameInfo GameInfo);
            ~Game(){};
        private:
        void DrawSquare(Point start, int width, int height);
        GameInfo gameinfo;

    };
}