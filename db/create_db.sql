DROP DATABASE IF EXISTS sp;
CREATE DATABASE sp;

USE sp;

/*

'gameserver' table - Contains the authentication information for game servers. Things like the actual server name, channel and server number should be specified by the game server itself, in run-time, when connecting to the login server.

Columns that must be specified on creation:
- name
- password

*/
DROP TABLE IF EXISTS gameserver;
CREATE TABLE gameserver (
    id                  INT         NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    name                VARCHAR(20) NOT NULL    UNIQUE, -- not the name of the server itself, just a name for authentication
    password            VARCHAR(20) NOT NULL,
    last_online_date    TIMESTAMP   NULL        DEFAULT NULL -- if null, it never went online
);

/*

'user' table - Contains user account information.

Columns that must be specified on creation:
- name
- password
- is_male

Columns that should be also specified on creation, but are not mandatory:
- creation_ip
- last_website_online_date (if registered from website)

The creation of a user should be followed by:
- the creation of a userip with the same user id and creation_ip (see 'userip' table)

*/
DROP TABLE IF EXISTS user;
CREATE TABLE user (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    name                    VARCHAR(20)     NOT NULL    UNIQUE,
    password                VARCHAR(20)     NOT NULL,
    is_male                 BOOL            NOT NULL,
    auth                    TINYINT         NOT NULL    DEFAULT 0,
    is_deleted              BOOL            NOT NULL    DEFAULT 0,
    date_of_last_deletion   TIMESTAMP       NULL        DEFAULT NULL,
    default_character       TINYINT         NOT NULL    DEFAULT 0, -- assuming 0 as unset, 1 as Xyrho
    user_rank               TINYINT         NOT NULL    DEFAULT 0,
    user_rank_record        TINYINT         NOT NULL    DEFAULT 0,
    points                  BIGINT          NOT NULL    DEFAULT 0, -- current amount of points
    points_earned_total     BIGINT          NOT NULL    DEFAULT 0, -- total points earned, not counting any loss of points
    code                    BIGINT          NOT NULL    DEFAULT 0, -- current amount of code
    code_earned_total       BIGINT          NOT NULL    DEFAULT 0, -- total code earned from playing games, selling cards to card shop, and events
    code_spent_total        BIGINT          NOT NULL    DEFAULT 0, -- total code spent on card fusions, buying cards from card shop, and gifting
    code_received_total     BIGINT          NOT NULL    DEFAULT 0, -- total code received from other users
    code_sent_total         BIGINT          NOT NULL    DEFAULT 0, -- total code sent to other users
    cash                    INT             NOT NULL    DEFAULT 0,
    coins                   INT             NOT NULL    DEFAULT 0,
    water_spirits           INT             NOT NULL    DEFAULT 0,
    fire_spirits            INT             NOT NULL    DEFAULT 0,
    earth_spirits           INT             NOT NULL    DEFAULT 0,
    wind_spirits            INT             NOT NULL    DEFAULT 0,
    spirits_earned_total    INT             NOT NULL    DEFAULT 0,
    spirits_spent_total     INT             NOT NULL    DEFAULT 0,
    spirits_received_total  INT             NOT NULL    DEFAULT 0,
    spirits_sent_total      INT             NOT NULL    DEFAULT 0,
    card_slots              SMALLINT        NOT NULL    DEFAULT 0,
    wins                    INT             NOT NULL    DEFAULT 0,
    losses                  INT             NOT NULL    DEFAULT 0, -- including quits
    draws                   INT             NOT NULL    DEFAULT 0,
    quits                   INT             NOT NULL    DEFAULT 0,
    kos                     INT             NOT NULL    DEFAULT 0,
    kos_total               INT             NOT NULL    DEFAULT 0, -- including KOs in modes that don't count for KO record
    downs                   INT             NOT NULL    DEFAULT 0,
    downs_total             INT             NOT NULL    DEFAULT 0, -- including downs in modes that don't count for downs record
    scroll1                 SMALLINT        NOT NULL    DEFAULT 0, -- scroll ID in slot 1 (an ID of 0 means that the slot is empty)
    scroll2                 SMALLINT        NOT NULL    DEFAULT 0,
    scroll3                 SMALLINT        NOT NULL    DEFAULT 0,
    mission_clear           INT             NOT NULL    DEFAULT 0,
    mission_clear_record    INT             NOT NULL    DEFAULT 0, -- ignoring the weekly drop in the mission level
    creation_date           TIMESTAMP       NOT NULL    DEFAULT NOW(),
    last_loginserver_online_date TIMESTAMP  NULL        DEFAULT NULL,
    last_gameserver_online_date TIMESTAMP   NULL        DEFAULT NULL,
    last_website_online_date TIMESTAMP      NULL        DEFAULT NULL,
    first_login_date        TIMESTAMP       NULL        DEFAULT NULL, -- first login to the login server
    last_login_date         TIMESTAMP       NULL        DEFAULT NULL, -- last login to the login server
    connected_time_total    INT             NOT NULL    DEFAULT 0, -- total time connected to all game servers (in seconds)
    connected_time_today    INT             NOT NULL    DEFAULT 0,
    playtime_total          INT             NOT NULL    DEFAULT 0, -- total playtime in all game servers (in seconds)
    playtime_today          INT             NOT NULL    DEFAULT 0,
    show_up_days_total      INT             NOT NULL    DEFAULT 0, -- total amount of days in which the user has appeared in anywhere
    game_show_up_days_total INT             NOT NULL    DEFAULT 0, -- total amount of days in which the user has appeared in the game
    creation_ip             VARCHAR(100)    NULL        DEFAULT NULL -- if null, it could have been created by us or something
);

/*

This trigger updates the user's show_up_days_total and game_show_up_days_total automatically when the last_*_online_date are updated.
If a user stays connected for several days straight, remember to update the last_*_online_date at least once per day!

*/
delimiter //
CREATE TRIGGER user_upd_trg AFTER UPDATE ON user
FOR EACH ROW BEGIN

    IF DATE(NEW.last_loginserver_online_date) <> DATE(OLD.last_loginserver_online_date) OR
       DATE(NEW.last_gameserver_online_date) <> DATE(OLD.last_gameserver_online_date) THEN
        UPDATE user SET game_show_up_days_total = game_show_up_days_total + 1 WHERE id = NEW.id;
    END IF;
    
    IF DATE(NEW.last_website_online_date) <> DATE(OLD.last_website_online_date) OR
       NEW.game_show_up_days_total > OLD.game_show_up_days_total THEN
        UPDATE user SET show_up_days_total = show_up_days_total + 1 WHERE id = NEW.id;
    END IF;
    
END //
delimiter ;

/*

'userip' table - Represents an association between a user and multiple IPs.

Columns that must be specified on creation:
- user_id
- ip

*/
DROP TABLE IF EXISTS userip;
CREATE TABLE userip (
    user_id                 INT             NOT NULL,
    ip                      VARCHAR(100)    NOT NULL,
    last_show_up_date       TIMESTAMP       NOT NULL    DEFAULT NOW(),
    show_up_days_total      INT             NOT NULL    DEFAULT 1,
    PRIMARY KEY (user_id, ip),
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE
);

/*

This trigger updates the userip's show_up_days_total and game_show_up_days_total automatically when the last_show_up_date is updated.
If a user stays connected for several days straight, remember to update the last_show_up_date at least once per day!

*/
delimiter //
CREATE TRIGGER userip_upd_trg AFTER UPDATE ON userip
FOR EACH ROW BEGIN

    IF DATE(NEW.last_show_up_date) <> DATE(OLD.last_show_up_date) THEN
        UPDATE userip SET show_up_days_total = show_up_days_total + 1 WHERE user_id = NEW.user_id AND ip = NEW.ip;
    END IF;
    
END //
delimiter ;

/*

'friend' table - Represents an association between a user and multiple users (his/her friends).

Columns that must be specified on creation:
- user_id
- friend_id

*/
DROP TABLE IF EXISTS friend;
CREATE TABLE friend (
    user_id                 INT             NOT NULL,
    friend_id               INT             NOT NULL,
    add_date                TIMESTAMP       NOT NULL    DEFAULT NOW(),
    PRIMARY KEY (user_id, friend_id),
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE,
    FOREIGN KEY (friend_id) REFERENCES user(id) ON DELETE CASCADE
);

/*

'userban' table - Represents a ban of a user, including expired bans. A user can be banned multiple times, so there may be multiple entries with the same user id.

Columns that must be specified on creation:
- user_id

*/
DROP TABLE IF EXISTS userban;
CREATE TABLE userban (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    user_id                 INT             NOT NULL,
    ban_date                TIMESTAMP       NOT NULL    DEFAULT NOW(),
    expiration_date         TIMESTAMP       NULL        DEFAULT NULL, -- null for permanent ban
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE
);

/*

'ipban' table - Represents a ban of an IP, including expired bans. An IP can be banned multiple times, so there may be multiple entries with the same IP.

Columns that must be specified on creation:
- ip

*/
DROP TABLE IF EXISTS ipban;
CREATE TABLE ipban (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    ip                      VARCHAR(100)    NOT NULL,
    ban_date                TIMESTAMP       NOT NULL    DEFAULT NOW(),
    expiration_date         TIMESTAMP       NULL        DEFAULT NULL -- null for permanent ban
);

/*

'card' table - Contains card information.

Columns that must be specified on creation:
- card_type
- level_or_remaining_uses
- skills
- slot

Columns that should be also specified on creation, but are not mandatory:
- owner_id (if the card is to be added to some user's inventory)
- first_owner_id (same as owner_id)
- force_expiration_date (if the card is black type)

*/
DROP TABLE IF EXISTS card;
CREATE TABLE card (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    is_disposed             BOOL            NOT NULL    DEFAULT 0, -- sold to card shop, or deleted in some other way
    date_of_disposal        TIMESTAMP       NULL        DEFAULT NULL,
    creation_date           TIMESTAMP       NOT NULL    DEFAULT NOW(),
    owner_id                INT             NULL        DEFAULT NULL, -- if the card is disposed, this contains the id of the last owner (i.e. who deleted it); is null when the card is being gifted or is in US2
    first_owner_id          INT             NULL        DEFAULT NULL,
    card_type               INT             NOT NULL,
    force_expiration_date   TIMESTAMP       NULL        DEFAULT NULL, -- if null, it never expires (eg. pets, avatar equipment)
    level_or_remaining_uses INT             NULL, -- null for pets, avatar equipment, and most of the silver cards
    skills                  INT             NULL, -- null for silver cards, 0 for black or gold cards with no skills
    slot                    SMALLINT        NOT NULL,
    FOREIGN KEY (owner_id) REFERENCES user(id) ON DELETE CASCADE,
    FOREIGN KEY (first_owner_id) REFERENCES user(id) ON DELETE SET NULL
);

/*

'transfer' table - Contains the information about transfers of cards/code/spirits done between users (trades and gifts).

Columns that must be specified on creation:
- sender_id
- receiver_id
- transfer_method

*/
DROP TABLE IF EXISTS transfer;
CREATE TABLE transfer (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    transfer_date           TIMESTAMP       NOT NULL    DEFAULT NOW(),
    sender_id               INT             NOT NULL,
    receiver_id             INT             NOT NULL,
    transfer_method         TINYINT         NOT NULL, -- could be 0 for trade and 1 for gift, for example
    FOREIGN KEY (sender_id) REFERENCES user(id) ON DELETE CASCADE,
    FOREIGN KEY (receiver_id) REFERENCES user(id) ON DELETE CASCADE
);

/*

'tradeobject' table - Represents something that was included in a transfer between 2 users. A transfer has multiple tradeobjects.

Columns that must be specified on creation:
- transfer_id
- sender_id
- item_type
- item_value (if not card)
- card_id (if card)

*/
DROP TABLE IF EXISTS tradeobject;
CREATE TABLE tradeobject (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    transfer_id             INT             NOT NULL,
    sender_id               INT             NOT NULL,
    item_type               TINYINT         NOT NULL, -- could be 0 for card, 1 for code, 2 for spirits, or something like that
    item_value              BIGINT          NULL        DEFAULT NULL, -- the meaning of this depends on the item_type; it can be null if item_type = card
    card_id                 INT             NULL        DEFAULT NULL, -- only matters if item_type = card
    FOREIGN KEY (transfer_id) REFERENCES transfer(id) ON DELETE CASCADE,
    FOREIGN KEY (sender_id) REFERENCES user(id) ON DELETE CASCADE,
    FOREIGN KEY (card_id) REFERENCES card(id) ON DELETE CASCADE
);

/*

'gift' table - Represents a gift.

Columns that must be specified on creation:
- sender_name (null for returned gifts)
- receiver_id
- gift_type
- gift_item_type
- gift_item_value (if not card)
- card_id (if card)

Columns that should be also specified on creation, but are not mandatory:
- sender_id (if it's a normal gift, not a returned gift)
- expiration_date

*/
DROP TABLE IF EXISTS gift;
CREATE TABLE gift (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    sender_id               INT             NULL,
    sender_name             VARCHAR(20)     NULL, -- in case the sender gets deleted, at least the receiver can see the name of the sender. a null value here could be useful for returned gifts (eg. a US2 expired item)
    receiver_id             INT             NOT NULL, -- remember to return the item to the sender before deleting the receiver...
    send_date               TIMESTAMP       NOT NULL    DEFAULT NOW(),
    expiration_date         TIMESTAMP       NULL        DEFAULT NULL, -- null for no expiration (not recommended)
    gift_type               TINYINT         NOT NULL, -- could be 0 for normal gift, 1 for returned gift, ...
    gift_item_type          TINYINT         NOT NULL, -- could be 0 for card, 1 for code, 2 for spirits, or something like that
    gift_item_value         BIGINT          NULL        DEFAULT NULL, -- the meaning of this depends on the gift_item_type; it can be null if gift_item_type = card
    card_id                 INT             NULL        DEFAULT NULL, -- only matters if gift_item_type = card
    FOREIGN KEY (sender_id) REFERENCES user(id) ON DELETE SET NULL,
    FOREIGN KEY (receiver_id) REFERENCES user(id) ON DELETE CASCADE,
    FOREIGN KEY (card_id) REFERENCES card(id) ON DELETE CASCADE
);

/*

'memo' table - Represents a memo.

Columns that must be specified on creation:
- sender_name (null for guild announcements and such)
- receiver_id
- memo_type
- gift_value

Columns that should be also specified on creation, but are not mandatory:
- sender_id (if it's a normal memo)
- expiration_date

*/
DROP TABLE IF EXISTS memo;
CREATE TABLE memo (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    sender_id               INT             NULL,
    sender_name             VARCHAR(20)     NULL, -- in case the sender gets deleted, at least the receiver can see the name of the sender. a null value here could be useful for maybe guild announcements
    receiver_id             INT             NOT NULL,
    send_date               TIMESTAMP       NOT NULL    DEFAULT NOW(),
    expiration_date         TIMESTAMP       NULL        DEFAULT NULL, -- null for no expiration (not recommended)
    memo_type               TINYINT         NOT NULL, -- could be 0 for normal memo, 1 for guild announcement, ...
    message                 VARCHAR(255)    NOT NULL,
    FOREIGN KEY (sender_id) REFERENCES user(id) ON DELETE SET NULL,
    FOREIGN KEY (receiver_id) REFERENCES user(id) ON DELETE CASCADE
);

/*

'us2item' table - Represents an item listed in User Shop II.

Columns that must be specified on creation:
- seller_id
- seller_name
- price
- item_type
- item_value (if not card)
- card_id (if card)

Columns that should be also specified on creation, but are not mandatory:
- expiration_date

*/
DROP TABLE IF EXISTS us2item;
CREATE TABLE us2item (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    seller_id               INT             NULL,
    seller_name             VARCHAR(20)     NULL, -- in case the seller gets deleted, at least the item can stay on US2
    insertion_date          TIMESTAMP       NOT NULL    DEFAULT NOW(),
    expiration_date         TIMESTAMP       NULL        DEFAULT NULL, -- null for no expiration (not recommended)
    price                   BIGINT          NOT NULL,
    item_type               TINYINT         NOT NULL, -- could be 0 for card, 1 for spirits, or something like that
    item_value              BIGINT          NULL        DEFAULT NULL, -- the meaning of this depends on the item_type; it can be null if item_type = card
    card_id                 INT             NULL        DEFAULT NULL, -- only matters if item_type = card
    FOREIGN KEY (seller_id) REFERENCES user(id) ON DELETE SET NULL,
    FOREIGN KEY (card_id) REFERENCES card(id) ON DELETE CASCADE
);

/*

'guild' table - Contains guild information.

Columns that must be specified on creation:
- name
- leader_id

*/
DROP TABLE IF EXISTS guild;
CREATE TABLE guild (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    name                    VARCHAR(20)     NULL,
    creation_date           TIMESTAMP       NOT NULL    DEFAULT NOW(),
    leader_id               INT             NOT NULL,
    member_slots            SMALLINT        NULL        DEFAULT NULL, -- let's use null for infinite slots
    mark                    TINYBLOB        NULL        DEFAULT NULL,
    banner_file_name        VARCHAR(255)    NULL        DEFAULT NULL,
    description             VARCHAR(1000)   NULL        DEFAULT '',
    announcement            VARCHAR(1000)   NULL        DEFAULT '',
    FOREIGN KEY (leader_id) REFERENCES user(id) ON DELETE CASCADE
);

/*

'guildpoints' table - Each guild has a certain amount of guild points in a given game server.

Columns that must be specified on creation:
- guild_id
- gameserver_id

*/
DROP TABLE IF EXISTS guildpoints;
CREATE TABLE guildpoints (
    guild_id                INT             NOT NULL,
    gameserver_id           INT             NOT NULL,
    points                  BIGINT          NOT NULL    DEFAULT 0,
    PRIMARY KEY (guild_id, gameserver_id),
    FOREIGN KEY (guild_id) REFERENCES guild(id) ON DELETE CASCADE,
    FOREIGN KEY (gameserver_id) REFERENCES gameserver(id) ON DELETE CASCADE
);

/*

'guildmember' table - Represents an association between a guild and multiple users (guild members).

Columns that must be specified on creation:
- guild_id
- user_id

*/
DROP TABLE IF EXISTS guildmember;
CREATE TABLE guildmember (
    guild_id                INT             NOT NULL,
    user_id                 INT             NOT NULL,
    join_date               TIMESTAMP       NOT NULL    DEFAULT NOW(),
    guild_title             VARCHAR(20)     NOT NULL    DEFAULT '',
    PRIMARY KEY (guild_id, user_id),
    FOREIGN KEY (guild_id) REFERENCES guild(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE
);

/*

'guildapplication' table - Represents an association between multiple guilds and multiple users. A user can apply to multiple guilds, and a guild can receive multiple applications.

Columns that must be specified on creation:
- guild_id
- user_id

*/
DROP TABLE IF EXISTS guildapplication;
CREATE TABLE guildapplication (
    guild_id                INT             NOT NULL,
    user_id                 INT             NOT NULL,
    application_date        TIMESTAMP       NOT NULL    DEFAULT NOW(),
    PRIMARY KEY (guild_id, user_id),
    FOREIGN KEY (guild_id) REFERENCES guild(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE
);

/*

'cashspend' table - Contains information on how and when users spend cash.

Columns that must be specified on creation:
- user_id
- cash_amount
- spend_type
- card_type
- card_id

*/
DROP TABLE IF EXISTS cashspend;
CREATE TABLE cashspend (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    user_id                 INT             NULL,
    spend_date              TIMESTAMP       NOT NULL    DEFAULT NOW(),
    cash_amount             INT             NOT NULL,
    spend_type              TINYINT         NOT NULL, -- could be 0 for card, 1 for force recharge, ...
    card_type               INT             NOT NULL,
    card_force              INT             NULL, -- null if irrelevant
    card_level_or_uses      INT             NULL, -- null if irrelevant
    card_id                 INT             NULL,
    force_charged           INT             NULL, -- null if irrelevant
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE,
    FOREIGN KEY (card_id) REFERENCES card(id) ON DELETE SET NULL
);

/*

'cashcharge' table - Contains information on how and when users charge cash.

Columns that must be specified on creation:
- user_id
- charge_date
- charge_method
- charged_amount

*/
DROP TABLE IF EXISTS cashcharge;
CREATE TABLE cashcharge (
    id                      INT             NOT NULL    PRIMARY KEY AUTO_INCREMENT,
    user_id                 INT             NULL,
    charge_date             TIMESTAMP       NOT NULL    DEFAULT NOW(),
    charge_method           TINYINT         NOT NULL, -- could be 0 for donation, 1 for... whatever
    charged_amount          INT             NOT NULL,
    FOREIGN KEY (user_id) REFERENCES user(id) ON DELETE CASCADE
);



