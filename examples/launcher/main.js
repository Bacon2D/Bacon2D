function createGameWindow() {
    var dynamicObject = Qt.createQmlObject(launcher.qmlData(), main);
    if (dynamicObject == null) {
        console.log("error creating game window");
        return;
    }

    main.width = dynamicObject.width
    main.height = dynamicObject.height
}
