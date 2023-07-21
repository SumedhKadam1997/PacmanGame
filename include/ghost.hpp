#ifndef GHOST_HPP
#define GHOST_HPP

#include "gameobject.hpp"
#include <QObject>

class Ghost : public GameObject {
    Q_OBJECT
    Q_PROPERTY(int ghostNo READ ghostNo WRITE setghostNo NOTIFY ghostNoChanged)
public:
    enum Color { RED = 1,
                 YELLOW = 2,
                 PINK = 3,
                 GREEN = 4 };
    Q_ENUM(Color)
    enum Status { NORMAL,
                  PANIC,
                  RUNNING };
    Q_ENUM(Status)
    explicit Ghost(int ghost_no, QObject *parent = nullptr);

    int ghostNo() const;
    void setghostNo(int newGhostNo);

signals:
    void ghostNoChanged();

private:
    int m_ghostNo;
};

#endif// GHOST_HPP
