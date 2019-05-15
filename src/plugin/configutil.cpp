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
#include "configutil.h"

/*!
 * \class ConfigUtil
 * \inmodule QtAnalytics
 * \brief A configuration utility.
 */

ConfigUtil::ConfigUtil()
{

}


QString ConfigUtil::resolvePath(const QString &name)
{
    QString upper = name.toUpper();
    QString lower = name.toLower();
    QString path = qEnvironmentVariable(name.toUpper().toLatin1() + "_CONFIG", QString(":/%1.json").arg(name.toLower().data()));
    if (!QFile(path).exists()) {
        qWarning() << "No analytics configuration";
        return QString();
    }
    return path;
}

QByteArray ConfigUtil::readJSON(const QString &path)
{
    if (path.isEmpty()) {
        qWarning() << "invalid config path";
        return QByteArray();
    }
    QFile device(path);
    if (!device.open(QIODevice::ReadOnly)) {
        qWarning() << "Can not open analytics config";
        return QByteArray();
    }
    return device.readAll();
}

QJsonObject ConfigUtil::parseJSON(const QByteArray &data)
{
    if (data.isNull()) {
        qWarning() << "invalid config data";
        return QJsonObject();
    }
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Error parsing analytics settings";
        qWarning() << error.errorString();
        return QJsonObject();
    }
    if (!doc.isObject()) {
        qWarning() << "settings must be a valid JSON object";
        return QJsonObject();
    }
    return doc.object();
}

QJsonObject ConfigUtil::loadJSON(const QString &name)
{
    QString path = resolvePath(name);
    if (path.isEmpty()) {
        return QJsonObject();
    }
    QByteArray data = readJSON(path);
    return parseJSON(data);
}

QJsonObject ConfigUtil::mergeJSON(const QJsonObject &a, const QJsonObject &b)
{
    QJsonObject result(a);
    for (auto key : b.keys()) {
        result.insert(key, b.value(key));
    }
    return result;
}

QVariantMap ConfigUtil::toVariantMap(const QJsonObject &o)
{
    return o.toVariantMap();
}

QVariantMap ConfigUtil::mergeMap(const QVariantMap &a, const QVariantMap &b)
{
    QVariantMap result(a);
    QMapIterator<QString, QVariant> i(b);
    while (i.hasNext()) {
        i.next();
        result.insert(i.key(), i.value());
    }
    return result;
}

