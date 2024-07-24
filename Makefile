# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Filename: Makefile                                                        #
#    Author:   Peru Riezu <riezumunozperu@gmail.com>                           #
#    github:   https://github.com/priezu-m                                     #
#    Licence:  GPLv3                                                           #
#    Created:  2023/09/27 18:57:07                                             #
#    Updated:  2024/07/24 01:15:25                                             #
#                                                                              #
# **************************************************************************** #

#GNU Make 3.81

################################################################################

SHELL :=	bash
USER :=		$(shell echo $$USER)

################################################################################

.DEFAULT_GOAL := all

create_schema:
	@sudo -u pong_role /usr/lib/postgresql/15/bin/postgres "-D" "./db/data/main" "-c" "config_file=./db/config/postgresql.conf" \
		&> /dev/null &
	@sleep 1
	@sudo -u pong_role psql -h /var/run/pong_db -d pongdb -f ./db/create_tables.sql
	@sudo pkill postgres

/usr/local/share/ca-certificates/pong.com.crt:
	@openssl req -x509 -out ./nginx_config/pong.com.crt -keyout ./nginx_config/pong.com.key -newkey rsa:2048 -nodes \
		-sha256 -subj '/CN=pong.com'
	@sudo cp ./nginx_config/pong.com.crt /usr/local/share/ca-certificates/
	@sudo update-ca-certificates

register_test_domain: /usr/local/share/ca-certificates/pong.com.crt
	@grep -Fxq "127.0.0.1 pong.com" "/etc/hosts" || (echo "127.0.0.1 pong.com" | \
		sudo tee -a "/etc/hosts" > /dev/null)

create_run_dir:
	-@sudo mkdir /var/run/pong_db &> /dev/null || true
	-@sudo chown pong_role /var/run/pong_db &> /dev/null || true
	-@sudo -u pong_role mkdir ./db/config/conf.d/ &> /dev/null || true
	-@sudo -u pong_role mkdir ./db/data/main/pg_notify/ &> /dev/null || true
	-@sudo -u pong_role mkdir ./db/data/main/pg_replslot/ &> /dev/null || true
	-@sudo -u pong_role mkdir ./db/data/main/pg_tblspc/ &> /dev/null || true
	-@sudo -u pong_role mkdir ./db/data/main/pg_twophase/ &> /dev/null || true
	-@sudo -u pong_role mkdir ./db/data/main/pg_commit_ts/ &> /dev/null || true
	-@sudo -u pong_role mkdir ./db/data/main/pg_snapshots/ &> /dev/null || true
	-@sudo -u pong_role mkdir -p ./db/data/main/pg_logical/snapshots/ &> /dev/null || true
	-@sudo -u pong_role mkdir -p ./db/data/main/pg_logical/mappings/ &> /dev/null || true

ifeq ($(filter ssl-cert, $(shell groups pong_role)),)
add_user_to_ssl_group:
	@sudo useradd pong_role
	@sudo usermod -a -G ssl-cert pong_role
	@sudo usermod -a -G $(USER) pong_role
	@sudo usermod -a -G pong_role $(USER)
	@echo reboot needed
else
add_user_to_ssl_group:
endif

set_permissions:
	@sudo chown -R pong_role db/data/main
	@sudo -u pong_role chmod 700 db/data/main

config_system: register_test_domain add_user_to_ssl_group create_run_dir set_permissions
	@grep -Fxq "vm.overcommit_memory=1" "/etc/sysctl.conf" || (echo "vm.overcommit_memory=1" | \
		sudo tee -a "/etc/sysctl.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "net.core.wmem_default=4608" "/etc/sysctl.conf" || (echo "net.core.wmem_default=4608" | \
		sudo tee -a "/etc/sysctl.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "net.core.rmem_default=4608" "/etc/sysctl.conf" || (echo "net.core.rmem_default=4608" | \
		sudo tee -a "/etc/sysctl.conf" > /dev/null && echo reboot needed)
	@grep -Fxq "net.core.netdev_max_backlog=1024" "/etc/sysctl.conf" || (echo "net.core.netdev_max_backlog=1024" | \
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

nginx_up:
	@sudo nginx -g 'daemon off; user pong_role;' -c /home/superuser/pong/nginx_config/nginx.conf

api_up:
	@make -C api --no-print-directory
	@./api/api

postgres_up:
	/usr/lib/postgresql/15/bin/postgres "-D" "./db/data/main" "-c" "config_file=./db/config/postgresql.conf"

all: config_system create_schema
	@mkdir api_sockets 2> /dev/null || true

clean:
	@make -C api --no-print-directory clean
	@rm -rf api_sockets/*

fclean: clean
	@make -C api --no-print-directory fclean

re: fclean
	@make --no-print-directory

pull:
	@git pull

push: fclean
	@sudo -u pong_role chmod -R 750 db/data/main
	@git add .
	@git commit
	@git push
	@sudo -u pong_role chmod -R 700 db/data/main
