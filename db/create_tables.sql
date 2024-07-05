drop table oponent_actions_t;
drop table match_t;
drop table tournament_subscription_t;
drop table tournament_t;
drop table group_chat_subscription_t;
drop table group_chat_t;
drop table ban_t;
drop table message_t;
drop table user_t;
drop type player_number;
drop type action_code;

create table user_t
(
	name char(7) primary key, /* stored hashed, locale must have char size of 1 byte */
	password char(32) not null, /* stored hashed */
	nick_name varchar(30) not null,
	join_date timestamp not null,
	email varchar(320) not null,
	profile_picture bytea default null,
	bio varchar(1024) default null,
	messages_pending boolean default false not null,
	email_verified boolean default false not null,
	session_token char(256) default null,
	session_token_expieres timestamp default null
);
insert into user_t (name, password, nick_name, join_date, email) values
('', '', 'ancillary message sender', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS'), ''),
('1', '', 'Guest', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS'), ''),
('2', '', 'AI oponent easy', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS'), ''),
('3', '', 'AI oponent medium', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS'), ''),
('4', '', 'AI oponent hard', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS'), '');

create table message_t
(
	sender char(7) references user_t(name) not null,
	recipient char(7) references user_t(name) not null,
	content text not null
);

create table ban_t
(
	issuer char(7) references user_t(name) not null,
	recipient char(7) references user_t(name) not null
);

create table group_chat_t
(
	id bigserial primary key,
	group_name_id varchar(30)
);

create table group_chat_subscription_t
(
	subscriber char(7) references user_t(name) not null,
	group_chat_id bigint references group_chat_t(id) not null,
	owner boolean not null default false,
	admin boolean not null default false
);

create table tournament_t
(
	id bigserial primary key,
	api_worker_id integer not null, /* For match-making pourposes, the same api worker must handle any given tournament. */
                                    /* So when an api worker recives a request relating to a tournament it's not the handler of, */
                                    /* he will pass the request to the proper worker.*/
	name varchar(30) not null,
	group_chat_id bigint references group_chat_t(id) not null
);

create table tournament_subscription_t
(
	tournament_id bigint references tournament_t(id),
	group_chat_id bigint references group_chat_t(id),
	tournament_score integer not null default 0,
	on_match boolean not null default false
);

create table match_t
(
	id bigserial primary key,
	tournament_id bigint references tournament_t(id) default null,
	player1_name char(7) references user_t(name) not null,
	player2_name char(7) references user_t(name) not null,
	player1_score integer not null default 0,
	player2_score integer not null default 0,
	game_began timestamp not null,
	game_ended timestamp
);

create type player_number as enum('1', '2');
create type action_code as enum('BALL_LAUCH_PROGRAMMED', 'DOWN_DOWN', 'DOWN_UP', 'UP_DOWN', 'UP_UP', 'VICTORY_CLAIMED');
create table oponent_actions_t
(
	match_id bigint references match_t(id) not null,
	actor_id player_number not null,
	action action_code not null,
	acknowledged timestamp not null default now(),
	ball_launch_seed integer
);
