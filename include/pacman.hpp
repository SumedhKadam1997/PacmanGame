#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "gameobject.hpp"
#include <QObject>

class Pacman : public GameObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(PacmanObject)
    QML_UNCREATABLE("")
    Q_PROPERTY(Dir currentDirection READ currentDirection WRITE setCurrentDirection NOTIFY currentDirectionChanged)
    Q_PROPERTY(Dir nextDirection READ nextDirection WRITE setNextDirection NOTIFY nextDirectionChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
public:
    explicit Pacman(QObject *parent = nullptr);

    enum Dir {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    };
    Q_ENUM(Dir)

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    enum Dir nextDirection() const;
    void setNextDirection(Dir newNextDirection);

    enum Dir currentDirection() const;
    void setCurrentDirection(Dir newCurrentDirection);

    bool running() const;
    void setRunning(bool newRunning);

signals:
    void nextDirectionChanged();
    void currentDirectionChanged(Dir currentDirection);
    void runningChanged(bool running);

private:
    Dir m_nextDirection;
    Dir m_currentDirection;
    bool m_running;
};

#endif// PACMAN_HPP
