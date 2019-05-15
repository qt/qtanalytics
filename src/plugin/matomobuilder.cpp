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
#include "matomobuilder.h"

#include "context.h"

/*!
 * \class MatomoBuilder
 * \inmodule QtAnalytics
 * \brief Plugin for the matomo tracking platform.
 */

// See https://developer.matomo.org/api-reference/tracking-api
const QString MatomoBuilder::SITE_ID("idsite");
const QString MatomoBuilder::ACTION_NAME("action_name");
const QString MatomoBuilder::ACTION_URL("url");
const QString MatomoBuilder::API_VERSION("apiv");
const QString MatomoBuilder::EVENT_CATEGORY("e_c");
const QString MatomoBuilder::EVENT_ACTION("e_a");
const QString MatomoBuilder::EVENT_NAME("e_n");
const QString MatomoBuilder::EVENT_VALUE("e_v");
const QString MatomoBuilder::RECORDING("rec");


MatomoBuilder::MatomoBuilder(Context *context, QObject *parent)
    : HitBuilder(context, parent)
{
}

MatomoBuilder::~MatomoBuilder()
{
}

void MatomoBuilder::initQuery()
{
    HitBuilder::initQuery();
    addQueryItem(API_VERSION, "1");
    configQueryItem(SITE_ID);
    addQueryItem(RECORDING, "1");
}

void MatomoBuilder::trackPage(const QString &path, const QString &title)
{
    QString domain = configString("domain");
    QString url = QString("%1/%2").arg(domain).arg(path);
    addQueryItem(ACTION_URL, url);
    addQueryItem(ACTION_NAME, title);
}

void MatomoBuilder::trackEvent(const QString &category, const QString &action, const QString &label, const QString &value)
{
    addQueryItem(EVENT_CATEGORY, category);
    addQueryItem(EVENT_ACTION, action);
    if (!label.isNull()) {
        addQueryItem(EVENT_NAME, label);
    }
    if (!value.isNull()) {
        addQueryItem(EVENT_VALUE, value);
    }
}
