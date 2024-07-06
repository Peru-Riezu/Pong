# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Filename: Makefile                                                        #
#    Author:   Peru Riezu <riezumunozperu@gmail.com>                           #
#    github:   https://github.com/priezu-m                                     #
#    Licence:  GPLv3                                                           #
#    Created:  2023/09/27 18:57:07                                             #
#    Updated:  2024/07/05 23:42:45                                             #
#                                                                              #
# **************************************************************************** #

#GNU Make 3.81

################################################################################

SHELL :=			bash

################################################################################

################################################################################

.DEFAULT_GOAL := all

all:
	psql db -f ./db/create_tables.sql

clean:

fclean: clean

re: fclean
	@make --no-print-directory

pull:
	@git pull

push: fclean
	@git add .
	@git commit
	@git push
