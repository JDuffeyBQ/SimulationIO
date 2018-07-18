/*
 * Your License or Copyright can go here
 */

#pragma once

#include <QtCore/QString>

#include "SIMPLib/CoreFilters/FileWriter.h"
#include "SIMPLib/DataArrays/StringDataArray.hpp"

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/DataArrays/IDataArray.h"
#include "SIMPLib/DataContainers/DataContainer.h"
#include "SIMPLib/FilterParameters/FloatVec3FilterParameter.h"
#include "SIMPLib/FilterParameters/IntVec3FilterParameter.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/Geometry/MeshStructs.h"
#include "SIMPLib/SIMPLib.h"


/**
 * @brief The Export3dSolidMesh class. See [Filter documentation](@ref export3dsolidmesh) for details.
 */
class Export3dSolidMesh : public AbstractFilter
{
  Q_OBJECT

  public:
    SIMPL_SHARED_POINTERS(Export3dSolidMesh )
    SIMPL_STATIC_NEW_MACRO(Export3dSolidMesh )
    SIMPL_TYPE_MACRO_SUPER(Export3dSolidMesh , AbstractFilter)

    virtual ~Export3dSolidMesh ();

    SIMPL_FILTER_PARAMETER(QString, JobName)
    Q_PROPERTY(QString JobName READ getJobName WRITE setJobName)

    SIMPL_FILTER_PARAMETER(QString, NodesFile)
    Q_PROPERTY(QString NodesFile READ getNodesFile WRITE setNodesFile)

    SIMPL_FILTER_PARAMETER(QString, ConnectivityFile)
    Q_PROPERTY(QString ConnectivityFile READ getConnectivityFile WRITE setConnectivityFile)

    SIMPL_FILTER_PARAMETER(QString, AbaqusInputFile)
    Q_PROPERTY(QString AbaqusInputFile READ getAbaqusInputFile WRITE setAbaqusInputFile)

    SIMPL_FILTER_PARAMETER(FloatVec3_t, BoxSize)
    Q_PROPERTY(FloatVec3_t BoxSize READ getBoxSize WRITE setBoxSize)
    
    SIMPL_FILTER_PARAMETER(IntVec3_t, numElem)
    Q_PROPERTY(IntVec3_t numElem READ getnumElem WRITE setnumElem)

    SIMPL_FILTER_PARAMETER(DataArrayPath, FeatureIdsArrayPath)
    Q_PROPERTY(DataArrayPath FeatureIdsArrayPath READ getFeatureIdsArrayPath WRITE setFeatureIdsArrayPath)

    SIMPL_FILTER_PARAMETER(DataArrayPath, CellPhasesArrayPath)
    Q_PROPERTY(DataArrayPath CellPhasesArrayPath READ getCellPhasesArrayPath WRITE setCellPhasesArrayPath)

    SIMPL_FILTER_PARAMETER(DataArrayPath, CellEulerAnglesArrayPath)
    Q_PROPERTY(DataArrayPath CellEulerAnglesArrayPath READ getCellEulerAnglesArrayPath WRITE setCellEulerAnglesArrayPath)

    /**
     * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getCompiledLibraryName() const override;

    /**
     * @brief getBrandingString Returns the branding string for the filter, which is a tag
     * used to denote the filter's association with specific plugins
     * @return Branding string
    */
    virtual const QString getBrandingString() const override;

    /**
     * @brief getFilterVersion Returns a version string for this filter. Default
     * value is an empty string.
     * @return
     */
    virtual const QString getFilterVersion() const override;

    /**
     * @brief newFilterInstance Reimplemented from @see AbstractFilter class
     */
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

    /**
     * @brief getGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getGroupName() const override;

    /**
     * @brief getSubGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getSubGroupName() const override;

    /**
     * @brief getUuid Return the unique identifier for this filter.
     * @return A QUuid object.
     */
    virtual const QUuid getUuid() override;
  
    /**
     * @brief getHumanLabel Reimplemented from @see AbstractFilter class
     */
    virtual const QString getHumanLabel() const override;

    /**
     * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
     */
    virtual void setupFilterParameters() override;

    /**
      * @brief readFilterParameters Reimplemented from @see AbstractFilter class
      */
     virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;


    /**
     * @brief execute Reimplemented from @see AbstractFilter class
     */
    virtual void execute() override;

    /**
    * @brief preflight Reimplemented from @see AbstractFilter class
    */
    virtual void preflight() override;

  signals:
    /**
     * @brief updateFilterParameters Emitted when the Filter requests all the latest Filter parameters
     * be pushed from a user-facing control (such as a widget)
     * @param filter Filter instance pointer 
     */
    void updateFilterParameters(AbstractFilter* filter);

    /**
     * @brief parametersChanged Emitted when any Filter parameter is changed internally
     */
    void parametersChanged();

    /**
     * @brief preflightAboutToExecute Emitted just before calling dataCheck()
     */
    void preflightAboutToExecute();

    /**
     * @brief preflightExecuted Emitted just after calling dataCheck()
     */
    void preflightExecuted();

  protected:
    Export3dSolidMesh ();

    /**
    * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
    */
    void dataCheck();

    /**
    * @brief Initializes all the private instance variables.
    */
    void initialize();

 private:
    DEFINE_DATAARRAY_VARIABLE(int32_t, FeatureIds)
    DEFINE_DATAARRAY_VARIABLE(int32_t, CellPhases)
    DEFINE_DATAARRAY_VARIABLE(float, CellEulerAngles)
      
    Export3dSolidMesh (const Export3dSolidMesh &) = delete; // Copy Constructor Not Implemented
    void operator=(const Export3dSolidMesh &); // Operator '=' Not Implemented
};

