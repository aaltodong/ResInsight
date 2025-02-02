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

#pragma once

#include "RimAbstractPlotCollection.h"

#include "cafPdmChildArrayField.h"
#include "cafPdmField.h"
#include "cafPdmObject.h"
#include "cvfCollection.h"

#include <gsl/gsl>

class RimWellLogPlot;
class RigEclipseWellLogExtractor;
class RigGeoMechWellLogExtractor;
class RimGeoMechCase;
class RigEclipseCaseData;
class RigGeoMechCaseData;
class RigWellPath;
class RimWellPath;
class RimEclipseCase;

//==================================================================================================
///
///
//==================================================================================================
class RimWellLogPlotCollection : public caf::PdmObject, public RimPlotCollection
{
    CAF_PDM_HEADER_INIT;

public:
    RimWellLogPlotCollection();
    ~RimWellLogPlotCollection() override;

    RigEclipseWellLogExtractor* findOrCreateSimWellExtractor( const QString&            simWellName,
                                                              const QString&            caseUserDescription,
                                                              const RigWellPath*        wellPathGeometry,
                                                              const RigEclipseCaseData* eclCaseData );

    RigEclipseWellLogExtractor* findOrCreateExtractor( RimWellPath* wellPath, RimEclipseCase* eclCase );
    RigGeoMechWellLogExtractor* findOrCreateExtractor( RimWellPath* wellPath, RimGeoMechCase* geoMechCase, int partId = 0 );

    std::vector<RimWellLogPlot*> wellLogPlots() const;

    void   addWellLogPlot( gsl::not_null<RimWellLogPlot*> wellLogPlot );
    void   removePlot( gsl::not_null<RimWellLogPlot*> plot );
    void   deleteAllPlots() override;
    void   loadDataAndUpdateAllPlots() override;
    size_t plotCount() const override;

    void deleteAllExtractors();
    void removeExtractors( const RigWellPath* wellPathGeometry );
    void removeExtractors( const RigEclipseCaseData* caseData );
    void removeExtractors( const RigGeoMechCaseData* caseData );

private:
    void onChildDeleted( caf::PdmChildArrayFieldHandle* childArray, std::vector<caf::PdmObjectHandle*>& referringObjects ) override;

    caf::PdmChildArrayField<RimWellLogPlot*>    m_wellLogPlots;
    cvf::Collection<RigEclipseWellLogExtractor> m_extractors;
    cvf::Collection<RigGeoMechWellLogExtractor> m_geomExtractors;
};
