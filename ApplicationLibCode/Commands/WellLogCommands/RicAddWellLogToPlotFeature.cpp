/////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2015-     Statoil ASA
//  Copyright (C) 2015-     Ceetron Solutions AS
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

#include "RicAddWellLogToPlotFeature.h"

#include "RicNewWellLogPlotFeatureImpl.h"
#include "RicWellLogPlotCurveFeatureImpl.h"

#include "RimMainPlotCollection.h"
#include "RimProject.h"
#include "RimWellLogFileChannel.h"
#include "RimWellLogLasFile.h"
#include "RimWellLogLasFileCurve.h"
#include "RimWellLogPlot.h"
#include "RimWellLogPlotCollection.h"
#include "RimWellLogTrack.h"
#include "RimWellPath.h"
#include "RimWellPathCollection.h"
#include "RiuPlotMainWindowTools.h"

#include "RigWellLogLasFile.h"

#include "RiuQwtPlotWidget.h"

#include "cafSelectionManager.h"

#include <QAction>

CAF_CMD_SOURCE_INIT( RicAddWellLogToPlotFeature, "RicAddWellLogToPlotFeature" );

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
bool RicAddWellLogToPlotFeature::isCommandEnabled() const
{
    std::vector<RimWellLogFileChannel*> selection = selectedWellLogs();
    return !selection.empty();
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
void RicAddWellLogToPlotFeature::onActionTriggered( bool isChecked )
{
    std::vector<RimWellLogFileChannel*> selection = selectedWellLogs();
    if ( selection.empty() ) return;

    RimWellLogPlot* plot = RicNewWellLogPlotFeatureImpl::createWellLogPlot();

    RimWellLogTrack* plotTrack = new RimWellLogTrack();
    plot->addPlot( plotTrack );
    plotTrack->setDescription( QString( "Track %1" ).arg( plot->plotCount() ) );

    plot->loadDataAndUpdate();

    for ( size_t wlIdx = 0; wlIdx < selection.size(); wlIdx++ )
    {
        RimWellLogFileChannel* wellLog = selection[wlIdx];

        auto wellPath    = wellLog->firstAncestorOrThisOfType<RimWellPath>();
        auto wellLogFile = wellLog->firstAncestorOrThisOfType<RimWellLogLasFile>();
        if ( wellLogFile )
        {
            RimWellLogLasFileCurve* curve      = new RimWellLogLasFileCurve;
            cvf::Color3f            curveColor = RicWellLogPlotCurveFeatureImpl::curveColorFromTable( plotTrack->curveCount() );
            curve->setColor( curveColor );

            plotTrack->addCurve( curve );

            RigWellLogLasFile* wellLogDataFile = wellLogFile->wellLogFileData();
            CVF_ASSERT( wellLogDataFile );

            if ( wlIdx == 0 )
            {
                // Initialize plot with depth unit from the first log file
                plot->setDepthUnit( wellLogDataFile->depthUnit() );
            }

            curve->setWellPath( wellPath );
            curve->setWellLogChannelName( wellLog->name() );
            curve->setWellLogFile( wellLogFile );

            curve->loadDataAndUpdate( true );
        }
    }
    plot->updateLayout();

    RiuPlotMainWindowTools::showPlotMainWindow();
    RiuPlotMainWindowTools::onObjectAppended( plot, plotTrack );
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
void RicAddWellLogToPlotFeature::setupActionLook( QAction* actionToSetup )
{
    actionToSetup->setText( "Add To New Plot" );
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
std::vector<RimWellLogFileChannel*> RicAddWellLogToPlotFeature::selectedWellLogs()
{
    std::vector<RimWellLogFileChannel*> selection;
    caf::SelectionManager::instance()->objectsByType( &selection );
    return selection;
}
