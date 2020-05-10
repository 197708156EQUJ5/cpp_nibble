#include "nibbles/level_factory.hpp"

namespace nibbles {

Level LevelFactory::createLevel1() {
    Level level;
    return level;
}

Level LevelFactory::createLevel2() {
    Wall wall{Location{20, 20}, 50, false};
    Level level;
    level.walls.push_back(wall);

    return level;
}

Level LevelFactory::createLevel3() {
    Wall wall{Location{20, 15}, 50, false};
    Level level;
    level.walls.push_back(wall);

    return level;
}

Level LevelFactory::createLevel4() {
    Wall wall{Location{20, 15}, 50, false};
    Level level;
    level.walls.push_back(wall);

    return level;
}

} // namespace nibbles

