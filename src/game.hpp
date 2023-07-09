#include <boost/asio.hpp>

namespace flappyBird {
    struct GameInfo
    {
        int WIDTH; 
        int HEIGHT;
    };
    

    class Game {
        public:
            Game(GameInfo gameInfo);
            ~Game(){};
        private:

    };
}