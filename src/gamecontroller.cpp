#include "gamecontroller.hpp"

GameController::GameController(QObject *parent)
    : m_score{0}
    , QObject{parent} {
    readMap(":/pacman/assets/mazeMap.txt");
    readObjects(":/pacman/assets/objectsMap.txt");
    setGameStatus(GameController::PAUSE);
    pacmanTimer = new QTimer(this);
    connect(pacmanTimer, &QTimer::timeout, this, &GameController::pacmanHandler);
}

GameController::~GameController() {
    for (int i = 0; i < MAPVERTICALBLOCKS; ++i) {
        qDeleteAll(m_gameMazeObjects[i]);
        m_gameMazeObjects[i].clear();
        qDeleteAll(m_gameObjects[i]);
        m_gameObjects[i].clear();
    }
    m_gameMazeObjects.clear();
    m_gameObjects.clear();
    delete pacmanTimer;
}

void GameController::readMap(const QString &map) {
    m_gameMazeObjects.clear();
    QFile mapFile{map};
    mapFile.open(QIODevice::ReadOnly | QIODevice::Text);
    int map_y = 0;
    int ghost_id = 1;
    for (int i = 0; i < MAPVERTICALBLOCKS; ++i) {
        QByteArray mapLine = mapFile.readLine();
        QList<GameObject *> gameMazeObjectsRow;
        int map_x = 0;
        for (int j = 0; j < MAPHOZIRONTALBLOCKS; ++j) {
            switch (static_cast<int>(mapLine[j])) {
                case GameObject::FLOOR: {
                    GameObject *gameObject = new GameObject{GameObject::FLOOR, this};
                    gameObject->setX(map_x);
                    gameObject->setY(map_y);
                    gameMazeObjectsRow.append(gameObject);
                    map_x += 20;
                    break;
                }
                case GameObject::WALL: {
                    GameObject *gameObject = new GameObject{GameObject::WALL, this};
                    gameObject->setX(map_x);
                    gameObject->setY(map_y);
                    gameMazeObjectsRow.append(gameObject);
                    map_x += 20;
                    break;
                }
                case GameObject::PILL: {
                    GameObject *gameObject = new GameObject{GameObject::PILL, this};
                    gameObject->setX(map_x);
                    gameObject->setY(map_y);
                    gameMazeObjectsRow.append(gameObject);
                    map_x += 20;
                    break;
                }
                case GameObject::POINT: {
                    GameObject *gameObject = new GameObject{GameObject::POINT, this};
                    gameObject->setX(map_x);
                    gameObject->setY(map_y);
                    gameMazeObjectsRow.append(gameObject);
                    map_x += 20;
                    break;
                }
                default: {
                    break;
                }
            }
        }
        map_y += 20;
        m_gameMazeObjects.append(gameMazeObjectsRow);
    }
    mapFile.close();
}

void GameController::readObjects(const QString &map) {
    m_gameObjects.clear();
    QFile mapFile{map};
    mapFile.open(QIODevice::ReadOnly | QIODevice::Text);
    int map_y = 0;
    int ghost_id = 1;
    for (int i = 0; i < MAPVERTICALBLOCKS; ++i) {
        QByteArray mapLine = mapFile.readLine();
        QList<GameObject *> gameObjectsRow;
        int map_x = 0;
        for (int j = 0; j < MAPHOZIRONTALBLOCKS; ++j) {
            switch (static_cast<int>(mapLine[j])) {
                case GameObject::EMPTY: {
                    GameObject *gameObject = new GameObject{GameObject::EMPTY, this};
                    gameObject->setX(map_x);
                    gameObject->setY(map_y);
                    gameObjectsRow.append(gameObject);
                    map_x += 20;
                    break;
                }
                case GameObject::GHOST: {
                    GameObject *gameObject = new Ghost{ghost_id, this};
                    gameObject->setX(map_x);
                    gameObject->setY(map_y);
                    gameObjectsRow.append(gameObject);
                    map_x += 20;
                    ghost_id += 1;
                    break;
                }
                case GameObject::PACMAN: {
                    GameObject *gameObject = new Pacman{this};
                    m_pacman = dynamic_cast<Pacman *>(gameObject);
                    gameObject->setX(map_x);
                    gameObject->setY(map_y);
                    gameObjectsRow.append(gameObject);
                    map_x += 20;
                    break;
                }
                default: {
                    break;
                }
            }
        }
        map_y += 20;
        m_gameObjects.append(gameObjectsRow);
    }
    mapFile.close();
}

void GameController::play() {
    pacmanTimer->start(200);
    setGameStatus(GameController::PLAYING);
}

void GameController::pause() {
    pacmanTimer->stop();
    setGameStatus(GameController::PAUSE);
}

void GameController::restart() {
    pacmanTimer->start(200);
    setGameStatus(GameController::PLAYING);
}

void GameController::pacmanHandler() {
    int xIndex = m_pacman->x() / 20;
    int yIndex = m_pacman->y() / 20;

    checkNextDirection(xIndex, yIndex);

    switch (m_pacman->currentDirection()) {
        case Pacman::UP: {
            if (canPacmanMove(yIndex - 1, xIndex)) {
                m_pacman->moveUp();
                m_pacman->setRunning(true);
                eatPill(xIndex, yIndex - 1);
            } else {
                m_pacman->setCurrentDirection(Pacman::STOP);
                m_pacman->setNextDirection(Pacman::STOP);
            }
            break;
        }
        case Pacman::DOWN: {
            if (canPacmanMove(yIndex + 1, xIndex)) {
                m_pacman->moveDown();
                m_pacman->setRunning(true);
                eatPill(xIndex, yIndex + 1);
            } else {
                m_pacman->setCurrentDirection(Pacman::STOP);
                m_pacman->setNextDirection(Pacman::STOP);
            }
            break;
        }
        case Pacman::LEFT: {
            if (canPacmanMove(yIndex, xIndex - 1)) {
                m_pacman->moveLeft();
                m_pacman->setRunning(true);
                eatPill(xIndex - 1, yIndex);
            } else {
                m_pacman->setCurrentDirection(Pacman::STOP);
                m_pacman->setNextDirection(Pacman::STOP);
            }
            break;
        }
        case Pacman::RIGHT: {
            if (canPacmanMove(yIndex, xIndex + 1)) {
                m_pacman->moveRight();
                m_pacman->setRunning(true);
                eatPill(xIndex + 1, yIndex);
            } else {
                m_pacman->setCurrentDirection(Pacman::STOP);
                m_pacman->setNextDirection(Pacman::STOP);
            }
            break;
        }
        case Pacman::STOP: {
            m_pacman->setRunning(false);
            break;
        }
        default: {
            break;
        }
    }
}

bool GameController::canPacmanMove(int yIndex, int xIndex) {
    switch (m_gameMazeObjects[yIndex][xIndex]->getGameObjectType()) {
        case GameObject::FLOOR: {
            return true;
            break;
        }
        case GameObject::PILL: {
            return true;
            break;
        }
        case GameObject::POINT: {
            return true;
            break;
        }
        case GameObject::WALL: {
            return false;
            break;
        }
        default: {
            return true;
            break;
        }
    }
}

void GameController::checkNextDirection(int xIndex, int yIndex) {
    switch (m_pacman->nextDirection()) {
        case Pacman::UP: {
            if (canPacmanMove(yIndex - 1, xIndex)) {
                m_pacman->setCurrentDirection(Pacman::UP);
            }
            break;
        }
        case Pacman::DOWN: {
            if (canPacmanMove(yIndex + 1, xIndex)) {
                m_pacman->setCurrentDirection(Pacman::DOWN);
            }
            break;
        }
        case Pacman::LEFT: {
            if (canPacmanMove(yIndex, xIndex - 1)) {
                m_pacman->setCurrentDirection(Pacman::LEFT);
            }
            break;
        }
        case Pacman::RIGHT: {
            if (canPacmanMove(yIndex, xIndex + 1)) {
                m_pacman->setCurrentDirection(Pacman::RIGHT);
            }
            break;
        }
        case Pacman::STOP: {
            break;
        }
        default: {
            break;
        }
    }
}

void GameController::eatPill(int xIndex, int yIndex) {
    switch (m_gameMazeObjects[yIndex][xIndex]->getGameObjectType()) {
        case GameObject::FLOOR: {
            break;
        }
        case GameObject::PILL: {
            setScore(score() + 1);
            int x = m_gameMazeObjects[yIndex][xIndex]->x();
            int y = m_gameMazeObjects[yIndex][xIndex]->y();
            delete m_gameMazeObjects[yIndex][xIndex];
            m_gameMazeObjects[yIndex][xIndex] = new GameObject{GameObject::FLOOR};
            emit gameMazeObjectsChanged();
            emit pillEaten(x, y, yIndex, xIndex);
            break;
        }
        case GameObject::POINT: {
            setScore(score() + 10);
            int x = m_gameMazeObjects[yIndex][xIndex]->x();
            int y = m_gameMazeObjects[yIndex][xIndex]->y();
            delete m_gameMazeObjects[yIndex][xIndex];
            m_gameMazeObjects[yIndex][xIndex] = new GameObject{GameObject::FLOOR};
            emit gameMazeObjectsChanged();
            emit pillEaten(x, y, yIndex, xIndex);
            break;
        }
        default: {
            break;
        }
    }
}

QList<QList<GameObject *>> GameController::gameMazeObjects() const {
    return m_gameMazeObjects;
}

void GameController::setGameMazeObjects(const QList<QList<GameObject *>> &newGameMazeObjects) {
    if (m_gameMazeObjects == newGameMazeObjects)
        return;
    m_gameMazeObjects = newGameMazeObjects;
    emit gameMazeObjectsChanged();
}

Pacman *GameController::pacman() const {
    return m_pacman;
}

void GameController::setPacman(Pacman *newPacman) {
    if (m_pacman == newPacman)
        return;
    m_pacman = newPacman;
    emit pacmanChanged();
}

int GameController::score() const {
    return m_score;
}

void GameController::setScore(int newScore) {
    if (m_score == newScore)
        return;
    m_score = newScore;
    emit scoreChanged();
}

QList<QList<GameObject *>> GameController::gameObjects() const {
    return m_gameObjects;
}

void GameController::setGameObjects(const QList<QList<GameObject *>> &newGameObjects) {
    if (m_gameObjects == newGameObjects)
        return;
    m_gameObjects = newGameObjects;
    emit gameObjectsChanged();
}

enum GameController::GameStatus GameController::gameStatus() const {
    return m_gameStatus;
}

void GameController::setGameStatus(GameStatus newGameStatus) {
    if (m_gameStatus == newGameStatus)
        return;
    m_gameStatus = newGameStatus;
    emit gameStatusChanged(m_gameStatus);
}
