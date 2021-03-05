##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

## VARIABLES
## --------------------------------------------->
NM_FOLDER :=		nm/
NM_EXEC :=			my_nm
OBJDUMP_FOLDER :=	objdump/
OBJDUMP_EXEC :=		my_objdump
MAKEFLAGS += 		--no-print-directory --silent --silence
## --------------------------------------------->

.PHONY: all re clean fclean nm objdump

## RULES
## --------------------------------------------->
all: nm objdump

nm:
	make -C $(NM_FOLDER)
	mv $(NM_FOLDER)$(NM_EXEC) $(NM_EXEC)

objdump:
	make -C $(OBJDUMP_FOLDER)
	mv $(OBJDUMP_FOLDER)$(OBJDUMP_EXEC) $(OBJDUMP_EXEC)

clean:
	make -C $(NM_FOLDER) clean
	make -C $(OBJDUMP_FOLDER) clean

fclean: clean
	make -C $(NM_FOLDER) fclean
	make -C $(OBJDUMP_FOLDER) fclean
	rm -f $(NM_EXEC)
	rm -f $(OBJDUMP_EXEC)

re: fclean
	make -C $(NM_FOLDER) re
	make -C $(OBJDUMP_FOLDER) re
	mv $(NM_FOLDER)$(NM_EXEC) $(NM_EXEC)
	mv $(OBJDUMP_FOLDER)$(OBJDUMP_EXEC) $(OBJDUMP_EXEC)
## --------------------------------------------->