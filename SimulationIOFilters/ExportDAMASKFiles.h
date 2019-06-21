/*
 * Your License or Copyright can go here
 */

#pragma once

#include <QtCore/QString>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/CoreFilters/FileWriter.h"
#include "SIMPLib/DataArrays/IDataArray.h"
#include "SIMPLib/DataArrays/StringDataArray.h"
#include "SIMPLib/DataContainers/DataContainer.h"
#include "SIMPLib/FilterParameters/DynamicTableData.h"
#include "SIMPLib/FilterParameters/FloatVec3FilterParameter.h"
#include "SIMPLib/FilterParameters/IntVec3FilterParameter.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/Geometry/MeshStructs.h"
#include "SIMPLib/DataArrays/DataArray.hpp"

#include "SimulationIO/SimulationIOPlugin.h"

/**
 * @brief The ExportDAMASKFiles class. See [Filter documentation](@ref exportdamaskfiles) for details.
 */
class SimulationIO_EXPORT ExportDAMASKFiles : public AbstractFilter
{
  Q_OBJECT

#ifdef SIMPL_ENABLE_PYTHON
  PYB11_CREATE_BINDINGS(ExportDAMASKFiles SUPERCLASS AbstractFilter)
  PYB11_SHARED_POINTERS(ExportDAMASKFiles)
  PYB11_FILTER_NEW_MACRO(ExportDAMASKFiles)
  PYB11_FILTER_PARAMETER(int, DataFormat)
  PYB11_FILTER_PARAMETER(QString, OutputPath)
  PYB11_FILTER_PARAMETER(QString, GeometryFileName)
  PYB11_FILTER_PARAMETER(int, HomogenizationIndex)
  PYB11_FILTER_PARAMETER(DataArrayPath, FeatureIdsArrayPath)
  PYB11_FILTER_PARAMETER(DataArrayPath, CellPhasesArrayPath)
  PYB11_FILTER_PARAMETER(DataArrayPath, CellEulerAnglesArrayPath)
  PYB11_FILTER_PARAMETER(bool, CompressGeomFile)
  PYB11_PROPERTY(int DataFormat READ getDataFormat WRITE setDataFormat)
  PYB11_PROPERTY(QString OutputPath READ getOutputPath WRITE setOutputPath)
  PYB11_PROPERTY(QString GeometryFileName READ getGeometryFileName WRITE setGeometryFileName)
  PYB11_PROPERTY(int HomogenizationIndex READ getHomogenizationIndex WRITE setHomogenizationIndex)
  PYB11_PROPERTY(DataArrayPath FeatureIdsArrayPath READ getFeatureIdsArrayPath WRITE setFeatureIdsArrayPath)
  PYB11_PROPERTY(DataArrayPath CellPhasesArrayPath READ getCellPhasesArrayPath WRITE setCellPhasesArrayPath)
  PYB11_PROPERTY(DataArrayPath CellEulerAnglesArrayPath READ getCellEulerAnglesArrayPath WRITE setCellEulerAnglesArrayPath)
  PYB11_PROPERTY(bool CompressGeomFile READ getCompressGeomFile WRITE setCompressGeomFile)
#endif

public:
  using Self = ExportDAMASKFiles;
  using Pointer = std::shared_ptr<Self>;
  using ConstPointer = std::shared_ptr<const Self>;
  using WeakPointer = std::weak_ptr<Self>;
  using ConstWeakPointer = std::weak_ptr<Self>;
  static Pointer NullPointer();

  static std::shared_ptr<ExportDAMASKFiles> New();

  /**
   * @brief Returns the name of the class for _SUPERExportDAMASKFiles
   */
  const QString getNameOfClass() const override;
  /**
   * @brief Returns the name of the class for _SUPERExportDAMASKFiles
   */
  static QString ClassName();

  ~ExportDAMASKFiles() override;

  /**
   * @brief Setter property for DataFormat
   */
  void setDataFormat(int value);
  /**
   * @brief Getter property for DataFormat
   * @return Value of DataFormat
   */
  int getDataFormat() const;

  Q_PROPERTY(int DataFormat READ getDataFormat WRITE setDataFormat)

  /**
   * @brief Setter property for OutputPath
   */
  void setOutputPath(const QString& value);
  /**
   * @brief Getter property for OutputPath
   * @return Value of OutputPath
   */
  QString getOutputPath() const;

  Q_PROPERTY(QString OutputPath READ getOutputPath WRITE setOutputPath)

  /**
   * @brief Setter property for GeometryFileName
   */
  void setGeometryFileName(const QString& value);
  /**
   * @brief Getter property for GeometryFileName
   * @return Value of GeometryFileName
   */
  QString getGeometryFileName() const;

  Q_PROPERTY(QString GeometryFileName READ getGeometryFileName WRITE setGeometryFileName)

  /**
   * @brief Setter property for HomogenizationIndex
   */
  void setHomogenizationIndex(int value);
  /**
   * @brief Getter property for HomogenizationIndex
   * @return Value of HomogenizationIndex
   */
  int getHomogenizationIndex() const;

  Q_PROPERTY(int HomogenizationIndex READ getHomogenizationIndex WRITE setHomogenizationIndex)

  /**
   * @brief Setter property for FeatureIdsArrayPath
   */
  void setFeatureIdsArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for FeatureIdsArrayPath
   * @return Value of FeatureIdsArrayPath
   */
  DataArrayPath getFeatureIdsArrayPath() const;

  Q_PROPERTY(DataArrayPath FeatureIdsArrayPath READ getFeatureIdsArrayPath WRITE setFeatureIdsArrayPath)

  /**
   * @brief Setter property for CellPhasesArrayPath
   */
  void setCellPhasesArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for CellPhasesArrayPath
   * @return Value of CellPhasesArrayPath
   */
  DataArrayPath getCellPhasesArrayPath() const;

  Q_PROPERTY(DataArrayPath CellPhasesArrayPath READ getCellPhasesArrayPath WRITE setCellPhasesArrayPath)

  /**
   * @brief Setter property for CellEulerAnglesArrayPath
   */
  void setCellEulerAnglesArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for CellEulerAnglesArrayPath
   * @return Value of CellEulerAnglesArrayPath
   */
  DataArrayPath getCellEulerAnglesArrayPath() const;

  Q_PROPERTY(DataArrayPath CellEulerAnglesArrayPath READ getCellEulerAnglesArrayPath WRITE setCellEulerAnglesArrayPath)

  /**
   * @brief Setter property for CompressGeomFile
   */
  void setCompressGeomFile(bool value);
  /**
   * @brief Getter property for CompressGeomFile
   * @return Value of CompressGeomFile
   */
  bool getCompressGeomFile() const;

  Q_PROPERTY(bool CompressGeomFile READ getCompressGeomFile WRITE setCompressGeomFile)

  /**
   * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
   */
  const QString getCompiledLibraryName() const override;

  /**
   * @brief getBrandingString Returns the branding string for the filter, which is a tag
   * used to denote the filter's association with specific plugins
   * @return Branding string
   */
  const QString getBrandingString() const override;

  /**
   * @brief getFilterVersion Returns a version string for this filter. Default
   * value is an empty string.
   * @return
   */
  const QString getFilterVersion() const override;

  /**
   * @brief newFilterInstance Reimplemented from @see AbstractFilter class
   */
  AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

  /**
   * @brief getGroupName Reimplemented from @see AbstractFilter class
   */
  const QString getGroupName() const override;

  /**
   * @brief getSubGroupName Reimplemented from @see AbstractFilter class
   */
  const QString getSubGroupName() const override;

  /**
   * @brief getUuid Return the unique identifier for this filter.
   * @return A QUuid object.
   */
  const QUuid getUuid() override;

  /**
   * @brief getHumanLabel Reimplemented from @see AbstractFilter class
   */
  const QString getHumanLabel() const override;

  /**
   * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
   */
  void setupFilterParameters() override;

  /**
   * @brief This method will read the options from a file
   * @param reader The reader that is used to read the options from a file
   */
  void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

  /**
   * @brief execute Reimplemented from @see AbstractFilter class
   */
  void execute() override;

  /**
   * @brief preflight Reimplemented from @see AbstractFilter class
   */
  void preflight() override;

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
  ExportDAMASKFiles();

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

private:
  std::weak_ptr<DataArray<int32_t>> m_FeatureIdsPtr;
  int32_t* m_FeatureIds = nullptr;
  std::weak_ptr<DataArray<int32_t>> m_CellPhasesPtr;
  int32_t* m_CellPhases = nullptr;
  std::weak_ptr<DataArray<float>> m_CellEulerAnglesPtr;
  float* m_CellEulerAngles = nullptr;

  int m_DataFormat = {};
  QString m_OutputPath = {};
  QString m_GeometryFileName = {};
  int m_HomogenizationIndex = {};
  DataArrayPath m_FeatureIdsArrayPath = {};
  DataArrayPath m_CellPhasesArrayPath = {};
  DataArrayPath m_CellEulerAnglesArrayPath = {};
  bool m_CompressGeomFile = {};

public:
  /* Rule of 5: All special member functions should be defined if any are defined.
   * https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c21-if-you-define-or-delete-any-default-operation-define-or-delete-them-all
   */
  ExportDAMASKFiles(const ExportDAMASKFiles&) = delete;            // Copy Constructor Not Implemented
  ExportDAMASKFiles& operator=(const ExportDAMASKFiles&) = delete; // Copy Assignment Not Implemented
  ExportDAMASKFiles(ExportDAMASKFiles&&) = delete;                 // Move Constructor Not Implemented
  ExportDAMASKFiles& operator=(ExportDAMASKFiles&&) = delete;      // Move Assignment Not Implemented
};
