#include "pacman.hpp"

Pacman::Pacman(QObject *parent)
    : m_currentDirection(Pacman::STOP)
    , m_nextDirection{Pacman::STOP}
    , GameObject{GameObject::PACMAN, parent} {}

enum Pacman::Dir Pacman::nextDirection() const {
    return m_nextDirection;
}

void Pacman::setNextDirection(Dir newNextDirection) {
    if (m_nextDirection == newNextDirection)
        return;
    m_nextDirection = newNextDirection;
    emit nextDirectionChanged();
}

enum Pacman::Dir Pacman::currentDirection() const {
    return m_currentDirection;
}

void Pacman::setCurrentDirection(Dir newCurrentDirection) {
    if (m_currentDirection == newCurrentDirection)
        return;
    m_currentDirection = newCurrentDirection;
    emit currentDirectionChanged(m_currentDirection);
}

void Pacman::moveUp() {
    this->setY(this->y() - 20);
}

void Pacman::moveDown() {
    this->setY(this->y() + 20);
}

void Pacman::moveLeft() {
    this->setX(this->x() - 20);
}

void Pacman::moveRight() {
    this->setX(this->x() + 20);
}

bool Pacman::running() const {
    return m_running;
}

void Pacman::setRunning(bool newRunning) {
    if (m_running == newRunning)
        return;
    m_running = newRunning;
    emit runningChanged(m_running);
}
