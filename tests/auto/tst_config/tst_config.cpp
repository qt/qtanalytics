/****************************************************************************
**
** Copyright (C) 2019 Luxoft Sweden AB. All rights reserved.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the analytics module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore>
#include <QtTest>

#include "configutil.h"

class ConfigTestCase: public QObject {
    Q_OBJECT
private Q_SLOTS:
    void testResolveConfig();
    void testReadConfig();
    void testParseConfig();
    void testLoadConfig();
};

void ConfigTestCase::testResolveConfig()
{

    QString path = ConfigUtil::resolvePath("analytics");
    QCOMPARE(path, ":/analytics.json");
}

void ConfigTestCase::testReadConfig()
{
    QByteArray data = ConfigUtil::readJSON(":/analytics.json");
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QVERIFY(doc.isObject());
    QCOMPARE(doc.object().value("service"), "matomo");
}

void ConfigTestCase::testParseConfig()
{
    QString path = ConfigUtil::resolvePath("analytics");
    QByteArray data = ConfigUtil::readJSON(path);
    QJsonObject o = ConfigUtil::parseJSON(data);
    QCOMPARE(o.value("service"), "matomo");
}

void ConfigTestCase::testLoadConfig()
{
    QJsonObject o = ConfigUtil::loadJSON("analytics");
    QCOMPARE(o.value("service"), "matomo");
}

QTEST_MAIN(ConfigTestCase)

#include "tst_config.moc"
