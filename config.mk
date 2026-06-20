# SPDX-License-Identifier: MIT
# Author:  Giovanni Santini
# Mail:    giovanni.santini@proton.me
# Github:  @San7o

ARCH     ?= x86_64
BACKEND  ?= uefi
FRONTEND ?= iperboot
CC        = clang # We only support clang for now
AS        = nasm

CFLAGS  ?= -Wall -Werror -Wextra -Wpedantic \
           -std=c23 -Wno-language-extension-token \
           -Wno-microsoft-enum-value
LDFLAGS ?=

BACKEND_CFLAGS   ?=
BACKEND_LDFLAGS  ?=

FRONTEND_CFLAGS  ?=
FRONTEND_LDFLAGS ?=

BACKEND_OUT      ?= iperboot_${BACKEND}_backend
FRONTEND_OUT     ?= iperboot_${FRONTEND}_frontend

DIST_OBJ = ${BACKEND_OUT} ${FRONTEND_OUT}

include backend/${BACKEND}/conf.mk

BACKEND_CFLAGS   += ${CFLAGS}
BACKEND_LDFLAGS  += ${LDFLAGS}

FRONTEND_CFLAGS  += ${CFLAGS}
FRONTEND_LDFLAGS += ${LDFLAGS}
