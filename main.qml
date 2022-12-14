import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Window {
    width: 240
    height: 480
    visible: true
    title: qsTr("Exam")
    maximumHeight: height
       maximumWidth: width
       minimumHeight: height
       minimumWidth: width
       property int amount : 9
       property string pin_code: ""
       Component.onCompleted: {
           for (let i=0; i<amount ; i++){
               let rnd = Randomizer.randomCode()
           gridView.model.append({
             code: rnd
                                 });
           }
       }

       function encrypt_pwd(crypt_password) {
               CryptoController.encrypt_login_or_password(crypt_password)
           }
       function crypt_controller(password) {
               let is_correct_passwd = CryptoController.check_password(password)
               if(is_correct_passwd) {
                   pin_code=password
                   stackView.push(pageMain)
               } else {
                   stackView.push(pageError)
               }
       }

StackView{
    anchors.fill: parent
    id: stackView
    initialItem: Page {
        id: pageLogin
        GridLayout {
            anchors.fill: parent
            rowSpacing: 10
            rows: 4
            flow: GridLayout.TopToBottom

            Item { // Для заполнения пространства
                Layout.row: 0
                Layout.fillHeight: true
            }

            TextField {
                id: password_code
                echoMode: TextField.Password
                passwordCharacter: "✱"
                Layout.row: 1
                Layout.alignment: Qt.AlignHCenter || Qt.AlignVCenter
            }

            Button {
                id: login_button
                    text: qsTr("Вход")
                    Layout.row: 2
                    Layout.alignment: Qt.AlignHCenter || Qt.AlignVCenter
                    onClicked:{
                        crypt_controller(password_code.text)
                        password_code.text = ""
                    }
            }

            Item { // Для заполнения пространства
                Layout.row: 4
                Layout.fillHeight: true
            }
        }
    }
    Page {
        id: pageError
        visible: false
        GridLayout {
            anchors.fill: parent
            rowSpacing: 10
            rows: 3
            flow: GridLayout.TopToBottom

            Item { // Для заполнения пространства
                Layout.row: 0
                Layout.fillHeight: true
            }
            Label {
                id: error_code
                text: "Код неверный!"
                Layout.row: 1
                Layout.alignment: Qt.AlignHCenter || Qt.AlignVCenter
            }

            Button {
                id: back_to_login_page
                text: qsTr("Назад")
                Layout.row: 2
                Layout.alignment: Qt.AlignHCenter || Qt.AlignVCenter
                onClicked:{
                    if( stackView.depth > 1 ) {
                        stackView.pop()
                    }
                }
            }
            Item { // Для заполнения пространства
                Layout.row: 3
                Layout.fillHeight: true
            }
        }
    }
    Page {
        id: pageMain
        visible: false
        Button {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin:10
            Layout.column: 0
            id: opencode
            text: qsTr("Открыть код")
            onClicked: {
                for (let i=0;i<amount;i++)
                {

                }
                let rnd = Randomizer.randomCode()
                gridView.model.append({
                  code: rnd
                                      });
             }
        }
        GridView {
             id:gridView
             anchors.topMargin:50
             anchors.leftMargin:30
            anchors.top: opencode.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            cellHeight : 50
            cellWidth : 90
            model: ListModel {id: codeModel}
            Component{
                   id: contactsDelegate
                   TextField {
                       id: wrapper
                       width: 80
                       height: 40
                       color: "black"
                       echoMode: gridView.isCurrentIndex ? TextField.Normal : TextField.Password
//                     echoMode: TextField.Password
                       passwordCharacter: "✱"
                       text: code
                       readOnly: true
                       property int itemIndex: index
                       MouseArea{
                           anchors.fill: parent
                           onClicked: {
                               gridView.currentIndex = itemIndex;
                           }
                       }

                   }
               }

//     model: contactModel
     delegate: contactsDelegate
        focus: true
        }
    }

    }

}
