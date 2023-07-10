#include "../Drawer/drawer.hpp"

namespace flappyBird {
    struct GameInfo
    {
        Window ClientWindow;
        int BirdPosition;
        int BirdSize;
        double BirdVelocity;
    };

    class Game {
        public:
            Game(GameInfo GameInfo);
            void RunTick();
            ~Game(){};
        private:
            GameInfo gameInfo;
            void GameLoop();
    };
}