###############################################################################
# Install header files
###############################################################################

install (
	DIRECTORY ${MLTCRD_INCLUDE_DIRECTORY}/
	DESTINATION ${MLTCRD_HEADER_INSTALL_DIRECTORY}
	FILES_MATCHING PATTERN "*.h"
)
