import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import QtCore
import TaskManager 1.0
import FilteredModel 1.0
import "qml"

ApplicationWindow {
    width: 800
    height: 640
    visible: true
    title: qsTr("My Todo List")

    TaskManager {
        id: todoModel
        Component.onCompleted: {
            filteredModel.setSourceModelQML(this)
        }
    }

    FilteredModel {
        id: filteredModel
    }

    property bool isFiltering: false

    Item {
        anchors.fill: parent
        Rectangle {
            id: topRect
            height: 100
            width: parent.width
            color: "#152e4a"
            anchors.top: parent.top

            Text {
                text: "My Todo List"
                font.bold: true
                font.pixelSize: 26
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#86a9d1"
            }
        }

        Item {
            id: bottomRectangle
            width: parent.width
            anchors.bottom: parent.bottom
            anchors.top: topRect.bottom

            Rectangle {
                id: leftRect
                width: 0.7 * parent.width
                height: parent.height
                anchors.left: parent.left
                color: "#0b1624"

                Filtering {
                    id: filterComponent
                    width: parent.width*0.9
                    height: 30
                    anchors.horizontalCenter: parent.horizontalCenter

                    onFilterDataChanged: {
                        isFiltering = false

                        if (filterComponent.titlefilter && filterComponent.titlefilter.text) {
                            isFiltering = true
                            filteredModel.setFilterTitle(filterComponent.titlefilter.text)
                        }
                        if (filterComponent.descfilter && filterComponent.descfilter.text) {
                            isFiltering = true
                            filteredModel.setFilterDescription(filterComponent.descfilter.text)
                        }
                        if (filterComponent.statusFilter && filterComponent.statusFilter.currentIndex>0) {
                            isFiltering = true
                            filteredModel.setFilterStatus(filterComponent.statusFilter.currentIndex-1)
                        }
                        if (filterComponent.toFilter && filterComponent.fromFilter && filterComponent.fromFilter.text && filterComponent.toFilter.text) {
                            isFiltering = true
                            filteredModel.setFilterDate(filterComponent.fromFilter.text + " " +filterComponent.toFilter.text)
                        }
                    }
                }

                ListView {
                    id: lv
                    model: isFiltering ? filteredModel : todoModel
                    spacing: 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: filterComponent.bottom
                    anchors.topMargin: 20
                    width: parent.width * 0.9
                    height: parent.height * 0.7
                    clip: true

                    onModelChanged: {
                        if (model === filteredModel) {
                            console.log("model changed")
                        }
                    }

                    delegate: Rectangle {
                        id: dlg

                        width: lv.width
                        height: 70
                        color: "#bbd4f0"
                        radius: 10

                        Rectangle {
                            id: deleteRec
                            color: "#86a9d1"
                            width: 60
                            radius: 10
                            height: parent.height
                            anchors.right: parent.right

                            Text {
                                color: "#0b1624"
                                font.bold: true
                                font.pixelSize: 16
                                text: "Delete"
                                anchors.centerIn: parent
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (isFiltering) {
                                        todoModel.removeTask(filteredModel.mapIndexFromSource(index))
                                    } else {
                                        todoModel.removeTask(index)
                                    }
                                }
                            }
                        }
                        Rectangle {
                            color : "#86a9d1"
                            width: 60
                            radius: 10
                            height: parent.height
                            anchors.right: deleteRec.left
                            anchors.rightMargin : 5
                            Text {
                                color : "#0b1624"
                                font.bold: true
                                font.pixelSize: 16
                                text: "Edit"
                                anchors.centerIn: parent
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    editDialog.open()
                                    editDialog.titleField = title
                                    editDialog.descriptionFieldText = description
                                    editDialog.dateFieldText = date
                                }
                            }
                        }

                        EditDialog {
                            id: editDialog
                            anchors.centerIn: parent
                            onAcceptClicked: {
                                if(!isFiltering){
                                    todoModel.updateDescription(todoModel.index(index, 0), descriptionFieldText)
                                    todoModel.updateTitle(todoModel.index(index, 0), titleField)
                                    todoModel.updateDate(todoModel.index(index, 0), dateFieldText)
                                } else {
                                    todoModel.updateDescription(todoModel.index(filteredModel.mapIndexFromSource(index), 0), descriptionFieldText)
                                    todoModel.updateTitle(todoModel.index(filteredModel.mapIndexFromSource(index), 0), titleField)
                                    todoModel.updateDate(todoModel.index(filteredModel.mapIndexFromSource(index), 0), dateFieldText)
                                }
                            }

                        }
                        RoundButton {
                            id: button
                            checked: status
                            text: checked ? "✓" : ""
                            height : 40
                            width : 40
                            anchors.margins: 50

                            onClicked: {
                                status = !status
                            }
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Column {
                            anchors {
                                fill: parent
                                leftMargin: 50
                                rightMargin: 100
                                topMargin: 5
                                bottomMargin: 5
                            }

                            Text {
                                color: "#0b1624"
                                font.bold: true
                                font.pixelSize: 16
                                text: title
                            }
                            Text {
                                color: "#0b1624"
                                font.pixelSize: 14
                                text: description
                            }
                            Text {
                                color : "#0b1624"
                                font.pixelSize: 14
                                text: date
                            }
                        }
                    }
                }
            }

            Item {
                id: rightItem
                width: 0.3 * parent.width
                height: parent.height
                anchors.right: parent.right

                Column {
                    anchors.top: parent.top
                    anchors.topMargin: 50
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    TextField {
                        id: t1
                        placeholderText: "Enter the title"
                        height: 50
                        width: rightItem.width * 0.7
                        color:  "#152e4a"
                    }
                    Item {
                        id: errorMessage
                        width: parent.width
                        height: 20
                        visible: false
                        Text {
                            anchors.centerIn: parent
                            text: "Title is required"
                            color: "red"
                        }
                    }
                    TextField {
                        id: t2
                        placeholderText: "Enter the description"
                        width: rightItem.width * 0.7
                        height: 50
                        color:  "#152e4a"
                    }
                    ComboBox {
                        id: statusComboBox
                        width: parent.width
                        model: ["New", "Completed"]
                    }

                    Button {
                        text: "Pick Date"
                        onClicked: {
                            datePickerPopup.open()
                        }
                    }
                    Popup{
                        id: datePickerPopup
                        width: 350
                        height: 250
                        parent: ApplicationWindow.contentItem
                        x: (parent.width - width) / 2
                        y: (parent.height - height) / 2

                        DatePicker {
                            id:datePicker
                            onClicked: {
                                t3.text = Qt.formatDate(selectedDate, 'dd-MM-yyyy')
                                datePickerPopup.close()
                            }
                        }
                    }

                    TextField {
                        id: t3
                        placeholderText: "date"
                        width: rightItem.width * 0.7
                        height: 50
                        color:  "#152e4a"
                        readOnly: true
                    }

                    Button {
                        text: "Add Task"
                        height: 50
                        width: rightItem.width * 0.7
                        onClicked: {
                            if (t1.text.trim() === "") {
                                errorMessage.visible = true;
                            } else {
                                errorMessage.visible = false;
                                todoModel.addTask(t1.text,t2.text,t3.text,statusComboBox.currentIndex)
                                t1.text=""
                                t2.text=""
                                t3.text=""
                                statusComboBox.currentIndex = 0
                            }
                        }
                    }
                }
            }
        }
    }
}

