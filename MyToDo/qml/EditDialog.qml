import QtQuick 2.0
import QtQuick.Controls 2.0

Popup {
    id: editDialog
    width: 400
    height: 200

    property alias titleField: titleField.text
    property alias descriptionFieldText: descriptionField.text
    property alias dateFieldText: dateField.text

    signal acceptClicked()

    TextField {
        id: titleField
        placeholderText: "Title"
        width: parent.width - 20
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }
    TextField {
        id: descriptionField
        placeholderText: "Description"
        width: parent.width - 20
        anchors.top: titleField.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: titleField.height*2
    }

    TextField {
        id: dateField
        placeholderText: "Date"
        readOnly: true
        width: 100
        anchors.top: descriptionField.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        MouseArea {
            anchors.fill: parent
            onClicked: {
                datePickerPopup.open()
            }
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
                dateField.text = Qt.formatDate(selectedDate, 'dd-MM-yyyy')
                datePickerPopup.close()
            }
        }
    }

    Button {
        id : saveButton
        text: "Save"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            acceptClicked()
            close()
        }
    }
    Button {
        text: "Cancel"
        anchors.bottom: saveButton.top
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            close()
        }
    }
}
