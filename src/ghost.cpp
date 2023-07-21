#include "ghost.hpp"

Ghost::Ghost(int ghost_no, QObject *parent)
    : m_ghostNo{ghost_no}
    , GameObject{GameObject::GHOST, parent} {
}

int Ghost::ghostNo() const {
    return m_ghostNo;
}

void Ghost::setghostNo(int newGhostNo) {
    if (m_ghostNo == newGhostNo)
        return;
    m_ghostNo = newGhostNo;
    emit ghostNoChanged();
}
