
BUILDTYPE ?= Release
PYTHON ?= python
CONFIG_OUTPUTS=build/bindings.target.mk build/Makefile build/binding.Makefile build/config.gypi
NODE-GYP-DEFAULT := $(shell which node-gyp 2>/dev/null || echo ./node_modules/node-gyp/bin/node-gyp.js)
NODE-GYP ?= $(NODE-GYP-DEFAULT)
GYPBUILDARGS=
ifeq ($(BUILDTYPE),Debug)
GYPBUILDARGS=--debug
endif

all: $(NODE-GYP) lib test

configure: $(CONFIG_OUTPUTS)

lib: $(NODE-GYP) $(CONFIG_OUTPUTS)
	$(NODE-GYP) build $(GYPBUILDARGS)

clean: $(NODE-GYP)
	@$(NODE-GYP) clean

node_modules: package.json
	@npm update

test: node_modules
	@node test.js

node-gyp: $(NODE-GYP)

$(CONFIG_OUTPUTS): $(NODE-GYP) binding.gyp
	@$(NODE-GYP) configure

$(NODE-GYP):
	@npm install node-gyp@0.3.5

.PHONY: all clean test configure lib node-gyp
