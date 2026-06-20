# SPDX-License-Identifier: MIT
# Author:  Giovanni Santini
# Mail:    giovanni.santini@proton.me
# Github:  @San7o

${BACKEND_OUT}: ${BACKEND_OBJ} ${BACKEND_DEPS}
	${LD} ${BACKEND_LDFLAGS} -o ${BACKEND_OUT} ${BACKEND_OBJ}
	@echo "backend done"

${FRONTEND_OUT}: ${FRONTEND_OBJ} ${FRONTEND_DEPS}
	#${CC} ${FRONTEND_LDFLAGS} -o ${FRONTEND_OUT} ${FRONTEND_OBJ}
	@echo "frontend done"

backend/%.o: backend/%.c
	${CC} ${BACKEND_CFLAGS} -c -o $@ $^

backend/%.o: backend/%.asm
	${AS} ${BACKEND_ASFLAGS} -o $@ $^

frontend/%.o: frontend/%.c
	${CC} ${FRONTEND_CFLAGS} -c -o $@ $^

frontend/%.o: frontend/%.asm
	${AS} ${FRONTEND_ASFLAGS} -o $@ $^
