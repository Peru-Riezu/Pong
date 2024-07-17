# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Filename: Makefile                                                        #
#    Author:   Peru Riezu <riezumunozperu@gmail.com>                           #
#    github:   https://github.com/priezu-m                                     #
#    Licence:  GPLv3                                                           #
#    Created:  2023/09/27 18:57:07                                             #
#    Updated:  2024/07/17 13:51:33                                             #
#                                                                              #
# **************************************************************************** #

#GNU Make 3.81

################################################################################

SHELL :=			bash

################################################################################

.DEFAULT_GOAL := all

create_schema:
	psql pongdb -f ./db/create_tables.sql

/usr/local/share/ca-certificates/pong.com.crt:
	openssl req -x509 -out ./nginx_config/pong.com.crt -keyout ./nginx_config/pong.com.key -newkey rsa:2048 -nodes \
		-sha256 -subj '/CN=pong.com'
	sudo cp ./nginx_config/pong.com.crt /usr/local/share/ca-certificates/
	sudo update-ca-certificates

register_test_domain: /usr/local/share/ca-certificates/pong.com.crt
	@grep -Fxq "127.0.0.1 pong.com" "/etc/hosts" || (echo "127.0.0.1 pong.com" | \
		sudo tee -a "/etc/hosts" > /dev/null)

config_system: register_test_domain
	@grep -Fxq "vm.overcommit_memory=1" "/etc/sysctl.conf" || (echo "vm.overcommit_memory=1" | \
		sudo tee -a "/etc/sysctl.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "* hard data unlimited" "/etc/security/limits.conf" || \
		(echo "* hard data unlimited" | sudo tee -a "/etc/security/limits.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "* soft data unlimited" "/etc/security/limits.conf" || \
		(echo "* soft data unlimited" | sudo tee -a "/etc/security/limits.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "* hard nofile unlimited" "/etc/security/limits.conf" || \
		(echo "* hard nofile unlimited" | sudo tee -a "/etc/security/limits.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "* soft nofile unlimited" "/etc/security/limits.conf" || \
		(echo "* soft nofile unlimited" | sudo tee -a "/etc/security/limits.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "* hard memlock unlimited" "/etc/security/limits.conf" || \
		(echo "* hard memlock unlimited" | sudo tee -a "/etc/security/limits.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "* soft memlock unlimited" "/etc/security/limits.conf" || \
		(echo "* soft memlock unlimited" | sudo tee -a "/etc/security/limits.conf" > /dev/null && echo reboot needed)

all: create_schema config_system

clean:
	@make -C api --no-print-directory clean
	@rm -rf api_sockets

fclean: clean
	@make -C api --no-print-directory fclean

re: fclean
	@make --no-print-directory

pull:
	@git pull

push: fclean
	@git add .
	@git commit
	@git push
