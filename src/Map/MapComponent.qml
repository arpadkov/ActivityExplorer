import QtQuick
import QtLocation
import QtPositioning

MapView {
    id: view

    Plugin {
            id: mapPlugin
            name: "osm"

            PluginParameter {
                name: "osm.mapping.providersrepository.disabled"
                value: "true"
            }

            PluginParameter {
                name: "osm.mapping.providersrepository.address"
                value: "http://maps-redirect.qt.io/osm/5.6/"
            }
        }

    map.plugin: mapPlugin

    map.zoomLevel: (maximumZoomLevel - minimumZoomLevel)/2
    map.center {
        // The Qt Company in Oslo
        latitude: 59.9485
        longitude: 10.7686
    }

    Shortcut {
        enabled: map.zoomLevel < map.maximumZoomLevel
        sequence: StandardKey.ZoomIn
        onActivated: map.zoomLevel = Math.round(map.zoomLevel + 1)
    }
    Shortcut {
        enabled: map.zoomLevel > map.minimumZoomLevel
        sequence: StandardKey.ZoomOut
        onActivated: map.zoomLevel = Math.round(map.zoomLevel - 1)
    }


/*
    DragHandler {
        id: drag
        target: null
        onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
    }
*/
}
