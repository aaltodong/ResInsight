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

#include "RifEclipseRestartDataAccess.h"

#include "ert/ecl/ecl_util.h"

#include "cvfObject.h"

#include <QDateTime>
#include <QString>
#include <QStringList>

#include <vector>

using ecl_file_type = struct ecl_file_struct;

class RifEclipseRestartDataAccess;
class RigEclipseTimeStepInfo;
class RigActiveCellInfo;
class QByteArray;

//==================================================================================================
//
//
//
//==================================================================================================
class RifEclipseOutputFileTools
{
public:
    RifEclipseOutputFileTools();
    virtual ~RifEclipseOutputFileTools();

    static std::vector<RifKeywordValueCount> keywordValueCounts( const std::vector<ecl_file_type*>& ecl_files );

    static void createResultEntries( const std::vector<RifKeywordValueCount>&   fileKeywordInfo,
                                     const std::vector<RigEclipseTimeStepInfo>& timeStepInfo,
                                     RiaDefines::ResultCatType                  resultCategory,
                                     RigEclipseCaseData*                        eclipseCaseData );

    static bool keywordData( const ecl_file_type* ecl_file, const QString& keyword, size_t fileKeywordOccurrence, std::vector<double>* values );
    static bool keywordData( const ecl_file_type* ecl_file, const QString& keyword, size_t fileKeywordOccurrence, std::vector<int>* values );

    static void timeSteps( const ecl_file_type*    ecl_file,
                           std::vector<QDateTime>* timeSteps,
                           std::vector<double>*    daysSinceSimulationStart,
                           size_t*                 perTimeStepHeaderKeywordCount );

    static bool       isValidEclipseFileName( const QString& fileName );
    static QByteArray md5sum( const QString& fileName );
    static bool       findSiblingFilesWithSameBaseName( const QString& fileName, QStringList* fileSet );

    static QString     firstFileNameOfType( const QStringList& fileSet, ecl_file_enum fileType );
    static QStringList filterFileNamesOfType( const QStringList& fileSet, ecl_file_enum fileType );

    static void readGridDimensions( const QString& gridFileName, std::vector<std::vector<int>>& gridDimensions );

    static int readUnitsType( const ecl_file_type* ecl_file );

    static cvf::ref<RifEclipseRestartDataAccess> createDynamicResultAccess( const QString& fileName );

    static QString createIndexFileName( const QString& resultFileName );

    static std::set<RiaDefines::PhaseType> findAvailablePhases( const ecl_file_type* ecl_file );

    static void transferNncFluxData( const ecl_grid_type*      grid,
                                     const ecl_file_view_type* summaryView,
                                     std::vector<double>*      waterFlux,
                                     std::vector<double>*      oilFlux,
                                     std::vector<double>*      gasFlux );

    static bool isExportedFromIntersect( const ecl_file_type* ecl_file );

    static FILE* fopen( const QString& filePath, const QString& mode );

    static bool assignActiveCellData( std::vector<std::vector<int>>& actnumValuesPerGrid, RigEclipseCaseData* eclipseCaseData );

private:
    static RifRestartReportKeywords          createReportStepsMetaData( const std::vector<ecl_file_type*>& ecl_files );
    static std::vector<RifKeywordValueCount> validKeywordsForPorosityModel( const std::vector<RifKeywordValueCount>& keywordItemCounts,
                                                                            const RigActiveCellInfo*                 activeCellInfo,
                                                                            const RigActiveCellInfo*                 fractureActiveCellInfo,
                                                                            RiaDefines::PorosityModelType            matrixOrFracture,
                                                                            size_t                                   timeStepCount );
};
