
namespace flappyBird {
    struct GameInfo
    {
        int WIDTH; 
        int HEIGHT;
        int BirdPosition;
        int BirdSize;
        double BirdVelocity;
    };

    class Game {
        public:
            Game(GameInfo GameInfo);
            ~Game(){};
        private:
        GameInfo gameInfo;
        void GameLoop();
        void runTick();
    };
}