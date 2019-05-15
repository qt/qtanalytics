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

#include "matomobuilder.h"
#include "context.h"

class MatomoTestCase: public QObject {
    Q_OBJECT
private slots:
    void init();
    void testRequired();
    void testTrackPage();
    void testTrackEvent();

};

void MatomoTestCase::init()
{
    qDebug() << "init";
}

void MatomoTestCase::testRequired()
{
    QVariantMap o{
        {"idsite", "123"},
        {"rec", "1"},
    };
    QScopedPointer<Context> ctx(new Context(this));
    ctx->setConfig(o);
    QScopedPointer<MatomoBuilder> b(new MatomoBuilder(ctx.data()));
    b->initQuery();
    QUrlQuery query = b->query();
    QCOMPARE("123", query.queryItemValue(MatomoBuilder::SITE_ID));
    QCOMPARE("1", query.queryItemValue(MatomoBuilder::RECORDING));
}

void MatomoTestCase::testTrackPage()
{
    QScopedPointer<Context> ctx(new Context(this));
    QScopedPointer<MatomoBuilder> b(new MatomoBuilder(ctx.data()));
    b->initQuery();
    b->trackPage("/home", "click");
    QUrlQuery query = b->query();
    qDebug() << query.toString();
    QCOMPARE("/home", query.queryItemValue(MatomoBuilder::ACTION_URL));
    QCOMPARE("click", query.queryItemValue(MatomoBuilder::ACTION_NAME));
}

void MatomoTestCase::testTrackEvent()
{
    QScopedPointer<Context> ctx(new Context(this));
    QScopedPointer<MatomoBuilder> b(new MatomoBuilder(ctx.data()));
    b->initQuery();
    b->trackEvent("category", "action", QString(), QString());
    QUrlQuery query = b->query();
    qDebug() << query.toString();
    QCOMPARE("category", query.queryItemValue(MatomoBuilder::EVENT_CATEGORY));
    QCOMPARE("action", query.queryItemValue(MatomoBuilder::EVENT_ACTION));
}

QTEST_MAIN(MatomoTestCase)

#include "tst_matomo.moc"
