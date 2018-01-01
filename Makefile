PROJECT_NAME = spoke
BUILD_TOOLS_PATH = build-tools/
SRCS_EXCEPT := modules/mprotocol-server/ServerSocketInterface.cpp \
               modules/mprotocol-server/test/test.cpp \
               modules/mprotocol-server/test/ProtocolTester.cpp \
               modules/mprotocol-server/test/BufferInterface.cpp \
               modules/mprotocol-server/test/TestNode.cpp \
               modules/mprotocol-server/test/MemoryNode.cpp

include build-tools/Makefile.in