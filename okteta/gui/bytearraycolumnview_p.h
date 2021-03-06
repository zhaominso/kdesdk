/*
    This file is part of the Okteta Gui library, made within the KDE community.

    Copyright 2003,2007-2010 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef OKTETA_BYTEARRAYCOLUMNVIEW_P_H
#define OKTETA_BYTEARRAYCOLUMNVIEW_P_H

// lib
#include "bytearraycolumnview.h"
#include "abstractbytearrayview_p.h"
#include "valuebytearraycolumnrenderer.h"
#include "charbytearraycolumnrenderer.h"


namespace Okteta
{
class Coord;


class ByteArrayColumnViewPrivate : public AbstractByteArrayViewPrivate
{
    Q_DECLARE_PUBLIC( ByteArrayColumnView )

  public:
    explicit ByteArrayColumnViewPrivate( ByteArrayColumnView* parent );
    virtual ~ByteArrayColumnViewPrivate();

  public:
    void init();

  public:
  // value column
    int/*PixelX*/ byteSpacingWidth() const;
    int noOfGroupedBytes() const;
    int/*PixelX*/ groupSpacingWidth() const;
    int/*PixelX*/ binaryGapWidth() const;

  // char column
    bool showsNonprinting() const;
    QChar substituteChar() const;
    QChar undefinedChar() const;

    bool isByteTypeColored() const;

  public: // logic value service
    QSize minimumSizeHint() const;

  public: // modification access
    void setByteArrayModel( AbstractByteArrayModel* byteArrayModel );
//    void repaintByte( int row, int column, bool Erase = true );
//    void updateByte( int row, int column );
//    void ensureByteVisible( int row, int column );

  public: // AbstractByteArrayViewPrivate API
    virtual void ensureVisible( const AddressRange& range, bool ensureStartVisible );
    virtual void ensureCursorVisible();
    virtual void placeCursor( const QPoint& point );
    virtual QRect cursorRect() const;
    virtual Address indexByPoint( const QPoint& point ) const;
    virtual void blinkCursor();

  public:
  // value column parameters
    void setByteSpacingWidth( int/*PixelX*/ byteSpacingWidth ) ;
    void setNoOfGroupedBytes( int noOfGroupedBytes );
    void setGroupSpacingWidth( int/*PixelX*/ groupSpacingWidth );
    void setBinaryGapWidth( int binaryGapWidth );
    void setBufferSpacing( /*PixelX*/int byteSpacingWidth, int noOfGroupedBytes, /*PixelX*/int groupSpacingWidth );
    void setValueCoding( AbstractByteArrayView::ValueCoding valueCoding );
  // char column parameters
    void setShowsNonprinting( bool showsNonprinting = true );
    void setSubstituteChar( QChar substituteChar );
    void setUndefinedChar( QChar undefinedChar );
    void setCharCoding( AbstractByteArrayView::CharCoding charCoding );
    void setCharCoding( const QString& charCodingName );
    void setByteTypeColored( bool isColored );

  protected: // drawing related operations
    /** recreates the cursor pixmaps and paints active and inactive cursors if doable */
    void createCursorPixmaps();
    /** draws the blinking cursor or removes it */
    void drawActiveCursor( QPainter* painter );
    void drawInactiveCursor( QPainter* painter );
    void updateCursor( const AbstractByteArrayColumnRenderer& column );

  protected: // partial operations
    void changeEvent( QEvent* event );

  protected:
    /** recalcs a layout due to the resize style that fits into the view size
      * and updates the dependant values
      */
    void ensureVisible( const AbstractByteArrayColumnRenderer& column, const Coord& coord );
    void renderColumns( QPainter* painter, int cx, int cy, int cw, int ch );

  protected: // AbstractByteArrayViewPrivate API
  // cursor control
    virtual void pauseCursor();
    virtual void updateCursors();

    virtual void setActiveCoding( AbstractByteArrayView::CodingTypeId codingId );
    virtual void setVisibleCodings( int visibleCodings );

  protected: // AbstractByteArrayViewPrivate API
    virtual AbstractByteArrayView::CodingTypeId activeCoding() const;
    virtual AbstractByteArrayView::CodingTypes visibleCodings() const;
    virtual int fittingBytesPerLine() const;
    virtual void adjustToLayoutNoOfBytesPerLine();
    virtual void updateChanged();

  protected:
    ValueByteArrayColumnRenderer* mValueColumn;
    BorderColumnRenderer*         mMiddleBorderColumn;
    CharByteArrayColumnRenderer*  mCharColumn;

    /** points to the column with keyboard focus */
    AbstractByteArrayColumnRenderer* mActiveColumn;
    /** points to the column without keyboard focus (if there is) */
    AbstractByteArrayColumnRenderer* mInactiveColumn;
};


inline PixelX ByteArrayColumnViewPrivate::byteSpacingWidth()  const { return mValueColumn->byteSpacingWidth(); }
inline int ByteArrayColumnViewPrivate::noOfGroupedBytes()      const { return mValueColumn->noOfGroupedBytes(); }
inline PixelX ByteArrayColumnViewPrivate::groupSpacingWidth() const { return mValueColumn->groupSpacingWidth(); }
inline PixelX ByteArrayColumnViewPrivate::binaryGapWidth()    const { return mValueColumn->binaryGapWidth(); }
inline bool ByteArrayColumnViewPrivate::showsNonprinting()     const { return mCharColumn->isShowingNonprinting(); }
inline QChar ByteArrayColumnViewPrivate::substituteChar()      const { return mCharColumn->substituteChar(); }
inline QChar ByteArrayColumnViewPrivate::undefinedChar()       const { return mCharColumn->undefinedChar(); }
inline bool ByteArrayColumnViewPrivate::isByteTypeColored()    const { return mValueColumn->isByteTypeColored(); }

}

#endif
