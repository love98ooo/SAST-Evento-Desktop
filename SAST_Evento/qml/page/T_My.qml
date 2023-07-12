import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtCore
import FluentUI
import "qrc:///SAST_Evento/qml/component"

FluScrollablePage {
    title: lang.my

    Settings {
        id: settings
        property string username
        property string password
    }

    property var loginPageRegister: registerForWindowResult("/login")

    Connections {
        target: loginPageRegister
        function onResult(data) {
            if (data.ok) {
                appInfo.changeIdentity(data.username, data.password)
                settings.username = data.username
            } else {
                status.text = "未登录"
                loader.sourceComponent = noLogin
            }
        }
    }

    Component.onCompleted: {
        if (appInfo.identity.authority === 0) {
            status.text = "未登录"
            loader.sourceComponent = noLogin
            return
        }
        status.text = "账号 " + appInfo.identity.username
        loader.sourceComponent = login
        if (appInfo.identity.authority === 2)
            loader.item.text = "管理员"
        if (appInfo.identity.authority === 1)
            loader.item.text = "普通用户"
    }

    Connections {
        target: appInfo
        function onLogin() {
            if (appInfo.identity.authority === 0) {
                status.text = "未登录"
                loader.sourceComponent = noLogin
                return
            }
            status.text = "账号 " + appInfo.identity.username
            loader.sourceComponent = login
            if (appInfo.identity.authority === 2)
                loader.item.text = "管理员"
            if (appInfo.identity.authority === 1)
                loader.item.text = "普通用户"
        }
    }

    FluArea {
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 85
        paddings: 10

        FluText {
            id: status
            text: "未登录"
            font: FluTextStyle.Title
            anchors.top: parent.top
        }
        Loader {
            id: loader
            anchors.bottom: parent.bottom
            sourceComponent: noLogin
        }

        Component {
            id: login
            FluText {
                text: ""
                font: FluTextStyle.Body
            }
        }

        Component {
            id: noLogin
            FluButton {
                id: button
                text: "登录"
                anchors.right: parent.right

                onClicked: {
                    loginPageRegister.launch({
                                                 "username": settings.value(
                                                                 "username", "")
                                             })
                }
            }
        }
    }
}
