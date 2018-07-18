/*
 * Your License or Copyright can go here
 */

#include "Export3dSolidMesh.h"

#include <QtCore/QDir>

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/Math/GeometryMath.h"
#include "SIMPLib/FilterParameters/FloatVec3FilterParameter.h"
#include "SIMPLib/FilterParameters/IntVec3FilterParameter.h"
#include "SIMPLib/FilterParameters/DataContainerSelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "SIMPLib/FilterParameters/StringFilterParameter.h"
#include "SIMPLib/FilterParameters/AbstractFilterParametersReader.h"
#include "SIMPLib/FilterParameters/OutputFileFilterParameter.h"
#include "SIMPLib/FilterParameters/SeparatorFilterParameter.h"
#include "SIMPLib/Math/SIMPLibMath.h"
#include "SIMPLib/Geometry/ImageGeom.h"
#include "SIMPLib/Geometry/EdgeGeom.h"

#include "SimulationIO/SimulationIOConstants.h"
#include "SimulationIO/SimulationIOVersion.h"

#define LLU_CAST(arg) static_cast<unsigned long long int>(arg)

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Export3dSolidMesh::Export3dSolidMesh() :
  AbstractFilter()
  , m_FeatureIdsArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, SIMPL::CellData::FeatureIds)
  , m_CellPhasesArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, SIMPL::CellData::Phases)
  , m_CellEulerAnglesArrayPath(SIMPL::Defaults::ImageDataContainerName, SIMPL::Defaults::CellAttributeMatrixName, SIMPL::CellData::EulerAngles)
  , m_FeatureIds(nullptr)
  , m_CellPhases(nullptr)
  , m_CellEulerAngles(nullptr)
  , m_JobName("")

{
  initialize();

  m_BoxSize.x = 2.0;
  m_BoxSize.y = 2.0;
  m_BoxSize.z = 2.0;
  
  m_numElem.x = 20;
  m_numElem.y = 20;
  m_numElem.z = 20;
  
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Export3dSolidMesh::~Export3dSolidMesh()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Export3dSolidMesh::initialize()
{
    setErrorCondition(0);
    setWarningCondition(0);
    setCancel(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Export3dSolidMesh::setupFilterParameters()
{
  FilterParameterVector parameters;
  parameters.push_back(SIMPL_NEW_STRING_FP("Job Name", JobName, FilterParameter::Parameter, Export3dSolidMesh));
  parameters.push_back(SIMPL_NEW_OUTPUT_FILE_FP("Nodes File", NodesFile, FilterParameter::Parameter, Export3dSolidMesh, "*"));
  parameters.push_back(SIMPL_NEW_OUTPUT_FILE_FP("Connectivity File", ConnectivityFile, FilterParameter::Parameter, Export3dSolidMesh, "*"));
  parameters.push_back(SIMPL_NEW_OUTPUT_FILE_FP("Abaqus Input File", AbaqusInputFile, FilterParameter::Parameter, Export3dSolidMesh, "*.inp"));
  parameters.push_back(SIMPL_NEW_FLOAT_VEC3_FP("Box Size", BoxSize, FilterParameter::Parameter, Export3dSolidMesh));
  parameters.push_back(SIMPL_NEW_INT_VEC3_FP("Number of Elements", numElem, FilterParameter::Parameter, Export3dSolidMesh));
  parameters.push_back(SeparatorFilterParameter::New("Cell Data", FilterParameter::RequiredArray));
  {
    DataArraySelectionFilterParameter::RequirementType req =
        DataArraySelectionFilterParameter::CreateRequirement(SIMPL::TypeNames::Int32, 1, AttributeMatrix::Type::Cell, IGeometry::Type::Image);
    parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("Feature Ids", FeatureIdsArrayPath, FilterParameter::RequiredArray, Export3dSolidMesh, req));
  }
  {
    DataArraySelectionFilterParameter::RequirementType req =
        DataArraySelectionFilterParameter::CreateRequirement(SIMPL::TypeNames::Float, 3, AttributeMatrix::Type::Cell, IGeometry::Type::Image);
    parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("Euler Angles", CellEulerAnglesArrayPath, FilterParameter::RequiredArray, Export3dSolidMesh, req));
  }
  {
    DataArraySelectionFilterParameter::RequirementType req =
        DataArraySelectionFilterParameter::CreateRequirement(SIMPL::TypeNames::Int32, 1, AttributeMatrix::Type::Cell, IGeometry::Type::Image);
    parameters.push_back(SIMPL_NEW_DA_SELECTION_FP("Phases", CellPhasesArrayPath, FilterParameter::RequiredArray, Export3dSolidMesh, req));
  }
  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Export3dSolidMesh::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  setNodesFile(reader->readString("Nodes File", getNodesFile()));
  setConnectivityFile(reader->readString("Connectivity File", getConnectivityFile()));
  setAbaqusInputFile(reader->readString("Abaqus Input File", getAbaqusInputFile()));
  setBoxSize(reader->readFloatVec3("BoxSize", getBoxSize()));
  setnumElem(reader->readIntVec3("Number of Elements", getnumElem()));
  setCellEulerAnglesArrayPath(reader->readDataArrayPath("CellEulerAnglesArrayPath", getCellEulerAnglesArrayPath()));
  setCellPhasesArrayPath(reader->readDataArrayPath("CellPhasesArrayPath", getCellPhasesArrayPath()));
  setFeatureIdsArrayPath(reader->readDataArrayPath("FeatureIdsArrayPath", getFeatureIdsArrayPath()));
  setJobName(reader->readString("JobName", getJobName()));
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Export3dSolidMesh::dataCheck()
{
  setErrorCondition(0);
  setWarningCondition(0);
  //
  //
  if(getNodesFile().isEmpty() == true)
    {
      QString ss = QObject::tr("The nodes file must be set");
      setErrorCondition(-1);
      notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    }
  
  QFileInfo fi1(getNodesFile());
  QDir parentPath1 = fi1.path();
  if(parentPath1.exists() == false)
    {
      setWarningCondition(-2001);
      QString ss = QObject::tr("The directory path for the nodes file does not exist. DREAM.3D will attempt to create this path during execution of the filter");
      notifyWarningMessage(getHumanLabel(), ss, getWarningCondition());
    }
  //
  //
  if(getConnectivityFile().isEmpty() == true)
    {
      QString ss = QObject::tr("The connectivity file must be set");
      setErrorCondition(-1);
      notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    }
  
  QFileInfo fi2(getConnectivityFile());
  QDir parentPath2 = fi2.path();
  if(parentPath2.exists() == false)
    {
      setWarningCondition(-2001);
      QString ss = QObject::tr("The directory path for the connectivity file does not exist. DREAM.3D will attempt to create this path during execution of the filter");
      notifyWarningMessage(getHumanLabel(), ss, getWarningCondition());
    }
  //
  //
  if(getAbaqusInputFile().isEmpty() == true)
    {
      QString ss = QObject::tr("The Abaqus input file must be set");
      setErrorCondition(-1);
      notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    }
  
  QFileInfo fi3(getAbaqusInputFile());
  QDir parentPath3 = fi3.path();
  if(parentPath3.exists() == false)
    {
      setWarningCondition(-2001);
      QString ss = QObject::tr("The directory path for the Abaqus input file does not exist. DREAM.3D will attempt to create this path during execution of the filter");
      notifyWarningMessage(getHumanLabel(), ss, getWarningCondition());
    }
  //
  //
  getDataContainerArray()->getPrereqGeometryFromDataContainer<ImageGeom, AbstractFilter>(this, getFeatureIdsArrayPath().getDataContainerName());

  QVector<DataArrayPath> dataArrayPaths;

  QVector<size_t> cDims(1, 1);

  m_FeatureIdsPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<int32_t>, AbstractFilter>(this, getFeatureIdsArrayPath(),
                                                                                                        cDims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
  if(nullptr != m_FeatureIdsPtr.lock().get())                                                                   /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
  {
    m_FeatureIds = m_FeatureIdsPtr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */
  if(getErrorCondition() >= 0)
  {
    dataArrayPaths.push_back(getFeatureIdsArrayPath());
  }

  m_CellPhasesPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<int32_t>, AbstractFilter>(this, getCellPhasesArrayPath(),
                                                                                                        cDims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
  if(nullptr != m_CellPhasesPtr.lock().get())                                                                   /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
  {
    m_CellPhases = m_CellPhasesPtr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */
  if(getErrorCondition() >= 0)
  {
    dataArrayPaths.push_back(getCellPhasesArrayPath());
  }

  cDims[0] = 3;
  m_CellEulerAnglesPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<float>, AbstractFilter>(this, getCellEulerAnglesArrayPath(),
                                                                                                           cDims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
  if(nullptr != m_CellEulerAnglesPtr.lock().get())                                                                 /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
  {
    m_CellEulerAngles = m_CellEulerAnglesPtr.lock()->getPointer(0);
  } /* Now assign the raw pointer to data from the DataArray<T> object */
  if(getErrorCondition() >= 0)
  {
    dataArrayPaths.push_back(getCellEulerAnglesArrayPath());
  }

  getDataContainerArray()->validateNumberOfTuples<AbstractFilter>(this, dataArrayPaths);

  //
  //
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Export3dSolidMesh::preflight()
{
  // These are the REQUIRED lines of CODE to make sure the filter behaves correctly
  setInPreflight(true); // Set the fact that we are preflighting.
  emit preflightAboutToExecute(); // Emit this signal so that other widgets can do one file update
  emit updateFilterParameters(this); // Emit this signal to have the widgets push their values down to the filter
  dataCheck(); // Run our DataCheck to make sure everthing is setup correctly
  emit preflightExecuted(); // We are done preflighting this filter
  setInPreflight(false); // Inform the system this filter is NOT in preflight mode anymore.
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Export3dSolidMesh::execute()
{
  initialize();
  dataCheck();
  if(getErrorCondition() < 0) { return; }
  //
  // Make sure any directory path is also available as the user may have just typed
  // in a path without actually creating the full path
  QFileInfo fi1(getNodesFile());
  QDir parentPath1(fi1.path());
  if(!parentPath1.mkpath("."))
  {
    QString ss = QObject::tr("Error creating parent path for nodes file'%1'").arg(parentPath1.absolutePath());
    setErrorCondition(-1);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  FILE* f1 = fopen(getNodesFile().toLatin1().data(), "wb");
  if(nullptr == f1)
  {
    QString ss = QObject::tr("Error opening nodes file '%1'").arg(getNodesFile());
    setErrorCondition(-1);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  //
  // Make sure any directory path is also available as the user may have just typed
  // in a path without actually creating the full path
  QFileInfo fi3(getAbaqusInputFile());
  QDir parentPath3(fi3.path());
  if(!parentPath3.mkpath("."))
  {
    QString ss = QObject::tr("Error creating parent path for Abaqus Input file'%1'").arg(parentPath3.absolutePath());
    setErrorCondition(-1);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  FILE* f3 = fopen(getAbaqusInputFile().toLatin1().data(), "wb");
  if(nullptr == f3)
  {
    QString ss = QObject::tr("Error opening Abaqus Input file '%1'").arg(getAbaqusInputFile());
    setErrorCondition(-1);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  //
  fprintf(f3, "*Heading\n");
  fprintf(f3, "%s\n", m_JobName.toLatin1().data());
  fprintf(f3, "** Job name : %s\n", m_JobName.toLatin1().data());
  fprintf(f3, "*Preprint, echo = NO, model = NO, history = NO, contact = NO\n");
  //
  int32_t ne_x,ne_y,ne_z;
  float sx,sy,sz;
  int32_t nnode_x,nnode_y,nnode_z;
  int32_t index;
  
  ne_x = m_numElem.x;
  ne_y = m_numElem.y;
  ne_z = m_numElem.z;
  
  sx = m_BoxSize.x/ne_x;
  sy = m_BoxSize.y/ne_y;
  sz = m_BoxSize.z/ne_z;

  nnode_x = ne_x + 1;
  nnode_y = ne_y + 1;
  nnode_z = ne_z + 1;

  FloatArrayType::Pointer m_coordLengthPtr = FloatArrayType::CreateArray(3*nnode_x*nnode_y*nnode_z , "NODAL_COORDINATES_INTERNAL_USE_ONLY");
  float* m_coord = m_coordLengthPtr->getPointer(0);

  fprintf(f3,"*NODE, NSET=ALLNODES\n");  

  for(int32_t k = 0; k < nnode_z; k++)
  {
      for(int32_t j = 0; j < nnode_y; j++)
      {
          for(int32_t i = 0; i < nnode_x; i++)
          {
              index = k*nnode_x*nnode_y+j*nnode_x+i;
              m_coord[index*3] = i*sx;
              m_coord[index*3+1] = j*sy;
              m_coord[index*3+2] = (nnode_z-1-k)*sz;
          }
      }
  }
  
  for(int32_t k = 0; k < nnode_z; k++)
  {
      for(int32_t j = 0; j < nnode_y; j++)
      {
          for(int32_t i = 0; i < nnode_x; i++)
          {
              index = k*nnode_x*nnode_y+j*nnode_x+i;
              fprintf(f1,"%d %.3f %.3f %.3f\n", index+1, m_coord[index*3],m_coord[index*3+1],m_coord[index*3+2]);  
              fprintf(f3,"%d %.3f %.3f %.3f\n", index+1, m_coord[index*3],m_coord[index*3+1],m_coord[index*3+2]);  
          }
      }
  }
  //
  fclose(f1);
  //
  //
  // Make sure any directory path is also available as the user may have just typed
  // in a path without actually creating the full path
  QFileInfo fi2(getConnectivityFile());
  QDir parentPath2(fi2.path());
  if(!parentPath2.mkpath("."))
    {
      QString ss = QObject::tr("Error creating parent path for connectivity file'%1'").arg(parentPath2.absolutePath());
      setErrorCondition(-1);
      notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    }  
  FILE* f2 = fopen(getConnectivityFile().toLatin1().data(), "wb");
  if(nullptr == f2)
    {
      QString ss = QObject::tr("Error opening connectivity file '%1'").arg(getConnectivityFile());
      setErrorCondition(-1);
      notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    }
  
  Int32ArrayType::Pointer m_connLengthPtr = Int32ArrayType::CreateArray(8*ne_x*ne_y*ne_z , "CONNECTIVITY_INTERNAL_USE_ONLY");
  int32_t* m_conn = m_connLengthPtr->getPointer(0);

  fprintf(f3,"*ELEMENTS, TYPE=C3D8, ELSET=ALLELEMENTS\n");  
  
  for(int32_t k = 0; k < ne_z; k++)
  {
      for(int32_t j = 0; j < ne_y; j++)
      {
          for(int32_t i = 0; i < ne_x; i++)
          {
              index = k*nnode_x*nnode_y + j*nnode_x + i + 1;
              int32_t eindex =  k*ne_x*ne_y + j*ne_x + i;    
              m_conn[eindex*8] = index;
              m_conn[eindex*8+1] = index + 1;
              m_conn[eindex*8+2] = (index+1) + nnode_x;
              m_conn[eindex*8+3] = (index+1) + nnode_x - 1;
              m_conn[eindex*8+4] = index + nnode_x*nnode_y;
              m_conn[eindex*8+5] = index + 1 + nnode_x*nnode_y;
              m_conn[eindex*8+6] = (index+1) + nnode_x + nnode_x*nnode_y;
              m_conn[eindex*8+7] = (index+1) + nnode_x - 1 + nnode_x*nnode_y;
          }
      }
  }
  
  for(int32_t k = 0; k < ne_z; k++)
  {
      for(int32_t j = 0; j < ne_y; j++)
      {
          for(int32_t i = 0; i < ne_x; i++)
          {
              index =  k*ne_x*ne_y + j*ne_x + i;
              fprintf(f2,"%d %d %d %d %d %d %d %d %d\n", index+1, m_conn[index*8],m_conn[index*8+1],m_conn[index*8+2],m_conn[index*8+3],m_conn[index*8+4],m_conn[index*3+5],m_conn[index*8+6],m_conn[index*8+7]);  
              fprintf(f3,"%d %d %d %d %d %d %d %d %d\n", index+1, m_conn[index*8],m_conn[index*8+1],m_conn[index*8+2],m_conn[index*8+3],m_conn[index*8+4],m_conn[index*3+5],m_conn[index*8+6],m_conn[index*8+7]);  
          }
      }
  }

  fclose(f2);
  //  
  //

  DataContainer::Pointer m = getDataContainerArray()->getDataContainer(getFeatureIdsArrayPath().getDataContainerName());

  size_t dims[3] = {0, 0, 0};
  std::tie(dims[0], dims[1], dims[2]) = m->getGeometryAs<ImageGeom>()->getDimensions();
  float res[3] = {0.0f, 0.0f, 0.0f};
  m->getGeometryAs<ImageGeom>()->getResolution(res);
  float origin[3] = {0.0f, 0.0f, 0.0f};
  m->getGeometryAs<ImageGeom>()->getOrigin(origin);

  float phi1 = 0.0f, phi = 0.0f, phi2 = 0.0f;
  int32_t featureId = 0;
  int32_t phaseId = 0;
  size_t index1 = 0;

  // find total number of Grain Ids
  int32_t maxGrainId = 0;
  int32_t totalPoints = m->getGeometryAs<ImageGeom>()->getNumberOfElements();
  for(int32_t i = 0; i < totalPoints; i++) // find number of grainIds
  {
    if(m_FeatureIds[i] > maxGrainId)
    {
      maxGrainId = m_FeatureIds[i];
    }
  }
  //
  //
  int32_t voxelId = 1;
  while(voxelId <= maxGrainId)
  {
    size_t elementPerLine = 0;
    fprintf(f3, "\n*Elset, elset=Grain%d_set\n", voxelId);

    for(int32_t i = 0; i < totalPoints + 1; i++)
    {
      if(m_FeatureIds[i] == voxelId)
      {
        if(elementPerLine != 0) // no comma at start
        {
          if(elementPerLine % 16) // 16 per line
          {
            fprintf(f3, ", ");
          }
          else
          {
            fprintf(f3, ",\n");
          }
        }
        fprintf(f3, "%llu", static_cast<unsigned long long int>(i + 1));
        elementPerLine++;
      }
    }
    voxelId++;
  }
  //
  // We are now defining the sections, which is for each grain
  int32_t grain = 1;
  while(grain <= maxGrainId)
    {
      fprintf(f3, "** Section: Grain%d\n", grain);
      fprintf(f3, "*Solid Section, elset=Grain%d_set, material=Grain_Mat%d\n", grain, grain);
      grain++;
    }

  //
  //
  if (getCancel() == true) { return; }

  //
  //
  fclose(f3);
  //
  //

  notifyStatusMessage(getHumanLabel(), "Complete");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer Export3dSolidMesh::newFilterInstance(bool copyFilterParameters) const
{
  Export3dSolidMesh::Pointer filter = Export3dSolidMesh::New();
  if(true == copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Export3dSolidMesh::getCompiledLibraryName() const
{ 
  return SimulationIOConstants::SimulationIOBaseName;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Export3dSolidMesh::getBrandingString() const
{
  return "SimulationIO";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Export3dSolidMesh::getFilterVersion() const
{
  QString version;
  QTextStream vStream(&version);
  vStream <<  SimulationIO::Version::Major() << "." << SimulationIO::Version::Minor() << "." << SimulationIO::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Export3dSolidMesh::getGroupName() const
{ 
  return SIMPL::FilterGroups::Unsupported; 
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Export3dSolidMesh::getSubGroupName() const
{ 
  return "SimulationIO"; 
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString Export3dSolidMesh::getHumanLabel() const
{ 
  return "Export 3d Solid Mesh"; 
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QUuid Export3dSolidMesh::getUuid()
{
  return QUuid("{e7f02408-6c01-5b56-b970-7813e64c12e2}");
}

