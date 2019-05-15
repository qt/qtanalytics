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

#include "googlebuilder.h"
#include "context.h"

class GoogleTestCase: public QObject {
    Q_OBJECT
private slots:
    void testEmpty();
    void testTrackPage();
    void testTrackEvent();
};


void GoogleTestCase::testEmpty()
{
    QVariantMap o{
        {"tid", "12345"},
    };
    QScopedPointer<Context> ctx(new Context(this));
    ctx->setConfig(o);
    QScopedPointer<GoogleBuilder> b(new GoogleBuilder(ctx.data()));
    b->initQuery();
    QUrlQuery query = b->query();
    QCOMPARE("1", query.queryItemValue(GoogleBuilder::VERSION));
    QCOMPARE("12345", query.queryItemValue(GoogleBuilder::TRACKER_ID));
    ctx->deleteLater();
}

void GoogleTestCase::testTrackPage()
{
    QScopedPointer<Context> ctx(new Context(this));
    QScopedPointer<GoogleBuilder> b(new GoogleBuilder(ctx.data()));
    QVariantMap o{
        {"tid", "12345"},
        {"cid", "44144"},
    };
    ctx->updateConfig(o);
    b->initQuery();
    b->trackPage("/home", "click");
    QUrlQuery query = b->query();
    QCOMPARE("12345", query.queryItemValue("tid"));
    QCOMPARE("44144", query.queryItemValue("cid"));
    QCOMPARE("1", query.queryItemValue("v"));
    QCOMPARE("pageview", query.queryItemValue("t"));
    QCOMPARE("/home", query.queryItemValue("dp"));
    QCOMPARE(b->url().toString(), "https://www.google-analytics.com/collect");
}

void GoogleTestCase::testTrackEvent()
{
    QScopedPointer<Context> ctx(new Context(this));
    QVariantMap o{
        {"tid", "12345"},
        {"cid", "44144"},
    };
    ctx->updateConfig(o);
    QScopedPointer<GoogleBuilder> b(new GoogleBuilder(ctx.data()));
    b->trackEvent("cat", "click", QString(), QString());
    b->initQuery();
    QUrlQuery query = b->query();
    QCOMPARE("12345", query.queryItemValue("tid"));
    QCOMPARE("44144", query.queryItemValue("cid"));
    QCOMPARE("cat", query.queryItemValue("ec"));
    QCOMPARE("click", query.queryItemValue("ea"));
    QCOMPARE(b->url().toString(), "https://www.google-analytics.com/collect");
}

QTEST_MAIN(GoogleTestCase)

#include "tst_google.moc"
