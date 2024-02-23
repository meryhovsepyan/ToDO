import QtQuick 2.0

ListView {
    id: root

    function set(date) {
        selectedDate = new Date(date)
        positionViewAtIndex((selectedDate.getFullYear()) * 12 + selectedDate.getMonth(), ListView.Center) // index from month year
    }

    signal clicked(date date);

    property date selectedDate: new Date()

    width: 320;  height: 220
    snapMode:    ListView.SnapOneItem
    orientation: Qt.Horizontal
    clip:        true

    model: 3000 * 12

    delegate: Item {
        property int year: Math.floor(index / 12)
        property int month: index % 12
        property int firstDay: new Date(year, month, 1).getDay()

        width: root.width;  height: root.height

        Column {
            Item {
                width: root.width;  height: root.height - grid.height
                Text {
                    anchors.centerIn: parent
                    text: ['January', 'February', 'March', 'April', 'May', 'June',
                        'July', 'August', 'September', 'October', 'November', 'December'][month] + ' ' + year
                    font {pixelSize: 0.7 * grid.cellHeight}
                }
            }

            Grid {
                id: grid

                width: root.width;  height: 0.8 * root.height
                property real cellWidth:  width  / columns;
                property real cellHeight: height / rows

                columns: 7
                rows:    7

                Repeater {
                    model: grid.columns * grid.rows

                    delegate: Rectangle {
                        property int day:  index - 7
                        property int date: day - firstDay + 1

                        width: grid.cellWidth;  height: grid.cellHeight
                        border.width: 0.3 * radius
                        border.color: new Date(year, month, date).toDateString() == selectedDate.toDateString()  &&  text.text  &&  day >= 0?
                                          'black': 'transparent'
                        radius: 0.02 * root.height
                        opacity: !mouseArea.pressed? 1: 0.3

                        Text {
                            id: text
                            anchors.centerIn: parent
                            font.pixelSize: 0.5 * parent.height
                            font.bold:      new Date(year, month, date).toDateString() == new Date().toDateString() // today
                            text: {
                                if(day < 0)                                               ['S', 'M', 'T', 'W', 'T', 'F', 'S'][index]
                                else if(new Date(year, month, date).getMonth() == month)  date // 1-31
                                else                                                      ''
                            }
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            enabled:    text.text  &&  day >= 0
                            onClicked: {
                                selectedDate = new Date(year, month, date)
                                root.clicked(selectedDate)
                            }
                        }
                    }
                }
            }
        }
    }
    Component.onCompleted: set(new Date())
}
