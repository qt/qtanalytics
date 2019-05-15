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

#include "matomotracker.h"

/*
 * The tracking API is documented at:
 * https://developer.matomo.org/api-reference/tracking-api
 */

class UrlBuilderTestCase: public QObject {
    Q_OBJECT
public:
    explicit UrlBuilderTestCase();
private Q_SLOTS:
    void init();
    void cleanup();
    void testDefault();
    void testPing();
    void testVisit();
    void testEvent();
private:
};


UrlBuilderTestCase::UrlBuilderTestCase()
    : QObject ()
{
}

void UrlBuilderTestCase::init()
{
}

void UrlBuilderTestCase::cleanup()
{
}


void UrlBuilderTestCase::testDefault()
{
}
void UrlBuilderTestCase::testPing()
{
}

void UrlBuilderTestCase::testVisit()
{
}

void UrlBuilderTestCase::testEvent()
{
}

QTEST_MAIN(UrlBuilderTestCase)

#include "tst_urlbuilder.moc"
