###############################################################################
# Build the shared library
###############################################################################

add_library (
	${PROJECT_NAME} SHARED
	ftr.c pack.c async_call.c
)

target_include_directories (
	${PROJECT_NAME} PUBLIC
	${MLTCRD_INCLUDE_DIRECTORY}
)

set_target_properties (
	${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
)

###############################################################################
# Install the shared library
###############################################################################

install (
	TARGETS ${PROJECT_NAME}
	DESTINATION ${MLTCRD_SHARED_INSTALL_DIRECTORY}
)
