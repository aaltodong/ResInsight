/////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2011-2012 Statoil ASA, Ceetron AS
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

#include "RigEclipseResultAddress.h"

#include "RigHistogramData.h"

#include "RigStatisticsDataCache.h"

#include "cvfObject.h"

class RimEclipseResultDefinition;
class RimGeoMechContourMapView;
class RimEclipseContourMapView;
class RimEclipseView;
class RimGeoMechView;

//==================================================================================================
///
///
//==================================================================================================
class RimHistogramCalculator
{
public:
    enum class StatisticsTimeRangeType
    {
        ALL_TIMESTEPS,
        CURRENT_TIMESTEP
    };

    enum class StatisticsCellRangeType
    {
        ALL_CELLS,
        VISIBLE_CELLS
    };

    RimHistogramCalculator();

    void setNumBins( size_t numBins );

    RigHistogramData histogramData( RimEclipseContourMapView* contourMap );
    RigHistogramData histogramData( RimGeoMechContourMapView* contourMap );
    RigHistogramData histogramData( RimEclipseView* eclipseView, StatisticsCellRangeType cellRange, StatisticsTimeRangeType timeRange );

    RigHistogramData histogramData( RimGeoMechView* geoMechView, StatisticsCellRangeType cellRange, StatisticsTimeRangeType timeRange );

    RigHistogramData histogramData( RimEclipseView*             eclipseView,
                                    RimEclipseResultDefinition* eclResultDefinition,
                                    StatisticsCellRangeType     cellRange,
                                    StatisticsTimeRangeType     timeRange,
                                    int                         timeStep );

    void invalidateVisibleCellsCache();

private:
    void updateVisCellStatsIfNeeded( RimEclipseView* eclipseView, RimEclipseResultDefinition* eclResultDefinition );

    void updateVisCellStatsIfNeeded( RimGeoMechView* geoMechView );

    std::vector<RigEclipseResultAddress> sourcesForMultiPropertyResults( const QString& resultName );

    bool                             m_isVisCellStatUpToDate;
    cvf::ref<RigStatisticsDataCache> m_visibleCellStatistics;
    size_t                           m_numBins;
};
