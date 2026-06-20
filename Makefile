# SPDX-License-Identifier: MIT
# Author:  Giovanni Santini
# Mail:    giovanni.santini@proton.me
# Github:  @San7o

include config.mk

all: iperboot

.PHONY: iperboot
iperboot: frontend backend ## Build the entire bootloader
	@echo "Iperboot compilation finished"

.PHONY: backend
backend: ${BACKEND_OUT} ## Build the backend

.PHONY: frontend
frontend: ${FRONTEND_OUT} ## Build the frontend

.PHONY: img
img: ${IPERBOOT_IMG}

.PHONY: clean
clean: ## Clean all build files
	rm -f ${BACKEND_OBJ} ${FRONTEND_OBJ}

.PHONY: distclean
distclean: clean ## Clean all generated files
	rm -f ${DIST_OBJ}

.PHONY: help
help: ## Display this help.
	@awk 'BEGIN {FS = ":.*##"; printf "povOS\n\n    make <command>\n\ncommands:\n"} /^[a-zA-Z_0-9-]+:.*?##/ { printf "  %-15s %s\n", $$1, $$2 } /^##@/ { printf "\n%s\n", substr($$0, 5) } ' ${MAKEFILE_LIST}

include rules.mk
