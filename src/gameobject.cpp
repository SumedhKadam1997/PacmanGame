#include "gameobject.hpp"

GameObject::GameObject(enum GameObjectType gameObjectType, QObject *parent)
    : m_gameObjectType{gameObjectType}
    , QObject{parent} {
}

GameObject::~GameObject() {
}

int GameObject::x() const {
    return m_x;
}

void GameObject::setX(int newX) {
    if (m_x == newX)
        return;
    m_x = newX;
    emit xChanged();
}

int GameObject::y() const {
    return m_y;
}

void GameObject::setY(int newY) {
    if (m_y == newY)
        return;
    m_y = newY;
    emit yChanged();
}

enum GameObject::GameObjectType GameObject::getGameObjectType() const {
    return m_gameObjectType;
}
