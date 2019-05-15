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
#pragma once

#include <QtCore>

#include "hitbuilder.h"

class Context;

class GoogleBuilder : public HitBuilder
{
    Q_OBJECT
public:
    static const QString TRACKER_ID;
    static const QString VERSION;
    static const QString DATA_SOURCE;
    static const QString DOCUMENT_PATH;
    static const QString DOCUMENT_TITLE;
    static const QString EVENT_CATEGORY;
    static const QString EVENT_ACTION;
    static const QString EVENT_LABEL;
    static const QString EVENT_VALUE;
    static const QString HIT_TYPE;
    static const QString CLIENT_ID;

    explicit GoogleBuilder(Context *context, QObject *parent=nullptr);
    ~GoogleBuilder();

    // HitBuilder interface
public:
    void initQuery();
    void trackPage(const QString &path, const QString &title);
    void trackEvent(const QString &category, const QString &action, const QString &label, const QString &value);
    QNetworkReply *sendQuery();
};
