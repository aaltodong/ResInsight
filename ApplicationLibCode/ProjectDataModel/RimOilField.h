/////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2011-     Statoil ASA
//  Copyright (C) 2013-     Ceetron Solutions AS
//  Copyright (C) 2011-2012 Ceetron AS
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

#include "cafPdmChildField.h"
#include "cafPdmField.h"
#include "cafPdmObject.h"
#include "cafPdmPointer.h"

class RimEclipseCaseCollection;
class RimFormationNamesCollection;
class RimFractureTemplateCollection;
class RimCompletionTemplateCollection;
class RimValveTemplateCollection;
class RimGeoMechModels;
class RimObservedDataCollection;
class RimSummaryCase;
class RimSummaryCaseMainCollection;
class RimWellPathCollection;
class RimAnnotationCollection;
class RimMeasurement;
class RimSeismicDataCollection;
class RimSeismicViewCollection;
class RimSurfaceCollection;
class RimEnsembleWellLogsCollection;
class RimPolygonCollection;
class RimEclipseViewCollection;
class RimEclipseContourMapViewCollection;

//==================================================================================================
///
///
//==================================================================================================
class RimOilField : public caf::PdmObject
{
    CAF_PDM_HEADER_INIT;

public:
    RimOilField();
    ~RimOilField() override;

    RimFractureTemplateCollection*       fractureDefinitionCollection();
    const RimFractureTemplateCollection* fractureDefinitionCollection() const;

    RimValveTemplateCollection*       valveTemplateCollection();
    const RimValveTemplateCollection* valveTemplateCollection() const;

    caf::PdmChildField<RimEclipseCaseCollection*>           analysisModels;
    caf::PdmChildField<RimGeoMechModels*>                   geoMechModels;
    caf::PdmChildField<RimWellPathCollection*>              wellPathCollection;
    caf::PdmChildField<RimCompletionTemplateCollection*>    completionTemplateCollection;
    caf::PdmChildField<RimSummaryCaseMainCollection*>       summaryCaseMainCollection;
    caf::PdmChildField<RimObservedDataCollection*>          observedDataCollection;
    caf::PdmChildField<RimFormationNamesCollection*>        formationNamesCollection;
    caf::PdmChildField<RimAnnotationCollection*>            annotationCollection;
    caf::PdmChildField<RimMeasurement*>                     measurement;
    caf::PdmChildField<RimSurfaceCollection*>               surfaceCollection;
    caf::PdmChildField<RimSeismicDataCollection*>           seismicDataCollection;
    caf::PdmChildField<RimSeismicViewCollection*>           seismicViewCollection;
    caf::PdmChildField<RimEclipseViewCollection*>           eclipseViewCollection;
    caf::PdmChildField<RimEnsembleWellLogsCollection*>      ensembleWellLogsCollection;
    caf::PdmChildField<RimPolygonCollection*>               polygonCollection;
    caf::PdmChildField<RimEclipseContourMapViewCollection*> eclipseContourMapCollection;

protected:
    void initAfterRead() override;

private:
    caf::PdmChildField<RimFractureTemplateCollection*> m_fractureTemplateCollection_OBSOLETE;
};
