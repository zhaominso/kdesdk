/*
    This file is part of the Okteta Kasten module, made within the KDE community.

    Copyright 2009 Friedrich W. H. Kossebau <kossebau@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BYTEARRAYRANDOMDATAGENERATOR_H
#define BYTEARRAYRANDOMDATAGENERATOR_H

// Kasten core
#include <abstractmodeldatagenerator.h>
// Qt
#include <QtCore/QObject>
#include <QtCore/QString>


namespace Kasten2
{


class ByteArrayRandomDataGeneratorSettings
{
  public:
    ByteArrayRandomDataGeneratorSettings();

  public:
    int size;
};


class ByteArrayRandomDataGenerator : public AbstractModelDataGenerator
{
    Q_OBJECT

  public:
    ByteArrayRandomDataGenerator();

    virtual ~ByteArrayRandomDataGenerator();

  public: // AbstractModelDataGenerator API
    virtual QMimeData* generateData();

  public:
    ByteArrayRandomDataGeneratorSettings settings() const;
    void setSettings( const ByteArrayRandomDataGeneratorSettings& settings );

  protected:
    ByteArrayRandomDataGeneratorSettings mSettings;
};


inline ByteArrayRandomDataGeneratorSettings ByteArrayRandomDataGenerator::settings() const { return mSettings; }
inline void ByteArrayRandomDataGenerator::setSettings( const ByteArrayRandomDataGeneratorSettings& settings )
{
    mSettings = settings;
//     emit settingsChanged();
}

}

#endif
