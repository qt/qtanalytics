/****************************************************************************
**
** Copyright (C) 2018, 2019 Luxoft Sweden AB. All rights reserved.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the analytics module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.11
import QtQuick.Controls 2.4

import analytics 1.0

Page {
    id: root
    objectName: "subscriptions"
    title: qsTr("Subscriptions Page")

    property int activationIndex: -1


    ListModel {
        id: listModel
        ListElement {
            name: "Special offers"
            service: "offers"
            active: false
        }
        ListElement {
            name: "Company news"
            service: "news.company"
            active: false
        }
        ListElement {
            name: "Sales"
            service: "sales"
            active: false
        }
        ListElement {
            name: "Password expiration"
            service: "account.changes"
            active: false
        }
        ListElement {
            name: "Private messages"
            service: "account.message"
            active: false
        }
        ListElement {
            name: "New features"
            service: "news.features"
            active: false
        }
    }

    contentItem: ListView {
        model: listModel
        delegate: ItemDelegate {
            width: ListView.view.width
            height: 80
            contentItem: Item {
                Label {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 26
                    text: model.name
                }
                Button {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    width: 100
                    checked: model.active
                    text: model.active ? qsTr("Deactivate") : qsTr("Activate")
                    enabled: activationIndex == -1
                    onClicked: {
                        Analytics.sendEvent(root.objectName, "UserAction", "Subscription Activation", model.service, (!model.active))
                        activationIndex = index
                        fakeActivation.start()
                        labelError.visible = false
                    }
                    BusyIndicator {
                        anchors.centerIn: parent
                        visible: activationIndex == index
                    }
                }
            }
        }
    }

    Label {
        id: labelError
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        visible: false
        text: "Error. Please, try again."
    }

    Timer {
        id: fakeActivation
        interval: 1500
        repeat: false
        triggeredOnStart: false
        onTriggered: {
            var success = Math.random()
            console.log(success)
            if (success > 0.4) {
                var active = listModel.get(activationIndex).active
                var service = listModel.get(activationIndex).service
                listModel.setProperty(activationIndex, "active", !active)
                Analytics.sendEvent(root.objectName, "ServerResponse", "Subscription Activation", service, 1)
            } else {
                labelError.visible = true
                Analytics.sendEvent(root.objectName, "ServerResponse", "Subscription Activation", service, 0)
            }

            activationIndex = -1
        }
    }


    Component.onCompleted: Analytics.sendVisit(objectName, "created")
}
