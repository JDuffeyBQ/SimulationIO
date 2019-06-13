/*
 * Your License or Copyright can go here
 */

#pragma once

#include <QtCore/QMutex>
#include <QtCore/QProcess>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
#include <QtCore/QWaitCondition>

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/FilterParameters/FloatVec3FilterParameter.h"
#include "SIMPLib/FilterParameters/IntVec3FilterParameter.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/DataArrays/DataArray.hpp"
#include "SIMPLib/Geometry/IGeometry.h"

#include "SimulationIO/SimulationIOPlugin.h"

class QProcess;
class DataContainer;

/**
 * @brief The Export3dSolidMesh class. See [Filter documentation](@ref export3dsolidmesh) for details.
 */
class SimulationIO_EXPORT Export3dSolidMesh : public AbstractFilter
{
  Q_OBJECT

#ifdef SIMPL_ENABLE_PYTHON
  PYB11_CREATE_BINDINGS(Export3dSolidMesh SUPERCLASS AbstractFilter)
  PYB11_SHARED_POINTERS(Export3dSolidMesh)
  PYB11_FILTER_NEW_MACRO(Export3dSolidMesh)
  PYB11_FILTER_PARAMETER(int, MeshingPackage)
  PYB11_FILTER_PARAMETER(QString, outputPath)
  PYB11_FILTER_PARAMETER(QString, PackageLocation)
  PYB11_FILTER_PARAMETER(DataArrayPath, SurfaceMeshFaceLabelsArrayPath)
  PYB11_FILTER_PARAMETER(DataArrayPath, FeaturePhasesArrayPath)
  PYB11_FILTER_PARAMETER(DataArrayPath, FeatureEulerAnglesArrayPath)
  PYB11_FILTER_PARAMETER(DataArrayPath, FeatureCentroidArrayPath)
  PYB11_FILTER_PARAMETER(bool, RefineMesh)
  PYB11_FILTER_PARAMETER(float, MaxRadiusEdgeRatio)
  PYB11_FILTER_PARAMETER(float, MinDihedralAngle)
  PYB11_FILTER_PARAMETER(bool, LimitTetrahedraVolume)
  PYB11_FILTER_PARAMETER(float, MaxTetrahedraVolume)
  PYB11_FILTER_PARAMETER(int, OptimizationLevel)
  PYB11_FILTER_PARAMETER(QString, TetDataContainerName)
  PYB11_FILTER_PARAMETER(QString, VertexAttributeMatrixName)
  PYB11_FILTER_PARAMETER(QString, CellAttributeMatrixName)
  PYB11_FILTER_PARAMETER(QString, GmshSTLFileName)
  PYB11_FILTER_PARAMETER(int, MeshFileFormat)
  PYB11_FILTER_PARAMETER(QString, NetgenSTLFileName)
  PYB11_FILTER_PARAMETER(int, MeshSize)
  PYB11_PROPERTY(int MeshingPackage READ getMeshingPackage WRITE setMeshingPackage)
  PYB11_PROPERTY(QString outputPath READ getoutputPath WRITE setoutputPath)
  PYB11_PROPERTY(QString PackageLocation READ getPackageLocation WRITE setPackageLocation)
  PYB11_PROPERTY(DataArrayPath SurfaceMeshFaceLabelsArrayPath READ getSurfaceMeshFaceLabelsArrayPath WRITE setSurfaceMeshFaceLabelsArrayPath)
  PYB11_PROPERTY(DataArrayPath FeaturePhasesArrayPath READ getFeaturePhasesArrayPath WRITE setFeaturePhasesArrayPath)
  PYB11_PROPERTY(DataArrayPath FeatureEulerAnglesArrayPath READ getFeatureEulerAnglesArrayPath WRITE setFeatureEulerAnglesArrayPath)
  PYB11_PROPERTY(DataArrayPath FeatureCentroidArrayPath READ getFeatureCentroidArrayPath WRITE setFeatureCentroidArrayPath)

  PYB11_PROPERTY(bool RefineMesh READ getRefineMesh WRITE setRefineMesh)
  PYB11_PROPERTY(float MaxRadiusEdgeRatio READ getMaxRadiusEdgeRatio WRITE setMaxRadiusEdgeRatio)
  PYB11_PROPERTY(float MinDihedralAngle READ getMinDihedralAngle WRITE setMinDihedralAngle)
  PYB11_PROPERTY(bool LimitTetrahedraVolume READ getLimitTetrahedraVolume WRITE setLimitTetrahedraVolume)
  PYB11_PROPERTY(float MaxTetrahedraVolume READ getMaxTetrahedraVolume WRITE setMaxTetrahedraVolume)
  PYB11_PROPERTY(int OptimizationLevel READ getOptimizationLevel WRITE setOptimizationLevel)

  PYB11_PROPERTY(QString TetDataContainerName READ getTetDataContainerName WRITE setTetDataContainerName)
  PYB11_PROPERTY(QString VertexAttributeMatrixName READ getVertexAttributeMatrixName WRITE setVertexAttributeMatrixName)
  PYB11_PROPERTY(QString CellAttributeMatrixName READ getCellAttributeMatrixName WRITE setCellAttributeMatrixName)

  PYB11_PROPERTY(QString GmshSTLFileName READ getGmshSTLFileName WRITE setGmshSTLFileName)
  PYB11_PROPERTY(int MeshFileFormat READ getMeshFileFormat WRITE setMeshFileFormat)

  PYB11_PROPERTY(QString NetgenSTLFileName READ getNetgenSTLFileName WRITE setNetgenSTLFileName)
  PYB11_PROPERTY(int MeshSize READ getMeshSize WRITE setMeshSize)
#endif

public:
  using Self = Export3dSolidMesh;
  using Pointer = std::shared_ptr<Self>;
  using ConstPointer = std::shared_ptr<const Self>;
  using WeakPointer = std::weak_ptr<Self>;
  using ConstWeakPointer = std::weak_ptr<Self>;
  static Pointer NullPointer();

  static std::shared_ptr<Export3dSolidMesh> New();

  /**
   * @brief Returns the name of the class for _SUPERExport3dSolidMesh
   */
  const QString getNameOfClass() const override;
  /**
   * @brief Returns the name of the class for _SUPERExport3dSolidMesh
   */
  static QString ClassName();

  ~Export3dSolidMesh() override;

  /**
   * @brief Setter property for MeshingPackage
   */
  void setMeshingPackage(const int& value);
  /**
   * @brief Getter property for MeshingPackage
   * @return Value of MeshingPackage
   */
  int getMeshingPackage() const;

  Q_PROPERTY(int MeshingPackage READ getMeshingPackage WRITE setMeshingPackage)

  /**
   * @brief Setter property for outputPath
   */
  void setoutputPath(const QString& value);
  /**
   * @brief Getter property for outputPath
   * @return Value of outputPath
   */
  QString getoutputPath() const;

  Q_PROPERTY(QString outputPath READ getoutputPath WRITE setoutputPath)

  /**
   * @brief Setter property for PackageLocation
   */
  void setPackageLocation(const QString& value);
  /**
   * @brief Getter property for PackageLocation
   * @return Value of PackageLocation
   */
  QString getPackageLocation() const;

  Q_PROPERTY(QString PackageLocation READ getPackageLocation WRITE setPackageLocation)

  /**
   * @brief Setter property for SurfaceMeshFaceLabelsArrayPath
   */
  void setSurfaceMeshFaceLabelsArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for SurfaceMeshFaceLabelsArrayPath
   * @return Value of SurfaceMeshFaceLabelsArrayPath
   */
  DataArrayPath getSurfaceMeshFaceLabelsArrayPath() const;

  Q_PROPERTY(DataArrayPath SurfaceMeshFaceLabelsArrayPath READ getSurfaceMeshFaceLabelsArrayPath WRITE setSurfaceMeshFaceLabelsArrayPath)

  /**
   * @brief Setter property for FeaturePhasesArrayPath
   */
  void setFeaturePhasesArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for FeaturePhasesArrayPath
   * @return Value of FeaturePhasesArrayPath
   */
  DataArrayPath getFeaturePhasesArrayPath() const;

  Q_PROPERTY(DataArrayPath FeaturePhasesArrayPath READ getFeaturePhasesArrayPath WRITE setFeaturePhasesArrayPath)

  /**
   * @brief Setter property for FeatureEulerAnglesArrayPath
   */
  void setFeatureEulerAnglesArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for FeatureEulerAnglesArrayPath
   * @return Value of FeatureEulerAnglesArrayPath
   */
  DataArrayPath getFeatureEulerAnglesArrayPath() const;

  Q_PROPERTY(DataArrayPath FeatureEulerAnglesArrayPath READ getFeatureEulerAnglesArrayPath WRITE setFeatureEulerAnglesArrayPath)

  /**
   * @brief Setter property for FeatureCentroidArrayPath
   */
  void setFeatureCentroidArrayPath(const DataArrayPath& value);
  /**
   * @brief Getter property for FeatureCentroidArrayPath
   * @return Value of FeatureCentroidArrayPath
   */
  DataArrayPath getFeatureCentroidArrayPath() const;

  Q_PROPERTY(DataArrayPath FeatureCentroidArrayPath READ getFeatureCentroidArrayPath WRITE setFeatureCentroidArrayPath)

  /**
   * @brief Setter property for RefineMesh
   */
  void setRefineMesh(const bool& value);
  /**
   * @brief Getter property for RefineMesh
   * @return Value of RefineMesh
   */
  bool getRefineMesh() const;

  Q_PROPERTY(bool RefineMesh READ getRefineMesh WRITE setRefineMesh)

  /**
   * @brief Setter property for MaxRadiusEdgeRatio
   */
  void setMaxRadiusEdgeRatio(const float& value);
  /**
   * @brief Getter property for MaxRadiusEdgeRatio
   * @return Value of MaxRadiusEdgeRatio
   */
  float getMaxRadiusEdgeRatio() const;

  Q_PROPERTY(float MaxRadiusEdgeRatio READ getMaxRadiusEdgeRatio WRITE setMaxRadiusEdgeRatio)

  /**
   * @brief Setter property for MinDihedralAngle
   */
  void setMinDihedralAngle(const float& value);
  /**
   * @brief Getter property for MinDihedralAngle
   * @return Value of MinDihedralAngle
   */
  float getMinDihedralAngle() const;

  Q_PROPERTY(float MinDihedralAngle READ getMinDihedralAngle WRITE setMinDihedralAngle)

  /**
   * @brief Setter property for LimitTetrahedraVolume
   */
  void setLimitTetrahedraVolume(const bool& value);
  /**
   * @brief Getter property for LimitTetrahedraVolume
   * @return Value of LimitTetrahedraVolume
   */
  bool getLimitTetrahedraVolume() const;

  Q_PROPERTY(bool LimitTetrahedraVolume READ getLimitTetrahedraVolume WRITE setLimitTetrahedraVolume)

  /**
   * @brief Setter property for MaxTetrahedraVolume
   */
  void setMaxTetrahedraVolume(const float& value);
  /**
   * @brief Getter property for MaxTetrahedraVolume
   * @return Value of MaxTetrahedraVolume
   */
  float getMaxTetrahedraVolume() const;

  Q_PROPERTY(float MaxTetrahedraVolume READ getMaxTetrahedraVolume WRITE setMaxTetrahedraVolume)

  /**
   * @brief Setter property for OptimizationLevel
   */
  void setOptimizationLevel(const int& value);
  /**
   * @brief Getter property for OptimizationLevel
   * @return Value of OptimizationLevel
   */
  int getOptimizationLevel() const;

  Q_PROPERTY(int OptimizationLevel READ getOptimizationLevel WRITE setOptimizationLevel)

  /**
   * @brief Setter property for TetDataContainerName
   */
  void setTetDataContainerName(const QString& value);
  /**
   * @brief Getter property for TetDataContainerName
   * @return Value of TetDataContainerName
   */
  QString getTetDataContainerName() const;

  Q_PROPERTY(QString TetDataContainerName READ getTetDataContainerName WRITE setTetDataContainerName)

  /**
   * @brief Setter property for VertexAttributeMatrixName
   */
  void setVertexAttributeMatrixName(const QString& value);
  /**
   * @brief Getter property for VertexAttributeMatrixName
   * @return Value of VertexAttributeMatrixName
   */
  QString getVertexAttributeMatrixName() const;

  Q_PROPERTY(QString VertexAttributeMatrixName READ getVertexAttributeMatrixName WRITE setVertexAttributeMatrixName)

  /**
   * @brief Setter property for CellAttributeMatrixName
   */
  void setCellAttributeMatrixName(const QString& value);
  /**
   * @brief Getter property for CellAttributeMatrixName
   * @return Value of CellAttributeMatrixName
   */
  QString getCellAttributeMatrixName() const;

  Q_PROPERTY(QString CellAttributeMatrixName READ getCellAttributeMatrixName WRITE setCellAttributeMatrixName)

  /**
   * @brief Setter property for GmshSTLFileName
   */
  void setGmshSTLFileName(const QString& value);
  /**
   * @brief Getter property for GmshSTLFileName
   * @return Value of GmshSTLFileName
   */
  QString getGmshSTLFileName() const;

  Q_PROPERTY(QString GmshSTLFileName READ getGmshSTLFileName WRITE setGmshSTLFileName)

  /**
   * @brief Setter property for MeshFileFormat
   */
  void setMeshFileFormat(const int& value);
  /**
   * @brief Getter property for MeshFileFormat
   * @return Value of MeshFileFormat
   */
  int getMeshFileFormat() const;

  Q_PROPERTY(int MeshFileFormat READ getMeshFileFormat WRITE setMeshFileFormat)

  /**
   * @brief Setter property for NetgenSTLFileName
   */
  void setNetgenSTLFileName(const QString& value);
  /**
   * @brief Getter property for NetgenSTLFileName
   * @return Value of NetgenSTLFileName
   */
  QString getNetgenSTLFileName() const;

  Q_PROPERTY(QString NetgenSTLFileName READ getNetgenSTLFileName WRITE setNetgenSTLFileName)

  /**
   * @brief Setter property for MeshSize
   */
  void setMeshSize(const int& value);
  /**
   * @brief Getter property for MeshSize
   * @return Value of MeshSize
   */
  int getMeshSize() const;

  Q_PROPERTY(int MeshSize READ getMeshSize WRITE setMeshSize)

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
  Export3dSolidMesh();

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  void dataCheck();

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize();

protected slots:
  void processHasFinished(int exitCode, QProcess::ExitStatus exitStatus);
  void processHasErroredOut(QProcess::ProcessError error);
  void sendErrorOutput();
  void sendStandardOutput();

private:
  std::weak_ptr<DataArray<float>> m_FeatureEulerAnglesPtr;
  float* m_FeatureEulerAngles = nullptr;
  std::weak_ptr<DataArray<float>> m_FeatureCentroidPtr;
  float* m_FeatureCentroid = nullptr;
  std::weak_ptr<DataArray<int32_t>> m_FeaturePhasesPtr;
  int32_t* m_FeaturePhases = nullptr;

  int m_MeshingPackage = {};
  QString m_outputPath = {};
  QString m_PackageLocation = {};
  DataArrayPath m_SurfaceMeshFaceLabelsArrayPath = {};
  DataArrayPath m_FeaturePhasesArrayPath = {};
  DataArrayPath m_FeatureEulerAnglesArrayPath = {};
  DataArrayPath m_FeatureCentroidArrayPath = {};
  bool m_RefineMesh = {};
  float m_MaxRadiusEdgeRatio = {};
  float m_MinDihedralAngle = {};
  bool m_LimitTetrahedraVolume = {};
  float m_MaxTetrahedraVolume = {};
  int m_OptimizationLevel = {};
  QString m_TetDataContainerName = {};
  QString m_VertexAttributeMatrixName = {};
  QString m_CellAttributeMatrixName = {};
  QString m_GmshSTLFileName = {};
  int m_MeshFileFormat = {};
  QString m_NetgenSTLFileName = {};
  int m_MeshSize = {};

  void runPackage(const QString& file, const QString& meshFile);
  void mergeMesh(const QString& mergefile, const QString& indivFile);

  void createTetgenInpFile(const QString& file, MeshIndexType numNodes, float* nodes, MeshIndexType numTri, MeshIndexType* triangles, size_t numfeatures, float* centroid);

  QWaitCondition m_WaitCondition;
  QMutex m_Mutex;
  bool m_Pause = false;
  QSharedPointer<QProcess> m_ProcessPtr;
  QStringList arguments;

  void scanTetGenFile(const QString& fileEle, const QString& fileNode, DataContainer* dataContainer, AttributeMatrix* vertexAttributeMatrix, AttributeMatrix* cellAttributeMatrix);

public:
  /* Rule of 5: All special member functions should be defined if any are defined.
   * https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c21-if-you-define-or-delete-any-default-operation-define-or-delete-them-all
   */
  Export3dSolidMesh(const Export3dSolidMesh&) = delete;            // Copy Constructor Not Implemented
  Export3dSolidMesh& operator=(const Export3dSolidMesh&) = delete; // Copy Assignment Not Implemented
  Export3dSolidMesh(Export3dSolidMesh&&) = delete;                 // Move Constructor Not Implemented
  Export3dSolidMesh& operator=(Export3dSolidMesh&&) = delete;      // Move Assignment Not Implemented
};
