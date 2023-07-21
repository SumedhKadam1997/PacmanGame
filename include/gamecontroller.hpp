#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "gameobject.hpp"
#include "ghost.hpp"
#include "pacman.hpp"
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QTimer>

#define MAPHOZIRONTALBLOCKS 17
#define MAPVERTICALBLOCKS 24

class GameController : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(GameStatus gameStatus READ gameStatus WRITE setGameStatus NOTIFY gameStatusChanged)
    Q_PROPERTY(QList<QList<GameObject *>> gameMazeObjects READ gameMazeObjects WRITE setGameMazeObjects NOTIFY gameMazeObjectsChanged)
    Q_PROPERTY(QList<QList<GameObject *>> gameObjects READ gameObjects WRITE setGameObjects NOTIFY gameObjectsChanged)
    Q_PROPERTY(Pacman *pacman READ pacman WRITE setPacman NOTIFY pacmanChanged)

public:
    explicit GameController(QObject *parent = nullptr);
    ~GameController();

    enum GameStatus { PLAYING,
                      WIN,
                      LOSE,
                      PAUSE };
    Q_ENUM(GameStatus)

    void readMap(const QString &map);
    void readObjects(const QString &map);

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void restart();

    void pacmanHandler();
    bool canPacmanMove(int yIndex, int xIndex);
    void checkNextDirection(int yIndex, int xIndex);
    void eatPill(int xIndex, int yIndex);

    QList<QList<int>> mapList() const;
    void setMapList(const QList<QList<int>> &newMapList);

    QList<QList<GameObject *>> gameMazeObjects() const;
    void setGameMazeObjects(const QList<QList<GameObject *>> &newGameMazeObjects);

    Pacman *pacman() const;
    void setPacman(Pacman *newPacman);

    int score() const;
    void setScore(int newScore);

    QList<QList<GameObject *>> gameObjects() const;
    void setGameObjects(const QList<QList<GameObject *>> &newGameObjects);

    enum GameStatus gameStatus() const;
    void setGameStatus(GameStatus newGameStatus);

signals:
    void mapListChanged();
    void gameMazeObjectsChanged();
    void pacmanChanged();
    void scoreChanged();
    void gameObjectsChanged();
    void pillEaten(int x, int y, int row, int col);
    void gameStatusChanged();

private:
    QList<QList<GameObject *>> m_gameMazeObjects;
    Pacman *m_pacman = nullptr;
    QTimer *pacmanTimer = nullptr;
    int m_score;
    QList<QList<GameObject *>> m_gameObjects;
    GameStatus m_gameStatus;
};
Q_DECLARE_METATYPE(GameController)
#endif// GAMECONTROLLER_HPP
