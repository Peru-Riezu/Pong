drop table set_t cascade;
drop table match_actions_t cascade;
drop table match_invite_t cascade;
drop table match_t cascade;
drop table tournament_subscription_t cascade;
drop table tournament_invite_t cascade;
drop table tournament_t cascade;
drop table group_chat_subscription_t cascade;
drop table group_chat_invite_t cascade;
drop table group_chat_message_acknowleged_t cascade;
drop table group_chat_message_t cascade;
drop table group_chat_t cascade;
drop table ban_t cascade;
drop table direct_message_t cascade;
drop table contact_t cascade;
drop table user_t cascade;
drop type player_number cascade;
drop type action_code cascade;

create table user_t
(
	name char(7) primary key, /* stored hashed, locale must have char size of 1 byte */
	password char(44) not null, /* stored hashed */
	deleted_account boolean not null default false,
	session_token char(44) default null,
	session_token_expieres timestamp default null,
	incoming_message_manager_id integer default null, /* id of api worker handeling the incoming messages */
	match_event_manager_id integer default null, /* id of api worker handeling the incoming match events */
	messages_pending boolean default false not null,
	nick_name varchar(30) not null,
	join_date timestamp default now() not null,
	profile_picture bytea default null,
	bio varchar(1024) default null,
	normal_matches_won integer not null default 0,
	normal_matches_lost integer not null default 0,
	normal_matches_drawn integer not null default 0,
	tournament_matches_won integer not null default 0,
	tournament_matches_lost integer not null default 0,
	tournament_matches_drawn integer not null default 0,
	tournaments_won integer not null default 0,
	tournaments_played integer not null default 0
);
insert into user_t (name, password, nick_name, join_date) values
('', '', 'Ancillary message sender', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS')),
('1', '', 'Guest', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS')),
('2', '', 'Local player', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS')),
('3', '', 'AI oponent easy', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS')),
('4', '', 'AI oponent medium', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS')),
('5', '', 'AI oponent hard', to_timestamp('1-01-01 0:0:0', 'YYYY-MM-DD HH24:MI:SS'));

create table contact_t
(
	name char(7) references user_t(name) not null,
	contact_name char(7) references user_t(name) not null,
	primary key (name, contact_name)
);

create table direct_message_t
(
	id bigserial primary key,
	sender char(7) references user_t(name) not null,
	recipient char(7) references user_t(name) not null,
	content text not null,
	sent timestamp not null,
	recived timestamp default null,
	read timestamp default null
);

create table ban_t
(
	issuer char(7) references user_t(name) not null,
	recipient char(7) references user_t(name) not null,
	primary key (issuer, recipient)
);

create table group_chat_t
(
	id bigserial primary key,
	owner_name char(7) references user_t(name) not null,
	name varchar(30)
);

create table group_chat_message_t
(
	id bigserial primary key,
	sender char(7) references user_t(name) not null,
	recipient bigint references group_chat_t(id) not null,
	content text not null,
	sent timestamp not null
);

create table group_chat_message_acknowleged_t
(
	message_id bigint references group_chat_message_t(id) not null,
	recipient char(7) references user_t(name) not null,
	recived timestamp default null,
	read timestamp default null,
	primary key (message_id, recipient)
);

create table group_chat_invite_t
(
	group_chat_id bigint references group_chat_t(id) not null,
	recipient char(7) references user_t(name) not null,
	valid boolean not null default true
);

create table group_chat_subscription_t
(
	subscriber char(7) references user_t(name) not null,
	group_chat_id bigint references group_chat_t(id) not null,
	admin boolean not null default false
);

create table tournament_t
(
	id bigserial primary key,
	api_worker_id integer not null, /* For match-making pourposes, the same api worker must handle any given tournament */
                                    /* So when an api worker recives a request relating to a tournament it's not the */
                                    /* handler of, he will pass the request to the proper worker.*/
	name varchar(30) not null,
	group_chat_id bigint references group_chat_t(id) not null,
	tournament_started boolean not null default false,
	tournament_over boolean not null default false
);

create table tournament_invite_t
(
	tournament_id bigint references tournament_t(id) not null,
	recipient char(7) references user_t(name) not null,
	valid boolean not null default true
);

create table tournament_subscription_t
(
	tournament_id bigint references tournament_t(id),
	group_chat_id bigint references group_chat_t(id),
	can_use_chat boolean not null default true,
	tournament_score integer not null default 0,
	on_match boolean not null default false,
	left_tournament boolean not null default false
);

create table match_t
(
	id bigserial primary key,
	tournament_id bigint references tournament_t(id) default null,
	match_overseer_id integer default null, /* id of api worker overseeing the match */
	player1_name char(7) references user_t(name) not null,
	player2_name char(7) references user_t(name) not null,
	player1_score integer not null default 0,
	player2_score integer not null default 0,
	match_began timestamp not null,
	match_ended timestamp
);

create table match_invite_t
(
	match_id bigint references match_t(id) not null,
	recipient char(7) references user_t(name) not null,
	valid boolean not null default true
);

create type player_number as enum('1', '2');
create type action_code as enum('BALL_LAUCH_PROGRAMMED', 'DOWN_DOWN', 'DOWN_UP', 'UP_DOWN', 'UP_UP', 'VICTORY_CLAIMED');
create table match_actions_t
(
	match_id bigint references match_t(id) not null,
	actor_id player_number not null,
	action action_code not null,
	acknowledged timestamp not null default now(),
	ball_launch_seed integer
);

create table set_t
(
	match_id bigint references match_t(id) not null,
	set_number integer not null,
	duraition interval not null,
	winer player_number
);
