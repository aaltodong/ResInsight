/////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2020-     Equinor ASA
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

#include "RiuInterfaceToViewWindow.h"

#include "cafPdmPointer.h"

#include <QtCharts/QChartView>

class RimPlotWindow;

//==================================================================================================
//
//==================================================================================================
class RiuQtChartView : public QtCharts::QChartView, public RiuInterfaceToViewWindow
{
public:
    RiuQtChartView( RimPlotWindow* plotWindow, QWidget* parent = nullptr );
    ~RiuQtChartView() override;

    RimViewWindow* ownerViewWindow() const override;

protected:
    void mouseReleaseEvent( QMouseEvent* event ) override;
    void mousePressEvent( QMouseEvent* event ) override;
    void mouseMoveEvent( QMouseEvent* event ) override;

private:
    caf::PdmPointer<RimPlotWindow> m_plotWindow;

    bool   m_isPanning;
    QPoint m_panStartPosition;
};
