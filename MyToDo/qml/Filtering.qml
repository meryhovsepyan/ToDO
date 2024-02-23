import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    id: filteringItem
    property alias titlefilter: titlefilter
    property alias descfilter: descfilter
    property alias statusFilter: statusFilter
    property alias fromFilter: fromDate
    property alias toFilter: toDate
    signal filterDataChanged()

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        ComboBox {
            id :statusFilter
            model: ["All", "New", "Completed"]
            onCurrentIndexChanged: {
                if (currentIndex === 0) {
                    fromDate.text = ""
                    toDate.text = ""
                    descfilter.text = ""
                    titlefilter.text = ""
                    filterDataChanged()
                } else {
                    fromDate.text = ""
                    toDate.text = ""
                    descfilter.text = ""
                    titlefilter.text = ""
                    filterDataChanged()
                }
            }
        }

        TextField {
            id: titlefilter
            placeholderText: "Enter title filter"
            Layout.fillWidth: true
            Layout.fillHeight: true
            onTextEdited: {
                descfilter.text = ""
                fromDate.text = ""
                toDate.text = ""
                statusFilter.currentIndex = 0
                filterDataChanged()
            }
        }

        TextField {
            id:descfilter
            placeholderText: "Enter description filter"
            Layout.fillWidth: true
            Layout.fillHeight: true
            onTextEdited: {
                titlefilter.text = ""
                fromDate.text = ""
                toDate.text = ""
                statusFilter.currentIndex = 0
                filterDataChanged()
            }
        }

        Popup{
            id: datePickerPopup2
            width: 350
            height: 250
            parent: ApplicationWindow.contentItem
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2

            DatePicker {
                id:datePicker
                onClicked: {
                    fromDate.text = Qt.formatDate(selectedDate, 'dd-MM-yyyy')
                    filterDataChanged()
                    datePickerPopup2.close()
                }
            }
        }

        Popup{
            id: datePickerPopup1
            width: 350
            height: 250
            parent: ApplicationWindow.contentItem
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2

            DatePicker {
                id:datePicker2
                onClicked: {
                    toDate.text = Qt.formatDate(selectedDate, 'dd-MM-yyyy')
                    filterDataChanged()
                    datePickerPopup1.close()
                }
            }
        }

        TextField {
            id:fromDate
            placeholderText: "from date"
            Layout.fillWidth: true
            Layout.fillHeight: true
            readOnly: true
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    datePickerPopup2.open()
                    titlefilter.text = ""
                    descfilter.text = ""
                    statusFilter.currentIndex = 0
                    filterDataChanged()
                }
            }
        }
        TextField {
            id:toDate
            placeholderText: "to date"
            Layout.fillWidth: true
            Layout.fillHeight: true
            readOnly: true
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    datePickerPopup1.open()
                    titlefilter.text = ""
                    descfilter.text = ""
                    statusFilter.currentIndex = 0
                    filterDataChanged()
                }
            }
        }
    }
}

