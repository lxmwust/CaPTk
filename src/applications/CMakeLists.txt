# This CMakeLists file will add the source files in this directory for compilation

# common_includes will have all the functions and classes from CBICA_Toolkit_ITK branch and more

# each header file, "$application.h" : main entry point of an application whose input will be either a single "itk::Image" or a "std::vector< itk::Image >"

# each application-specific include folder, "/$application_includes" : dependencies which are not taken care by the default dependencies (i.e., ITK and OpenCV), for example libSVM for recurrence

INCLUDE(CaPTk_macros)

FILE( GLOB
  COMMON_DEPENDENCIES
  "${CMAKE_CURRENT_SOURCE_DIR}/common_includes/*.*"

)
SET( SOURCES "" )
SET( DEPENDENCIES ${COMMON_DEPENDENCIES} )
SET( INCLUDES "")
SET( CAPTK_MACOSX_BUNDLE_FILES "")

SET( APPLICATIONS
  WhiteStripe
  GeodesicSegmentation
  EGFRvIIISurrogateIndex
  EGFRvIIIIndexPredictor
  RecurrenceEstimator
  SurvivalPredictor
  PseudoProgressionEstimator
  MolecularSubtypePredictor
  #ImagingSubtypePredictor
  PopulationAtlases
  DirectionalityEstimate
  FeatureExtraction
  DiffusionDerivatives
  PerfusionDerivatives
  TrainingModule
  PerfusionPCA
  DeepMedicNormalizer
  GreedyRegistration
  SBRT_LungField
  SBRT_Nodule
  SBRT_Analysis
)
SET( CAPTK_APP_LIST "" )

SET( CAPTK_BRAIN_APPS "" )
SET( CAPTK_BREAST_APPS "" )
SET( CAPTK_LUNG_APPS "" )
SET( CAPTK_MISC_APPS "" )

ADD_SUBDIRECTORY( FeatureExtraction )
ADD_SUBDIRECTORY( Preprocessing )
INCLUDE_DIRECTORIES( 
  FeatureExtraction/src/depends 
  FeatureExtraction/src 
  Preprocessing/src/depends
)

SET(PREPROCESSING_ALGOS "DCM2NIfTI Denoise-SUSAN Register BiasCorrect-N3 HistogramMatching SkullStripping" CACHE STRING "All Preprocessing algorithms available")

MACRO( ADD_APPLICATION application)
  # ensure that specified application has been found
  IF( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${application}.h")

    SET( SOURCES ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/${application}.h" )

  # if implementation is present, include that for compilation
    IF( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${application}.cpp")
      SET( SOURCES ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/${application}.cpp" )
    ELSEIF( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${application}.hxx")
      SET( SOURCES ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/${application}.hxx" )
    ENDIF()
    
    IF( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${application}_includes/" )
      # include dependency directory of ${application} for compilation
      SET( INCLUDES ${INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/${application}_includes/" )

      # add all dependencies of ${application} to compilation
      FILE( GLOB
        APPLICATION_SPECIFIC_DEPENDENCIES
        "${CMAKE_CURRENT_SOURCE_DIR}/${application}_includes/*.*"
      )
    ENDIF()

    # keep storing all dependencies
    SET( DEPENDENCIES ${DEPENDENCIES} ${APPLICATION_SPECIFIC_DEPENDENCIES} )

    # add to variable which will be used in source code to generate menu items
    SET( CAPTK_APP_LIST "${CAPTK_APP_LIST} ${application}" )

  ENDIF()
ENDMACRO()

FOREACH(application ${APPLICATIONS})

  IF(${application} STREQUAL GreedyRegistration)
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_TRAINING AND (${application} STREQUAL TrainingModule))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_PCA AND (${application} STREQUAL PerfusionPCA))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_PDERIVATIVES AND (${application} STREQUAL PerfusionDerivatives))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_DDERIVATIVES AND (${application} STREQUAL DiffusionDerivatives))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_EGFRvIII AND (${application} STREQUAL EGFRvIIISurrogateIndex))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_EGFRvIIISVM AND (${application} STREQUAL EGFRvIIIIndexPredictor))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_RECURRENCE AND (${application} STREQUAL RecurrenceEstimator))
    ADD_APPLICATION( ${application} )
  ENDIF()
  
	IF ( BUILD_PSEUDOPROGRESSION AND (${application} STREQUAL PseudoProgressionEstimator))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_GEODESIC AND (${application} STREQUAL GeodesicSegmentation))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_SURVIVAL AND (${application} STREQUAL SurvivalPredictor))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_ISUBTYPE AND (${application} STREQUAL ImagingSubtypePredictor))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_MSUBTYPE AND (${application} STREQUAL MolecularSubtypePredictor))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_ATLAS AND (${application} STREQUAL PopulationAtlases))
    ADD_APPLICATION( ${application} )
  ENDIF()
  
  IF ( BUILD_SBRT AND (${application} STREQUAL SBRT_LungField))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( BUILD_SBRT AND (${application} STREQUAL SBRT_Nodule))
    ADD_APPLICATION( ${application} )
  ENDIF()
  
  IF ( BUILD_SBRT AND (${application} STREQUAL SBRT_Analysis))
    ADD_APPLICATION( ${application} )
  ENDIF()
  
  IF ( (${application} STREQUAL DirectionalityEstimate))
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF( (${application} STREQUAL WhiteStripe) )
    ADD_APPLICATION( ${application} )
  ENDIF()

  IF ( (${application} STREQUAL FeatureExtraction))
    SET( CAPTK_APP_LIST "${CAPTK_APP_LIST} ${application}" )
  ENDIF()

ENDFOREACH()

## this is for all stand-alone applications which do not integrate at source code level with CaPTk
SET( CAPTK_APP_LIST_PY_GUI "" )

## download and extract the prepared binaries of external apps

    ## download exe from url
    #IF (PACKAGE_PROJECT)
    #  FILE(DOWNLOAD "${URL_GOES_HERE}" "${SUBDIRPATH}/libra.zip" TIMEOUT 600 STATUS STATUS_CODE)
    #  IF(NOT STATUS_CODE EQUAL 0)
    #    message(FATAL_ERROR "Failed to download LIBRA. Status=${STATUS_CODE}")
    #  ENDIF()
    #ENDIF()
    #EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E tar xz "${SUBDIRPATH}/libra.zip"
    #              WORKING_DIRECTORY "${SUBDIRPATH}/LIBRA"
    #              RESULT_VARIABLE RESULT_CODE)
    #IF(NOT RESULT_CODE EQUAL 0)
    #  message(FATAL_ERROR "Failed to unpack LIBRA from ${SUBDIRPATH}/libra.zip to ${SUBDIRPATH}/LIBRA with error ${RESULT_CODE}")
    #ENDIF()

SET( FILENAME_TO_EXTRACT "" )
SET( DOWNLOAD_URL "" )
SET( DOWNLOADED_APPS_DIR ${PROJECT_BINARY_DIR}/externalApps )
SET( SOURCE_APPLICATIONS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/individualApps )

IF(WIN32)
  SET( FILENAME_TO_EXTRACT "binaries_windows")
  SET( DOWNLOAD_URL "ftp://www.nitrc.org/var/home/groups/captk/downloads/sourceBuild_extra_windows.zip")
ELSEIF(APPLE)
  SET( FILENAME_TO_EXTRACT "binaries_mac")
  SET( DOWNLOAD_URL "ftp://www.nitrc.org/var/home/groups/captk/downloads/sourceBuild_extra_mac.zip")
ELSE()
  SET( FILENAME_TO_EXTRACT "binaries_linux")
  SET( DOWNLOAD_URL "ftp://www.nitrc.org/var/home/groups/captk/downloads/sourceBuild_extra_linux.zip")
ENDIF()

# putting this condition so that the extraction doesn't happen every single time
IF( NOT EXISTS "${DOWNLOADED_APPS_DIR}" )

  SET( FILE_TO_EXTRACT ${PROJECT_BINARY_DIR}/${FILENAME_TO_EXTRACT}.zip)

  IF( NOT EXISTS "${FILE_TO_EXTRACT}" )
    # download exe from url
    MESSAGE( STATUS "Downloading pre-compiled external applications" )
    FILE(DOWNLOAD "${DOWNLOAD_URL}" "${FILE_TO_EXTRACT}" TIMEOUT 1000000 STATUS STATUS_CODE SHOW_PROGRESS)
    IF(NOT STATUS_CODE EQUAL 0)
      MESSAGE(FATAL_ERROR "Failed to download Precompiled packages. Status=${STATUS_CODE}")
    ENDIF()
  ENDIF()

  FILE(MAKE_DIRECTORY ${DOWNLOADED_APPS_DIR})

  MESSAGE( STATUS "Extracting pre-compiled external applications" )
  IF( EXISTS "${FILE_TO_EXTRACT}" )

    EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E tar xfz ${FILE_TO_EXTRACT}
      WORKING_DIRECTORY ${DOWNLOADED_APPS_DIR}
      RESULT_VARIABLE RESULT_CODE
    )

    IF(NOT RESULT_CODE EQUAL 0)
      MESSAGE( WARNING "Extracting the pre-compiled applications failed" )
    ENDIF()

  ENDIF()
ENDIF()

SUBDIRLIST(EXTERNAL_APPS ${DOWNLOADED_APPS_DIR}/${FILENAME_TO_EXTRACT}/)

# copy the prepared app into the appropriate folder
FOREACH(external_app ${EXTERNAL_APPS})

  IF( NOT EXISTS "${SOURCE_APPLICATIONS_PATH}/${external_app}" )

    FILE(MAKE_DIRECTORY ${SOURCE_APPLICATIONS_PATH}/${external_app})
    
    EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${DOWNLOADED_APPS_DIR}/${FILENAME_TO_EXTRACT}/${external_app} ${SOURCE_APPLICATIONS_PATH}/${external_app}
    )
  
  ENDIF()

ENDFOREACH()

SUBDIRLIST(SUBDIRECTORIES ${SOURCE_APPLICATIONS_PATH})
INCLUDE(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

FOREACH(subdir ${SUBDIRECTORIES})

  SET(SUBDIRPATH "${SOURCE_APPLICATIONS_PATH}/${subdir}")

  IF (BUILD_DEEPMEDIC AND (${subdir} STREQUAL "deepmedic"))

    SET( CAPTK_APP_LIST_PY_GUI "${CAPTK_APP_LIST_PY_GUI} deepmedic" CACHE STRING "Available stand-alone apps" FORCE)

    IF (APPLE)
      FILE(GLOB_RECURSE DEEPMEDIC_EXAMPLES "${SUBDIRPATH}/examples/*")
      FILE(GLOB_RECURSE DEEPMEDIC_CONFIGFILES "${SUBDIRPATH}/configFiles/*")
      FILE(GLOB_RECURSE DEEPMEDIC_SAVEDMODELS "${SUBDIRPATH}/saved_models/*")

      SET(CAPTK_MACOSX_BUNDLE_FILES ${CAPTK_MACOSX_BUNDLE_FILES} ${DEEPMEDIC_EXAMPLES} ${DEEPMEDIC_CONFIGFILES} ${DEEPMEDIC_SAVEDMODELS})
    ELSE()
      INSTALL(DIRECTORY "${SUBDIRPATH}/examples" DESTINATION data/deepMedic)
      INSTALL(DIRECTORY "${SUBDIRPATH}/configFiles" DESTINATION data/deepMedic)
      INSTALL(DIRECTORY "${SUBDIRPATH}/saved_models" DESTINATION data/deepMedic)
    ENDIF()

    IF(WIN32)
      INSTALL(FILES ${SUBDIRPATH}/deepMedicRun.exe
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
    ELSEIF(APPLE)
      INSTALL(FILES ${SUBDIRPATH}/deepMedicRun.exe
        DESTINATION ${EXE_NAME}.app/Contents/Resources/bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
    ELSE()
      INSTALL(FILES ${SUBDIRPATH}/bin/deepMedicRun
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
    ENDIF()

  ENDIF()

  IF (BUILD_LIBRASINGLE AND (${subdir} STREQUAL "libra"))
    #FIND_PACKAGE(MATLAB REQUIRED)
    #MATLAB_GET_RELEASE_NAME_FROM_VERSION(MATLAB_VERSION)
    #MESSAGE(STATUS "[debug]matlab_Version=${MATLAB_VERSION}")

    #TBD: discuss name with Mark
    SET( CAPTK_APP_LIST_PY_GUI "${CAPTK_APP_LIST_PY_GUI} librasingle" CACHE STRING "Available stand-alone apps" FORCE)
    # ALSO add this to CAPTK_BRREAST_APPS

    IF(WIN32)
      INSTALL(FILES ${SUBDIRPATH}/libra.exe
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(FILES ${SUBDIRPATH}/libra.bat
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(DIRECTORY "${SUBDIRPATH}/Mathworks" DESTINATION bin)

    ELSEIF(LINUX)
      INSTALL(FILES ${SUBDIRPATH}/bin/libra
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(FILES ${SUBDIRPATH}/libexec/libra
        DESTINATION libexec
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(DIRECTORY ${SUBDIRPATH}/MCR
        DESTINATION libexec
      )
    ENDIF()

  ENDIF()

  IF(BUILD_LIBRABATCH AND (${subdir} STREQUAL "libra"))
    #FIND_PACKAGE(MATLAB REQUIRED)
    #MATLAB_GET_RELEASE_NAME_FROM_VERSION(MATLAB_VERSION)
    #MESSAGE(STATUS "[debug]matlab_Version=${MATLAB_VERSION}")

    ## TBD: this needs to be discussed with Mark
    SET( CAPTK_APP_LIST_PY_GUI "${CAPTK_APP_LIST_PY_GUI} librabatch" CACHE STRING "Available stand-alone apps" FORCE)
    # ALSO add this to CAPTK_BRREAST_APPS

    IF(WIN32)
      INSTALL(FILES ${SUBDIRPATH}/libra.exe
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(FILES ${SUBDIRPATH}/libra.bat
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(DIRECTORY "${SUBDIRPATH}/Mathworks" DESTINATION bin)
    ELSEIF(LINUX)
      INSTALL(FILES ${SUBDIRPATH}/bin/libra
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(FILES ${SUBDIRPATH}/libexec/libra
        DESTINATION libexec
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(DIRECTORY ${SUBDIRPATH}/MCR
        DESTINATION libexec
      )
    ENDIF()

  ENDIF()

  IF (BUILD_ITKSNAP AND (${subdir} STREQUAL "itksnap"))

    SET( CAPTK_APP_LIST_PY_GUI "${CAPTK_APP_LIST_PY_GUI} itksnap" CACHE STRING "Available stand-alone apps" FORCE )
    # ALSO add this to CAPTK_BRAIN_APPS

    IF (WIN32)
      FILE(GLOB allFiles ${SUBDIRPATH}/bin/*.*)
      INSTALL(FILES ${allFiles}
        DESTINATION bin
        #FILES_MATCHING
        #PATTERN "*.*"
        #PATTERN ".svn" EXCLUDE
      )
      #INSTALL(DIRECTORY ${SUBDIRPATH}/bin/platforms
      #  DESTINATION bin
      #  #FILES_MATCHING
      #  #PATTERN "*.*"
      #  #PATTERN ".svn" EXCLUDE
      #)
    ELSEIF (APPLE)
      SET(ITKSNAP_EXE "${SUBDIRPATH}/ITK-SNAP.app/Contents/MacOS/ITK-SNAP")
        
      SET(CAPTK_MACOSX_BUNDLE_FILES ${CAPTK_MACOSX_BUNDLE_FILES} ${ITKSNAP_EXE})

    ELSE()
      INSTALL( FILES ${SUBDIRPATH}/bin/itksnap
        DESTINATION bin
        #FILES_MATCHING
        #PATTERN "*.*"
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      #FILE(GLOB allFiles ${SUBDIRPATH}/lib/snap-3.6.0-rc1/*.*)
      #INSTALL(FILES ${allFiles}
      #  DESTINATION lib/snap-3.6.0-rc1
        #FILES_MATCHING
        #PATTERN "*.*"
        #PATTERN ".svn" EXCLUDE
      #  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      #)
      INSTALL(DIRECTORY ${SUBDIRPATH}/lib/snap-3.6.0-rc1
        DESTINATION lib
        # USE_SOURCE_PERMISSIONS
        #FILES_MATCHING
        #PATTERN "*.*"
        #PATTERN ".svn" EXCLUDE
        #PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
    ENDIF()

  ENDIF()
  
  IF (${subdir} STREQUAL "theia")
    IF(WIN32)
      INSTALL(FILES ${SUBDIRPATH}/Theia.exe
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
    ENDIF()
  ENDIF()

  IF (${subdir} STREQUAL "theia_source")
    IF(LINUX)
      INSTALL(FILES ${SUBDIRPATH}/Theia.py
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(DIRECTORY ${SUBDIRPATH}/visualizer
        DESTINATION bin
        #PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
    ELSEIF (APPLE)
      INSTALL(FILES ${SUBDIRPATH}/Theia.py
        DESTINATION ${EXE_NAME}.app/Contents/Resources/bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
      INSTALL(DIRECTORY ${SUBDIRPATH}/visualizer
        DESTINATION ${EXE_NAME}.app/Contents/Resources/bin
        #PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
    ENDIF()
  ENDIF()

  IF (BUILD_CONFETTI AND (${subdir} STREQUAL "confetti")) # this will only be present for WIN32

    SET( CAPTK_APP_LIST_PY_GUI "${CAPTK_APP_LIST_PY_GUI} confetti" CACHE STRING "Available stand-alone apps" FORCE)
    # ALSO add this to CAPTK_BRAIN_APPS
    IF (${subdir} STREQUAL "confetti") # this is only valid for WIN32 since Confetti is distributed as a compiled EXE for it

      IF (APPLE)
        
        FILE(GLOB allFiles ${SUBDIRPATH}/*.*)
        INSTALL(FILES ${allFiles}
          DESTINATION ${EXE_NAME}.app/Contents/Resources/bin
          #FILES_MATCHING
          #PATTERN "*.*"
          #PATTERN ".svn" EXCLUDE
        )
        INSTALL(DIRECTORY ${SUBDIRPATH}/ConfettiBundleAtlas
          DESTINATION ${EXE_NAME}.app/Contents/Resources/bin
          #FILES_MATCHING
          #PATTERN "*.*"
          #PATTERN ".svn" EXCLUDE
        )
      ELSE()
        FILE(GLOB allFiles ${SUBDIRPATH}/*.*)
        INSTALL(FILES ${allFiles}
          DESTINATION bin
          #FILES_MATCHING
          #PATTERN "*.*"
          #PATTERN ".svn" EXCLUDE
        )
        INSTALL(DIRECTORY ${SUBDIRPATH}/ConfettiBundleAtlas
          DESTINATION bin
          #FILES_MATCHING
          #PATTERN "*.*"
          #PATTERN ".svn" EXCLUDE
        )
      ENDIF()

    ENDIF()

  ENDIF()

  IF (BUILD_SBRT AND (${subdir} STREQUAL "sbrt_source"))

    #ADD_SUBDIRECTORY(${SUBDIRPATH})
    #MESSAGE( "External project - SBRT" )
    #ExternalProject_Add( ${subdir}
    #  DOWNLOAD_COMMAND ""
    #  PATCH_COMMAND ""
    #  SOURCE_DIR ${SUBDIRPATH}
    #  #DEPENDS ${ITK_DIR}${OpenCV_DIR}
    #  #PREFIX ${PROJECT_BINARY_DIR}/${subdir}
    #  BINARY_DIR ${PROJECT_BINARY_DIR}/${subdir}
    #  UPDATE_COMMAND ""
    #  PATCH_COMMAND ""
    #  CMAKE_GENERATOR ${gen}
    #  INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
    #  CMAKE_ARGS
    #    ${ep_common_args}
    #    -DITK_DIR=${ITK_DIR}
    #    -DOpenCV_DIR=${OpenCV_DIR}
    #    -DBUILD_TESTING:BOOL=OFF # testing the ITK build is not required
    #    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE} # toggle for type of build if something different that
    #)

    SET( CAPTK_APP_LIST_PY_GUI "${CAPTK_APP_LIST_PY_GUI} SBRT_Segment SBRT_Analyze" CACHE STRING "Available stand-alone apps" FORCE)
    # ALSO add this to CAPTK_LUNG_APPS

  ENDIF()

  IF (${subdir} STREQUAL "dcm2nii") # this is a pre-processing algorithm and should be present as a pre-compiled binary package

    SET( DCM2NII_EXE "" )
    IF (WIN32)
      SET( DCM2NII_EXE "${SUBDIRPATH}/dcm2nii.exe" )
    ELSE ()
      SET( DCM2NII_EXE "${SUBDIRPATH}/dcm2nii" )
    ENDIF()

    IF (APPLE)
        
      SET(CAPTK_MACOSX_BUNDLE_FILES ${CAPTK_MACOSX_BUNDLE_FILES} ${DCM2NII_EXE})
    ELSE()
      INSTALL(FILES ${DCM2NII_EXE}
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
      )
     ENDIF()

  ENDIF()

ENDFOREACH()


SET( CAPTK_APP_LIST ${CAPTK_APP_LIST} CACHE STRING "Available Code-level Applications" FORCE)
#SET( CAPTK_BRAIN_APPS ${CAPTK_BRAIN_APPS} CACHE STRING "Available Brain Applications" FORCE )
#SET( CAPTK_BREAST_APPS ${CAPTK_BREAST_APPS} CACHE STRING "Available Breast Applications" FORCE )
#SET( CAPTK_LUNG_APPS ${CAPTK_LUNG_APPS} CACHE STRING "Available Lung Applications" FORCE )
#SET( CAPTK_MISC_APPS ${CAPTK_MISC_APPS} CACHE STRING "Available Misc. Applications" FORCE )
SET( APPLICATION_SOURCES  "${SOURCES}" CACHE STRING "Code-level Application sources" FORCE)
SET( APPLICATION_INCLUDES "${INCLUDES}" CACHE STRING "Code-level Application dependency folders" FORCE)
SET( APPLICATION_DEPENDS "${DEPENDENCIES}" CACHE STRING "Code-level Application dependencies" FORCE)
SET( CAPTK_MACOSX_BUNDLE_FILES_INSTALL_TARGETS "${CAPTK_MACOSX_BUNDLE_FILES}" CACHE STRING "macOS specific stuff" FORCE)
