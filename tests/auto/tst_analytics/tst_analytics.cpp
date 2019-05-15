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

#include "analytics.h"
#include "hitbuilder.h"
#include "googlebuilder.h"
#include "matomobuilder.h"
#include "context.h"

class AnalyticsTestCase: public QObject {
    Q_OBJECT
private slots:
    void testEmptyTracker();
    void testGoogleTracker();
    void testMatomoTracker();
    void testWrongTracker();
    void testServerConfig();
};

void AnalyticsTestCase::testEmptyTracker()
{
    QScopedPointer<Analytics> a(new Analytics());
    HitBuilder * builder = a->getBuilder();
    QCOMPARE(nullptr, builder);
}

void AnalyticsTestCase::testGoogleTracker()
{
    QScopedPointer<Analytics> a(new Analytics());
    QVariantMap o{
        {"tracker", "google"},
    };
    a->context()->updateConfig(o);
    HitBuilder * builder = a->getBuilder();
    QVERIFY(qobject_cast<GoogleBuilder*>(builder));
}

void AnalyticsTestCase::testMatomoTracker()
{
    QScopedPointer<Analytics> a(new Analytics());
    QVariantMap o{
        {"tracker", "matomo"},
    };
    a->context()->updateConfig(o);
    HitBuilder * builder = a->getBuilder();
    QVERIFY(qobject_cast<MatomoBuilder*>(builder));

}

void AnalyticsTestCase::testWrongTracker()
{
    QScopedPointer<Analytics> a(new Analytics());
    QVariantMap o{
        {"tracker", "unknown"},
    };
    a->context()->updateConfig(o);
    HitBuilder * builder = a->getBuilder();
    QCOMPARE(nullptr, builder);

}

void AnalyticsTestCase::testServerConfig()
{
    QScopedPointer<Analytics> a(new Analytics());
    QVariantMap o{
        {"tracker", "matomo"},
        {"server", "http://localhost:8000"},
    };
    a->context()->updateConfig(o);
    HitBuilder *builder = a->getBuilder();
    QVERIFY(qobject_cast<MatomoBuilder*>(builder));
    qDebug() << "003";
    QCOMPARE(builder->context()->configString("server"), "http://localhost:8000");
}


QTEST_MAIN(AnalyticsTestCase)

#include "tst_analytics.moc"
