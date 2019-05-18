import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
ApplicationWindow {
id: window
visible: true
 width: 465
height: 318
Rectangle {
x:0
y:0
width:465
height:318
Rectangle {
x:0
y:0
width:0
height:0
border.color: "black"
Rectangle {
x:50
y:10
width:101
height:50
border.color: "black"
Column {
Label {
text:"Layout Text!"
}
Label {
text:"2nd Layout Text"
}
}
}
Rectangle {
x:200
y:10
width:120
height:80
border.color: "black"
Label {
x:30
y:40
width:47
height:13
text:"FreeText!"
}
}
Button {
x:230
y:120
width:75
height:23
text:"PushButton"
}
TextInput {
x:60
y:140
width:113
height:20
text:"LineEdit text"
}
CheckBox {
x:230
y:180
width:111
height:41
text:"CheckBox 1"
checked:true
}
CheckBox {
x:230
y:230
width:121
height:21
text:"CheckBox 2"
checked:false
}
Rectangle {
x:10
y:160
width:171
height:131
border.color: "black"
Column {
RadioButton {
text:"RadioButton2"
checked:false
}
RadioButton {
text:"RadioButton1"
checked:true
}
RadioButton {
text:"RadioButton3"
checked:false
}
}
}
}
}
}
