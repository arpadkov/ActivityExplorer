import QtQuick
import QtLocation
import QtPositioning

Rectangle{
    id: container_rect
    anchors.fill: parent

        MapComponent {
            id: map_component
            anchors.fill: parent

            //map.center: QtPositioning.coordinate(59.91, 10.75) // Oslo
            //map.zoomLevel: 14
            property geoCoordinate startCentroid

            /*
            PinchHandler {
                id: pinch
                target: null
                onActiveChanged: if (active) {
                    map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
                }
                onScaleChanged: (delta) => {
                    map.zoomLevel += Math.log2(delta)
                    map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
                }
                onRotationChanged: (delta) => {
                    map.bearing -= delta
                    map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
                }
                grabPermissions: PointerHandler.TakeOverForbidden
            }
            WheelHandler {
                id: wheel
                // workaround for QTBUG-87646 / QTBUG-112394 / QTBUG-112432:
                // Magic Mouse pretends to be a trackpad but doesn't work with PinchHandler
                // and we don't yet distinguish mice and trackpads on Wayland either
                acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                                 ? PointerDevice.Mouse | PointerDevice.TouchPad
                                 : PointerDevice.Mouse
                rotationScale: 1/120
                property: "zoomLevel"
            }
            */



        }
}


/*
Map {
    id: viewXYZ

    zoomLevel: (maximumZoomLevel - minimumZoomLevel)/2
    center {
        // The Qt Company in Oslo
        latitude: 59.9485
        longitude: 10.7686
    }

}
/*

/*
    Rectangle {
        id: rectangle
        color: "red"
        width: 200
        height: 200
        anchors.fill: parent

        Text {
            id: text
            text: "This is QML code.\n(Click to pause)"
            font.pointSize: 14
            anchors.centerIn: parent
            PropertyAnimation {
                id: animation
                target: text
                property: "rotation"
                from: 0; to: 360; duration: 5000
                loops: Animation.Infinite
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: animation.paused ? animation.resume() : animation.pause()
        }
        Component.onCompleted: animation.start()
    }
*/
