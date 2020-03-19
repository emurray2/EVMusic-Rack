# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -Idep/include
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

# Static libs
libsoundpipe := dep/lib/libsoundpipe.a
OBJECTS += $(libsoundpipe)

# Dependencies
DEPS += $(libsoundpipe)

$(libsoundpipe):
	$(WGET) https://github.com/PaulBatchelor/Soundpipe/archive/v1.7.0.tar.gz
	cd dep && $(UNTAR) ../v1.7.0.tar.gz
	cd dep/v1.7.0.tar.gz && $(CONFIGURE)
	cd dep/v1.7.0.tar.gz/src && $(MAKE)
	cd dep/v1.7.0.tar.gz/src && $(MAKE) install

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk
