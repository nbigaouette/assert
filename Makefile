# Timing template library

# Project options
LIB             := assert
BIN              = $(LIB)_test
SRCDIRS          = src
SRCEXT           = cpp
HEADEXT          = hpp
HEADERS          = $(wildcard $(addsuffix *.$(HEADEXT),$(addsuffix /, $(SRCDIRS)) ) )
LANGUAGE         = CPP

# Include the generic rules
include makefiles/Makefile.rules

#################################################################
# Project specific options

LIB_OBJ          = $(OBJ)

test:
	# HEADERS_NOTESTING = $(HEADERS_NOTESTING)
	# HEADERS_NOTESTING_NOSRC = $(HEADERS_NOTESTING_NOSRC)
	# HEADERS = $(HEADERS)
	# SOURCES = $(SOURCES)
	# OBJ = $(OBJ)
	# LIB = $(LIB)

### Just build "full" and install
.PHONY: f
f:
	$(MAKE) install $(filter-out f, $(MAKECMDGOALS) )

### Install #####################################################
INSTALL          = $(GNU)install -m644
INSTALL_EXEC     = $(GNU)install -m755

DEFAULT_DESTDIR := $(HOME)/usr
ifeq ($(DESTDIR),)
DESTDIR         := $(DEFAULT_DESTDIR)
endif

### If installing to "/home/...", we don't need sudo
ifneq ($(findstring $(HOME),$(DESTDIR) ),)
    SUDO        :=
else
    SUDO        := sudo
endif

# Find which cluster we run on
# For this, we iterate through the machines list: for each one of the list,
# we check if it is part of the $(host). If any match is found, then the
# corresponding possible_host_*_match is not empty.
possible_host_HPCVL_match    := $(strip $(foreach possible_host, $(HPCVL_MACHINES),    $(findstring $(possible_host), $(host) ) ) )
# Do specific stuff for different clusters
ifneq ($(possible_host_HPCVL_match), )
INSTALL := $(subst -D,,$(INSTALL) )
INSTALL_EXEC := $(subst -D,,$(INSTALL_EXEC) )
endif

### Add compiler to library directory, but only if not GCC
DESTDIR_INC      = $(DESTDIR)/include
ifeq ($(DESTDIRCOMPILER),gcc)
DESTDIR_LIB      = $(DESTDIR)/lib
else
    DESTDIR_LIB := $(DESTDIR)/lib/$(DESTDIRCOMPILER)
endif

HEADERS_NOTESTING=$(filter-out $(wildcard testing/*.$(HEADEXT)), $(HEADERS) )
HEADERS_NOTESTING_NOSRC=$(subst src/,,$(HEADERS_NOTESTING) )
INSTALLED_HEADERS=$(addprefix $(DESTDIR)/include/, $(HEADERS_NOTESTING_NOSRC) )
###############################################################


### Install only headers
TO_INSTALL       = install_headers
.PHONY: install
install: $(TO_INSTALL)

$(DESTDIR)/include:
	mkdir -p $(DESTDIR)/include

.PHONY: install_headers install_headers_print install_headers_print_done
ifeq ($(wildcard $(INSTALLED_HEADERS)),)
install_headers_print: install_create_folders
	############################################################
	######## Installing library headers to $(DESTDIR_INC)... ###
install_headers_print_done:
	############################################################
	######## Done ##############################################
else
install_headers_print:
install_headers_print_done:
endif
install_headers: install_headers_print $(INSTALLED_HEADERS) install_headers_print_done
$(DESTDIR)/include/%.$(HEADEXT): $(DESTDIR)/include src/%.$(HEADEXT)
	$(SUDO) $(INSTALL) $< $@

install_create_folders:
ifneq (,$(filter $(host), $(HPCVL_MACHINES) ))
	$(SUDO) mkdir -p $(DESTDIR_LIB)
endif

.PHONY: uninstall
uninstall: force
	############################################################
	######## Removing library headers from $(DESTDIR_INC)... ###
	$(SUDO) $(RM) -r $(INSTALLED_HEADERS)

############ End of file ########################################
