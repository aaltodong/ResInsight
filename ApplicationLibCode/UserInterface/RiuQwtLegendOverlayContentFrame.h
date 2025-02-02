/////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2022-     Equinor ASA
//
//  ResInsight is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  ResInsight is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.
//
//  See the GNU General Public License at <http://www.gnu.org/licenses/gpl.html>
//  for more details.
//
/////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "RiuAbstractOverlayContentFrame.h"

#include <QPointer>
#include <QString>

#include "qwt_legend.h"

class QLabel;

class RiuQwtLegendOverlayContentFrame : public RiuAbstractOverlayContentFrame
{
    Q_OBJECT
public:
    RiuQwtLegendOverlayContentFrame( QWidget* parent = nullptr );

    void setLegend( QwtLegend* legend );
    void renderTo( QPainter* painter, const QRect& targetRect ) override;

private:
    QPointer<QwtLegend> m_legend;
};
