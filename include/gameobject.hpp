#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <QObject>
#include <QQmlEngine>

class GameObject : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(GameObjectType gameObjectType READ getGameObjectType CONSTANT)
public:
    enum GameObjectType {
        EMPTY = 101,
        FLOOR = 102,
        GHOST = 103,
        PILL = 105,
        POINT = 111,
        PACMAN = 112,
        WALL = 119,
    };
    Q_ENUM(GameObjectType)

    explicit GameObject(GameObjectType gameObjectType, QObject *parent = nullptr);
    virtual ~GameObject();

    int x() const;
    void setX(int newX);

    int y() const;
    void setY(int newY);

    enum GameObjectType getGameObjectType() const;

signals:
    void xChanged();
    void yChanged();

private:
    int m_x;
    int m_y;
    enum GameObjectType m_gameObjectType;
};
Q_DECLARE_METATYPE(GameObject)
#endif// GAMEOBJECT_HPP
