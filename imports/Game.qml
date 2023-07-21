import QtQuick
import PacmanGame 1.0

Rectangle {
    id: rectGame

    property var ghost1
    property var ghost2
    property var ghost3
    property var ghost4
    property var maze: []
    property var pacman

    color: "#050505"

    Connections {
        function onCurrentDirectionChanged(currentDirection) {
            switch (currentDirection) {
            case PacmanObject.UP:
                {
                    rectGame.pacman.rotationAngle = -90;
                    break;
                }
            case PacmanObject.DOWN:
                {
                    rectGame.pacman.rotationAngle = 90;
                    break;
                }
            case PacmanObject.RIGHT:
                {
                    rectGame.pacman.rotationAngle = 0;
                    break;
                }
            case PacmanObject.LEFT:
                {
                    rectGame.pacman.rotationAngle = 180;
                    break;
                }
            }
        }

        function onRunningChanged(running) {
            if (running) {
                rectGame.pacman.animatePacman();
            } else {
                rectGame.pacman.inanimatePacman();
            }
        }

        function onXChanged() {
            rectGame.pacman.x = gameController.pacman.x;
        }

        function onYChanged() {
            rectGame.pacman.y = gameController.pacman.y;
        }

        target: gameController.pacman
    }

    Connections {
        function onPillEaten(x, y, col, row) {
            rectGameArea.eatPill(x, y, col, row);
        }

        target: gameController
    }

    MouseArea {
        anchors.fill: parent
    }

    Component {
        id: wallComponent

        Wall {
        }
    }

    Component {
        id: pacmanComponent

        Pacman {
        }
    }

    Component {
        id: ghostComponent

        Ghost {
        }
    }

    Component {
        id: floorComponent

        Floor {
        }
    }

    Component {
        id: pillComponent

        Pill {
        }
    }

    Component {
        id: pointComponent

        Point {
        }
    }

    Component {
        id: emptyComponent

        Item {
        }
    }

    Text {
        id: txtScore

        color: "#FFFFFF"
        text: "Score : " + gameController.score

        anchors {
            left: rectGameArea.left
            top: parent.top
            topMargin: 15
        }

        font {
            family: "bradley hand itc"
            pixelSize: 18
            weight: Font.Bold
        }
    }

    Rectangle {
        id: rectGameArea

        function createGameObjects() {
            let gameObjects = gameController.gameObjects;
            for (let i = 0; i < gameObjects.length; ++i) {
                let gameObjectsRowLength = gameController.gameObjects[i].length;
                for (let j = 0; j < gameObjectsRowLength; ++j) {
                    switch (gameObjects[i][j].gameObjectType) {
                    case GameObject.GHOST:
                        {
                            switch (gameObjects[i][j].ghostNo) {
                            case 1:
                                {
                                    rectGame.ghost1 = ghostComponent.createObject(rectGameArea, {
                                            "x": gameObjects[i][j].x,
                                            "y": gameObjects[i][j].y,
                                            "z": 4,
                                            "ghostImgSrc": "qrc:/pacman/assets/Ghost/Body1.png",
                                            "eyesImgSrc": "qrc:/pacman/assets/Ghost/EyesUp.png"
                                        });
                                    break;
                                }
                            case 2:
                                {
                                    rectGame.ghost2 = ghostComponent.createObject(rectGameArea, {
                                            "x": gameObjects[i][j].x,
                                            "y": gameObjects[i][j].y,
                                            "z": 4,
                                            "ghostImgSrc": "qrc:/pacman/assets/Ghost/Body2.png",
                                            "eyesImgSrc": "qrc:/pacman/assets/Ghost/EyesDown.png"
                                        });
                                    break;
                                }
                            case 3:
                                {
                                    rectGame.ghost3 = ghostComponent.createObject(rectGameArea, {
                                            "x": gameObjects[i][j].x,
                                            "y": gameObjects[i][j].y,
                                            "z": 4,
                                            "ghostImgSrc": "qrc:/pacman/assets/Ghost/Body3.png",
                                            "eyesImgSrc": "qrc:/pacman/assets/Ghost/EyesLeft.png"
                                        });
                                    break;
                                }
                            case 4:
                                {
                                    rectGame.ghost4 = ghostComponent.createObject(rectGameArea, {
                                            "x": gameObjects[i][j].x,
                                            "y": gameObjects[i][j].y,
                                            "z": 4,
                                            "ghostImgSrc": "qrc:/pacman/assets/Ghost/Body4.png",
                                            "eyesImgSrc": "qrc:/pacman/assets/Ghost/EyesRight.png"
                                        });
                                    break;
                                }
                            }
                            break;
                        }
                    case GameObject.PACMAN:
                        {
                            rectGame.pacman = pacmanComponent.createObject(rectGameArea, {
                                    "x": gameObjects[i][j].x,
                                    "y": gameObjects[i][j].y,
                                    "z": 4
                                });
                            break;
                        }
                    }
                }
            }
        }

        function createMaze() {
            rectGame.maze = [];
            let gameObjects = gameController.gameMazeObjects;
            for (let i = 0; i < gameObjects.length; ++i) {
                let gameObjectsRowLength = gameController.gameObjects[i].length;
                var mazeRow = [];
                for (let j = 0; j < gameObjectsRowLength; ++j) {
                    switch (gameObjects[i][j].gameObjectType) {
                    case GameObject.FLOOR:
                        {
                            var floor = floorComponent.createObject(rectGameArea, {
                                    "x": gameObjects[i][j].x,
                                    "y": gameObjects[i][j].y
                                });
                            mazeRow.push(floor);
                            break;
                        }
                    case GameObject.PILL:
                        {
                            var pill = pillComponent.createObject(rectGameArea, {
                                    "x": gameObjects[i][j].x,
                                    "y": gameObjects[i][j].y
                                });
                            mazeRow.push(pill);
                            break;
                        }
                    case GameObject.POINT:
                        {
                            var point = pointComponent.createObject(rectGameArea, {
                                    "x": gameObjects[i][j].x,
                                    "y": gameObjects[i][j].y
                                });
                            mazeRow.push(point);
                            break;
                        }
                    case GameObject.WALL:
                        {
                            var wall = wallComponent.createObject(rectGameArea, {
                                    "x": gameObjects[i][j].x,
                                    "y": gameObjects[i][j].y
                                });
                            mazeRow.push(wall);
                            break;
                        }
                    }
                }
                rectGame.maze.push(mazeRow);
            }
        }

        function eatPill(x, y, col, row) {
            rectGame.maze[col][row].destroy();
            rectGame.maze[col][row] = floorComponent.createObject(rectGameArea, {
                    "x": x,
                    "y": y
                });
        }

        Keys.enabled: true
        color: "#050505"
        focus: true
        height: 480
        width: 340

        Component.onCompleted: {
            rectGameArea.forceActiveFocus();
            createMaze();
            createGameObjects();
        }
        Keys.onPressed: event => {
            if ((event.key === Qt.Key_Right) || (event.key === Qt.Key_D)) {
                gameController.pacman.nextDirection = PacmanObject.RIGHT;
            } else if ((event.key === Qt.Key_Left) || (event.key === Qt.Key_A)) {
                gameController.pacman.nextDirection = PacmanObject.LEFT;
            } else if ((event.key === Qt.Key_Up) || (event.key === Qt.Key_W)) {
                gameController.pacman.nextDirection = PacmanObject.UP;
            } else if ((event.key === Qt.Key_Down) || (event.key === Qt.Key_S)) {
                gameController.pacman.nextDirection = PacmanObject.DOWN;
            } else if (event.key === Qt.Key_Escape) {
                switch (gameController.gameStatus) {
                case GameController.PLAYING:
                    {
                        gameController.pause();
                        break;
                    }
                case GameController.PAUSE:
                    {
                        gameController.play();
                        break;
                    }
                }
            }
        }

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 40
        }
    }
}
