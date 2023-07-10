
namespace flappyBird {
    struct GameInfo
    {
        int WIDTH; 
        int HEIGHT;
        int BirdPosition;
        int BirdSize;
        double BirdVelocity;
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
        GameInfo gameInfo;
        void DrawSquare(Point start, int width, int height);
        void GameLoop();
        void runTick();
    };
}