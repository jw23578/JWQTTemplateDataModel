import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ListView
    {
        id: theView
        model: StringAndIntObjectModel
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        delegate:
        Rectangle
        {
            width: theView.width
            height: 20
            Text
            {
                text: sai.name + " " + sai.age
            }
        }
    }
}
